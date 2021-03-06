#pragma once

#include <precompile.h>
#include "recorded_animation_playback.hpp"

namespace Yelo
{
	namespace Scripting
	{
		struct s_recorded_animations_datum : Memory::s_datum_base_aligned
		{
			datum_index unit_index;
			short time_left;
			unsigned short flags;
			long relative_ticks;
			void* event_stream;
			Objects::s_unit_control_data control_data;
			s_recorded_animation_controller controller;
			short codec; // see Enums::e_recorded_animation_version
			unsigned short : 16;
		}; static_assert( sizeof(s_recorded_animations_datum) == 0x64 );
	};
};
