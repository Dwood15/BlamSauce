#pragma once

#include <precompile.h>
#include "globals.hpp"

namespace Yelo::TagGroups {
	struct s_game_globals_difficulty_information {
		struct {
			real easy, normal, hard, impossible;
		} values[Enums::k_number_of_game_difficulty_values];
		long:8 * sizeof(long) * 17; // could potentially have 4 more difficulty values, with 4 bytes left over
	}; static_assert(sizeof(s_game_globals_difficulty_information) <= 0x284);

	struct s_game_globals_grenade {
		short maximum_count;
		short multiplayer_spawn_count; // PC only
		tag_reference throwing_effect;
		tag_reference hud_interface;
		tag_reference equipment;
		tag_reference projectile;
	}; static_assert(sizeof(s_game_globals_grenade) == 0x44);

	struct s_game_globals_tag_reference {
		tag_reference reference;
	};

	struct s_game_globals_multiplayer_information {
		tag_reference flag;
		tag_reference unit;
		Yelo::TagBlock<const s_game_globals_tag_reference> vehicles; // 20
		tag_reference hill_shader;
		tag_reference flag_shader;
		tag_reference ball;
		Yelo::TagBlock<const s_game_globals_tag_reference> sounds; // 60
		long:8 * sizeof(long) * 14;
	}; static_assert(sizeof(s_game_globals_multiplayer_information) == 0xA0);

	struct s_game_globals_player_information {
		tag_reference unit;
		  PAD_TYPE(tag_reference);
		struct {
			unsigned long : 32;
			unsigned long : 32;
			unsigned long : 32;
			real speed;
		} walk;
		real double_speed_multiplier;
		struct {
			real forward;
			real backward;
			real sideways;
			real acceleration;
		} run,
		  sneak;
		real airborne_acceleration;
		  PAD_TYPE(tag_reference);
		real_point3d grenade_origin;
		PAD_TYPE(real_point3d);
		struct _stun {
			real movement_penalty;
			real turning_penalty;
			real jumping_penalty;
			real minimum_time;
			real maximum_time;
		} stun;                                       // 0x80
		PAD_TYPE(real_bounds);
		struct {
			real_bounds idle_time;
			real_fraction skip_fraction;
		} first_person;
		  PAD_TYPE(tag_reference);
		tag_reference coop_respawn_effect; // 0xB8
		long:8 * sizeof(long) * 11;
	}; static_assert(sizeof(s_game_globals_player_information) == 0xF4);

	struct s_game_globals_player_representation // game_globals_first_person_interface
	{
		tag_reference fp_hands;
		tag_reference base_bitmap;
		struct {
			tag_reference meter;
			point2d meter_origin;
		} shield, body;
		struct {
			tag_reference off_on_effect;
			tag_reference on_off_effect;
		} night_vision;
		long:8 * sizeof(long) * 22;
	}; static_assert(sizeof(s_game_globals_player_representation) == 0xC0);

	struct s_game_globals_falling_damage {
		PAD64;
		real_bounds harmful_falling_distance;
		tag_reference falling_damage;
		PAD64;
		real maximum_falling_distance;
		tag_reference distance_damage;
		tag_reference vehicle_environment_collision_damage_effect;
		tag_reference vehicle_killed_unit_damage_effect;
		tag_reference vehicle_collision_damage;
		tag_reference flaming_death_damage;
		  PAD_TYPE(tag_reference);

		struct { // multiply the tag values by 0.0071303584f, and you get these runtime values
			real        maximum_falling_distance;
			real_bounds harmful_falling_distance;
		} runtime;
	}; static_assert(sizeof(s_game_globals_falling_damage) == 0x98);

	struct material_definition {
		long:8 * sizeof(long) * 25;
		long:8 * sizeof(long) * 12;
		struct {
			real ground_friction_scale;
			real ground_friction_normal_k1_scale;
			real ground_friction_normal_k0_scale;
			real ground_depth_scale;
			real ground_damp_fraction_scale;
		} vehicle_terrain_params;
		long:8 * sizeof(long) * 19;
		long:8 * sizeof(long) * 120;
		struct {
			real maximum_vitality;
			PAD64;
			unsigned long : 32;
			tag_reference effect;
			tag_reference sound;
			long:8 * sizeof(long) * 6;
			tag_block particle_effects;
		} breakable_surface_params;
		long:8 * sizeof(long) * 15;
		tag_reference melee_hit_sound;
	}; static_assert(sizeof(material_definition) == 0x374);

	struct s_game_globals {
		enum { k_group_tag = 'matg' };

		long_enum language;

		byte:8 * sizeof(byte) * 244;

		Yelo::TagBlock<const tag_reference> sounds;
		Yelo::TagBlock<const tag_reference> camera;

		tag_block:8 * sizeof(tag_block) * 1; // s_game_globals_player_control

		Yelo::TagBlock<const s_game_globals_difficulty_information> difficulty_info;
		Yelo::TagBlock<const s_game_globals_grenade> grenades;

		tag_block:8 * sizeof(tag_block) * 1 + 1; // s_game_globals_interface_tag_references

		Yelo::TagBlock<const s_game_globals_tag_reference> weapons_list;
		Yelo::TagBlock<const s_game_globals_tag_reference> cheat_powerups;
		Yelo::TagBlock<s_game_globals_multiplayer_information> multiplayer_info;
		Yelo::TagBlock<const s_game_globals_player_information> player_info;
		Yelo::TagBlock<const s_game_globals_player_representation> player_representation;
		Yelo::TagBlock<const s_game_globals_falling_damage> falling_damage;
		Yelo::TagBlock<const material_definition> materials;
		tag_block playlist_members;
	}; static_assert(sizeof(s_game_globals) == 0x1AC);
};
};
