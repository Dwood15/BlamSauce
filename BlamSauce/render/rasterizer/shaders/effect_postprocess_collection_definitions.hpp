#pragma once

#include <precompile.h>
#include "effect_postprocess_generic_definitions.hpp"

namespace Yelo::TagGroups {
	struct s_effect_postprocess_collection_script_variable {
		tag_string script_variable_name;
		tag_string exposed_parameter_name;

		struct {
			void *exposed_parameter; //void* to avoid a problematic include

			byte:8 * sizeof(byte) * 12;
		} runtime;
	}; static_assert(sizeof(s_effect_postprocess_collection_script_variable) == 0x50);

	struct s_effect_postprocess_collection_effect {
		tag_reference                                                   effect;
		tag_string                                                      name;
		Yelo::TagBlock<s_effect_postprocess_collection_script_variable> script_variables;
		byte:8 * sizeof(byte) * 12;
	}; static_assert(sizeof(s_effect_postprocess_collection_effect) == 0x48);

	struct s_effect_postprocess_collection {
		enum { k_group_tag = 'efpc' };

		byte:8 * sizeof(byte) * 12;
		Yelo::TagBlock<tag_reference>                                shaders;
		Yelo::TagBlock<s_effect_postprocess_collection_effect>       effects;
		Yelo::TagBlock<s_effect_postprocess_generic_effect_instance> effect_instances;
	}; static_assert(sizeof(s_effect_postprocess_collection) == 0x30);
};
