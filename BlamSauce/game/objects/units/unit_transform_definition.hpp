/* LICENSE.md */
#pragma once

#include "../../game.hpp"
#include "../../../tags/group/markup.h"
#include "../../../tags/group/tag_groups_base_yelo.hpp"

namespace Yelo {
	namespace Enums {
		enum game_team : short;
		enum actor_default_state : short;
		enum actor_action : short;
		enum unit_animation_keyframe : short;

		enum actor_variant_transform_keyframe_rider_handling : short {
			_actor_variant_transform_keyframe_rider_handling_none,
			_actor_variant_transform_keyframe_rider_handling_kill,
			_actor_variant_transform_keyframe_rider_handling_eject,

			_actor_variant_transform_keyframe_rider_handling
		};

		enum actor_variant_transform_keyframe_effect_target : short {
			_actor_variant_transform_keyframe_effect_target_self,
			_actor_variant_transform_keyframe_effect_target_riders,

			_actor_variant_transform_keyframe_effect_target
		};

		enum actor_variant_transform_team_handling : short {
			_actor_variant_transform_team_handling_inherit_from_old_actor,
			_actor_variant_transform_team_handling_inherit_from_attacker,
			_actor_variant_transform_team_handling_override,

			_actor_variant_transform_team
		};

		enum actor_variant_transform_in_actor_state_handling : short {
			_actor_variant_transform_in_actor_state_handling_inherit,
			_actor_variant_transform_in_actor_state_handling_override,
			_actor_variant_transform_in_actor_state_handling_actor_default,

			_actor_variant_transform_in_actor_state_handling
		};

		enum actor_variant_transform_in_actor_action_handling : short {
			_actor_variant_transform_in_actor_action_handling_default,
			_actor_variant_transform_in_actor_action_handling_inherit,
			_actor_variant_transform_in_actor_action_handling_override,

			_actor_variant_transform_in_actor_action_handling
		};

		enum actor_variant_transform_in_encounter_squad_handling : short {
			_actor_variant_transform_in_encounter_squad_handling_inherit_from_old_actor,
			_actor_variant_transform_in_encounter_squad_handling_inherit_from_attacker,
			_actor_variant_transform_in_encounter_squad_handling_free_actor,

			_actor_variant_transform_in_encounter_squad_handling
		};

		enum actor_variant_transform_in_vitality_handling : short {
			_actor_variant_transform_in_vitality_handling_neither,
			_actor_variant_transform_in_vitality_handling_both,
			_actor_variant_transform_in_vitality_handling_shield_only,
			_actor_variant_transform_in_vitality_handling_health_only,

			_actor_variant_transform_in_vitality_handling
		};

		enum actor_variant_transform_out_threshold_type : short {
			_actor_variant_transform_out_threshold_type_both,
			_actor_variant_transform_out_threshold_type_shield_amount_only,
			_actor_variant_transform_out_threshold_type_health_amount_only,

			_actor_variant_transform_out_threshold_type
		};

		enum actor_variant_transform_out_damage_type : short {
			_actor_variant_transform_out_damage_type_both,
			_actor_variant_transform_out_damage_type_weapon_only,
			_actor_variant_transform_out_damage_type_melee_only,

			_actor_variant_transform_out_damage_type
		};
	};

	namespace Flags {
		enum actor_variant_transform_collection_transform_flags {
			_actor_variant_transform_collection_transform_flags_scripted_only,

			_actor_variant_transform_collection_transform_flags
		};

		enum actor_variant_transform_in_target_flags {
			_actor_variant_transform_in_target_flags_try_to_use_existing_unit,
			_actor_variant_transform_in_target_flags_drop_weapon,
			_actor_variant_transform_in_target_flags_inherit_seated_units,
			_actor_variant_transform_in_target_flags_delete_attached_actors,

			_actor_variant_transform_in_target_flags
		};

		enum actor_variant_transform_out_attachment_flags {
			_actor_variant_transform_out_attachment_flags_destroy_attachments_on_death,

			_actor_variant_transform_out_attachment_flags
		};

		enum actor_variant_transform_out_flags {
			_actor_variant_transform_out_flags_invicible_during_transform_out_bit,

			_actor_variant_transform_out_flags
		};

		enum actor_variant_transform_out_criteria_flags {
			_actor_variant_transform_out_criteria_flags_transform_on_damage_only_bit,
			_actor_variant_transform_out_criteria_flags_ignore_friendly_fire_bit,
			_actor_variant_transform_out_criteria_flags_transform_on_actor_action_bit,
			_actor_variant_transform_out_criteria_flags_transform_on_actor_state_bit,
			_actor_variant_transform_out_criteria_flags_transform_on_shield_range_bit,
			_actor_variant_transform_out_criteria_flags_transform_on_health_range_bit,

			_actor_variant_transform_out_criteria_flags
		};
	};

	namespace TagGroups {
		struct actor_variant_transform_keyframe_action {
			Enums::unit_animation_keyframe keyframe;
			Enums::actor_variant_transform_keyframe_rider_handling rider_handling;
			Enums::actor_variant_transform_keyframe_effect_target target;
			unsigned short : 16;
			tag_reference damage_effect;
			tag_reference effect;
			tag_string effect_marker;
		};

		struct actor_variant_transform_in_target {
			tag_string target_name;
			unsigned short flags;
			unsigned short : 16;
			real_fraction selection_chance[Enums::k_number_of_game_difficulty_levels];

			tag_reference actor_variant;
			Enums::actor_variant_transform_in_encounter_squad_handling encounter_squad_handling;
			unsigned short : 16;
			Enums::actor_variant_transform_team_handling team_handling;
			Enums::game_team team_override;
			Enums::actor_variant_transform_in_actor_state_handling initial_state_handling;
			Enums::actor_default_state initial_state_override;
			Enums::actor_variant_transform_in_actor_state_handling return_state_handling;
			Enums::actor_default_state return_state_override;
			unsigned short : 16; // TAG_FIELD(Enums::actor_variant_transform_in_actor_action_handling, actor_action_handling);
			unsigned short : 16; // TAG_FIELD(Enums::actor_action, actor_action_override);

			tag_string transform_in_anim;
			Yelo::TagBlock<const actor_variant_transform_keyframe_action> keyframe_actions;

			unsigned long : 32;
			Enums::actor_variant_transform_in_vitality_handling vitality_inheritance;
			Enums::actor_variant_transform_in_vitality_handling vitality_override;
			real shield_override;
			real health_override;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_in_target) == 0xAC);

		struct actor_variant_transform_in_definition {
			enum { k_group_tag = 'avti' };

			Yelo::TagBlock<const actor_variant_transform_in_target> targets;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_in_definition) == 0x24);

		struct actor_variant_transform_out_instigator {
			tag_reference unit;
			Enums::actor_variant_transform_out_damage_type damage_type;
			unsigned short : 16;
			tag_block:8 * sizeof(tag_block) * 1;
		};
		static_assert(sizeof(actor_variant_transform_out_instigator) == 0x20);

		struct actor_variant_transform_out_attachment {
			tag_reference object_type;
			tag_string object_marker;
			tag_string destination_marker;
			short destination_marker_count;
			unsigned short : 16;
			Enums::actor_variant_transform_team_handling team_handling;
			Enums::game_team team_override;
			real_bounds attachment_scale;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_out_attachment) == 0x78);

		struct actor_variant_transform_out_definition {
			enum { k_group_tag = 'avto' };

			unsigned short flags;
			unsigned short : 16;

			unsigned short criteria_flags;
			unsigned short : 16;
			unsigned short actor_action;
			unsigned short actor_state;
			real_bounds shield_range;
			real_bounds health_range;
			tag_block:8 * sizeof(tag_block) * 2;

			Yelo::TagBlock<const actor_variant_transform_out_instigator> instigators;

			tag_string transform_out_anim;
			Yelo::TagBlock<const actor_variant_transform_keyframe_action> keyframe_actions;

			unsigned short attachment_flags;
			unsigned short : 16;
			Yelo::TagBlock<const actor_variant_transform_out_attachment> attachments;

			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_out_definition) == 0x94);


		struct actor_variant_transform_collection_transform {
			unsigned short flags;
			unsigned short : 16;
			tag_string transform_name;
			real_fraction selection_chance[Enums::k_number_of_game_difficulty_levels];

			tag_reference transform_out;
			actor_variant_transform_out_definition *transform_out_ptr;
			tag_reference transform_in;
			actor_variant_transform_in_definition *transform_in_ptr;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_collection_transform) == 0x74);

		struct actor_variant_transform_collection_entry {
			tag_reference actor_variant;
			Yelo::TagBlock<actor_variant_transform_collection_transform> transforms;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_collection_entry) == 0x34);

		struct actor_variant_transform_collection_definition {
			enum { k_group_tag = 'avtc' };

			Yelo::TagBlock<actor_variant_transform_collection_entry> actor_variant_transforms;
			tag_block:8 * sizeof(tag_block) * 2;
		};
		static_assert(sizeof(actor_variant_transform_collection_definition) == 0x24);
	};
};
