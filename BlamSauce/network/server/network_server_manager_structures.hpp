/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo::Networking {
	struct s_network_client_machine_message_header {
		MessageDeltas::decoding_information_data *decoding_information;
		PAD128;
		PAD128;
		PAD128; // unknown bytes
	}; static_assert(sizeof(s_network_client_machine_message_header) == 0x34);

	struct s_network_client_machine_dedi {
		enum {
			k_sizeof                                            = 0,
			k_network_game_server_client_machines_offset_amount = Enums::k_maximum_network_machine_count * s_network_client_machine_dedi::k_sizeof,
		};

		wchar_t player_name[Enums::k_player_name_length + 1];
		long   player_number;
		long   team_index;
		char    ip_address[32];
		char    cdkey[74];
				  unsigned short : 16;
	}; static_assert(sizeof(s_network_client_machine_dedi) == 0x8C);

	struct s_network_client_machine {
		s_network_connection *connection;                     // 0x0
		long                                   last_received_update_sequence_number;               // 0x4
		long                                   stall_start_time;                              // 0x8
		short                                   machine_index;                              // 0xC
		// BIT(0) - marked for removal
		// BIT(1) - is_joined_to_game
		// BIT(2) - game_loading_complete
		// BIT(3) - is_precached
		// BIT(4) - is holding up
		unsigned short                              flags;                                 // 0xE
		bool                                    should_be_removed;
															 unsigned char : 8; unsigned short : 16;                        // 0x10
		long                                   removal_reject_time;                           // 0x14 game time the removal was initiated
		long                                   removal_process_time;                           // 0x18 game time the removal will take effect
		s_network_client_machine_message_header message_header;      // 0x1C
		bool                                    has_players;                                 // 0x50
		bool                                    is_cleaned_up;                                 // 0x51 true if touched by client_machine_cleanup
		char                                    challenge[Enums::k_network_game_challenge_length + 1];   // 0x52 gamespy challenge string
															 unsigned short : 16;
		long                                   machine_key;                                 // 0x5C same value as gs_machine_data->unknown1
	};

	static_assert(sizeof(s_network_client_machine) == 0x60);

	struct s_countdown_timer {
		long time_remaining;
		long relative_to; // system tick when time remaining was set
		long start_time;

		UNKNOWN_TYPE(bool);

		bool  pause_countdown;

		UNKNOWN_TYPE(bool);

				unsigned char : 8;
	};

	static_assert(sizeof(s_countdown_timer) == 0x10);

	struct s_network_game_server {
		enum {
			//////////////////////////////////////////////////////////////////////////
			// flag bits
				_game_is_open        = 0,
				_server_is_dedicated = 2, // doesn't show sv_status info when not set

			k_dedi_offset = s_network_client_machine_dedi::k_network_game_server_client_machines_offset_amount,
		};

		s_network_server_connection *connection;         // 0x0
		Enums::network_game_server_state state;            // 0x4
		unsigned short                       flags;                           // 0x6
		s_network_game                   game;                        // 0x8
		s_network_client_machine         client_machines
													[Enums::k_maximum_network_machine_count];      // 0x3F8
		long                            next_update_number;                     // 0x9F8+k_dedi_offset
		long                            time_of_last_keep_alive;                  // 0x9FC+k_dedi_offset
		long                            time_of_last_ping;                     // 0xA00+k_dedi_offset
		long                            time_of_first_client_loading_completion;      // 0xA04+k_dedi_offset
		s_countdown_timer                countdown_timer;               // 0xA08+k_dedi_offset
		s_network_game_player            queued_player;            // 0xA18+k_dedi_offset
		bool                             queued_player_valid;                     // 0xA38+k_dedi_offset
		bool                             game_has_started;                        // 0xA39+k_dedi_offset
		UNKNOWN_TYPE(bool);                           // 0xA3A
													unsigned char : 8;
		wchar_t                          password
													[Enums::k_network_server_password_length + 1];   // 0xA3C+k_dedi_offset
		UNKNOWN_TYPE(bool);                           // 0xA4E
		UNKNOWN_TYPE(bool);                           // 0xA4F

		bool IsDedi() const { return TEST_FLAG(flags, _server_is_dedicated); }

		s_network_client_machine *GetClient(int machine_index) {
			if (machine_index >= 0 && machine_index < NUMBEROF(client_machines)) {
				for (auto &machine : client_machines)
					if (machine_index == machine.machine_index)
						return &machine;
			}

			return nullptr;
		}
	};

	static_assert(sizeof(s_network_game_server) == (0xA50 + s_network_client_machine_dedi::k_network_game_server_client_machines_offset_amount));

	// For increased player counts game states
	struct s_network_game_server_yelo : s_network_game_server {
		s_network_game           game_yelo;
		s_network_client_machine client_machines_yelo[Enums::k_maximum_network_machine_count_upgrade];

		s_network_client_machine *GetClientYelo(int machine_index) {
			if (machine_index >= 0 && machine_index < NUMBEROF(client_machines_yelo)) {
				for (auto &machine : client_machines_yelo)
					if (machine_index == machine.machine_index)
						return &machine;
			}

			return nullptr;
		}
	};
};
