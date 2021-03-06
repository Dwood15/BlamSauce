#pragma once

#include "../cseries/base.h"

namespace Yelo {
	typedef long byte_swap_code_t;

	namespace Enums {
		enum {
			k_byte_swap_signature = 'bysw',
		};

		// positive numbers are runs (of bytes) to leave untouched
		// zero is invalid
		enum /*e_bs_code*/ : byte_swap_code_t {
			_bs_code_array_end   = -101, // _end_bs_array
			_bs_code_array_start = -100, // _begin_bs_array

			_bs_code_8byte = 0 - (byte_swap_code_t) sizeof(uint64), // _8byte
			_bs_code_4byte = 0 - (byte_swap_code_t) sizeof(uint), // _4byte
			_bs_code_2byte = 0 - (byte_swap_code_t) sizeof(unsigned short), // _2byte

			_bs_code_1byte = sizeof(byte), // _byte
		};
	};

	namespace Memory {
		struct s_byte_swap_definition {
			const char * name;
			size_t  size;
			// _bs_code_array_start,
			// <count>,
			// ...codes...
			// _bs_code_array_end
			byte_swap_code_t *codes;
			tag  signature;
			bool initialized;
			short : 16;
			byte  : 8;
		}; static_assert(sizeof(s_byte_swap_definition) == 0x14);
	};
};
