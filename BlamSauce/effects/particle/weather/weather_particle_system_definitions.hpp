#pragma once

#include "../../../tags/group/markup.h"
#include "../../../tags/group/tag_groups_base_yelo.hpp"
#include "../particle_definitions.hpp"
#include "../../shader/shader_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum weather_particle_render_direction_source : short
		{
			_weather_particle_render_direction_source_from_velocity,
			_weather_particle_render_direction_source_from_acceleration,

			_weather_particle_render_direction_source,
		};
	};
	namespace TagGroups
	{
		struct s_weather_particle_type
		{
			struct __flags
			{
				Yelo::long_flags interpolate_colors_in_hsv_bit:1;
				Yelo::long_flags _along_long_hue_path_bit:1;
				Yelo::long_flags random_rotation_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			tag_string name;
			__flags flags;
			real fade_in_start_distance;
			real fade_in_end_distance;
			real fade_out_start_distance;
			real fade_out_end_distance;
			real fade_in_start_height;
			real fade_in_end_height;
			real fade_out_start_height;
			real fade_out_end_height;
			long:8 * sizeof(long) * 24;
			real_bounds particle_count;
			tag_reference physics;
			long:8 * sizeof(long) * 4;
			real_bounds acceleration_magnitude;
			real_fraction acceleration_turning_rate;
			real acceleration_change_rate;
			long:8 * sizeof(long) * 8;
			real_bounds particle_radius;
			real_bounds animation_rate;
			angle_bounds rotation_rate;
			long:8 * sizeof(long) * 8;
			real_argb_color color_lower_bound;
			real_argb_color color_upper_bound;
			long:8 * sizeof(long) * 16;

			////////////////////////////////////////////////////////////////
			// SHADER
			tag_reference sprite_bitmap;
			Enums::particle_orientation render_mode;
			Enums::weather_particle_render_direction_source render_direction_source;
			s_shader_effect shader_effect;
		}; static_assert( sizeof(s_weather_particle_type) == 0x25C ); // max count: 8

		struct s_weather_particle_system_definition
		{
			enum { k_group_tag = 'rain' };

			struct __flags
			{
				Yelo::long_flags unused_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			__flags flags;
			long:8 * sizeof(long) * 8;
			Yelo::TagBlock<const s_weather_particle_type> particle_types;
		}; static_assert( sizeof(s_weather_particle_system_definition) == 0x30 ); // max count: 1
	};
};
