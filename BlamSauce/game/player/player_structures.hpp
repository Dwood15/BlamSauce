#pragma once

#include "../../cseries/base.h"
#include "../../memory/data_base.h"
#include "players.hpp"
#include "../../math/color_math.h"
#include "player_action.hpp"
#include "../configuration.hpp"
#include "../objects/units/c_unit_seat_boarding_manager.hpp"
#include "../objects/units/unit_structures.hpp"
#include "../../network/game/manager.hpp"
#include "../../network/player_update/client.hpp"
#include "../../network/player_update/server.hpp"

namespace Yelo {
	namespace Players {
		union u_player_multiplayer_stats {
			PAD64;

			struct s_ctf {
				short flag_grabs;
				short flag_returns;
				short flag_scores;
			} ctf_statistics;

			struct s_slayer {
			} slayer;

			struct s_oddball {
				UNKNOWN_TYPE(short);
				short target_kills;
				short kills;
			} oddball;

			struct s_king {
				short hill_score;
			} king;

			struct s_race {
				short time;
				short laps;
				short best_time;
			} race;
		}; static_assert(sizeof(u_player_multiplayer_stats) == 8);

		// Special yelo data used for player_update datums when running as a server
		struct s_player_yelo_server_data {
			enum { k_max_struct_size = 0x38 };

			struct _rcon_access {
				long last_bad_password_time;      // Game tick of when the last failure took place
				short bad_password_cooldown;      // Ticks until it's kosher to decrement [number_of_bad_passwords]
				short number_of_bad_passwords;      // Number of times the player_update has given a bad password in a given threshold of time
			} rcon_access;

			struct _voting {
				bool  voted;      // Has this player_update voted yet?
				sbyte option;   // Option, in enumerated form. Or NONE.
				unsigned short : 16;
			} voting;

		}; static_assert(sizeof(s_player_yelo_server_data) <= s_player_yelo_server_data::k_max_struct_size);

		struct s_player_datum : Memory::s_datum_base {
			struct s_game_engine_state_message {
				long       message_index;
				datum_index message_player_index; // player_update to use in the message?

				// values used for rendering a target player_update's name
				datum_index target_player;
				long       target_time; // timer used to fade in the target player_update name
			};

			short                  local_player_index;                     // 0x2
			wchar_t                display_name[Enums::k_player_name_length + 1];// 0x4
			UNUSED_TYPE(long);                           // 0x1C
			union {                                    // 0x20
				long      team_index;
				argb_color color;
			};
			s_player_action_result nearest_object_action_result;// 0x24
			game_ticks_t           respawn_time;                     // 0x2C
			UNKNOWN_TYPE(long);                        // 0x30 respawn time growth related
			datum_index slave_unit_index;                  // 0x34
			datum_index last_slave_unit_index;               // 0x38
			short       cluster_index;                        // 0x3C
			bool        weapon_swap_result;                     // 0x3E
			unsigned char : 8;
			datum_index                             auto_aim_target;                  // 0x40 biped_index
			game_ticks_t                            auto_aim_update_time;               // 0x44
			Yelo::Networking::s_network_game_player network_player;   // 0x48
			game_time_t                             powerup_times[Enums::k_number_of_player_powerups];   // 0x68
			real                                    speed;                                 // 0x6C
			long                                   source_teleporter_netgame_index;            // 0x70 index to a netgame flag in the scenario, or NONE
			s_game_engine_state_message             engine_state_messsage;   // 0x74
			game_ticks_t                            last_death_time;                  // 0x84 game tick of the last time this player_update was killed
			datum_index                             target_player_index;               // 0x88 player_update index of the slayer target for this player_update
			bool                                    odd_man_out;                           // 0x8C
			unsigned char : 8; unsigned short : 16;
			UNUSED_TYPE(long);                           // 0x90
			UNUSED_TYPE(short);                           // 0x94
			short kills_this_lifetime;                     // 0x96 how many kills we've had in this lifetime (since the last spawn)
			short current_spree_count;                     // 0x98 how many kills we've had in our 'spree time' (4 second intervals max)
			short last_kill_time;                        // 0x9A set from game_time_globals::local_time
			union {                                    // 0x9C
				byte player_score_buffer[0x10];
				struct {
					short kills[4];                        // 0x9C
					short assists[4];                     // 0xA4
				}    player_score;
			};
			short friendly_fire_kills;                     // 0xAC
			short deaths;                              // 0xAE
			short suicides;                              // 0xB0
			unsigned short : 16;
			UNUSED_TYPE(long);                           // 0xB4
			UNUSED_TYPE(long);                           // 0xB8
			UNUSED_TYPE(long);                           // 0xBC
			short team_kills;                           // 0xC0
			unsigned short : 16;
			u_player_multiplayer_stats multiplayer_stats;      // 0xC4
			long                      telefrag_counter;                        // 0xCC # of ticks spent blocking teleporter
			game_ticks_t               quit_game_tick;                  // 0xD0 game tick the player_update quick at
			bool                       telefrag_enabled;                        // 0xD4 if we're blocking a teleporter, this will be true
			bool                       quit_out_of_game;                        // 0xD5
			unsigned short : 16;
			UNUSED_TYPE(long);                           // 0xD8
			long ping;                                 // 0xDC
			long team_kill_number;                        // 0xE0
			long team_kill_timer;                        // 0xE4

			union {                                    // 0xE8
				byte _unused_networking_buffer[0x200 - 0xE8];

				struct {
					Yelo::Networking::s_player_client_update update_data;
					unsigned long : 32;                              // 0x1FC
				}    client;
				struct {
					Networking::s_player_server_update update_data;
					// !!! Only use this when the local machine is the host (ie, GameState::IsServer() == true) !!!
					s_player_yelo_server_data          yelo_data;      // 0x1C8
				}    server;
			};

			Objects::s_unit_datum *GetPlayerUnit();

			datum_index GetVehicleIndex();

			s_player_yelo_server_data &GetYeloServerData();
		};

		static_assert(sizeof(s_player_datum) == 0x200); // 0x160 in Stubbs


		struct s_team_datum : Memory::s_datum_base_aligned {
			byte pad[0x3C];

			// nothing even uses this...this structure 
			// could have no real fields...maybe use it 
			// for our own evil deeds?
		}; static_assert(sizeof(s_team_datum) == 0x40); // same size in Stubbs


		struct s_players_globals_data {
			UNUSED_TYPE(long);                                                // 0x0, initialized to NONE but that's all I can tell
			// the player_index for each local player_update
			datum_index local_player_players[Enums::k_maximum_number_of_local_players];      // 0x4
			// the object_index of each local player_update's dead unit (their old body)
			datum_index local_player_dead_units[Enums::k_maximum_number_of_local_players];   // 0x8
			short       local_player_count;                                          // 0xC
			short       double_speed_ticks_remaining;                                    // 0xE
			bool        are_all_dead;                                                // 0x10
			bool        input_disabled;                                             // 0x11
			UNKNOWN_TYPE(short);                                             // 0x12, bsp switch trigger index
			short respawn_failure;                                             // 0x14
			bool  was_teleported;                                             // 0x16, or respawned
			unsigned char : 8;
			unsigned long combined_pvs[BIT_VECTOR_SIZE_IN_DWORDS(512)];                  // 0x18 combined pvs of all players in the game
			unsigned long combined_pvs_local[BIT_VECTOR_SIZE_IN_DWORDS(512)];               // 0x58 combined pvs of all local players
		}; static_assert(sizeof(s_players_globals_data) == 0x98);
	};
};
