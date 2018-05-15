/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <array>
#include "../cseries/base.h"
#include "../memory/datum_index.h"
#include "constants.hpp"
#include "../scenario/scenario.h"
#include "structures.hpp"
#include "runtime.hpp"

namespace Yelo {
	namespace Enums {
		enum game_difficulty_level : short;
		enum game_team : short;
		enum actor_default_state : short;
		enum actor_type : short;
		enum hud_anchor : short;

		enum {
			k_maximum_number_of_hs_function_parameters = 32,
		};

		enum hs_type : short {
			_hs_unparsed = 0,
			// script or global
			_hs_special_form,
			_hs_function_name,
			_hs_passthrough,
			_hs_type_void,
			_hs_type_bool,
			_hs_type_real,
			_hs_type_short,
			_hs_type_long,
			_hs_type_string,
			_hs_type_script,

			_hs_type_trigger_volume,
			_hs_type_cutscene_flag,
			_hs_type_cutscene_camera_point,
			_hs_type_cutscene_title,
			_hs_type_cutscene_recording,
			_hs_type_device_group,
			_hs_type_ai,
			_hs_type_ai_command_list,
			_hs_type_starting_profile,
			_hs_type_conversation,

			_hs_type_navpoint,
			_hs_type_hud_message,

			_hs_type_object_list,

			_hs_type_sound,
			_hs_type_effect,
			_hs_type_damage,
			_hs_type_looping_sound,
			_hs_type_animation_graph,
			_hs_type_actor_variant,
			_hs_type_damage_effect,
			_hs_type_object_definition,

			_hs_type_enum_game_difficulty,
			_hs_type_enum_team,
			_hs_type_enum_ai_default_state,
			_hs_type_enum_actor_type,
			_hs_type_enum_hud_corner,

			_hs_type_object,
			_hs_type_unit,
			_hs_type_vehicle,
			_hs_type_weapon,
			_hs_type_device,
			_hs_type_scenery,

			_hs_type_object_name,
			_hs_type_unit_name,
			_hs_type_vehicle_name,
			_hs_type_weapon_name,
			_hs_type_device_name,
			_hs_type_scenery_name,

			k_number_of_hs_types,

			//_hs_type_string_id = k_number_of_hs_types,
			//_hs_type_any_tag,
			//_hs_type_any_tag_not_resolving,
				k_number_of_hs_types_yelo = k_number_of_hs_types,

			// faux HS type, only for the sake of OS code which exposes 8-bit integers
			// NOTE: we treat sbyte as a byte still!
				_hs_type_byte = _hs_type_bool,

			_hs_type_data__first = _hs_type_bool,
			_hs_type_data__last  = k_number_of_hs_types - 1,
			_hs_type_data__count = (_hs_type_data__last - _hs_type_data__first) + 1,

			_hs_type_tag_reference__first = _hs_type_sound,
			_hs_type_tag_reference__last  = _hs_type_object_definition,
			_hs_type_tag_reference__count = (_hs_type_tag_reference__last - _hs_type_tag_reference__first) + 1,

			_hs_type_enum__first = _hs_type_enum_game_difficulty,
			_hs_type_enum__last  = _hs_type_enum_hud_corner,
			_hs_type_enum__count = (_hs_type_enum__last - _hs_type_enum__first) + 1,

			_hs_type_object__first = _hs_type_object,
			_hs_type_object__last  = _hs_type_scenery,
			_hs_type_object__count = (_hs_type_object__last - _hs_type_object__first) + 1,

			_hs_type_object_name__first = _hs_type_object_name,
			_hs_type_object_name__last  = _hs_type_scenery_name,
			_hs_type_object_name__count = (_hs_type_object_name__last - _hs_type_object_name__first) + 1,
		};

		enum hs_object_type : short {
			_hs_object_type_any     = _hs_type_object - _hs_type_object__first,
			_hs_object_type_unit    = _hs_type_unit - _hs_type_object__first,
			_hs_object_type_vehicle = _hs_type_vehicle - _hs_type_object__first,
			_hs_object_type_weapon  = _hs_type_weapon - _hs_type_object__first,
			_hs_object_type_device  = _hs_type_device - _hs_type_object__first,
			_hs_object_type_scenery = _hs_type_scenery - _hs_type_object__first,

			k_number_of_hs_object_types
		};

		enum hs_script_type : short {
			_hs_script_startup,
			_hs_script_dormant,
			_hs_script_continuous,
			_hs_script_static,
			_hs_script_stub,

			k_number_of_hs_script_types,
		};
	};

	namespace Scripting {
		struct hs_function_definition;
		struct hs_global_definition;

		struct hs_syntax_node;

		typedef Memory::DataArray<hs_syntax_node, Enums::k_maximum_hs_syntax_nodes_per_scenario, Enums::k_maximum_hs_syntax_nodes_per_scenario_upgrade> hs_syntax_data_t;

		union script_idx {
			int16 script_index;
			int16 global_index;
		};

		struct s_hs_script_container_datum_index {
			script_idx idx;
			//			int16 script_container_index;

			bool IsNull() const { return HandleIsNone(*this); }

			// TODO: remove default parameter when containers come online
			static s_hs_script_container_datum_index CreateIndex(int16 index, int16 script_container_index = 0) {
				return {
					index,
					//script_container_index // TODO: uncomment when containers come online
				};
			}

			static const s_hs_script_container_datum_index k_null = {
				NONE,
				//NONE // TODO: uncomment when containers come online
			};
		};

		static_assert(sizeof(s_hs_script_container_datum_index) == 2);

		typedef s_hs_script_container_datum_index hs_script_index_t;
		typedef s_hs_script_container_datum_index hs_global_index_t;

		union s_hs_value_union {
			uintptr_t bits;
			void      *pointer;

			bool    boolean;
			real    real;
			int16   int16;
			int32   int32;
			cstring string;

			hs_script_index_t script;
			//			hs_global_index_t global;

			Enums::game_difficulty_level difficulty_level;
			Enums::game_team             team;
			Enums::actor_default_state   ai_default_state;
			Enums::actor_type            actor_type;
			Enums::hud_anchor            hud_corner;

			datum_index tag_index;
			datum_index datum;

			string_id string_id;

			datum_index ToExpressionIndex() const { return datum; }

			datum_index ToTagIndex() const { return datum; }

			datum_index ToObjectIndex() const { return datum; }
		};

		static_assert(sizeof(s_hs_value_union) == sizeof(void *));
		extern const s_hs_value_union k_null_value_union = {NULL};
		extern const s_hs_value_union k_none_value_union = {NONE};

		hs_syntax_data_t &HsSyntax();
	};

	namespace blam {
		void hs_nodes_garbage_collect() {
			// NOTE: engine seems to use a for(;;) using data_next_index() on syntax nodes
			for (auto node : HsSyntax()) {
				if (node->IsGarbageCollectable())
					continue;

				HsSyntax().Delete(node.index);
			}
		}

		Scripting::hs_function_definition *hs_function_get(int16 function_index) {
			return c_hs_library::GetFunction(function_index);
		}

		Scripting::hs_global_definition *hs_global_external_get(int16 global_index) {
			return c_hs_library::GetGlobal(global_index);
		}

		Enums::hs_type hs_global_get_type(int16 global_index) {
			assert(global_index != NONE); // engine doesn't do this

			bool is_internal = (global_index & Enums::_hs_global_index_is_external_mask) == 0;
			global_index &= Enums::_hs_global_index_mask;

			if (is_internal) {
				return global_scenario_get()->globals[global_index].global.type;
			}

			return hs_global_external_get(global_index)->type;
		}

		cstring hs_global_get_name(int16 global_index) {
			assert(global_index != NONE); // engine doesn't do this

			bool is_internal = (global_index & Enums::_hs_global_index_is_external_mask) == 0;
			global_index &= Enums::_hs_global_index_mask;

			if (is_internal) {
				return global_scenario_get()->globals[global_index].name;
			}

			return hs_global_external_get(global_index)->name;
		}

		int16 hs_find_global_by_name(cstring name) {
			// TODO: update code when containers come online

			// search the globals external from the scenario first
			int32     global_index = 0;
			for (auto *external_global : c_hs_library::GetExternalGlobals()) {
				if (!_stricmp(name, external_global->name)) {
					global_index |= Enums::_hs_global_index_is_external_mask;
					// engine casts down as well, so we will too
					return CAST(int16, global_index);
				}

				global_index++;
			}

			auto *scenario = global_scenario_try_and_get();
			// if NULL, a scenario isn't currently loaded. engine actually checks that global_scenario_index isn't NONE
			if (scenario == nullptr)
				return NONE;

			// now search the globals internal to the scenario
			global_index = 0;
			for (auto &internal_global : scenario->globals) {
				if (!_stricmp(name, internal_global.name)) {
					// engine casts down as well, so we will too
					return CAST(int16, global_index);
				}

				global_index++;
			}

			// no global by the given name was found
			return NONE;
		}

		int16 hs_find_function_by_name(cstring name) {
			int32     function_index = 0;
			for (auto *function : c_hs_library::GetFunctionsTable()) {
				if (!_stricmp(name, function->name)) {
					// engine casts down as well, so we will too
					return CAST(int16, function_index);
				}

				function_index++;
			}

			// no function by the given name was found
			return NONE;
		}

		int16 hs_find_tag_reference_by_index(datum_index tag_index) {
			// TODO: update code when containers come online

			auto *scenario = global_scenario_try_and_get();
			// if NULL, a scenario isn't currently loaded. engine actually checks that global_scenario_index isn't NONE
			if (scenario == nullptr) {
				return -1;
			}

			int32     reference_index = 0;
			for (auto &reference : scenario->references) {
				if (reference.reference.tag_index == tag_index) {
					// engine casts down as well, so we will too
					return static_cast<int16>(reference_index);
				}

				reference_index++;
			}

			// no reference with the given tag_index was found
			return -1;
		}

		Scripting::hs_script_index_t hs_find_script_by_name(cstring name) {
			// TODO: update code when containers come online

			auto *scenario = global_scenario_try_and_get();
			// if NULL, a scenario isn't currently loaded. engine actually checks that global_scenario_index isn't NONE
			if (scenario == nullptr) {
				return hs_script_index_t::k_null;
			}

			int32     script_index = 0;
			for (auto &script : scenario->scripts) {
				if (!_stricmp(name, script.name)) {
					return hs_script_index_t::CreateIndex(static_cast<int16>(script_index));
				}

				script_index++;
			}

			// no script by the given name was found
			return hs_script_index_t::k_null;
		}

		bool hs_evaluate_by_script_name(cstring name) {
			// TODO: update code when containers come online

			auto script = hs_find_script_by_name(name);
			if (script.IsNull())
				return false;

			auto *scenario = global_scenario_get();

			hs_runtime_evaluate(scenario->scripts[script.idx.script_index].script.root_expression_index);
			return true;
		}

		Scripting::hs_syntax_node *hs_syntax_get(datum_index expression_index) { return HsSyntax()[expression_index.handle]; }
	};

	// these are now defined in hs_types.cpp
	namespace blam {
		extern const std::array<word_flags, Enums::k_number_of_hs_object_types> k_hs_object_type_masks;
		extern const std::array<tag, Enums::_hs_type_tag_reference__count>      k_hs_tag_reference_type_group_tags;

		extern std::array<cstring, Enums::k_number_of_hs_types>           hs_type_names;
		extern std::array<cstring, Enums::k_number_of_hs_script_types>    hs_script_type_names;
		extern std::array<const string_list, Enums::_hs_type_enum__count> hs_enum_table;

		bool hs_type_valid(short type) { return type >= Enums::_hs_type_void && type < Enums::k_number_of_hs_types; }

		bool hs_type_is_enum(short type) { return type >= Enums::_hs_type_enum__first && type < Enums::_hs_type_enum__last; }

		bool hs_type_is_tag_reference(short type) { return type >= Enums::_hs_type_tag_reference__first && type < Enums::_hs_type_tag_reference__last; }

		bool hs_type_is_object(short type) { return type >= Enums::_hs_type_object__first && type < Enums::_hs_type_object__last; }

		bool hs_type_is_object_name(short type) { return type >= Enums::_hs_type_object_name__first && type < Enums::_hs_type_object_name__last; }
	};
};

