/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo {
	namespace Enums {
		enum {
			k_max_sound_references_per_graph         = 257,
			k_max_sound_references_per_graph_upgrade = k_max_sound_references_per_graph * 2,

			// Halo2's unit_seat block was refactored to animation_mode
				k_max_unit_seat_modes_per_graph         = 32,
				k_max_unit_seat_modes_per_graph_upgrade = 512, // Halo2's amount

			k_max_animations_per_graph         = 256,
			// must be <= k_maximum_tool_import_files_upgrade
			k_max_animations_per_graph_upgrade = 2048,
		};

		enum model_animation_type {
			_model_animation_type_base,         // _animation_base
			_model_animation_type_overlay,
			_model_animation_type_replacement,

			k_number_of_model_animation_types
		};

		enum weapon_type_animation {
			_weapon_type_animation_reload1,
			_weapon_type_animation_reload2,
			_weapon_type_animation_chamber1,
			_weapon_type_animation_chamber2,
			_weapon_type_animation_fire1,
			_weapon_type_animation_fire2,
			_weapon_type_animation_charged1,
			_weapon_type_animation_chareged2,
			_weapon_type_animation_melee,
			_weapon_type_animation_overheat,

			k_number_of_weapon_type_animations,
		};
		enum weapon_class_animation {
			_weapon_class_animation_idle,
			_weapon_class_animation_gesture,
			_weapon_class_animation_turn_left,
			_weapon_class_animation_turn_right,
			_weapon_class_animation_dive_front,
			_weapon_class_animation_dive_back,
			_weapon_class_animation_dive_left,
			_weapon_class_animation_dive_right,
			_weapon_class_animation_move_front,
			_weapon_class_animation_move_back,
			_weapon_class_animation_move_left,
			_weapon_class_animation_move_right,
			_weapon_class_animation_slide_front,
			_weapon_class_animation_slide_back,
			_weapon_class_animation_slide_left,
			_weapon_class_animation_slide_right,
			_weapon_class_animation_airborne,
			_weapon_class_animation_land_soft,
			_weapon_class_animation_land_hard,
			_weapon_class_animation_unused19,
			_weapon_class_animation_throw_grenade,
			_weapon_class_animation_disarm,
			_weapon_class_animation_drop,
			_weapon_class_animation_ready,
			_weapon_class_animation_put_away,
			_weapon_class_animation_aim_still,
			_weapon_class_animation_aim_move,
			_weapon_class_animation_surprise_front,
			_weapon_class_animation_surprise_back,
			_weapon_class_animation_berserk,
			_weapon_class_animation_evade_left,
			_weapon_class_animation_evade_right,
			_weapon_class_animation_signal_move,
			_weapon_class_animation_signal_attack,
			_weapon_class_animation_warn,
			_weapon_class_animation_stunned_front,
			_weapon_class_animation_stunned_back,
			_weapon_class_animation_stunned_left,
			_weapon_class_animation_stunned_right,
			_weapon_class_animation_melee,
			_weapon_class_animation_celebrate,
			_weapon_class_animation_panic,
			_weapon_class_animation_melee_airborne,
			_weapon_class_animation_flaming,
			_weapon_class_animation_resurrect_front,
			_weapon_class_animation_resurrect_back,
			_weapon_class_animation_melee_continuous,
			_weapon_class_animation_feeding,
			_weapon_class_animation_leap_start,
			_weapon_class_animation_leap_airborne,
			_weapon_class_animation_leap_melee,
			_weapon_class_animation_zapping,
			_weapon_class_animation_unused52,
			_weapon_class_animation_unused53,
			_weapon_class_animation_unused54,

			k_number_of_weapon_class_animations,
		};

		enum unit_seat_animation : short {
			_unit_seat_animation_airborne_dead,
			_unit_seat_animation_landing_dead,
			_unit_seat_animation_acc_front_back,
			_unit_seat_animation_acc_left_right,
			_unit_seat_animation_acc_up_down,
			_unit_seat_animation_push,
			_unit_seat_animation_twist,
			_unit_seat_animation_enter,
			_unit_seat_animation_exit,
			_unit_seat_animation_look,
			_unit_seat_animation_talk,
			_unit_seat_animation_emotions,
			_unit_seat_animation_unused12,
			_unit_seat_animation_user0,
			_unit_seat_animation_user1,
			_unit_seat_animation_user2,
			_unit_seat_animation_user3,
			_unit_seat_animation_user4,
			_unit_seat_animation_user5,
			_unit_seat_animation_user6,
			_unit_seat_animation_user7,
			_unit_seat_animation_user8,
			_unit_seat_animation_user9,
			_unit_seat_animation_flying_front,
			_unit_seat_animation_flying_back,
			_unit_seat_animation_flying_left,
			_unit_seat_animation_flying_right,
			_unit_seat_animation_opening,
			_unit_seat_animation_closing,
			_unit_seat_animation_hovering,

			k_number_of_unit_seat_animations,

			// yelo animation states
				_unit_seat_animation_yelo_boarding = k_number_of_unit_seat_animations,
				_unit_seat_animation_yelo_ejecting,
				_unit_seat_animation_yelo_mounted,

			k_number_of_unit_seat_animations_yelo,
		};

		enum vehicle_animation {
			_vehicle_animation_steering,
			_vehicle_animation_roll,
			_vehicle_animation_throttle,
			_vehicle_animation_velocity,
			_vehicle_animation_braking,
			_vehicle_animation_ground_speed,
			_vehicle_animation_occupied,
			_vehicle_animation_unoccupied,

			k_number_of_vehicle_animations,
		};

		enum device_animation {
			_device_animation_position,
			_device_animation_power,

			k_number_of_device_animations,
		};

		enum first_person_weapon_animation {
			_first_person_weapon_animation_idle,
			_first_person_weapon_animation_posing,
			_first_person_weapon_animation_fire1,
			_first_person_weapon_animation_moving,
			_first_person_weapon_animation_overlays,
			_first_person_weapon_animation_light_off,
			_first_person_weapon_animation_light_on,
			_first_person_weapon_animation_reload_empty,
			_first_person_weapon_animation_reload_full,
			_first_person_weapon_animation_overheated,
			_first_person_weapon_animation_ready,
			_first_person_weapon_animation_put_away,
			_first_person_weapon_animation_overcharged,
			_first_person_weapon_animation_melee,
			_first_person_weapon_animation_fire2,
			_first_person_weapon_animation_overcharged_jitter,
			_first_person_weapon_animation_throw_grenade,
			_first_person_weapon_animation_ammunition,
			_first_person_weapon_animation_misfire1,
			_first_person_weapon_animation_misfire2,
			_first_person_weapon_animation_throw_overheated,
			_first_person_weapon_animation_overheating,
			_first_person_weapon_animation_overheating_again,
			_first_person_weapon_animation_enter,
			_first_person_weapon_animation_exit_empty,
			_first_person_weapon_animation_exit_full,
			_first_person_weapon_animation_overheating_exit, // o-h-exit
			_first_person_weapon_animation_overheating_enter,// o-h-s-enter

			k_number_of_first_person_weapon_animations,
		};
	};

	namespace TagGroups {
		struct animation_graph_weapon_type {
			tag_string label;
			long:8 * sizeof(long) * 4;
			Yelo::TagBlock<const short> animations; // block index to model_animation
		};
		static_assert( sizeof(animation_graph_weapon_type) == 0x3C ); // max count: 16
		struct animation_graph_weapon {
			tag_string name;
			tag_string grip_marker;
			tag_string hand_marker;

			////////////////////////////////////////////////////////////////
			// aiming screen bounds
			angle right_yaw_per_frame;
			angle left_yaw_per_frame;
			short right_frame_count;
			short left_frame_count;
			angle down_pitch_per_frame;
			angle up_pitch_per_frame;
			short down_pitch_frame_count;
			short up_pitch_frame_count;
			long:8 * sizeof(long) * 8;
			Yelo::TagBlock<const short> animations; // block index to model_animation
			tag_block ik_points;
			Yelo::TagBlock<const animation_graph_weapon_type> weapon_types;
		};
		static_assert( sizeof(animation_graph_weapon) == 0xBC ); // max count: 16
		struct animation_graph_unit_seat {
			tag_string label;

			////////////////////////////////////////////////////////////////
			// looking screen bounds
			angle right_yaw_per_frame;
			angle left_yaw_per_frame;
			short right_frame_count;
			short left_frame_count;
			angle down_pitch_per_frame;
			angle up_pitch_per_frame;
			short down_pitch_frame_count;
			short up_pitch_frame_count;
			long:8 * sizeof(long) * 2;
			Yelo::TagBlock<const short> animations; // block index to model_animation
			tag_block ik_points;
			Yelo::TagBlock<const animation_graph_weapon> weapons;
		};
		static_assert( sizeof(animation_graph_unit_seat) == 0x64 ); // max count: 32
		struct model_animation {
			tag_string name;
			short type;
			short frame_count;
			short frame_size;
			short frame_info_type;
			long node_list_checksum;
			short node_count;
			short loop_frame_index;
			real_fraction weight;
			short key_frame_index;
			short second_key_frame_index;
			short next_animation;
			struct _flags {
				unsigned short compressed_data_bit:1;
				unsigned short world_relative_bit:1;
				unsigned short _25Hz_PAL_bit:1;
			} flags;
			static_assert( sizeof(_flags) == sizeof(unsigned short) );
			short sound;
			short sound_frame_index;
			sbyte left_foot_frame_index;
			sbyte right_foot_frame_index;
			//////////////////////////////////////////////////////////////////////////
			// postprocessed fields (thus, not exposed to the editor)
			short         first_animation; // if this is a permutated animation, this represents the first animation (first animation will also have this set)
			real_fraction random_fraction;
			//////////////////////////////////////////////////////////////////////////
			tag_data frame_info;
			long node_trans_flag_data1;
			long node_trans_flag_data2;
			byte:8 * sizeof(byte) * 8;
			long node_rotation_flag_data1;
			long node_rotation_flag_data2;
			byte:8 * sizeof(byte) * 8;
			long node_scale_flag_data1;
			long node_scale_flag_data2;
			byte:8 * sizeof(byte) * 4;
			long offset_to_compressed_data;
			tag_data default_data;
			tag_data frame_data;
		};
		static_assert( sizeof(model_animation) == 0xB4 );
		struct model_animation_graph {
			enum { k_group_tag = 'antr' };

			tag_block objects;
			Yelo::TagBlock<const animation_graph_unit_seat> units;
			tag_block weapons;
			tag_block vehicles;
			tag_block devices;
			tag_block unit_damage;
			tag_block first_person_weapons;
			tag_block sound_references;
			real limp_body_node_radius;
			struct _flags {
				unsigned short compress_all_animations_bit:1;
				unsigned short force_idle_compression_bit:1;
			} flags;
			static_assert( sizeof(_flags) == sizeof(unsigned short) );
			unsigned short : 16;
			tag_block nodes;
			Yelo::TagBlock<const model_animation> animations;
		};
		static_assert( sizeof(model_animation_graph) == 0x80 );
	};
};
