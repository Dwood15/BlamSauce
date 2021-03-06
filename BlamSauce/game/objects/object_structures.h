#pragma once

#include <const char *>
#include <precompile.h>
#include "../../memory/datum_index.h"
#include "../allegiance.h"
#include "../../math/real_math.h"
#include "../../math/color_math.h"
#include "object_definitions.hpp"
#include "../../models/animations/model.hpp"
#include "../../models/model_definitions.hpp"
#include "object_types.h"
#include "../../scenario/structures.h"
#include "../../cseries/base.h"
#include "vehicles/structures.h"

namespace Yelo {
	namespace Enums {
		enum networked_datum : unsigned long {
			_networked_datum_master,
			_networked_datum_puppet,
			_networked_datum_puppet_controlled_by_local_player,
			_networked_datum_local_only,
		};

		enum object_sizes {
			// The base object datum allocates 2 real_orientation3d and 1 real_matrix4x3 FOR EVERY model node
				k_object_size_object        = 0x1F4,
				k_object_size_projectile    = 0xBC + k_object_size_object,
				k_object_size_scenery       = 0x4 + k_object_size_object,
				k_object_size_placeholder   = 0x8 + k_object_size_object,
				k_object_size_sound_scenery = 0x4 + k_object_size_object,

			k_object_size_device        = 0x20 + k_object_size_object,
			k_object_size_machine       = 0x14 + k_object_size_device,
			k_object_size_control       = 0x8 + k_object_size_device,
			k_object_size_light_fixture = 0x18 + k_object_size_device,

			k_object_size_item      = 0x38 + k_object_size_object,
			k_object_size_weapon    = 0x114 + k_object_size_item,
			k_object_size_equipment = 0x68 + k_object_size_item,
			k_object_size_garbage   = 0x18 + k_object_size_item,

			k_object_size_unit    = 0x2D8 + k_object_size_object,
			k_object_size_biped   = 0x84 + k_object_size_unit,
			k_object_size_vehicle = 0xF4 + k_object_size_unit,
		};

		enum attachment_type : char {
			_attachment_type_invalid = NONE,

			_attachment_type_light = 0,
			_attachment_type_looping_sound,
			_attachment_type_effect,
			_attachment_type_contrail,
			_attachment_type_particle,
			_attachment_type,
		};
	};

	namespace Flags {
		enum {
			// --- 0x10

			_object_hidden_bit = 0,
			_object_is_on_the_ground_bit,
			_object_unk2_bit,
			_object_is_in_water_bit,
			_object_unk4_bit,
			_object_at_reset_bit, // when set, physics aren't updated
			_object_unk6_bit,
			_object_unk7_bit,
			_object_unk8_bit,
			_object_unk9_bit,
			_object_unk10_bit, // set when the object has a looping sound attachment
			_object_connected_to_map_bit,
			_object_not_placed_automatically_bit,
			_object_unk13_bit, // set in device_machine's 'new' function, always
			_object_unk14_bit, // set in device_machine's 'new' function, if _machine_is_elevator_bit is true
			_object_unk15_bit, // set in device_machine's 'new' function, if _machine_is_elevator_bit is true
			_object_garbage_bit,
			_object_unk17_bit, // unit and weapon 'place' functions set this, but I don't see any code which tests for it
			_object_does_not_cast_shadow_bit,
			_object_deactivation_is_deletion_bit, // instead of deactivating (and persisting), the object is deleted
			_object_unk20_bit, // prohibits the object from ever being activated again
			_object_outside_map_bit,
			_object_beautify_bit,
			_object_limping_bit, // used with _biped_limping_bit; node matrices won't be updated
			_object_collideable_bit,
			_object_has_collision_model_bit,
			_object_unk26_bit, // HaloPC, message delta related. see object_type_should_force_baseline_update
			_object_unk27_bit, // HaloPC, message delta related. see *_process_update_delta
			_object_yelo_is_transforming_out_bit,
			_object_yelo_is_transforming_in_bit,
			//_object_30_bit,
			//_object_31_bit,

			// --- 0x106

			// These are set when the damage thresholds are reached and the game applies the
			// respective s_damage_resistance's damage_effect
				_object_body_damage_effect_applied_bit = 0,
				_object_shield_damage_effect_applied_bit,
			// test this bit if you want to see if the unit is_dead
				_object_body_depleted_bit, // if this is set, _hud_draw_element_1_bit will be set when the unit interface is rendered
				_object_shield_depleted_bit, // if this is set, _hud_draw_element_0_bit will be set when the unit interface is rendered
				_object_damage_unk4_bit, // shield related
				_object_killed_bit,
				_object_killed_silent_bit,
				_object_melee_attack_inhibited_bit,
				_object_damage_unk8_bit, // unused?
				_object_damage_unk9_bit, // unused?
				_object_damage_unk10_bit, // unused?
				_object_cannot_take_damage_bit,
				_object_shield_recharging_bit,
				_object_killed_no_statistics_bit,
		};
	};

	namespace Objects {
		// Object datums in the memory pool can have dynamically allocated nested-blocks.
		// Due to the way the game implements this, OS can allocate a nested-block of its own in an object,
		// and when the stock game uses a gamesave with an object like this, it will silently but safely
		// operate on it, even when it comes time to delete the object from the pool.
		// An object gets reallocated when a nested-block is requested (and the additional size is added to
		// the object's overall pool block size)
		struct s_object_header_block_reference {
			unsigned short size;
			unsigned short offset;
		}; static_assert(sizeof(s_object_header_block_reference) == 0x4);

		struct s_object_placement_data {
			datum_index definition_index;
			unsigned long  flags;
			datum_index player_index;
			datum_index owner_object_index;
			UNKNOWN_TYPE(long);
			Enums::game_team owner_team;
			short            region_permutation; // variant id
			real_point3d     position;
			float : 32; // angle?
			real_vector3d  transitional_velocity;
			real_vector3d  forward;
			real_vector3d  up;
			real_vector3d  angular_velocity;
			real_rgb_color change_colors[Enums::k_number_of_object_change_colors];
		}; static_assert(sizeof(s_object_placement_data) == 0x88);

		struct s_object_datum_network_delta_data // should be populated during the object type's process_update_delta
		{
			bool valid_position;               // 0x18
			unsigned char : 8; unsigned short : 16;
			real_point3d position;               // 0x1C

			bool valid_forward_and_up;            // 0x28
			unsigned char : 8; unsigned short : 16;
			real_vector3d forward;               // 0x2C
			real_vector3d up;                  // 0x38

			bool valid_transitional_velocity;      // 0x44
			unsigned char : 8; unsigned short : 16;
			real_vector3d transitional_velocity;   // 0x48

			bool valid_timestamp;               // 0x54
			unsigned char : 8; unsigned short : 16;
			long timestamp;                  // 0x58
		}; static_assert(sizeof(s_object_datum_network_delta_data) == 0x44);

		struct s_object_datum_animation_data {
			datum_index       definition_index;   // 0xCC
			s_animation_state state;      // 0xD0
			short             interpolation_frame_index;// 0xD4
			short             interpolation_frame_count;// 0xD6
		}; static_assert(sizeof(s_object_datum_animation_data) == 0xC);

		struct s_object_datum_damage_data {
			real        maximum_health;            // 0xD8
			real        maximum_shield;            // 0xDC
			real        health;                  // 0xE0, health = body
			real        shield;                  // 0xE4
			real        shield_damage_current;         // 0xE8
			real        body_damage_current;         // 0xEC
			// when this object is damaged, the 'entangled' object will also get damaged.
			// this is an immediate link, the entangled object's parent chain or 'entangled' reference isn't walked
			datum_index entangled_object_index;   // 0xF0
			real        shield_damage_recent;         // 0xF4
			real        body_damage_recent;         // 0xF8
			long       shield_damage_update_tick;   // 0xFC, these update ticks are set to NONE when not active
			long       body_damage_update_tick;      // 0x100
			short       stun_ticks;               // 0x104, based on ftol(s_shield_damage_resistance->stun_time * 30f)
			unsigned short  flags;               // 0x106
		}; static_assert(sizeof(s_object_datum_damage_data) == 0x30);

		struct s_object_datum_attachments_data {
			Enums::attachment_type attached_types[Enums::k_maximum_number_of_attachments_per_object];   // 0x144
			// game state datum_index
			// ie, if Attachments[x]'s definition (object_attachment_block[x]) says it is a 'cont'
			// then the datum_index is a contrail_data handle
			datum_index            attachment_indices[Enums::k_maximum_number_of_attachments_per_object];         // 0x14C
			datum_index            first_widget_index;                                                // 0x16C
		}; static_assert(sizeof(s_object_datum_attachments_data) == 0x2C);

		struct s_object_data {
			datum_index            definition_index;                                       // 0x0
			//////////////////////////////////////////////////////////////////////////
			// Added in HaloPC
			Enums::networked_datum datum_role;                                    // 0x4
			UNKNOWN_TYPE(bool);                                                // 0x8
			bool should_force_baseline_update;                                    // 0x9
			unsigned short : 16; // haven't verified if this is padding or not
			long                               network_time;                                                // 0xC
			//////////////////////////////////////////////////////////////////////////
			long_flags                          flags;                                                // 0x10
			long                               object_marker_id;                                             // 0x14
			//////////////////////////////////////////////////////////////////////////
			// Added in HaloPC
			s_object_datum_network_delta_data   network_delta;                        // 0x18
			//////////////////////////////////////////////////////////////////////////
			real_point3d                        position;                                             // 0x5C
			real_vector3d                       transitional_velocity;                                 // 0x68
			real_vector3d                       forward;                                             // 0x74
			real_vector3d                       up;                                                // 0x80
			real_vector3d                       angular_velocity;                                       // 0x8C
			Yelo::Scenario::s_scenario_location location;                                       // 0x98
			real_point3d                        center;                                             // 0xA0
			real                                radius;                                                   // 0xBC
			real                                scale;                                                      // 0xB0
			short                               type;                                                      // 0xB4
			unsigned short : 16;
			Enums::game_team owner_team;                                       // 0xB8
			short            name_list_index;                                             // 0xBA
			// ticks spent not at_rest. only bipeds updates this
			short            moving_time;                                                // 0xBC
			short            region_permutation;                                          // 0xBE, variant id
			datum_index      player_index;                                          // 0xC0
			// If this were a projectile, I believe this would be the handle to
			// the weapon which spawned it
			datum_index      owner_object_index;                                       // 0xC4
			unsigned long : 32;                                                         // 0xC8 unused
			s_object_datum_animation_data animation;                              // 0xCC
			s_object_datum_damage_data    damage;                                    // 0xD8
			unsigned long : 32;                                                         // 0x108 unused
			datum_index cluster_partition_index;                                 // 0x10C
			UNKNOWN_TYPE(datum_index);                                          // 0x110, object_index, garbage collection related
			datum_index next_object_index;                                       // 0x114
			datum_index first_object_index;                                       // 0x118
			datum_index parent_object_index;                                    // 0x11C
			sbyte       parent_node_index;                                          // 0x120
			UNUSED_TYPE(byte);                                                // 0x121 idk if this is an sbyte or bool here
			bool       force_shield_update;                                          // 0x122
			byte_flags valid_outgoing_functions;                                 // 0x123, 1<<function_index
			real       incoming_function_values[Enums::k_number_of_incoming_object_functions];   // 0x124
			real       outgoing_function_values[Enums::k_number_of_outgoing_object_functions];   // 0x134

			s_object_datum_attachments_data attachments;                           // 0x144
			datum_index                     cached_render_state_index;                                 // 0x170
			unsigned short                      regions_destroyed_flags;                                    // 0x174 once a region is destroyed, its bit index is set
			short                           shader_permutation;                                          // 0x176, shader's bitmap block index
			byte                            region_vitality[Enums::k_maximum_regions_per_model];                  // 0x178
			sbyte                           region_permutation_indices[Enums::k_maximum_regions_per_model];         // 0x180

			real_rgb_color change_colors[Enums::k_number_of_object_change_colors];         // 0x188
			real_rgb_color change_colors2[Enums::k_number_of_object_change_colors];         // 0x1B8

			// one of these are for interpolating
			s_object_header_block_reference node_orientations;                        // 0x1E8 real_orientation3d[node_count]
			s_object_header_block_reference node_orientations2;                        // 0x1EC real_orientation3d[node_count]
			s_object_header_block_reference node_matrix_block;                        // 0x1F0 real_matrix4x3[node_count]

			void CopyToPlacementData(s_object_placement_data &data) const {
				data.player_index = player_index;
				data.owner_object_index = owner_object_index;
				std::memcpy(&data.position,				&position, sizeof(position));
				std::memcpy(&data.transitional_velocity,&transitional_velocity, sizeof(transitional_velocity));
				std::memcpy(&data.forward,				&forward, sizeof(forward));
				std::memcpy(&data.up,					&up, sizeof(up));
				std::memcpy(&data.angular_velocity,		&angular_velocity, sizeof(angular_velocity));
			}

			bool VerifyType(unsigned long type_mask) const {
				return TEST_FLAG(type_mask, type);
			}

			template <typename TBlockData>
			TBlockData *GetBlock(s_object_header_block_reference ref) {
				byte *obj = reinterpret_cast<byte *>(this);

				return ref.offset == 0 ? nullptr : reinterpret_cast<TBlockData *>(&obj[ref.offset]);
			}

			template <typename TBlockData, size_t kBlockReferenceOffset>
			TBlockData *GetBlock() {
				byte *obj = reinterpret_cast<byte *>(this);

				auto *ref = reinterpret_cast<s_object_header_block_reference *>(obj + kBlockReferenceOffset);

				return GetBlock<TBlockData>(*ref);
			}
		};

		static_assert(sizeof(s_object_data) == 0x1F4); //Enums::k_object_size_object);

		struct s_object_datum {
			enum { k_object_types_mask = Enums::_object_type_object };

			s_object_data object;
		}; static_assert(sizeof(s_object_datum) == Enums::k_object_size_object);

		//////////////////////////////////////////////////////////////////////////
		// scenery
		struct s_scenery_data {
			unsigned long flags; // FLAG(0) - playing animation
		}; static_assert(sizeof(s_scenery_data) == (Enums::k_object_size_scenery - Enums::k_object_size_object));

		struct s_scenery_datum {
			enum { k_object_types_mask = Enums::_object_type_scenery };

			s_object_data  object;
			s_scenery_data scenery;
		}; static_assert(sizeof(s_scenery_datum) == Enums::k_object_size_scenery);


		//////////////////////////////////////////////////////////////////////////
		// placeholder
		struct s_placeholder_data {
			PAD64;
		}; static_assert(sizeof(s_placeholder_data) == (Enums::k_object_size_placeholder - Enums::k_object_size_object));

		struct s_placeholder_datum {
			enum { k_object_types_mask = Enums::_object_type_placeholder };

			s_object_data      object;
			s_placeholder_data placeholder;
		}; static_assert(sizeof(s_placeholder_datum) == Enums::k_object_size_placeholder);


		//////////////////////////////////////////////////////////////////////////
		// sound_scenery
		struct s_sound_scenery_data {
			unsigned long : 32;
		}; static_assert(sizeof(s_sound_scenery_data) == (Enums::k_object_size_sound_scenery - Enums::k_object_size_object));

		struct s_sound_scenery_datum {
			enum { k_object_types_mask = Enums::_object_type_sound_scenery };

			s_object_data        object;
			s_sound_scenery_data sound_scenery;
		}; static_assert(sizeof(s_sound_scenery_datum) == Enums::k_object_size_sound_scenery);
	};
};
