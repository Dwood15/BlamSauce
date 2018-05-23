/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_effect_locations_count = 32,

			k_maximum_effect_particles_per_event_count = 32,
		};
	};

	namespace TagGroups
	{
		struct effect_definition
		{
			enum { k_group_tag = 'effe' };

			unsigned long flags;
			short loop_start_event_index;
			short loop_stop_event_index;
			UNKNOWN_TYPE(real); // runtime field
			long:8 * sizeof(long) * 7;
			tag_block locations;
			tag_block events;
		}; static_assert( sizeof(effect_definition) == 0x40 );
	};
};
