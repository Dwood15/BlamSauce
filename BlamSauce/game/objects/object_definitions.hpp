#pragma once

#include <precompile.h>
#include "../../math/periodic_functions.h"
#include "../../cache/predicted_resources.hpp"
#include "object_types.h"

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_number_of_attachments_per_object = 8,
		};

		enum incoming_object_function {
			_incoming_object_function_a,
			_incoming_object_function_b,
			_incoming_object_function_c,
			_incoming_object_function_d,

			k_number_of_incoming_object_functions
		};
		enum outgoing_object_function {
			_outgoing_object_function_a,
			_outgoing_object_function_b,
			_outgoing_object_function_c,
			_outgoing_object_function_d,

			k_number_of_outgoing_object_functions
		};

		enum object_function_reference {
			_object_function_reference_none,
			_object_function_reference_a,
			_object_function_reference_b,
			_object_function_reference_c,
			_object_function_reference_d,

			k_number_of_object_function_references,
		};

		enum object_function_scalar {
			_object_function_scalar_none,

			_object_function_scalar_a_in,
			_object_function_scalar_b_in,
			_object_function_scalar_c_in,
			_object_function_scalar_d_in,

			_object_function_scalar_a_out,
			_object_function_scalar_b_out,
			_object_function_scalar_c_out,
			_object_function_scalar_d_out,

			k_number_of_object_function_scalars,
		};

		enum object_function_bounds_mode {
			_object_function_bounds_mode_clip,
			_object_function_bounds_mode_clip_and_normalize,
			_object_function_bounds_mode_scale_to_fit,

			k_number_of_object_function_bounds_modes,
		};

		enum object_change_color : short
		{
			_object_change_color_a,
			_object_change_color_b,
			_object_change_color_c,
			_object_change_color_d,

			k_number_of_object_change_colors,
		};
		enum object_change_color_reference : short
		{
			_object_change_color_reference_none,
			_object_change_color_reference_a,
			_object_change_color_reference_b,
			_object_change_color_reference_c,
			_object_change_color_reference_d,

			k_number_of_object_change_color_references,
		};
	};

	namespace Flags
	{
		enum object_definition_flags : unsigned short
		{
			_object_definition_does_not_cast_shadow_bit,
			_object_definition_transparent_self_occlusion_bit,
			_object_definition_brighter_than_it_should_bit,
			_object_definition_not_pathfinding_obstacle_bit,

			k_number_of_object_definition_flags,

			_object_definition_cast_shadow_by_default_yelo_bit = k_number_of_object_definition_flags,

			k_number_of_object_definition_flags_yelo,
		};
	};

	namespace TagGroups
	{
		struct object_attachment_definition
		{
			tag_reference type;
			tag_string marker;
			struct {
				short primary_scale;
				short secondary_scale;
				short change_color;
				unsigned short : 16;
			}function_references; // Enums::object_function_reference
			long:8 * sizeof(long) * 4;
		};

		struct object_definition_widget
		{
			tag_reference reference;
			long:8 * sizeof(long) * 4;
		};

		struct s_object_function_definition
		{
			struct _object_function_flags {
				unsigned long invert_bit:1;
				unsigned long additive_bit:1;
				unsigned long always_active_bit:1;
			}flags; static_assert( sizeof(_object_function_flags) == sizeof(unsigned long) );

			real period;
			Enums::object_function_scalar period_scale;

			Enums::periodic_function function;
			Enums::object_function_scalar function_scale;

			Enums::periodic_function wobble_function;
			real wobble_period;
			real wobble_magnitude;

			real square_wave_threshold;
			short step_count;
			Enums::transition_function map_to;
			short sawtooth_count;

			Enums::object_function_scalar add;
			Enums::object_function_scalar result_scale;

			Enums::object_function_bounds_mode bounds_mode;
			real_fraction_bounds bounds;
			unsigned long : 32;
			unsigned short : 16;
			short turn_off_with;
			real scale_by;
			byte:8 * sizeof(byte) * 252; // useless padding

			// postprocessed fields; labeled as PAD(16) in group definitions
			real_fraction bounds_normal;		// 1f / (max - min)
			real_fraction step_count_normal;	// 1f / (--step_count)
			real_fraction sawtooth_count_normal;// 1f / (--sawtooth_count)
			real_fraction period_normal;		// 1f / period

			tag_string usage;
		}; static_assert( sizeof(s_object_function_definition) == 0x168 );

		struct _object_definition
		{
			Enums::object_type runtime_object_type;
			unsigned short flags;

			real bounding_radius;
			real_point3d bounding_offset, origin_offset;
			real acceleration_scale;
			struct {
				unsigned long change_colors_scaled_by_function_bit:1; // toggled when there is 1+ change colors that have their scale-by set to something other than NONE
			}runtime_flags;

			struct {
				tag_reference render_model;
				tag_reference animations;
				long:8 * sizeof(long) * 10;
				tag_reference collision;
				tag_reference physics;
				tag_reference modifier_shader;
				tag_reference creation_effect;
			}references;
			long:8 * sizeof(long) * 21;

			real render_bounding_radius;
			
			short function_exports[Enums::k_number_of_incoming_object_functions];
			long:8 * sizeof(long) * 11;
			short hud_text_message_index;
			short forced_shader_permutation;

			Yelo::TagBlock<const object_attachment_definition> attachments;

			Yelo::TagBlock<const object_definition_widget> widgets;

			tag_block:8 * sizeof(tag_block) * 1; // object_function_definition
			tag_block:8 * sizeof(tag_block) * 1; // object_change_color_definition
			Yelo::TagBlock<predicted_resource> predicted_resources; // predicted resources
		}; static_assert( sizeof(_object_definition) == 0x17C );


		struct s_object_definition
		{
			enum { k_group_tag = 'obje' };

			_object_definition object;
		};
	};
};
