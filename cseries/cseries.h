#pragma once

#include <cstddef>
#include <rpc.h>
#include "./MacrosCpp.h"

namespace Yelo::blam {
	void *__cdecl system_malloc(size_t size) { return GlobalAlloc(GMEM_FIXED, size); }

	void __cdecl system_free(void *pointer) { GlobalFree(pointer); }

	void *__cdecl system_realloc(void *pointer, size_t size) {
		//YELO_ASSERT(size >= 0);  we use size_t, which is unsigned and thus this will always be true
		if (pointer == nullptr) {
			return system_malloc(size);

		} else if (size == 0) {
			system_free(pointer);
			return nullptr;
		}

		return GlobalReAlloc(pointer, size, GMEM_MOVEABLE);
	}
};

