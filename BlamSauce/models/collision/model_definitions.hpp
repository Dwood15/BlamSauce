#pragma once

#include <precompile.h>
#include "../../effects/material/material_effect_definitions.hpp"
#include "../../math/periodic_functions.h"

namespace Yelo
{
	namespace Enums
	{
		enum damage_part {
			// pelvis
			_damage_part_spine,
			_damage_part_spine1,
			// neck
			_damage_part_head,
			// left upperarm
			_damage_part_left_clavicle,
			// left hand
			_damage_part_left_forearm,
			_damage_part_left_thigh,
			// left horselink
			// left calf
			// left foot
			_damage_part_left_thigh1,
			// right upperarm
			_damage_part_right_clavicle,
			// right hand
			_damage_part_right_forearm,
			_damage_part_right_thigh,
			// right horselink
			// right calf
			// right foot
			// tail
			_damage_part_right_thigh1,

			k_number_of_damage_parts,
		};
	};

	namespace Flags
	{
		enum damage_region_flags : long_flags
		{
			_damage_region_lives_unit_object_dies_bit,
			_damage_region_forces_object_to_die_bit,
			_damage_region_dies_when_object_dies_bit,
			_damage_region_dies_when_object_is_damaged_bit,
			_damage_region_disappears_when_shield_is_off_bit,
			_damage_region_inhibits_melee_attack_bit,
			_damage_region_inhibits_weapon_attack_bit,
			_damage_region_inhibits_walking_bit,
			_damage_region_forces_drop_weapon_bit,
			_damage_region_causes_head_maimed_scream_bit,
		};
	};

	namespace TagGroups
	{
		struct s_body_damage_resistance
		{
			real maximum_vitality;

			real system_shock;
			long:8 * sizeof(long) * 6;

			long:8 * sizeof(long) * 7;

			real_fraction friendly_damage_resistance;
			long:8 * sizeof(long) * 2;
			long:8 * sizeof(long) * 8;

			tag_reference localized_damage_effect;
			real area_damage_effect_threshold;
			tag_reference area_damage_effect;

			real damaged_threshold;
			tag_reference damaged_effect;
			tag_reference depleted_effect;
			real destroyed_threshold;
			tag_reference destroyed_effect;
		}; static_assert( sizeof(s_body_damage_resistance) == 0xC4 );

		struct s_shield_damage_resistance
		{
			real maximum_vitality;

			unsigned short : 16;
			Enums::material_type material_type;
			long:8 * sizeof(long) * 6;

			transition_function failure_function;
			unsigned short : 16;
			real_fraction failure_threshold;
			real_fraction failing_leak_fraction;
			long:8 * sizeof(long) * 4;

			real minimum_stun_damage;
			real stun_time;
			real recharge_time;
			long:8 * sizeof(long) * 4;
			long:8 * sizeof(long) * 24;

			real damaged_threshold;
			tag_reference damaged_effect;
			tag_reference depleted_effect;

			tag_reference recharging_effect;
		}; static_assert( sizeof(s_shield_damage_resistance) == 0xEC );

		struct s_damage_resistance // or s_model_damage_info
		{
			unsigned long flags;
			short indirect_damage_material;
			unsigned short : 16;
			s_body_damage_resistance body_damage_resistance;
			s_shield_damage_resistance shield_damage_resistance;
			long:8 * sizeof(long) * 3;
			long:8 * sizeof(long) * 28;
		}; static_assert( sizeof(s_damage_resistance) == 0x234 );

		struct collision_model_material
		{
			tag_string name;
			unsigned long flags;

			Enums::material_type material_type;
			unsigned short : 16;
			struct {
				real_fraction leak_percentage; // unused for 'body'?
				real damaged_multiplier;

				// either an unused real field or a post-process field
				unsigned long : 32;
				unsigned long : 32;
			}shield, body;
		}; static_assert( sizeof(collision_model_material) == 0x48 );

		struct collision_model_region
		{
			tag_string name;
			Flags::damage_region_flags flags;
			unsigned long : 32;
			real damage_threshold;
			long:8 * sizeof(long) * 3;
			tag_reference destroyed_effect;
			Yelo::TagBlock<const tag_string> permutations;
		}; static_assert( sizeof(collision_model_region) == 0x54 ); // aka damage region

		struct collision_model_pathfinding_sphere
		{
			short node;
			unsigned short : 16;
			long:8 * sizeof(long) * 3;
			real_point3d center;
			real radius;
		}; static_assert( sizeof(collision_model_pathfinding_sphere) == 0x20 );

		struct collision_model_node
		{
			tag_string name;
			short region;
			short parent_node;
			short next_sibling_node;
			short first_child_node;

			tag_block:8 * sizeof(tag_block) * 1;
			Yelo::TagBlock<const collision_bsp> bsp;
		}; static_assert( sizeof(collision_model_node) == 0x40 );

		struct collision_model_definition
		{
			enum { k_group_tag = 'coll' };

			s_damage_resistance damage_resistance;

			Yelo::TagBlock<const collision_model_material> materials;
			Yelo::TagBlock<const collision_model_region> regions;
			tag_block:8 * sizeof(tag_block) * 1; // damage_modifiers_block is unused

			long:8 * sizeof(long) * 4;
			struct s_pathfinding {
				struct s_box {
					real_bounds x;
					real_bounds y;
					real_bounds z;
				}box;
				Yelo::TagBlock<const collision_model_pathfinding_sphere> spheres;
			}pathfinding;
			Yelo::TagBlock<const collision_model_node> nodes;
		}; static_assert( sizeof(collision_model_definition) == 0x298 );
	};
};
