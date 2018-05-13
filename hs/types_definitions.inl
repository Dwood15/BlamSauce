/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#include "types.hpp"

#define HS_TYPE_ABI(_hs_type) &k##_hs_type##_abi,

// HS_TYPE_ABI(_hs_unparsed)
// HS_TYPE_ABI(_hs_special_form)
// HS_TYPE_ABI(_hs_function_name)
// HS_TYPE_ABI(_hs_passthrough)
// HS_TYPE_ABI(_hs_type_void)
// HS_TYPE_ABI(_hs_type_bool)

#undef HS_TYPE_ABI

//#define HS_TYPE_ABI(abi_type, _hs_type, ...)



