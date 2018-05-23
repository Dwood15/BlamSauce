#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Enums
	{
		enum predicted_resource : short {
			_predicted_resource_bitmap,
			_predicted_resource_sound,

			k_number_of_predicted_resources
		};
	};

	namespace TagGroups
	{
		struct predicted_resource
		{
			short type;
			short resource_index;
			datum_index tag_index;
		}; static_assert( sizeof(predicted_resource) == 0x8 ); // max count: 1024
	};

	namespace blam
	{
		// NOTE: function is actually defined in the engine's physical_memory_map.c
		// May be 'physical_memory_map_precache_resources' or something
		void predicted_resources_precache(TagBlock<TagGroups::predicted_resource>& resources);
	};
};
