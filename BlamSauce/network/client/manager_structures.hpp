#pragma once
#include <precompile.h>
#include "../../cseries/base.h"
#include "../game/globals.hpp"
#include "../transport/address.h"
#include "../game/manager_structures.hpp"
#include "manager.hpp"

namespace Yelo::Networking {
		struct s_network_client_time;
		struct s_network_connection;
		struct s_player_update_history;


		// I'm pretty sure this is deprecated on the PC (gamespy and all)
		struct s_network_advertised_game : TStructImpl(0x130) {};
		
		struct s_network_game_client
		{
			struct s_join_parameters
			{
				short pad_;						// 0xAEE
				wchar_t password[Enums::k_network_server_password_length+1];// 0xAF0
				char token[Enums::k_network_game_join_token_size];			// 0xB02
			}; static_assert( sizeof(s_join_parameters) == 0x24 );
			struct s_join_data
			{
				UNKNOWN_TYPE(long);						// 0xAE0
				long join_process_start_time;				// 0xAE4
				UNKNOWN_TYPE(long);						// 0xAE8
				UNKNOWN_TYPE(bool); unsigned char : 8;					// 0xAEC
				s_join_parameters parameters;				// 0xAEE
				unsigned short : 16;
			}; static_assert( sizeof(s_join_data) == 0x34 );

			struct s_ping_target
			{
				long last_ping_time;						// 0xACC
				short samples_sent;							// 0xAD0
				short samples_received;						// 0xAD2
				short ping_time;							// 0xAD4
				UNKNOWN_TYPE(bool); unsigned char : 8;					// 0xAD6
				s_network_client_time* tc;					// 0xAD8
			}; static_assert( sizeof(s_ping_target) == 0x10 );

			short machine_index; unsigned short : 16;
			s_network_advertised_game discovered_games[9];
			s_transport_address server_address;				// 0xAB4
			s_ping_target current_ping_target;				// 0xACC
			s_network_connection* connection;				// 0xADC
			s_join_data join_data;							// 0xAE0
			s_network_game game;							// 0xB14
			UNKNOWN_TYPE(long);							// 0xF04
			long time_of_last_game_search_packet;			// 0xF08
			long next_update_number;						// 0xF0C
			long time_of_last_update;						// 0xF10
			UNKNOWN_TYPE(long);							// 0xF14, time for something
			short seconds_to_game_start;					// 0xF18
			Enums::network_game_client_state state;			// 0xF1A
			short error;									// 0xF1C
			unsigned short flags;								// 0xF1E
			bool is_out_of_sync;							// 0xF20
			bool is_lagging_out;							// 0xF21, "network client connection has been silent for a dangerously long 'amount of time"
			unsigned short : 16; // guessing there is alignment padding here
			//////////////////////////////////////////////////////////////////////////
			// 0x30 byte data structure
				PAD64;										// 0xF24, unknown
				UNKNOWN_TYPE(bool); unsigned char : 8; unsigned short : 16;					// 0xF2C
				unsigned long : 32;										// 0xF30, unknown
				UNKNOWN_TYPE(long);						// 0xF34
				//////////////////////////////////////////////////////////////////////////
				// 0x18 byte data structure
					PAD128;
					PAD64;							// 0xF38
				long team_index;							// 0xF50
			PAD128; PAD128; PAD128; unsigned long : 32;					// 0xF54, 0x34 byte data structure
			s_player_update_history* update_history;		// 0xF88
			byte_enum connection_class;						// 0xF8C Enums::network_connection_class
			unsigned char : 8; unsigned short : 16;
		}; static_assert( sizeof(s_network_game_client) == 0xF90 );

		// For increased player counts game states
		struct s_network_game_client_yelo : s_network_game_client
		{
			s_network_game_yelo game_yelo;
		};
	};

