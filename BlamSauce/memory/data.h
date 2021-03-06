#pragma once

#include <precompile.h>
#include "datum_index.h"
#include "data_base.h"
#include "../cseries/base.h"
#include <engine_functions.h>

static constexpr Yelo::datum_index::salt_t k_datum_index_salt_msb = 1U << (BIT_COUNT(Yelo::datum_index::salt_t) - 1);

namespace Yelo {
	namespace Memory {
		struct s_data_array {
			tag_string name;
			short      max_datum;
			short      datum_size;
			bool       is_valid;
			bool       identifier_zero_invalid;
			unsigned short : 16;
			tag         signature;
			short       next_index;      // Next index to use when creating a new datum
			short       last_datum;      // Last used datum index
			datum_index next_datum;   // Next datum value to use
			/// <summary>	Base address of the array's datum. </summary>
			void        *base_address;

			datum_index::salt_t GetInitialSalt() const {
				datum_index::salt_t result = 0;
				// NOTE: engine uses strncpy
				std::memcpy(&result, this->name, sizeof(result));

				result |= k_datum_index_salt_msb;

				return result;
			}

			datum_index::salt_t GetNextSalt(datum_index::salt_t cursor) const {
				return ++cursor != 0 ? cursor : k_datum_index_salt_msb;
			}

			short NumberOfInvalidDatums() const {
				assert(base_address);

				auto  *datum_address = reinterpret_cast<const byte *>(base_address);
				short invalid_count  = 0;

				for (int x = 0, max_count = max_datum; x < max_count; x++, datum_address += datum_size)
					if (reinterpret_cast<const s_datum_base *>(datum_address)->IsNull())
						invalid_count++;

				return invalid_count;
			}

			short NumberOfValidDatums() const {
				return max_datum - NumberOfInvalidDatums();
			}
		};

		static_assert(sizeof(s_data_array) == 0x38);

		struct s_data_iterator {
			s_data_array *data;
			short        next_index;
			short        finished_flag; // actually alignment, unused by the engine
			datum_index  index;
			tag          signature;

			//////////////////////////////////////////////////////////////////////////
			// stl end() hacks
			enum { k_end_hack_signature = 'hack' };

			inline void SetEndHack() { signature = k_end_hack_signature; }

			inline bool IsEndHack() const { return signature == k_end_hack_signature; }

			// HACK: don't use this unless the s_data_iterator was created in the OS codebase!
			// engine's iterator_new doesn't initialize 'finished_flag' and we use it for end() hacks
			bool operator !=(const s_data_iterator &other) const {
				auto last_datum = this->data->last_datum;

				if (other.IsEndHack()) {
					return !this->finished_flag;
				}

				if (this->IsEndHack()) {
					return !other.finished_flag;
				}

				return this->index != other.index;
			}
		};

		static_assert(sizeof(s_data_iterator) == 0x10);

		s_data_array *DataNewAndMakeValid(const char *  name, long maximum_count, size_t datum_size) {
			//
			// Memory::s_data_array *data = blam::data_new(name, maximum_count, datum_size);
			//
			// if (data != nullptr) {
			// 	data->is_valid = true;
			// 	Yelo::blam::data_delete_all(data);
			// }
			//
			// return data;
			return (s_data_array *) -1;
		}

	};

	namespace blam {
		using namespace Yelo::Memory;

		void __cdecl data_verify(const Memory::s_data_array *data) {}

		void __cdecl data_delete_all(Memory::s_data_array *data);

		//A little hacky until I figure out a better way of doing the maximum_count thing.
		//Perhaps make the function into a templated constexpr function?
		Memory::s_data_array *__cdecl data_new(const char *  name, long maximum_count, size_t datum_size);

		template <typename T, const int maximum_count>
		Memory::s_data_array *data_new(const char *  name) {
			return data_new(name, maximum_count, sizeof(T));
		}

		Memory::s_data_array *__cdecl data_new(const char *  name, long maximum_count, size_t datum_size) {
			static const uintptr_t FUNCTION = K_DATA_NEW;

			API_FUNC_NAKED_START()
			push   ebx

			mov      ebx, datum_size
			push   maximum_count
			push   name
			call   FUNCTION
			add      esp, 4 * 2

			pop      ebx
			API_FUNC_NAKED_END_NO_STACK_POP()
		}

		void __cdecl data_dispose(Memory::s_data_array *data) {
			if (data != nullptr) {
				data_verify(data);
				reinterpret_cast<Yelo::Memory::s_data_array *>(GlobalFree(data));
			}
		}

		void __cdecl data_delete_all(Memory::s_data_array *data) {
			static const uintptr_t FUNCTION = K_DATA_DELETE_ALL;

			API_FUNC_NAKED_START()
			push   esi

			mov      esi, data
			call   FUNCTION

			pop      esi
			__asm pop ebp __asm retn }
		}

		void __cdecl data_make_valid(Memory::s_data_array *data) {
			data_verify(data);
			data->is_valid = true;
			data_delete_all(data);
		}

		void __cdecl data_make_invalid(Memory::s_data_array *data) {
			data_verify(data);
			data->is_valid = false;
		}

		datum_index __cdecl data_next_index(const Memory::s_data_array *data, datum_index cursor) {
			static const uintptr_t FUNCTION = K_DATA_NEXT_INDEX;

			if (data == nullptr || cursor.IsNull()) return {static_cast<uint>(-1)};

			__asm {
			push   esi
			push   edi

			mov      esi, cursor
			mov      edi, data
			call   FUNCTION

			pop      edi
			pop      esi
			}
		}

		void __cdecl data_iterator_new(s_data_iterator &iterator, Memory::s_data_array *data) {
			data_verify(data);

			if (!data->is_valid) {
				throw std::exception("invalid data array passed to " __FUNCTION__);
			}
			iterator.data          = data;
			iterator.next_index    = 0;
			iterator.finished_flag = false;
			iterator.index         = {static_cast<uint>(-1)};
			iterator.signature     = reinterpret_cast<uintptr_t>(data) ^ Enums::k_data_iterator_signature;
		}

		void *__cdecl data_iterator_next(s_data_iterator &iterator) {
			if (!(iterator.signature == (reinterpret_cast<uintptr_t>(iterator.data) ^ Enums::k_data_iterator_signature))) {
				throw std::exception("uninitialized iterator passed to " __FUNCTION__);
			}

			const Memory::s_data_array *data = iterator.data;
			data_verify(data);
			if (!data->is_valid) {
				//std::str(data->name)
				throw std::exception("tried to iterate when it was in an invalid state ");
			}
			datum_index::index_t absolute_index = iterator.next_index;
			long                datum_size     = data->datum_size;
			byte                 *pointer       = reinterpret_cast<byte *>(data->base_address) + (datum_size * absolute_index);

			for (short last_datum  = data->last_datum; absolute_index < last_datum; pointer += datum_size, absolute_index++) {
				auto datum = reinterpret_cast<const s_datum_base *>(pointer);

				if (!datum->IsNull()) {
					iterator.next_index = absolute_index + 1;
					iterator.index      = datum_index::Create(absolute_index, datum->GetHeader());
					return pointer;
				}
			}
			iterator.next_index    = absolute_index; // will equal last_datum at this point
			iterator.finished_flag = true;
			iterator.index         = {static_cast<uint>(-1)};
			return nullptr;
		}

		datum_index __cdecl datum_new_at_index(Memory::s_data_array *data, datum_index index) {
			static constexpr uintptr_t FUNCTION = K_DATUM_NEW_AT_INDEX;

			if (data == nullptr || index.IsNull()) return {static_cast<uint>(-1)};

			__asm {
			mov      eax, index
			mov      edx, data
			call   FUNCTION
			}
		}

		// creates a new element in [data] and returns the datum index
		datum_index __cdecl datum_new(Memory::s_data_array *data) {
			static constexpr uintptr_t FUNCTION = K_DATUM_NEW;

			if (data == nullptr) return {static_cast<uint>(-1)};

			__asm {
			mov      edx, data
			call   FUNCTION
			}
		}

		// Delete the data associated with the [index] handle in [data]
		void __cdecl datum_delete(Memory::s_data_array *data, datum_index index) {
			static constexpr uintptr_t FUNCTION = K_DATUM_DELETE;

			if (data == nullptr || index.IsNull()) return;

			__asm {
			mov      edx, index
			mov      eax, data
			call   FUNCTION
			}
		}

		// Get the data associated with [index] from the [data] array
		void *__cdecl datum_get(Memory::s_data_array *data, datum_index index);

		// Get the data associated with [index] from the [data] array
		// Returns NULL if the handle is invalid
		void *__cdecl datum_try_and_get(Memory::s_data_array *data, datum_index index) {
			static constexpr uintptr_t FUNCTION = K_DATUM_TRY_AND_GET;

			if (data == nullptr) return nullptr;

			__asm {
			push   edx
			push   esi

			mov      edx, index
			mov      esi, data
			call   FUNCTION

			pop      esi
			pop      edx
			}
		}
	};
};
