#pragma once

#include "byte_swapping_base.h"

namespace Yelo {
	namespace blam {
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Byte swap 1 or more structures at a given address. </summary>
		/// <remarks>	Initializes the definition if it hasn't been already. </remarks>
		///
		/// <param name="definition">	The structure byte swap definition. </param>
		/// <param name="address">   	Memory address of the structure instances. </param>
		/// <param name="data_count">	Number of structure instances at the address. </param>
		void __cdecl byte_swap_data(Memory::s_byte_swap_definition *definition, void *address, long data_count = 1);

		void __cdecl byte_swap_data_explicit(cstring name, long size, byte_swap_code_t *codes, int data_count = 1, void *address = nullptr);
	};
};
