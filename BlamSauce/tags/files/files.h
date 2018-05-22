/*
	Yelo: Open Sauce SDK
		Halo 1 (Editing Kit) Edition

	See license\OpenSauce\Halo1_CheApe for specific license information
*/
#pragma once

namespace Yelo {
	namespace Enums {
		enum {
			k_maximum_filename_length = 255, // MAXIMUM_FILENAME_LENGTH
		};

		enum file_reference_location : short {
			_file_reference_location_none                 = CAST(short, NONE),
			_file_reference_location_application_relative = 0, // _file_reference_application_relative
			_file_reference_location_tags,
			_file_reference_location_absolute, // _file_reference_absolute

			k_number_of_file_reference_locations
		};
	};

	namespace Flags {
		enum file_reference_flags : word_flags {
			_name_directory_bit,
			_name_parent_directory_bit,
			_name_file_bit,
			_name_extension_bit,

			k_number_of_name_flags, // NUMBER_OF_REFERENCE_INFO_FLAGS

			_name_full_path_flags = FLAG(_name_directory_bit) | FLAG(_name_file_bit) | FLAG(_name_extension_bit)
		};

		enum file_permission_flags : long_flags {
			_permission_read_bit,
			_permission_write_bit,
			_permission_append_bit,
		};
	};

	struct s_file_reference {
		enum { k_signature = 'filo' };

		tag                            signature;
		Flags::file_reference_flags    flags;
		Enums::file_reference_location location;
		char                           file_name[Enums::k_maximum_filename_length + 1];
		HANDLE                         handle;

		void Verify() const {
			YELO_ASSERT(signature == k_signature);
			YELO_ASSERT(VALID_FLAGS(flags, Flags::k_number_of_name_flags));
			YELO_ASSERT(location >= NONE && location < Enums::k_number_of_file_reference_locations);
		}

		static int __cdecl CompareProc(long_flags name_flags, const s_file_reference *lhs, const s_file_reference *rhs) {
			char lhs_name[Enums::k_maximum_filename_length + 1];
			char rhs_name[Enums::k_maximum_filename_length + 1];

			blam::file_reference_get_name(*lhs, name_flags, lhs_name);
			blam::file_reference_get_name(*rhs, name_flags, rhs_name);

			return _stricmp(lhs_name, rhs_name);
		}
	};

	static_assert(sizeof(s_file_reference) == 0x10C);

	namespace blam {
		void __cdecl file_reference_create(s_file_reference &reference, long_enum location = Enums::_file_reference_location_tags) {
			char buffer[Enums::k_maximum_filename_length + 1];
			int  result = _snprintf_s(buffer, Enums::k_maximum_filename_length, "%s%s%s.%s", directory,
											  !is_null_or_empty(directory) ? "\\" : "",
											  name, ext);

			file_reference_create(reference, location);
			if (result > 0)
				file_reference_set_name(reference, buffer);
			else {
				YELO_WARN("file_reference_create failed: %d; hint: @%p %s.%s", result,
							 _ReturnAddress(), name, ext);
			}

			return reference;
		}

		template <size_t k_buffer_size = 1024, bool k_set_eof = true>
		// defaults are based on engine code
		static void file_printf_internal(s_file_reference &reference, cstring format, va_list argptr) {
			char buffer[k_buffer_size];
			int  result = vsprintf_s(buffer, format, argptr);

			// NOTE: engine doesn't do this
			if (result < 0) {
				file_error(__FUNCTION__, reference);
				return;
			}

			size_t buffer_length = strlen(buffer);
			file_write(reference, buffer_length, buffer);

			if (k_set_eof) {
				uint32 position = file_get_position(reference);
				file_set_eof(reference, position);
			}
		}

		void file_printf(s_file_reference &reference, cstring format, ...) {
			if (format == nullptr)
				return;

			va_list argptr;
			va_start(argptr, format);
			file_printf_internal(reference, format, argptr);
			va_end(argptr);
		}

		s_file_reference &__cdecl file_reference_add_directory(s_file_reference &reference, cstring directory);

		s_file_reference &__cdecl file_reference_set_name(s_file_reference &reference, cstring name);

		char *__cdecl file_reference_get_name(const s_file_reference &reference, long_flags flags, __out char name[Enums::k_maximum_filename_length + 1]);

		s_file_reference &file_reference_create(s_file_reference &reference, cstring directory, cstring name, cstring ext,
															 long_enum location = Enums::_file_reference_location_tags);

		s_file_reference &file_reference_create_from_path(s_file_reference &reference, cstring path, bool is_directory = false) {
			file_reference_create(reference, Enums::_file_reference_location_none);

			if (is_directory)
				file_reference_add_directory(reference, path);
			else
				file_reference_set_name(reference, path);

			return reference;
		}

		short __cdecl find_files(long_flags flags, const s_file_reference &directory, long maximum_count, s_file_reference references[]);

		template <size_t _SizeOfArray>
		short find_files(long_flags flags, const s_file_reference &directory, s_file_reference (&references)[_SizeOfArray]) {
			return find_files(flags, directory, _SizeOfArray, references);
		}

		void file_references_sort(long_flags name_flags, size_t count, s_file_reference references[]) {
			Qsort(references, count, s_file_reference::CompareProc, name_flags);
		}

		template <size_t _SizeOfArray>
		void file_references_sort(long_flags name_flags, s_file_reference (&references)[_SizeOfArray]) {
			file_references_sort(name_flags, _SizeOfArray, references);
		}

		void __cdecl file_error(cstring operation, const s_file_reference &reference);

		bool __cdecl file_create(const s_file_reference &reference);

		bool __cdecl file_delete(const s_file_reference &reference);

		bool __cdecl file_exists(const s_file_reference &reference);

		bool __cdecl file_open(s_file_reference &reference, long_flags flags);

		bool __cdecl file_close(s_file_reference &reference);

		uint32 __cdecl file_get_position(const s_file_reference &reference) {
			reference.Verify();
			DWORD position = SetFilePointer(reference.handle, 0, nullptr, FILE_CURRENT);
			// NOTE: engine doesn't check if not NO_ERROR. see MSDN for more details
			if (position == INVALID_SET_FILE_POINTER /*&& GetLastError() != NO_ERROR*/)
				file_error(__FUNCTION__, reference);

			return position;
		}

		bool __cdecl file_set_position(s_file_reference &reference, uint32 position);

		uint32 __cdecl file_get_eof(const s_file_reference &reference);

		bool __cdecl file_set_eof(s_file_reference &reference, uint32 position) {
			reference.Verify();
			if (file_set_position(reference, position)) {
				SetEndOfFile(reference.handle);
				return true;
			}

			file_error(__FUNCTION__, reference);
			return false;
		}

		bool __cdecl file_read(s_file_reference &reference, size_t buffer_size, void *buffer);

		bool __cdecl file_write(s_file_reference &reference, size_t buffer_size, const void *buffer);

		bool __cdecl file_read_from_position(s_file_reference &reference, uint32 position,
														 size_t buffer_size, void *buffer);

		bool __cdecl file_write_to_position(const s_file_reference &reference, uint32 position,
														size_t buffer_size, const void *buffer);

		bool __cdecl file_read_only(const s_file_reference &reference);
	};
};
