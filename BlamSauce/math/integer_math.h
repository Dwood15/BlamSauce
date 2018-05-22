/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <precompile.h>

namespace Yelo {
	// 2 shorts representing 'x' and 'y'
	struct point2d {
		short x;
		short y;

		OVERRIDE_OPERATOR_CAST_THIS(short);
	};

#define pad_point2d unsigned short : 16; unsigned short : 16

	// 4 shorts, Top, Left, Bottom, Right
	struct rectangle2d {
		// Top
		short top;

		// Left
		short left;

		// Bottom
		short bottom;

		// Right
		short right;

		OVERRIDE_OPERATOR_CAST_THIS(short);
	};

#define pad_rectangle2d unsigned short : 16; unsigned short : 16; unsigned short : 16; unsigned short : 16

	// bounding in short integer values
	struct short_bounds {
		short lower;
		short upper;

		OVERRIDE_OPERATOR_CAST_THIS(short);
	};
};
