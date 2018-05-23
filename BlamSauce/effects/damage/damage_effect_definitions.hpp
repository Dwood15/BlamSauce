/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <blamlib/Halo1/effects/material_effect_definitions.hpp>

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum damage_side_effect
		{
			_damage_side_effect_none,
			_damage_side_effect_harmless,
			_damage_side_effect_legthal_to_unsuspecting,
			_damage_side_effect_emp,

			_damage_side_effect,
		};

		enum damage_category
		{
			_damage_category_none,
			_damage_category_falling,
			_damage_category_bullet,
			_damage_category_grenade,
			_damage_category_high_explosive,
			_damage_category_sniper,
			_damage_category_melee,
			_damage_category_flame,
			_damage_category_mounted_weapon,
			_damage_category_vehicle,
			_damage_category_plasma,
			_damage_category_needle,
			_damage_category_shotgun,

			_damage_category
		};
	};

	namespace Flags
	{
		enum {
			_damage_does_not_hurt_owner_bit,
			_damage_can_cause_headshots_bit,
			_damage_pings_resistant_units_bit,
			_damage_does_not_hurt_friends_bit,
			_damage_does_not_ping_units_bit,
			_damage_detonates_explosives_bit,
			_damage_only_hurts_shields_bit,
			_damage_causes_flaming_death_bit,
			_damage_direction_indicators_always_point_down_bit,
			_damage_skips_shields_bit,
			_damage_only_hurts_one_infection_form_bit,
			_damage_can_cause_multiplayer_headshots_bit,
			_damage_infection_form_pop_bit,

			k_number_of_damage_flags,

			_damage_use_3d_acceleration_yelo_bit = k_number_of_damage_flags,

			k_number_of_damage_flags_yelo,
		};
	};

	namespace TagGroups
	{
		struct s_damage_effect
		{
			real_bounds radius;
			real_fraction cutoff_scale;
			unsigned long flags; // not exposed for continuous_damage_effect
			long:8 * sizeof(long) * 5;
		}; static_assert( sizeof(s_damage_effect) == 0x24 );

		struct s_damage_camera_effect
		{
			unsigned long : 32;
			long:8 * sizeof(long) * 3;
			real shake_duration; // not exposed for continuous_damage_effect
			short shake_falloff_function; // not exposed for continuous_damage_effect
			unsigned short : 16;

			real random_translation;
			real random_rotation;
			long:8 * sizeof(long) * 3;

			short wobble_function;
			unsigned short : 16;
			real wobble_period;
			real_fraction wobble_weight;
			unsigned long : 32;

			long:8 * sizeof(long) * 5;
			long:8 * sizeof(long) * 2;
		}; static_assert( sizeof(s_damage_camera_effect) == 0x58 );

		struct s_damage_breaking_effect
		{
			long:8 * sizeof(long) * 28;

			struct {
				real velocity;
				real radius;
				real exponent;
				long:8 * sizeof(long) * 3;
			}forward, outward;
		}; static_assert( sizeof(s_damage_breaking_effect) == 0xA0 );

		struct s_damage_definition
		{
			short side_effect;
			short category;
			unsigned long flags;
			real area_of_effect_core_radius; // not exposed for continuous_damage_effect
			real damage_lower_bound;
			real_bounds damage_upper_bound;
			real vehicle_pass_through_penalty;
			real active_camo_damage; // not exposed for continuous_damage_effect
			real stun;
			real max_stun;
			real stun_time;
			unsigned long : 32;

			union {
				real instantaneous_acceleration;
				//unsigned long : 32; unsigned long : 32;

				// modifies instantaneous_acceleration to support specifying the j & k component acceleration
				real_vector3d instantaneous_acceleration3d;
			};

			bool UseInstantaneousAcceleration3D() const
			{
				return TEST_FLAG(flags, Flags::_damage_use_3d_acceleration_yelo_bit);
			}
		}; static_assert( sizeof(s_damage_definition) == 0x3C );

		struct s_damage_modifiers
		{
			real modifier[Enums::k_number_of_material_types];
			long:8 * sizeof(long) * 7;
		}; static_assert( sizeof(s_damage_modifiers) == 0xA0 );

		struct s_damage_effect_definition
		{
			enum { k_group_tag = 'jpt!' };

			struct s_duration_function {
				real duration;
				short fade_function;
				unsigned short : 16;

				angle rotation; // these are only exposed for camera impulse freq
				real pushback;
			};

			s_damage_effect damage_effect;

			struct s_screen_flash {
				short type;
				short priority;
				long:8 * sizeof(long) * 3;

				s_duration_function function;
				real_fraction max_intensity;
				unsigned long : 32;
				real_argb_color color;
			}screen_flash;

			struct s_rumble_frequency {
				real_fraction frequency;
				s_duration_function function;
			} rumble_low, rumble_high;
			s_rumble_frequency:8 * sizeof(s_rumble_frequency) * 1;

			struct s_camera_impulse_frequency {
				s_duration_function function;
				real_bounds jitter;
				unsigned long : 32; unsigned long : 32;
			}temp_camera_impulse;
			angle perm_camera_impulse_angle;

			s_damage_camera_effect damage_camera_effect;

			tag_reference sound;

			s_damage_breaking_effect breaking_effect;
			s_damage_definition damage;
			s_damage_modifiers damage_modifiers;
		}; static_assert( sizeof(s_damage_effect_definition) == 0x2A0 );


		struct s_continuous_damage_effect_definition
		{
			enum { k_group_tag = 'cdmg' };

			s_damage_effect damage_effect;

			real_fraction_bounds vibrate_frequency;
			s_damage_camera_effect damage_camera_effect;
			s_damage_breaking_effect breaking_effect; // not exposed
			s_damage_definition damage;
			s_damage_modifiers damage_modifiers;
		}; static_assert( sizeof(s_continuous_damage_effect_definition) == 0x200 );
	};
};
