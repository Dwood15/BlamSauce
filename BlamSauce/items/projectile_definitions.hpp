#pragma once
#include <precompile.h>
#include "../game/objects/object_definitions.hpp"
#include "../ai/ai.h"

namespace Yelo
{
	namespace Enums
	{
		enum material_response
		{
			_material_response_disappear,
			_material_response_detonate,
			_material_response_reflect,
			_material_response_overpenetrate,
			_material_response_attach,

			_material_response,
		};
	};

	namespace TagGroups
	{
		struct s_projectile_material_response_definition
		{
			struct _flags {
				unsigned short cannot_be_overpenetrated_bit:1;
			}flags;

			struct _default_result {
				material_response response;
				tag_reference effect;
				tag_reference:8 * sizeof(tag_reference) * 1; // 16
			}default_result;

			struct _potential_result {
				material_response response;
				struct _flags {
					unsigned short only_against_units_bit:1;
				}flags;
				real skip_fraction;
				angle_bounds between;
				real_boundsand;
				tag_reference effect;
				tag_reference:8 * sizeof(tag_reference) * 1; // 16
			}potential_result;

			effect_scale scale_effects_by;
			unsigned short : 16;
			real angular_noise;
			real velocity_noise;
			tag_reference detonation_effect;
			long:8 * sizeof(long) * 6; // 24

			real initial_friction;
			real max_distance;

			real parallel_friction;
			real perpendicular_friction;
		}; static_assert( sizeof(s_projectile_material_response_definition) == 0xA0 );

		struct _projectile_definition
		{
			struct _projectile_definition_flags {
				unsigned long oriented_along_velocity_bit:1;
				unsigned long ai_must_use_basllistic_aiming_bit:1;
				unsigned long detonation_max_time_if_attached_bit:1;
				unsigned long has_super_combining_explosion_bit:1;
				//combine initial velocity with parent velocity
				//random attached detonation time
				//minimum unattached detonation time
			}flags; static_assert( sizeof(_projectile_definition_flags) == sizeof(unsigned long) );

			projectile_detonation_timer_mode detonation_timer_starts;
			ai_sound_volume impact_noise;

			short function_exports[Enums::k_number_of_incoming_object_functions];

			tag_reference super_detonation;

			real ai_perception_radius;
			real collision_radius;

			real arming_time;
			real danger_radius;
			tag_reference effect;
			real_bounds timer;
			real min_velocity;
			real max_range;

			real air_gravity_scale;
			real_bounds air_damage_range;
			real water_gravity_scale;
			real_bounds water_damage_range;
			real initial_velocity;
			real final_velocity;
			real guided_angular_velocity;
			ai_sound_volume detonation_noise;
			unsigned short : 16;

			tag_reference detonation_started;
			tag_reference flyby_sound;
			tag_reference attached_detonation_damage;
			tag_reference impact_damage;
			tag_block:8 * sizeof(tag_block) * 1; // 12

			Yelo::TagBlock<const s_projectile_material_response_definition> material_responses;

		}; static_assert( sizeof(_projectile_definition) == 0xD0 );


		struct s_projectile_definition : s_object_definition
		{
			enum { k_group_tag = 'proj' };

			_projectile_definition projectile;
		};
	};
};
