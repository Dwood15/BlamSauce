#pragma once

#include <precompile.h>
#include "variants.h"
#include "../../cseries/base.h"

namespace Yelo {
	namespace MessageDeltas {
		struct message_dependant_header;
	};
	namespace Networking {
		struct s_network_game_client;
	};
	namespace Objects {
		struct s_weapon_datum;
	};

	namespace Enums {
		enum game_engine : int {
			_game_engine_none,
			_game_engine_ctf,
			_game_engine_slayer,
			_game_engine_oddball,
			_game_engine_king,
			_game_engine_race,
			_game_engine_stub,

			k_number_of_game_engines
		};
	};

	namespace Flags {
		enum game_engine_flags : unsigned long {
			_game_engine_player_spawn_in_team_designator_locations_only_bit,
			// Engine's score is based on the kills a player_update has
			_game_engine_uses_slayer_scoring_bit,
		};
	};

	namespace GameEngine {
		struct game_engine_definition {
			const char * name;                                 // 0x0

			short type;                                    // 0x4
			unsigned short : 16;                                       // 0x6

			typedef void (__cdecl *_dispose)();

			_dispose dispose;                              // 0x8

			typedef bool (__cdecl *_initialize_for_new_map)();

			_initialize_for_new_map initialize_for_new_map;         // 0xC

			typedef void (__cdecl *_dispose_from_old_map)();

			_dispose_from_old_map dispose_from_old_map;            // 0x10

			typedef void (__cdecl *_player_added)(datum_index player_index);

			_player_added player_added;                        // 0x14

			void *unused0;                                 // 0x18

			typedef void (__cdecl *_game_ending)();

			_game_ending game_ending;                        // 0x1C

			typedef void (__cdecl *_game_starting)();

			_game_starting game_starting;                     // 0x20

			// --- DEPRECATED functions (used on xbox)
			unsigned long : 32;                                       // 0x24
			unsigned long : 32;                                       // 0x28
			unsigned long : 32;                                       // 0x2C
			unsigned long : 32;                                       // 0x30
			// --- DEPRECATED

			typedef void (__cdecl *_post_rasterize)();

			_post_rasterize post_rasterize;                     // 0x34

			typedef void (__cdecl *_player_update)(datum_index player_index);

			_player_update player_update;                     // 0x38

			typedef void (__cdecl * _weapon_update)(datum_index weapon_index, Objects::s_weapon_datum *weapon);

			_weapon_update weapon_update;                     // 0x3C

			typedef bool (__cdecl *_weapon_pickup)(datum_index weapon_index, datum_index player_index);

			_weapon_pickup weapon_pickup;                     // 0x40

			typedef void (__cdecl *_weapon_drop)(datum_index weapon_index);

			_weapon_drop weapon_drop;                        // 0x44

			typedef void (__cdecl *_update)();

			_update update;                                 // 0x48

			typedef long (__cdecl *_get_score)(datum_index player_index, long use_team_score);

			_get_score get_score;                           // 0x4C

			typedef long (__cdecl *_get_team_score)(long team_index);

			_get_team_score get_team_score;                     // 0x50

			// returns out buffer
			typedef wchar_t *(__cdecl *_get_score_string)(wchar_t *out_buffer, datum_index player_index);

			_get_score_string get_score_string;                  // 0x54

			// returns out buffer
			typedef wchar_t *(__cdecl *_get_score_header_string)(wchar_t *out_buffer);

			_get_score_header_string get_score_header_string;      // 0x58

			// returns out buffer
			typedef wchar_t *(__cdecl *_get_team_score_string)(long team_index, wchar_t *out_buffer);

			_get_team_score_string get_team_score_string;         // 0x5C

			typedef bool (__cdecl *_allow_pick_up)(datum_index unit_index, datum_index weapon_index);

			_allow_pick_up allow_pick_up;                     // 0x60

			typedef void (__cdecl *_player_damaged_player)(datum_index player_index, datum_index damaged_player, bool /*update_speed?*/);

			_player_damaged_player *player_damaged_player;         // 0x64

			typedef void (__cdecl *_player_killed_player)(datum_index player_index, datum_index unit_index, datum_index dead_player, bool /*update_speed?*/);

			_player_killed_player player_killed_player;            // 0x68

			typedef bool (__cdecl *_display_score)(datum_index player_index, long format_type, wchar_t *out_buffer, long max_length);

			_display_score display_score;                     // 0x6C

			typedef real (__cdecl *_starting_location_rating)(datum_index player_index, real_point3d *location);

			_starting_location_rating starting_location_rating;      // 0x70

			typedef void (__cdecl *_prespawn_player_update)(datum_index player_index);

			_prespawn_player_update prespawn_player_update;         // 0x74

			typedef bool (__cdecl *_postspawn_player_update)(datum_index player_index);

			_postspawn_player_update postspawn_player_update;      // 0x78

			void *unused1;                                 // 0x7C

			// returns [true] if the engine's goal is [player_index]
			typedef bool (__cdecl *_goal_matches_player)(datum_index player_index);

			_goal_matches_player goal_matches_player;            // 0x80

			typedef bool (__cdecl *_test_flag)(uint flags);

			_test_flag test_flag;                           // 0x84

			typedef bool (__cdecl *_test_trait)(datum_index player_index, Enums::game_trait trait);

			_test_trait test_trait;                           // 0x88

			// returns [true] if [player_index] was the winner of the game
			typedef bool (__cdecl *_test_player_won)(datum_index player_index);

			_test_player_won test_player_won;                  // 0x8C

			// new to pc

			// -1 for machine sends to all.
			typedef void (__cdecl *_to_network)(void *baselines, long specific_machine /* = NONE*/ );

			_to_network to_network;                           // 0x90

			typedef void (__cdecl *_from_network)(MessageDeltas::message_dependant_header *header, Networking::s_network_game_client *client);

			_from_network from_network;                        // 0x94

			typedef void (__cdecl *_player_reset_score)(datum_index player_index);

			_player_reset_score player_reset_score;               // 0x98

			// used by gamespy api
			typedef bool (__cdecl *_get_gamespy_packet_field_string)(signed long field /*gamespy_field*/, char *buffer);

			_get_gamespy_packet_field_string get_gamespy_packet_field_string;   // 0x9C

			// 1st param must be 22 (_gamespy_qr_field_score) in order to return true
			typedef bool (__cdecl *_create_player_score_strings)(signed long field /*gamespy_field*/, datum_index player_index, const char * out_buffer);

			_create_player_score_strings create_player_score_strings;   // 0xA0

			// 1st param must be 29 (_gamespy_qr_field_score_t) in order to return true
			typedef bool (__cdecl *_create_team_score_strings)(signed long field /*gamespy_field*/, long team_index, const char * out_buffer);

			_create_team_score_strings create_team_score_strings;   // 0xA4

			typedef long (__cdecl *_get_gamespy_key_count)(signed long keytype);

			_get_gamespy_key_count get_gamespy_key_count;         // 0xA8

			typedef void (__cdecl *_initialize_for_reset_map)();

			_initialize_for_reset_map initialize_for_reset_map;      // 0xAC
		}; static_assert(sizeof(game_engine_definition) == 0xB0);
	};

	namespace blam {
		datum_index __cdecl find_closest_player_index(datum_index player_index);

		void __cdecl game_engine_rasterize_message(wconst char * message, real alpha);
	};
};
