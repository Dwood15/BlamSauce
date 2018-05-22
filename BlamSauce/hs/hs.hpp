#include <precompile.h>
#include "../cseries/base.h"
#include "../memory/datum_index.h"
#include "../scenario/scenario.h"
#include "structures.hpp"
#include "runtime.hpp"
#include "../cseries/handle_abi.hpp"
#include "../game/game.hpp"
#include "../game/allegiance.hpp"
#include "../ai/actors/actors.hpp"
#include "../memory/upgrades/blam_memory_upgrades.hpp"

#pragma once

namespace Yelo::Scripting {
	auto item = Yelo::Enums::k_maximum_hs_syntax_nodes_per_scenario_upgrade;
	using hs_syntax_data_t = Memory::DataArray<hs_syntax_node, Enums::k_maximum_hs_syntax_nodes_per_scenario, Enums::k_maximum_hs_syntax_nodes_per_scenario_upgrade>;

	union script_idx {
		short script_index;
		short global_index;
	};

	struct s_hs_script_container_datum_index {
		script_idx idx;
		//			short script_container_index;

		bool IsNull() const { return HandleIsNone(*this); }

		// TODO: remove default parameter when containers come online
		static s_hs_script_container_datum_index CreateIndex(short index, short script_container_index = 0) {
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
		short   short;
		long   long;
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

namespace Yelo::blam {
	void hs_nodes_garbage_collect() {
		// NOTE: engine seems to use a for(;;) using data_next_index() on syntax nodes
		for (auto node : HsSyntax()) {
			if (node->IsGarbageCollectable())
				continue;

			HsSyntax().Delete(node.index);
		}
	}

	Scripting::hs_function_definition *hs_function_get(short function_index) {
		return c_hs_library::GetFunction(function_index);
	}

	Scripting::hs_global_definition *hs_global_external_get(short global_index) {
		return c_hs_library::GetGlobal(global_index);
	}

	Enums::hs_type hs_global_get_type(short global_index) {
		assert(global_index != NONE); // engine doesn't do this

		bool is_internal = (global_index & Enums::_hs_global_index_is_external_mask) == 0;
		global_index &= Enums::_hs_global_index_mask;

		if (is_internal) {
			return global_scenario_get()->globals[global_index].global.type;
		}

		return hs_global_external_get(global_index)->type;
	}

	cstring hs_global_get_name(short global_index) {
		assert(global_index != NONE); // engine doesn't do this

		bool is_internal = (global_index & Enums::_hs_global_index_is_external_mask) == 0;
		global_index &= Enums::_hs_global_index_mask;

		if (is_internal) {
			return global_scenario_get()->globals[global_index].name;
		}

		return hs_global_external_get(global_index)->name;
	}

	short hs_find_global_by_name(cstring name) {
		// TODO: update code when containers come online

		// search the globals external from the scenario first
		long     global_index = 0;
		for (auto *external_global : c_hs_library::GetExternalGlobals()) {
			if (!_stricmp(name, external_global->name)) {
				global_index |= Enums::_hs_global_index_is_external_mask;
				// engine casts down as well, so we will too
				return CAST(short, global_index);
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
				return CAST(short, global_index);
			}

			global_index++;
		}

		// no global by the given name was found
		return NONE;
	}

	short hs_find_function_by_name(cstring name) {
		long     function_index = 0;
		for (auto *function : c_hs_library::GetFunctionsTable()) {
			if (!_stricmp(name, function->name)) {
				// engine casts down as well, so we will too
				return CAST(short, function_index);
			}

			function_index++;
		}

		// no function by the given name was found
		return NONE;
	}

	short hs_find_tag_reference_by_index(datum_index tag_index) {
		// TODO: update code when containers come online

		auto *scenario = global_scenario_try_and_get();
		// if NULL, a scenario isn't currently loaded. engine actually checks that global_scenario_index isn't NONE
		if (scenario == nullptr) {
			return -1;
		}

		long     reference_index = 0;
		for (auto &reference : scenario->references) {
			if (reference.reference.tag_index == tag_index) {
				// engine casts down as well, so we will too
				return static_cast<short>(reference_index);
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

		long     script_index = 0;
		for (auto &script : scenario->scripts) {
			if (!_stricmp(name, script.name)) {
				return hs_script_index_t::CreateIndex(static_cast<short>(script_index));
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
namespace Yelo::blam {
	extern const std::array<word_flags, Yelo::Enums::k_number_of_hs_object_types> k_hs_object_type_masks;
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

