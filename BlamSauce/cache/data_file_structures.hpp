#pragma once

#include <precompile.h>
#include "../cseries/base.h"
#include "data_file.hpp"
#include "../cseries/errors.h"

namespace Yelo {
	namespace Cache {
		struct s_data_file_header {
			signed long type; // Enums::data_file_reference_type
			// when building or updating a data file, acts as the write cursor for new items
			long     file_names_offset;
			long     file_index_table_offset;
			long     tag_count;
		}; static_assert(sizeof(s_data_file_header) == 0x10);

		struct s_data_file_item {
			long name_offset;
			long size;
			long data_offset;
		}; static_assert(sizeof(s_data_file_item) == 0xC);


		struct index_tbl {
			s_data_file_item *address;
			long            count;
		};

		struct data_file_info {
			long total_size;
			long used_size;
			char  *address;

			byte *AsByteBuffer() { return reinterpret_cast<byte *>(address); }

			const byte *AsByteBuffer() const { return reinterpret_cast<const byte *>(address); }
		};

		struct count_w_size {
			long count;
			long size;
		};

		struct s_data_file {
			s_data_file_header header;
			index_tbl          file_index_table;
			data_file_info     file_names;

			bool writable;
			unsigned char : 8; unsigned short : 16;
			count_w_size item_hits;
			count_w_size item_adds_or_misses;
			const char *       name;
			HANDLE       file_handle;

		private:
			void FreeResources() {
				if (file_names.address != nullptr) {
					YELO_DELETE_ARRAY(file_names.address);
				}

				if (file_index_table.address != nullptr) {
					YELO_DELETE_ARRAY(file_index_table.address);
				}
			}

			bool Read(uint position, void *buffer, size_t buffer_size) {
				DWORD bytes_read;

				OVERLAPPED overlapped = {};
				overlapped.Offset = position;
				if (ReadFile(file_handle, buffer, buffer_size, &bytes_read, &overlapped) != FALSE) {
					return bytes_read == buffer_size;
				} else if (GetLastError() == ERROR_IO_PENDING &&
							  GetOverlappedResult(file_handle, &overlapped, &bytes_read, TRUE) != FALSE) {
					return bytes_read == buffer_size;
				}

				return false;
			}

			bool ReadHeader(Enums::data_file_reference_type expected_type) {
				if (!Read(0, &header, sizeof(header))) {
					DWORD last_error = GetLastError();
					//printf_s("Failed to read data file header %s\n", name);
					return false;
				}

				if (header.type != expected_type) {
					memset(&header, 0, sizeof(header));
					//printf_s("Invalid data file id in data file %s\n", name);
					return false;
				}

				return true;
			}

			bool ReadFileNames() {
				DWORD buffer_size = header.file_index_table_offset - header.file_names_offset;
				file_names.address = YELO_NEW_ARRAY(char, buffer_size);

				if (!Read(header.file_names_offset, file_names.address, buffer_size)) {
					DWORD last_error = GetLastError();
					// printf_s("Invalid format in data file %s\n", name);
					return false;
				}

				file_names.total_size = file_names.used_size = buffer_size;

				return true;
			}

			bool ReadFileIndexTable() {
				DWORD buffer_size = sizeof(s_data_file_item) * header.tag_count;
				file_index_table.address = YELO_NEW_ARRAY(s_data_file_item, header.tag_count);

				if (!Read(header.file_index_table_offset, file_index_table.address, buffer_size)) {
					DWORD last_error = GetLastError();
					//printf_s("Invalid format in data file %s\n", name);
					return false;
				}

				file_index_table.count = header.tag_count;

				return true;
			}

		public:

			// full_path should NOT be allocated on the stack, as it will become the value of 'name'
			// TODO: OpenForEdit and OpenForRead
			bool Open(Yelo::Enums::data_file_reference_type data_file, bool store_resources, const char *  full_path) {
				memset(this, 0, sizeof(*this));
				this->name     = full_path;
				this->writable = store_resources;

				DWORD file_access = GENERIC_READ;

				if (store_resources) {
					file_access |= GENERIC_WRITE;
				}

				DWORD file_share_mode = PLATFORM_ENGINE_VALUE(FILE_SHARE_READ, 0);

				DWORD file_flags = FILE_ATTRIBUTE_NORMAL;
				file_flags |= FILE_FLAG_SEQUENTIAL_SCAN;
				file_flags |= FILE_FLAG_OVERLAPPED;

				this->file_handle = CreateFileA(full_path, file_access, file_share_mode, nullptr, OPEN_ALWAYS, file_flags, nullptr);

				if (file_handle != INVALID_HANDLE_VALUE &&
					 ReadHeader(data_file) && ReadFileNames() && ReadFileIndexTable()) {
					SetFilePointer(file_handle, header.file_names_offset, nullptr, FILE_BEGIN);
					return true;
				}

				FreeResources();
				if (store_resources) {
					header.type              = data_file;
					header.file_names_offset = sizeof(header);
					DWORD bytes_written;
					WriteFile(file_handle, &header, sizeof(header), &bytes_written, nullptr);
				}

				DWORD last_error = GetLastError();
				printf_s("### FAILED TO OPEN DATA-CACHE FILE: %s.\n\n", this->name);
				return false;
			}

			bool Close() {
				CloseHandle(file_handle);
				FreeResources();
				//TODO: CloseAfterUpdate instead of ifdefs.
				// #if PLATFORM_TYPE == PLATFORM_TOOL
				float item_hits_size = CAST(float, item_hits.size);
				if (item_hits.size == 0)
					item_hits_size += 4.2949673e9f;

				//printf_s("Cache pack file %s hits: %d for %3.2fM\n", name, item_hits.count, item_hits_size * 9.5367432e-7f);

				float item_adds_or_misses_size = CAST(float, item_hits.size);
				if (item_adds_or_misses.size == 0) {
					item_adds_or_misses_size += 4.2949673e9f;
				}

				//printf_s("Cache pack file %s adds/misses: %d for %3.2fM\n", name, item_adds_or_misses.count, item_adds_or_misses_size * 9.5367432e-7f);
				// #endif

				memset(&header, 0, sizeof(header));
				file_handle = INVALID_HANDLE_VALUE; // engine doesn't do this
				return true;
			}

			bool GetItemDataInfo(long item_index, long &out_data_offset, long &out_data_size) const {
				if (item_index < 0 || item_index >= file_index_table.count)
					return false;

				s_data_file_item *item = &file_index_table.address[item_index];
				out_data_offset = item->data_offset;
				out_data_size   = item->size;

				return true;
			}

			bool ReadItemData(uint position, void *buffer, size_t buffer_size) {
				assert(file_handle != INVALID_HANDLE_VALUE);

				return Read(position, buffer, buffer_size);
			}

			// #if PLATFORM_IS_EDITOR && PLATFORM_TYPE == PLATFORM_TOOL
		private:
			long AddItemName(const char *  item_name) {
				assert(item_name);
				assert(writable);

				size_t item_name_size = strlen(item_name) + 1;

				// name will begin at the end of the current buffer
				long name_offset    = file_names.used_size;
				long new_names_size = file_names.used_size + CAST(long, item_name_size);
				if (new_names_size >= file_names.total_size) {
					// double the names buffer size
					file_names.total_size += file_names.total_size;
					file_names.address = YELO_RENEW_ARRAY(char, file_names.address, file_names.total_size);
				}

				memcpy(file_names.AsByteBuffer() + file_names.used_size,
						 item_name, item_name_size);
				file_names.used_size += item_name_size;

				return name_offset;
			}

			long AddNewItem(const char *  item_name) {
				assert(item_name);
				assert(writable);

				if (header.tag_count >= file_index_table.count) {
					// engine reserves an additional 16 items
					file_index_table.count += 16;
					file_index_table.address = YELO_RENEW_ARRAY(s_data_file_item, file_index_table.address, file_index_table.count);
				}

				long item_index = header.tag_count++;
				auto  *item      = &file_index_table.address[item_index];
				item->name_offset = AddItemName(item_name);

				return item_index;
			}

			long GetItemIndex(const char *  item_name) const {
				assert(item_name);

				for (int x = 0; x < header.tag_count; x++) {
					long   name_offset = file_index_table.address[x].name_offset;
					const char *  name        = reinterpret_cast<const char * >(file_names.AsByteBuffer() + name_offset);

					if (!_stricmp(name, item_name))
						return x;
				}

				return NONE;
			}

		public:
			long AddItem(const char *  item_name, void *item_buffer, long item_buffer_size) {
				assert(item_name && item_buffer); // NOTE: engine doesn't verify buffer pointer

				long item_index = GetItemIndex(item_name);
				if (item_index == NONE) {
					if (writable) {
						item_index = AddNewItem(item_name);
						auto *item = &file_index_table.address[item_index];
						item->size        = item_buffer_size;
						item->data_offset = header.file_names_offset;

						DWORD num_bytes_written;
						WriteFile(file_handle, item_buffer, item_buffer_size, &num_bytes_written, nullptr);
						header.file_names_offset += item_buffer_size;
					}
				} else if (file_index_table.address[item_index].size == item_buffer_size) {
					item_hits.count++;
					item_hits.size += item_buffer_size;
				} else {
					YELO_ERROR_FAILURE("%s: Tried to add item %s with different size (%d) than expected (%d).", name, item_name, item_buffer_size, file_index_table.address[item_index].size);
					item_index = NONE;
				}

				item_adds_or_misses.count++;
				item_adds_or_misses.size += item_buffer_size;

				return item_index;
			}

			long GetItemDataOffset(long item_index) {
				if (item_index < 0 || item_index >= header.tag_count) {
					return NONE;
				}

				return file_index_table.address[item_index].data_offset;
			}

			static void DeleteForCopy(const char *  file) {
				BOOL delete_result = DeleteFileA((LPCSTR) file);
				if (delete_result == ERROR_ACCESS_DENIED)
					printf_s("Could not delete %s for copy\n", file);
			}

			void PreprocessForSave() {
				SetFilePointer(this->file_handle, this->header.file_names_offset, nullptr, FILE_BEGIN);
				SetEndOfFile(this->file_handle);

				// data_file_open does this before it returns, so do the same
				SetFilePointer(this->file_handle, this->header.file_names_offset, nullptr, FILE_BEGIN);
			}

			void Save() {
				SetFilePointer(this->file_handle, 0, nullptr, FILE_END);

				this->header.file_names_offset = SetFilePointer(this->file_handle, 0, nullptr, FILE_CURRENT);
				DWORD bytes_written;
				// Write the file names
				WriteFile(this->file_handle, this->file_names.address, this->file_names.used_size, &bytes_written, nullptr);

				// Write the file index table
				this->header.file_index_table_offset = SetFilePointer(this->file_handle, 0, nullptr, FILE_CURRENT);

				WriteFile(this->file_handle, this->file_index_table.address, this->file_index_table.count * sizeof(s_data_file_item), &bytes_written, nullptr);

				// Go back to the start and write the new header
				SetFilePointer(this->file_handle, 0, nullptr, FILE_BEGIN);

				WriteFile(this->file_handle, &this->header, sizeof(this->header), &bytes_written, nullptr);
			}
		};

		static_assert(sizeof(s_data_file) == 0x40);

		// build_cache_file_globals (tools) and cache_file_globals (runtime) share the same ordering of the s_data_file instances, so I wrap them in this fake struct
		struct s_data_file_globals {
			Cache::s_data_file sounds;
			Cache::s_data_file locale;
			Cache::s_data_file bitmaps;

			s_data_file &Get(Yelo::Enums::data_file_reference_type data_file);

		};

		static_assert(sizeof(s_data_file_globals) == 0xC0);
	};
};
