/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../cseries/base.h"

namespace Yelo::blam {
	inline constexpr bool game_in_editor() {
		//TODO: Detect platforms via constexpr's.
		constexpr bool PLATFORM_SAPIEN = false;
		return PLATFORM_SAPIEN;
	}
};
