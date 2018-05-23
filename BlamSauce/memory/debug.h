#pragma once
/*
	See LICENSE for license information
*/
#include <cstdio>
#include "../cseries/base.h"

namespace Yelo::Debug {
	struct s_debug_memory_header {
		enum {
			k_disposed_signature = '<BAD',
			k_header_signature   = '--->',
			k_footer_signature   = '<---',
		};

		tag                   signature;
		s_debug_memory_header *next;
		s_debug_memory_header *previous;
		size_t                size;
		cstring               file;
		uint                line;
		long                 marker;
		uint                checksum;

		static size_t AllocationSize(size_t size) {
			return sizeof(s_debug_memory_header) + size + sizeof(tag); // header + size + footer
		}
	};

	static_assert(sizeof(s_debug_memory_header) == 0x20);

	struct s_debug_memory_globals {
		enum {
			k_signature                   = 'SAFT',
			k_maximum_files_with_pointers = 512,
		};

		tag                   header;
		size_t                current_heap_size;
		size_t                largest_heap_size;
		s_debug_memory_header *heap;
		s_debug_memory_header *first;
		s_debug_memory_header *last;
		long                 next_marker;            // increments with each malloc and realloc, never decrements
		tag                   footer;
	}; static_assert(sizeof(s_debug_memory_globals) == 0x20);

	void BlamMemoryManagerDispose() {
		// TODO: check for possible memory leaks with s_debug_memory_globals
	}
};

namespace Yelo::blam {
	void __cdecl debug_dump_memory();

	// The engine's debug memory manager on win32 boils down to GlobalAlloc family of memory functions,
	// which is guaranteed to be aligned on an 8-byte boundary (http://msdn.microsoft.com/en-us/library/aa366574%28v=vs.12%29.ASPX)
	// See the system_malloc, etc functions in the engine's cseries.hpp

	// returns NULL when out of memory
	void *__cdecl debug_malloc(const size_t size, const bool fill_with_garbage, cstring file, const uint line);

	template <typename T>
	inline T *debug_new(const bool fill_with_garbage, cstring file, const uint line) {
		return CAST_PTR(T*, debug_malloc(sizeof(T) * 1, fill_with_garbage, file, line));
	}

	template <typename T>
	inline T *debug_new_array(const size_t count, const bool fill_with_garbage, cstring file, const uint line) {
		return CAST_PTR(T*, debug_malloc(sizeof(T) * count, fill_with_garbage, file, line));
	}

	void __cdecl debug_free(void *pointer, cstring file, const uint line);

	// Nulls [pointer] before returning
	template <typename T>
	void debug_free_with_null(T *&pointer, cstring file, const uint line) {
		debug_free(pointer, file, line);

		pointer = nullptr;
	}

	// Nulls [pointer] before returning
	template <typename T>
	void debug_delete(T *&pointer, cstring file, const uint line) {
		if (pointer != nullptr) {
			pointer->~T();
			debug_free(pointer, file, line);
		}

		pointer = nullptr;
	}

	// Nulls [pointer] before returning
	template <typename T>
	void debug_delete_array(T *&pointer, cstring file, const uint line) {
		debug_free(pointer, file, line);

		pointer = nullptr;
	}

	void *__cdecl debug_realloc(void *pointer, const size_t new_size, cstring file, const uint line);

	template <typename T>
	T *debug_renew(T *pointer, cstring file, const uint line) {
		return CAST_PTR(T*, debug_realloc(pointer, sizeof(T) * 1, file, line));
	}

	template <typename T>
	T *debug_renew_array(T *pointer, const size_t count, cstring file, const uint line) {
		return CAST_PTR(T*, debug_realloc(pointer, sizeof(T) * count, file, line));
	}
};
