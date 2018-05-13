/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#include "Common/Precompile.hpp"

namespace Yelo {
	namespace Scripting {


#define HS_TYPE_ABI_NAME(_hs_type)            k##_hs_type##_abi

#define HS_TYPE_ABI(abi_type, _hs_type, ...)   static const abi_type HS_TYPE_ABI_NAME(_hs_type) = { Enums::_hs_type, __VA_ARGS__ };

#include <blamlib/Halo1/hs/hs_types_definitions.inl>

#undef HS_TYPE_ABI

		const c_hs_type_abi *c_hs_type_abi::Get(Enums::hs_type type) {

			static std::array<const c_hs_type_abi *, Enums::k_number_of_hs_types> hs_type_abis = {

#define HS_TYPE_ABI(abi_type, _hs_type, ...)   &HS_TYPE_ABI_NAME(_hs_type),

#include <blamlib/Halo1/hs/hs_types_definitions.inl>

#undef HS_TYPE_ABI

			};

			return hs_type_abis[type];
		}

#undef HS_TYPE_ABI_NAME
	};

	namespace blam {
		using namespace Scripting;

		const std::array <word_flags, Enums::k_number_of_hs_object_types> k_hs_object_type_masks = {
			Enums::_object_type_mask_all, // engine actually uses 0xFFFF here
			Enums::_object_type_mask_unit,
			FLAG(Enums::_object_type_vehicle),
			FLAG(Enums::_object_type_weapon),
			Enums::_object_type_mask_device,
			FLAG(Enums::_object_type_scenery),
		};

		const std::array <tag, Enums::_hs_type_tag_reference__count> k_hs_tag_reference_type_group_tags = {
			TagGroups::sound_definition::k_group_tag,
			TagGroups::effect_definition::k_group_tag,
			TagGroups::s_damage_effect_definition::k_group_tag,   // damage
			TagGroups::looping_sound_definition::k_group_tag,
			TagGroups::model_animation_graph::k_group_tag,
			TagGroups::s_actor_variant_definition::k_group_tag,
			TagGroups::s_damage_effect_definition::k_group_tag,   // damage_effect
			TagGroups::s_object_definition::k_group_tag,
		};

		std::array <cstring, Enums::k_number_of_hs_types> hs_type_names = {
			"unparsed",
			"special_form",      // NOTE: changed spaces to underscores
			"function_name",   // NOTE: changed spaces to underscores
			"passthrough",
			"void",

			"boolean",
			"real",
			"short",
			"long",
			"string",
			"script",

			"trigger_volume",
			"cutscene_flag",
			"cutscene_camera_point",
			"cutscene_title",
			"cutscene_recording",
			"device_group",
			"ai",
			"ai_command_list",
			"starting_profile",
			"conversation",

			"navpoint",
			"hud_message",

			"object_list",

			"sound",
			"effect",
			"damage",
			"looping_sound",
			"animation_graph",
			"actor_variant",
			"damage_effect",
			"object_definition",

			"game_difficulty",
			"team",
			"ai_default_state",
			"actor_type",
			"hud_corner",

			"object",
			"unit",
			"vehicle",
			"weapon",
			"device",
			"scenery",

			"object_name",
			"unit_name",
			"vehicle_name",
			"weapon_name",
			"device_name",
			"scenery_name",
		};

		std::array <cstring, Enums::k_number_of_hs_script_types> hs_script_type_names = {
			"startup",
			"dormant",
			"continuous",
			"static",
			"stub",
		};

		// should be in game/game.cpp
		cstring                                                    g_game_difficulty_level_names[Enums::k_number_of_game_difficulty_levels] = {
			"easy",
			"normal",
			"hard",
			"impossible",
		};
		// should be in game/game_allegiance.cpp
		cstring                                                    g_game_team_names[Enums::k_number_of_game_teams]                         = {
			"default",
			"player_update",
			"human",
			"covenant",
			"flood",
			"sentinel",
			"unused6",
			"unused7",
			"unused8",
			"unused9",
		};
		// should be in ai/ai_scenario_definitions.cpp
		cstring                                                    g_ai_default_state_names[Enums::k_number_of_actor_default_states]        = {
			"none",
			"sleep",
			"alert",
			"move_repeat",
			"move_loop",
			"move_loop_back_and_forth",
			"move_loop_random",
			"move_random",
			"guard",
			"guard_at_position",
			"search",
			"flee",
		};
		// should be in ai/actor_types.cpp
		cstring                                                    g_actor_type_names[Enums::k_number_of_actor_types]                       = {
			"elite",
			"jackal",
			"grunt",
			"hunter",
			"engineer",
			"assassin",
			"player_update",
			"marine",
			"crew",
			"combat_form",
			"infection_form",
			"carrier_form",
			"monitor",
			"sentinel",
			"none",
			"mounted_weapon",
		};
		// should be in interface/hud_definitions.cpp
		cstring                                                    g_hud_anchor_names[Enums::k_number_of_hud_anchors]                       = {
			"top_left",
			"top_right",
			"bottom_left",
			"bottom_right",
			"center",
		};
		std::array<const string_list, Enums::_hs_type_enum__count> hs_enum_table                                                            = {
			string_list{std::size(g_game_difficulty_level_names), &g_game_difficulty_level_names[0]},
			string_list{std::size(g_game_team_names), &g_game_team_names[0]},
			string_list{std::size(g_ai_default_state_names), &g_ai_default_state_names[0]},
			string_list{std::size(g_actor_type_names), &g_actor_type_names[0]},
			string_list{std::size(g_hud_anchor_names), &g_hud_anchor_names[0]},
		};
	};
};
