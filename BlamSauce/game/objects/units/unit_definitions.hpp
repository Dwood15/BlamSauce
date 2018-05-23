/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>
#include "unit_camera.hpp"
#include "unit_definitions_yelo.hpp"
#include "../object_definitions.hpp"

namespace Yelo {
	namespace Enums {
		enum tag_postprocess_mode : byte_enum;

		enum {
			k_maximum_weapons_per_unit = 4,
		};

		enum powered_seat {
			_powered_seat_driver,
			_powered_seat_gunner,

			k_number_of_powered_seats
		};

		enum unit_base_seat {
			_unit_base_seat_asleep,
			_unit_base_seat_alert,
			//_unit_base_seat_aware, PLATFORM_IS_STUBBS
			_unit_base_seat_stand,
			_unit_base_seat_crouch,
			_unit_base_seat_flee,
			_unit_base_seat_flaming,
			//_unit_base_seat_maimed, PLATFORM_IS_STUBBS
			k_number_of_unit_base_seats,
		};

		enum unit_base_weapon {
			_unit_base_weapon_unarmed,
			k_number_of_unit_base_weapons,
		};
	};

	namespace Flags {
		enum unit_definition_flags {
			_unit_circular_aiming_bit,
			_unit_destroyed_after_dying_bit,
			_unit_half_speed_interpolation_bit,
			_unit_fires_from_camera_bit,
			_unit_entrance_inside_bounding_sphere_bit,
			_unit_unused5_bit,                     // Halo2: 'doesn't show readied weapon'
			_unit_causes_passenger_dialogue_bit,
			_unit_resists_pings_bit,
			_unit_melee_attack_is_fatal_bit,
			_unit_dont_reface_during_pings_bit,
			_unit_has_no_aiming_bit,
			_unit_simple_creature_bit,
			_unit_impact_melee_attaches_to_unit_bit,
			_unit_impact_melee_dies_on_shields_bit,
			_unit_cannot_open_doors_automaticlly_bit,
			_unit_melee_attackers_cannot_attach_bit,
			_unit_not_instantly_killed_by_melee_bit,
			_unit_shield_sapping_bit,
			_unit_runs_around_flaming_bit,
			_unit_inconsequential_bit,
			_unit_special_cinematic_unit_bit,
			_unit_ignored_by_autoaiming_bit,
			_unit_shields_fry_infection_forms_bit,
			_unit_integrated_light_controls_weapon_bit,   // Halo2: unused
			_unit_integrated_light_lasts_forever_bit,   // Halo2: unused
			_unit_reserved25_bit,                  // Halo2: acts as gunner for parent
			_unit_reserved26_bit,                  // Halo2: controlled by parent gunner
			_unit_reserved27_bit,                  // Halo2: parent's primary weapon
			_unit_reserved28_bit,                  // Halo2: unit has boost
			_unit_unused29_bit,
			_unit_unused30_bit,
			_unit_has_boarding_seats_yelo_bit,         // YELO: set by postprocess proc, for runtime

			k_number_of_unit_definition_flags
		};
		static_assert(k_number_of_unit_definition_flags <= BIT_COUNT(unsigned long));

		enum unit_seat_definition_flags {
			_unit_seat_invisable_bit,
			_unit_seat_locked_bit,
			_unit_seat_driver_bit,
			_unit_seat_gunner_bit,
			_unit_seat_third_person_camera_bit,
			_unit_seat_allows_weapons_bit,
			_unit_seat_third_person_on_enter_bit,
			_unit_seat_first_person_camera_slaved_to_gun_bit,
			_unit_seat_allow_vehicle_communication_anims_bit,
			_unit_seat_not_valid_without_driver_bit,
			_unit_seat_allow_ai_noncombatants_bit,

			k_number_of_unit_seat_definition_flags,

			_unit_seat_reserved11_bit =            // Halo2
			k_number_of_unit_seat_definition_flags,
			_unit_seat_reserved12_bit,               // Halo2: ai firing disabled by max acceleration
			_unit_seat_reserved13_bit,      // Halo2
			_unit_seat_reserved14_bit,   // Halo2
			_unit_seat_reserved15_bit,      // Halo2
			_unit_seat_reserved16_bit,   // Halo2: invalid for player
			_unit_seat_reserved17_bit,   // Halo2: invalid for non-player
			_unit_seat_reserved18_bit,   // Halo2: gunner (player only)
			_unit_seat_reserved19_bit,   // Halo2: invisible under major damage
			_unit_seat_allows_melee_bit,   // YELO

			k_number_of_unit_seat_definition_flags_yelo,
		};
		static_assert(k_number_of_unit_seat_definition_flags_yelo <= BIT_COUNT(unsigned long));
	};

	namespace TagGroups {
		struct unit_seat_acceleration {
			real_vector3d seat_acceleration_scale;
			unsigned long : 32;
			unsigned long : 32;
			unsigned long : 32;
		};

		struct unit_hud_reference {
			tag_reference unit_hud_interface;
			byte uhr_pad0[sizeof(long) * (8)]; // 32
		};

		struct dialogue_variant_definition {
			short varient_number;
			unsigned short : 16;
			unsigned long : 32;
			tag_reference dialogue;
		};

		struct powered_seat_definition {
			unsigned long : 32;
			real driver_powerup_time;
			real driver_powerdown_time;
			byte psd_pad0[sizeof(long) * (14)]; // 56
		};

		struct unit_initial_weapon {
			tag_reference weapon;
			byte uiwpad0[sizeof(long) * (4)]; // 20
		};

		struct unit_seat {
			unsigned long flags;
			tag_string label;
			tag_string marker_name;
			byte uspad0[sizeof(tag_string)]; // 32
			unit_seat_acceleration acceleration;

			real yaw_rate;
			real pitch_rate;

			s_unit_camera unit_camera;
			Yelo::TagBlock<const unit_hud_reference> unit_hud_interface;
			byte uspad01[sizeof(long)]; // 4
			short hud_text_message_index;
			unsigned short : 16;

			real yaw_min;
			real yaw_max;

			tag_reference built_in_gunner;

			Yelo::TagBlock<const unit_seat_extensions> seat_extensions;
			byte uspad02[sizeof(long) * (2)]; // 8

		private:
			bool Postprocess(Enums::tag_postprocess_mode mode, datum_index tag_index);

		public:
			static bool __cdecl Postprocess(void *element, Enums::tag_postprocess_mode mode, datum_index tag_index);
		};

		static_assert(sizeof(unit_seat) == 284);

		//////////////////////////////////////////////////////////////////////////
		struct _unit_definition {
			unsigned long flags;
			short default_team;
			short constant_sound_volume;

			real rider_damage_fraction;

			tag_reference integrated_light_toggle;

			short function_exports[Enums::k_number_of_incoming_object_functions]; // Enums::unit_function_mode

			real camera_fov;
			real camera_stiffness;
			s_unit_camera unit_camera;

			unit_seat_acceleration acceleration;

			real soft_ping_threshold;
			real soft_ping_interrupt_time;

			real hard_ping_threshold;
			real hard_ping_interrupt_time;

			real hard_death_threshold;
			real feign_death_threshold;
			real feign_death_time;

			real distance_of_evade_anim;
			real distance_of_dive_anim;
			unsigned long : 32;

			real stunned_movement_threshold;
			real feign_death_chance;
			real feign_repeat_chance;

			tag_reference spawned_actor;
			short_bounds spawned_actor_count;
			real spawned_velocity;

			real aiming_velocity_max;
			real aiming_acceleration_max;
			real casual_aiming_modifier;

			real looking_velocity_max;
			real looking_acceleration_max;
			unsigned long : 32;
			unsigned long : 32;

			real ai_vehicle_radius;
			real ai_danger_radius;

			tag_reference melee_damage;

			short blip_type;
			unsigned short : 16;

			Yelo::TagBlock<const unit_extensions> extensions;

			Yelo::TagBlock<const unit_hud_reference> new_hud_interfaces;
			Yelo::TagBlock<const dialogue_variant_definition> dialogue_variants;

			real grenade_velocity;
			short grenade_type;
			short grenade_count;

			struct { // tag value * 30f
				short soft;
				short hard;
			}     runtime_ping_interrupt_time;

			Yelo::TagBlock<const powered_seat_definition> powered_seats;
			Yelo::TagBlock<const unit_initial_weapon> weapons;
			Yelo::TagBlock<const unit_seat> seats;

			bool Postprocess(Enums::tag_postprocess_mode mode, datum_index tag_index);

		};

		static_assert(sizeof(_unit_definition) == 0x174);

		struct s_unit_definition : s_object_definition {
			enum { k_group_tag = 'unit' };

			_unit_definition unit;

			bool Postprocess(Enums::tag_postprocess_mode mode, datum_index tag_index) {
				return unit.Postprocess(mode, tag_index);
			}
		};
	};
};
