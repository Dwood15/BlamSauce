#pragma once
/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/

#include <minwindef.h>

namespace Yelo::blam {
	void __cdecl generate_md5(char *data, DWORD data_size, char *md5_out);
};
