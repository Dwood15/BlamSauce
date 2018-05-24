#pragma once
#include <precompile.h>
#include "../cache/predicted_resources.hpp"
#include "item_definitions.h"

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_number_of_triggers_per_weapon = 2,
			k_maximum_number_of_magazines_per_weapon = 2,

			k_maximum_number_of_magazine_objects_per_magazine = 8,
		};
	};

	namespace TagGroups
	{
		struct aim_assist_parameters
		{
			angle autoaim_angle;
			real autoaim_range;
			angle magnetism_angle;
			real magnetism_range;
			angle deviation_angle;
			unsigned long : 32;
		};
		struct weapon_ammunition_object
		{
			short rounds;
			unsigned short : 16;
			unsigned __int64:64;;
			tag_reference equipment;
		}; static_assert( sizeof(weapon_ammunition_object) == 0x1C); // VS2012.2's intellisense is broken http://connect.microsoft.com/VisualStudio/feedback/details/745237/invalid-byte-order-in-intellisense
		struct weapon_magazine_definition
		{
			struct _flags {
				unsigned long wastes_rounds_when_reloaded_bit:1;
				unsigned long every_round_must_be_chambered_bit:1;
			}flags; static_assert( sizeof(_flags) == sizeof(unsigned long) );
			short rounds_recharged;
			short rounds_total_initial;
			short rounds_total_maximum;
			short rounds_loaded_maximum;
			long:8 * sizeof(long) * 2;
			real reload_time;
			short rounds_reloaded;
			unsigned short : 16;
			real chamber_time;
			long:8 * sizeof(long) * 2;
			tag_reference:8 * sizeof(tag_reference) * 1;
			tag_reference reloading_effect;
			tag_reference chambering_effect;
			tag_block:8 * sizeof(tag_block) * 1;
			Yelo::TagBlock<const weapon_ammunition_object> magazines;
		}; static_assert( sizeof(weapon_magazine_definition) == 0x70);
		struct weapon_trigger_firing_effect
		{
			short_bounds shot_count;
			tag_string:8 * sizeof(tag_string) * 1;
			tag_reference firing_effect;
			tag_reference misfire_effect;
			tag_reference empty_effect;
			tag_reference firing_damage;
			tag_reference misfire_damage;
			tag_reference empty_damage;
		}; static_assert( sizeof(weapon_trigger_firing_effect) == 0x84);
		struct weapon_trigger_definition
		{
			struct _flags{
				unsigned long tracks_fired_projectile_bit:1;
				unsigned long random_firing_effects_bit:1;
				unsigned long can_fire_with_partial_ammo_bit:1;
				unsigned long does_not_repeat_automatically_bit:1;
				unsigned long locks_in_on_off_state_bit:1;
				unsigned long projectiles_use_weapon_origin_bit:1;
				unsigned long sticks_when_dropped_bit:1;
				unsigned long ejects_during_chamber_bit:1;
				unsigned long discharging_spews_bit:1;
				unsigned long analog_rate_of_fire_bit:1;
				unsigned long use_error_when_unzoomed_bit:1;
				unsigned long projectile_vector_cannot_be_adjusted_bit:1;
				unsigned long projectiles_have_identical_error_bit:1;
				unsigned long projectile_is_client_side_only_bit:1; // added in HaloPC
			}flags; static_assert( sizeof(_flags) == sizeof(unsigned long) );

			//firing
			real_bounds rounds_per_second;
			real firing_acceleration_time;
			real firing_deceleration_time;
			real_fraction blurred_rate_of_fire;
			long:8 * sizeof(long) * 2;
			short magazine;
			short rounds_per_shot;
			short minimum_rounds_loaded;
			short rounds_between_tracers;
			unsigned long : 32;
			unsigned short : 16;
			short firing_noise;

			//error
			real_bounds error;
			real error_acceleration_time;
			real error_deceleration_time;
			long:8 * sizeof(long) * 2;

			//charging
			real charging_time;
			real charged_time;
			short overcharged_action;
			unsigned short : 16;
			real charged_illumination;
			real spew_time;
			tag_reference charging_effect;

			//projectile
			short distribution_function;
			short projectiles_per_shot;
			real distribution_angle;
			unsigned long : 32;
			angle minimum_error;
			angle_bounds error_angle;
			real_point3d first_person_offset;
			unsigned long : 32;
			tag_reference projectile;

			//misc
			real ejection_port_recovery_time;
			real illumination_recovery_time;
			long:8 * sizeof(long) * 3;
			real_fraction heat_generated_per_round;
			real_fraction age_generated_per_round;
			real_fraction age_generated_while_charged;
			real overload_time;
			long:8 * sizeof(long) * 2;
			tag_string:8 * sizeof(tag_string) * 1;
			struct { // all times are in game ticks (source fields are in seconds)
				real illumination_recovery_time;
				real ejection_port_recovery_time;
				real firing_acceleration_time;
				real firing_deceleration_time;
				real error_acceleration_time;
				real error_deceleration_time;
			}postprocessed;
			Yelo::TagBlock<const weapon_trigger_firing_effect> firing_effects;
		}; static_assert( sizeof(weapon_trigger_definition) == 0x114);
		struct _weapon_definition
		{
			struct _flags {
				unsigned long vertical_heat_display_bit:1;
				unsigned long mutually_exclusive_triggers_bit:1;
				unsigned long attacks_automatically_on_bump_bit:1;
				unsigned long must_be_readied_bit:1;
				unsigned long doesnt_count_toward_maximum_bit:1;
				unsigned long aim_assists_only_when_zoomed_bit:1;
				unsigned long prevents_grenade_throwing_bit:1;
				unsigned long must_be_picked_up_bit:1;
				unsigned long holds_triggers_when_dropped_bit:1;
				unsigned long prevents_melee_attack_bit:1;
				unsigned long detonates_when_dropped_bit:1;
				unsigned long cannot_fire_at_maximum_age_bit:1;
				unsigned long secondary_trigger_overrides_grenades_bit:1;
				unsigned long OBSOLETEdoes_not_depower_active_camo_in_multiplayer_bit:1;
				unsigned long enables_integrated_night_vision_bit:1;
				unsigned long AIs_use_weapon_melee_damage_bit:1;
				unsigned long third_person_weapon_bit:1;
			}flags; static_assert( sizeof(_flags) == sizeof(unsigned long) );
			tag_string label;
			short secondary_trigger_mode;
			short maximum_alternate_shots_loaded;

			short function_exports[Enums::k_number_of_incoming_object_functions];
			real ready_time;
			tag_reference ready_effect;

			//heat
			real_fraction heat_recovery_threshold;
			real_fraction overheated_threshold;
			real_fraction heat_detonation_threshold;
			real_fraction heat_detonation_fraction;
			real_fraction heat_loss_per_second;
			real_fraction heat_illumination;
			long:8 * sizeof(long) * 4;
			tag_reference overheated;
			tag_reference detonation;
			tag_reference player_melee_damage;
			tag_reference player_melee_response;
			long:8 * sizeof(long) * 2;

			//actor firing parameters
			tag_reference actor_firing_parameters;

			//reticle
			real near_reticle_range;
			real far_reticle_range;
			real intersection_reticle_range;

			//zoom
			unsigned short : 16;
			short magnification_levels;
			real_bounds magnification_range;

			aim_assist_parameters aim_assist;

			//movement
			short movement_penalized;
			unsigned short : 16;
			real_fraction forward_movement_penalty;
			real_fraction sideways_movement_penalty;
			unsigned long : 32;

			//AI targeting parameters
			real minimum_target_range;
			real looking_time_modifier;
			unsigned long : 32;

			//miscellaneous
			real light_power_on_time;
			real light_power_off_time;
			tag_reference light_power_on_effect;
			tag_reference light_power_off_effect;
			real age_heat_recovery_penalty;
			real age_rate_of_fire_penalty;
			real_fraction age_misfire_start;
			real_fraction age_misfire_chance;
			long:8 * sizeof(long) * 3;

			//interface
			tag_reference first_person_model;
			tag_reference first_person_animations;
			long: 32;
			tag_reference hud_interface;
			tag_reference pickup_sound;
			tag_reference zoom_in_sound;
			tag_reference zoom_out_sound;
			tag_block:8 * sizeof(tag_block) * 1;
			real active_camo_ding;
			real active_camo_regrowth_rate;
			long:8 * sizeof(long) * 3;

			//more miscellaneous
			unsigned short : 16;
			short weapon_type;
			Yelo::TagBlock<const predicted_resource> predicted_resources;
			Yelo::TagBlock<const weapon_magazine_definition> magazines;
			Yelo::TagBlock<const weapon_trigger_definition> triggers;
		}; static_assert( sizeof(_weapon_definition) == 0x200);

		struct s_weapon_definition : s_item_definition
		{
			enum { k_group_tag = 'weap' };

			_weapon_definition weapon;
		}; static_assert( sizeof(s_weapon_definition) == 0x508);
	};
};
