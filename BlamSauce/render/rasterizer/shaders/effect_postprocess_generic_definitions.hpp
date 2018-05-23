#pragma once

#include <precompile.h>
#include "shader_postprocess_definitions.hpp"

namespace Yelo::TagGroups {
		struct s_effect_postprocess_effect_activation_control
		{
			short state;
			struct _flags {
				unsigned short invert_bit:1;
			}flags;
		}; static_assert( sizeof(s_effect_postprocess_effect_activation_control) == 0x4);

		struct s_effect_postprocess_generic_effect_instance
		{
			tag_string name;
			short effect_index;
			Enums::postprocess_render_stage render_stage;
			s_effect_postprocess_quad_definition quad_definition;
			short activation_operation;
			unsigned short : 16;
			unsigned long : 32;
			Yelo::TagBlock<s_effect_postprocess_effect_activation_control> activation_controls;
			tag_block:8 * sizeof(tag_block) * 1;
			byte:8 * sizeof(byte) * 16;
		}; static_assert( sizeof(s_effect_postprocess_generic_effect_instance) == 0x74 );

		struct s_effect_postprocess_generic_exposed_parameter
		{
			tag_string exposed_name;
			tag_string parameter_name;
			long shader_index;
			shader_variable_type value_type;

			struct
			{
				void* parameter_instance; //void* to avoid a problematic include
			}runtime;

			unsigned long : 32;
		}; static_assert( sizeof(s_effect_postprocess_generic_exposed_parameter) == 0x50);

		struct s_effect_postprocess_generic : s_effect_postprocess_definition
		{
			enum { k_group_tag = 'efpg' };

			Yelo::TagBlock<tag_reference> shaders;
			Yelo::TagBlock<long> shader_indices;
			Yelo::TagBlock<s_effect_postprocess_generic_exposed_parameter> exposed_parameters;

		}; static_assert( sizeof(s_effect_postprocess_generic) == 0x24 + sizeof(s_effect_postprocess_definition));
	};
