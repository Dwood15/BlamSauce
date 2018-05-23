#pragma once

#include <precompile.h>
#include "../shader/shader_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum contrail_render_type : short
		{
			_contrail_render_type_vertical_orientation,
			_contrail_render_type_horizontal_orientation,
			_contrail_render_type_media_mapped,
			_contrail_render_type_ground_mapped,
			_contrail_render_type_viewer_facing,
			_contrail_render_type_double_marker_linked,

			_contrail_render_type,
		};
	};

	namespace TagGroups
	{
		struct s_contrail_point_states
		{
			struct __scale_flags
			{
				unsigned long duration_bit:1;
				unsigned long duration_delta_bit:1;
				unsigned long transition_duration_bit:1;
				unsigned long transition_duration_delta_bit:1;
				unsigned long width_bit:1;
				unsigned long color_bit:1;
			}; static_assert( sizeof(__scale_flags) == sizeof(unsigned long) );

			////////////////////////////////////////////////////////////////
			// state timing
			real_bounds duration;
			real_bounds transition_duration;

			////////////////////////////////////////////////////////////////
			// point variables
			tag_reference physics;
			long:8 * sizeof(long) * 8;
			real width;
			real_argb_color color_lower_bound;
			real_argb_color color_upper_bound;
			__scale_flags scale_flags;
		}; static_assert( sizeof(s_contrail_point_states) == 0x68 ); // max count: 16

		struct s_contrail_definition
		{
			enum { k_group_tag = 'cont' };

			struct __flags
			{
				unsigned short first_point_unfaded_bit:1;
				unsigned short last_point_unfaded_bit:1;
				unsigned short points_start_pinned_to_media_bit:1;
				unsigned short points_start_pinned_to_ground_bit:1;
				unsigned short points_always_pinned_to_media_bit:1;
				unsigned short points_always_pinned_to_ground_bit:1;
				unsigned short edge_effect_fades_slowly_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned short) );

			struct __scale_flags
			{
				unsigned short point_generation_rate_bit:1;
				unsigned short point_velocity_bit:1;
				unsigned short point_velocity_delta_bit:1;
				unsigned short point_velocity_cone_angle_bit:1;
				unsigned short inherited_velocity_fraction_bit:1;
				unsigned short sequence_animation_rate_bit:1;
				unsigned short texture_scale_u_bit:1;
				unsigned short texture_scale_v_bit:1;
				unsigned short texture_animation_u_bit:1;
				unsigned short texture_animation_v_bit:1;
			}; static_assert( sizeof(__scale_flags) == sizeof(unsigned short) );

			__flags flags;
			__scale_flags scale_flags;

			////////////////////////////////////////////////////////////////
			// point creation
			real point_generation_rate;
			real_bounds point_velocity;
			angle point_velocity_cone_angle;
			real_fraction inherited_velocity_fraction;

			////////////////////////////////////////////////////////////////
			// rendering
			//"this specifies how the contrail is oriented in space"
			Enums::contrail_render_type render_type;
			unsigned short : 16;
			real texture_repeats_u;
			real texture_repeats_v;
			real texture_animation_u;
			real texture_animation_v;
			real animation_rate;
			tag_reference bitmap;
			short first_sequence_index;
			short sequence_count;
			long:8 * sizeof(long) * 16;
			s_shader_effect shader_effect;
			Yelo::TagBlock<const s_contrail_point_states> point_states;
		}; static_assert( sizeof(s_contrail_definition) == 0x144 ); // max count: 1
	};
};
