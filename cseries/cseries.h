#pragma once

#include <cstddef>
#include "./MacrosCpp.h"

namespace Yelo {
	namespace blam {
		void* __cdecl system_malloc(size_t size);
		void __cdecl system_free(void* pointer);
		void* __cdecl system_realloc(void* pointer, size_t size);
	};
};
