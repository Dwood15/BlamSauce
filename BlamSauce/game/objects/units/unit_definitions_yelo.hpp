/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/units/unit_camera.hpp>

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum unit_animation_keyframe : short;

		enum unit_seat_mounted_keyframe_action_target : short
		{
			_unit_seat_mounted_keyframe_action_target_all_seats,
			_unit_seat_mounted_keyframe_action_target_mounted_trigger_seats,

			_unit_seat_mounted_keyframe_action_target
		};

		enum unit_seat_keyframe_action_self_seat_action : short
		{
			_unit_seat_keyframe_action_self_seat_action_none,
			_unit_seat_keyframe_action_self_seat_action_exit_current,
			_unit_seat_keyframe_action_self_seat_action_enter_target,

			_unit_seat_keyframe_action_seat_action_self
		};

		enum unit_seat_keyframe_action_target_seat_unit_action : short
		{
			_unit_seat_keyframe_action_target_seat_unit_action_none,
			_unit_seat_keyframe_action_target_seat_unit_action_exit_seat,
			_unit_seat_keyframe_action_target_seat_unit_action_eject_from_seat,

			_unit_seat_keyframe_action_seat_action_target
		};

		enum unit_seat_keyframe_action_unit_door_action : short
		{
			_unit_seat_keyframe_action_unit_door_action_neither,
			_unit_seat_keyframe_action_unit_door_action_open,
			_unit_seat_keyframe_action_unit_door_action_close,

			_unit_seat_keyframe_action_unit_door_action
		};

		enum unit_seat_keyframe_action_apply_damage_effect : short
		{
			_unit_seat_keyframe_action_apply_damage_effect_none,
			_unit_seat_keyframe_action_apply_damage_effect_mounted_unit,
			_unit_seat_keyframe_action_apply_damage_effect_mounted_unit_region,
			_unit_seat_keyframe_action_apply_damage_effect_seated_unit,

			_unit_seat_keyframe_action_apply_damage_effect
		};

		enum unit_seat_keyframe_action_apply_effect : short
		{
			_unit_seat_keyframe_action_apply_effect_none,
			_unit_seat_keyframe_action_apply_effect_mounted_unit,
			_unit_seat_keyframe_action_apply_effect_seated_unit,

			_unit_seat_keyframe_action_apply_effect
		};

		enum unit_seat_boarding_type : short
		{
			_unit_seat_boarding_type_immediate,
			_unit_seat_boarding_type_delayed,

			_unit_seat_boarding_type
		};

		enum unit_seat_boarding_vitality_threshold_source : short
		{
			_unit_seat_boarding_vitality_threshold_source_mounted_unit,
			_unit_seat_boarding_vitality_threshold_source_seated_unit,

			_unit_seat_boarding_vitality_threshold_source
		};

		enum unit_seat_damage_melee : short
		{
			_unit_seat_damage_melee_normal,
			_unit_seat_damage_melee_mounted_unit,
			_unit_seat_damage_melee_target_seat_unit,

			_unit_seat_damage_melee
		};

		enum unit_seat_damage_grenade : short
		{
			_unit_seat_damage_grenade_normal,
			_unit_seat_damage_grenade_disabled,
			_unit_seat_damage_grenade_plant_on_mounted_unit,
			_unit_seat_damage_grenade_plant_on_target_seat_unit,

			_unit_seat_damage_grenade
		};
	};
	
	namespace Flags
	{
		enum unit_mounted_state_flags
		{
			_unit_mounted_state_flags_third_person_camera,

			_unit_mounted_state_flags
		};

		enum unit_mounted_state_keyframe_action_flags
		{
			_unit_mounted_state_keyframe_action_flags_eject_mounted_units,

			_unit_mounted_state_keyframe_action_flags
		};

		enum unit_seat_access_flags
		{
			_unit_seat_access_flags_requires_target_seat_occupied_bit,
			_unit_seat_access_flags_enemy_access_only_bit,
			_unit_seat_access_flags_restrict_by_unit_sight_bit,
			_unit_seat_access_flags_restrict_by_mounting_unit_sight_bit,
			_unit_seat_access_flags_restrict_by_unit_shield_bit,
			_unit_seat_access_flags_restrict_by_unit_health_bit,
			_unit_seat_access_flags_restrict_by_ai_state_bit,

			_unit_seat_access_flags
		};

		enum unit_seat_extensions_flags
		{
			_unit_seat_extensions_flags_triggers_mounted_state_bit,
			_unit_seat_extensions_flags_exit_on_unit_death_bit,
			_unit_seat_extensions_flags_exit_on_target_seat_empty_bit,
			_unit_seat_extensions_flags_prevent_death_when_unit_dies,
			_unit_seat_extensions_flags_ignored_by_seated_ai_bit,
			_unit_seat_extensions_flags_ignored_by_mounted_ai_bit,
			_unit_seat_extensions_flags_cant_enter_seats_when_occupied_bit,

			_unit_seat_extensions_flags
		};

		enum unit_seat_keyframe_action_flags
		{
			_unit_seat_keyframe_action_flags_control_powered_seat_bit,

			_unit_seat_keyframe_action_flags
		};

		enum unit_seat_boarding_delay_until_flags
		{
			_unit_seat_boarding_delay_until_flags_empty_target_seat_bit,
			_unit_seat_boarding_delay_until_flags_unit_shield_threshold_bit,
			_unit_seat_boarding_delay_until_flags_unit_health_threshold_bit,
			_unit_seat_boarding_delay_until_flags_region_destroyed_bit,

			_unit_seat_boarding_delay_until_flags
		};

		enum unit_seat_damage_flags
		{
			_unit_seat_damage_flags_use_weapon_melee_bit,
			_unit_seat_damage_flags_exit_after_grenade_plant_bit,

			_unit_seat_damage_flags
		};

		enum unit_seat_region_damage_flags
		{
			_unit_seat_region_damage_flags_disable_grenades_until_destroyed_bit,

			_unit_seat_region_damage_flags
		};
	};

	namespace TagGroups
	{
		struct s_unit_camera;

		struct unit_mounted_state_keyframe_action
		{
			TAG_FIELD(Enums::unit_animation_keyframe, keyframe);
			TAG_FIELD(unsigned short, flags);
			TAG_FIELD(Enums::unit_seat_mounted_keyframe_action_target, target);
			unsigned short : 16;
			TAG_FIELD(tag_reference, damage_effect, "jpt!");
			TAG_FIELD(tag_reference, effect, "effe");
			TAG_FIELD(tag_string, effect_marker);
			TAG_PAD(tag_block, 2);
		}; static_assert(sizeof(unit_mounted_state_keyframe_action) == 0x60);

		struct unit_mounted_state
		{
			TAG_FIELD(unsigned short, flags);
			unsigned short : 16;
			TAG_FIELD(s_unit_camera, unit_camera);
			TAG_TBLOCK(keyframe_actions, unit_mounted_state_keyframe_action);
			TAG_PAD(tag_block, 2);
		}; static_assert(sizeof(unit_mounted_state) == 0x80);

		struct unit_extensions
		{
			TAG_TBLOCK(mounted_state, unit_mounted_state);
			TAG_PAD(tag_block, 4);
		}; static_assert(sizeof(unit_extensions) == 0x3C);


		struct unit_seat_keyframe_action
		{
			TAG_FIELD(Enums::unit_animation_keyframe, keyframe);
			TAG_FIELD(unsigned short, flags);
			TAG_FIELD(Enums::unit_seat_keyframe_action_self_seat_action, self_seat_action);
			TAG_FIELD(Enums::unit_seat_keyframe_action_target_seat_unit_action, target_seat_unit_action);
			TAG_FIELD(Enums::unit_seat_keyframe_action_unit_door_action, unit_door_action);
			unsigned short : 16;

			TAG_FIELD(Enums::unit_seat_keyframe_action_apply_damage_effect, apply_damage_to);
			TAG_FIELD(short, region_index);
			TAG_FIELD(tag_string, region_name);
			TAG_FIELD(tag_reference, damage_effect, "jpt!");

			TAG_FIELD(Enums::unit_seat_keyframe_action_apply_effect, apply_effect_to);
			unsigned short : 16;
			TAG_FIELD(tag_reference, effect, "effe");
			TAG_FIELD(tag_string, effect_marker);
			TAG_PAD(tag_block, 3);
		}; static_assert(sizeof(unit_seat_keyframe_action) == 0x98);

		struct unit_seat_boarding
		{
			TAG_FIELD(Enums::unit_seat_boarding_type, boarding_type);
			TAG_FIELD(unsigned short, delay_until);
			TAG_FIELD(Enums::unit_seat_boarding_vitality_threshold_source, unit_vitality_source);
			unsigned short : 16;
			TAG_FIELD(real_fraction, unit_shield_threshold);
			TAG_FIELD(real_fraction, unit_health_threshold);
			unsigned short : 16;
			TAG_FIELD(short, region_index);
			TAG_FIELD(tag_string, region_name);
			TAG_PAD(tag_block, 2);
			TAG_TBLOCK(keyframe_actions, unit_seat_keyframe_action);
			TAG_PAD(tag_block, 2);
		}; static_assert(sizeof(unit_seat_boarding) == 0x70);

		struct unit_seat_damage
		{
			TAG_FIELD(unsigned short, flags);
			TAG_FIELD(Enums::unit_seat_damage_melee, melee);
			TAG_FIELD(tag_reference, melee_damage_effect, "jpt!");
			TAG_FIELD(Enums::unit_seat_damage_grenade, grenade);
			TAG_FIELD(unsigned short, disabled_grenade_types);
			TAG_FIELD(real, grenade_detonation_time_scale);
			TAG_FIELD(tag_string, grenade_marker);
			TAG_FIELD(unsigned short, region_flags);
			TAG_FIELD(short, region_index);
			TAG_FIELD(tag_string, region_name);
			TAG_FIELD(tag_reference, region_damage_effect, "jpt!");
			TAG_PAD(tag_block, 2);
		}; static_assert(sizeof(unit_seat_damage) == 0x88);

		struct unit_seat_access
		{
			TAG_FIELD(unsigned short, flags);
			unsigned short : 16;
			TAG_FIELD(angle, unit_sight_angle);
			TAG_FIELD(tag_string, unit_sight_marker);
			TAG_FIELD(angle, mounting_unit_sight_angle);
			TAG_FIELD(tag_string, mounting_unit_sight_marker);
			TAG_FIELD(real_fraction, unit_shield_threshold);
			TAG_FIELD(real_fraction, unit_health_threshold);
			TAG_FIELD(unsigned short, permitted_ai_states);
			unsigned short : 16;
			TAG_PAD(tag_block, 3);
		}; static_assert(sizeof(unit_seat_access) == 0x7C);

		struct unit_seat_extensions
		{
			TAG_FIELD(unsigned short, flags);
			TAG_FIELD(short, target_seat_index);
			TAG_TBLOCK(seat_targeting_seats, short);
			TAG_TBLOCK(seat_access, unit_seat_access);
			TAG_TBLOCK(seat_boarding, unit_seat_boarding);
			TAG_TBLOCK(seat_damage, unit_seat_damage);
			TAG_PAD(tag_block, 4);
		}; static_assert(sizeof(unit_seat_extensions) == 0x64);
	};
};
