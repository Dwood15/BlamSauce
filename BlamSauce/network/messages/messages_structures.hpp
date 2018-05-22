/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

//#include <blamlib/Halo1/bungie_net/common/message_header.hpp>
#include <blamlib/Halo1/game/game_configuration.hpp>
#include <blamlib/Halo1/game/player_action.hpp>
#include <blamlib/Halo1/game/players.hpp>
#include <blamlib/Halo1/networking/network_game_globals.hpp>
#include <blamlib/Halo1/networking/network_game_manager.hpp>

namespace Yelo
{
	namespace Networking
	{
		struct message_server_new_client_challenge
		{
			char challenge[Enums::k_network_game_challenge_length+1];
			bool sv_public;
			unsigned char : 8; unsigned short : 16;
			short machine_index;
			unsigned short : 16;
			s_network_game_map map;
		}; static_assert( sizeof(message_server_new_client_challenge) == 0x94 );

		struct message_client_join_game_request
		{
			char token[Enums::k_network_game_join_token_size];
			wchar_t password[Enums::k_network_server_password_length+1];
			char unused[73];
			byte_enum connection_class;										// 0x6B Enums::network_connection_class
			unsigned short : 16;
			s_network_game_player player;									// 0x6E
			unsigned short : 16;
			uint32 map_crc_xor_challenge;									// 0x90
		}; static_assert( sizeof(message_client_join_game_request) == 0x94 );

		struct message_server_game_update
		{
			long update_id;
			long random_seed;

			game_ticks_t ticks_to_apply_update_to;
			UNKNOWN_TYPE(short); // unused?
			short action_count;
			Players::s_player_action actions[Enums::k_multiplayer_maximum_players];
		}; static_assert( sizeof(message_server_game_update) == 0x210 );

		struct message_client_game_update
		{
			game_ticks_t ticks_to_apply_update_to;
			UNKNOWN_TYPE(short); // unused?
			short action_count; // should be equal to local_player_count
			Players::s_player_action actions[Enums::k_maximum_number_of_local_players];
		}; static_assert( sizeof(message_client_game_update) == 0x28 );
	};
};
