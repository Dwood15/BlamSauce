/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/interface/hud_definitions.hpp>

namespace Yelo
{
	namespace Enums
	{
	};

	namespace Flags
	{
	};

	namespace TagGroups
	{
		struct equipment_hud_interface_definition
		{
			enum { k_group_tag = 'eqhi' };

			TAG_PAD(tag_reference, 1);
			struct {
				TAG_FIELD(unsigned short, flags);
				unsigned short : 16;
				TAG_PAD(short, 4);
				TAG_PAD(long, 8);
			}flash_cutoffs;

			s_hud_absolute_placement placement;

		}; //static_assert( sizeof(equipment_hud_interface_definition) == 0x );
	};
};
