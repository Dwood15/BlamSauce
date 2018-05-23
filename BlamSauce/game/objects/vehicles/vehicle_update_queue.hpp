#pragma once

#include <precompile.h>
#include "../../../memory/simple_circular_queue.h"

namespace Yelo
{
	namespace Game
	{
		struct s_vehicle_update_queue_entry : TStructImpl(72)
		{
		};
		struct s_vehicle_update_queue
		{
			Memory::s_simple_circular_queue queue;
			s_vehicle_update_queue_entry* entries;	// 0x14, #30, user_data
		}; static_assert( sizeof(s_vehicle_update_queue) == 0x18 );
	};
};
