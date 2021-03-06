#pragma once

#include <precompile.h>
#include <enginelayout/Networking.inl>
#include "messages/messages.hpp"
#include "server/network_server_manager_structures.hpp"
#include "game/manager.hpp"
#include "gamespy_api.h"
#include "server/network_server_manager.hpp"

namespace Yelo {
	namespace Enums {
		enum transport_rejection_code : signed long;

		enum {
			k_message_highest_priority = 0,
			k_message_lowest_priority  = 9,
		};

		enum network_game_generic_state : short // made this up for Yelo's code
		{
			_network_game_generic_state_pregame,
			_network_game_generic_state_ingame,
			_network_game_generic_state_postgame,

			_network_game_generic_state_unknown,
			_network_game_generic_state,
		};
	};

	namespace Networking {
		static const const char * message_packet_to_string_table[] = {
			"client-broadcast_game_search",
			"client-ping",
			"server-game_advertise",
			"server-pong",
			"server-new_client_challenge",
			"server-machine_accepted",
			"server-machine_rejected",
			"server-game_is_ending_holdup",
			"server-game_settings_update",
			"server-pregame_countdown",
			"server-begin_game",
			"server-graceful_game_exit_pregame",
			"server-pregame_keep_alive",
			"server-postgame_keep_alive",
			"client-join_game_request",
			"client-add_player_request_pregame",
			"client-remove_player_request_pregame",
			"client-settings_request",
			"client-player_settings_request",
			"client-game_start_request",
			"client-graceful_game_exit_pregame",
			"client-map_is_precached_pregame",
			"server-game_update",
			"server-add_player_ingame",
			"server-remove_player_ingame",
			"server-game_over",
			"client-loaded",
			"client-game_update",
			"client-add_player_request_ingame",
			"client-remove_player_request_ingame",
			"client-graceful_game_exit_ingame",
			"client-host_crashed_cry_for_help",
			"client-join_new_host",
			"server-reconnect",
			"server-graceful_game_exit",
			"client-remove_player_request_postgame",
			"client-switch_to_pregame",
			"client-graceful_game_exit_postgame",
		};

		struct s_network_yelo_settings {
			bool gs_no_update_check;
			unsigned char  : 8;
			unsigned short : 16;
		};

		s_update_client_globals *UpdateClientGlobals()

		PTR_IMP_GET2(update_client_globals);

		s_update_server_globals *UpdateServerGlobals()

		PTR_IMP_GET2                   (update_server_globals);
		static s_network_yelo_settings g_network_yelo_settings;

		network_update_globals *UpdateSettings()

		PTR_IMP_GET2(network_update_globals);

		// Points to a static structure, 'network_game_server_memory_do_not_use_directly'
		s_network_game_server *NetworkGameServer() {
			{
				auto global_network_game_server = ppglobal_network_game_server);
				(void) ((!!((reinterpret_cast<void *>(0)) != global_network_game_server && (reinterpret_cast<void *>(0x1337BEEF)) != global_network_game_server)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != global_network_game_server && CAST_PTR(void*,PTR_NULL) != global_network_game_server", L"_file_name_", (unsigned) (82)), 0));
			}
			auto global_network_game_server = (*ppglobal_network_game_server);
			return global_network_game_server;
		};

		// Points to a static structure, 'network_game_client_memory_do_not_use_directly'
		s_network_game_client *NetworkGameClient() {
			{
				auto global_network_game_client = ppglobal_network_game_client);
				(void) ((!!((reinterpret_cast<void *>(0)) != global_network_game_client && (reinterpret_cast<void *>(0x1337BEEF)) != global_network_game_client)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != global_network_game_client && CAST_PTR(void*,PTR_NULL) != global_network_game_client", L"_file_name_", (unsigned) (84)), 0));
			}
			auto global_network_game_client = (*ppglobal_network_game_client);
			return global_network_game_client;
		};

		//////////////////////////////////////////////////////////////////////////
		// Player Hooks (join/leave)
		static void OnPlayerJoin(s_network_game_player *player) {
		}

		static void OnPlayerExit(s_network_game_player *player) {
		}

#pragma region OnPlayerJoinDelegate

		__declspec(naked) static void __cdecl OnPlayerJoinDelegate(s_network_game *network_game_data) {
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_ADD_PLAYER);

			API_FUNC_NAKED_START()
			push   esi
			mov      esi, eax // eax = struct s_network_player

			push   eax      // s_network_player.player_list_index
			call   OnPlayerJoin

			mov      eax, esi
			mov      esi, network_game_data
			push   esi
			call   CALL_ADDR
			add      esp, 4 * 1

			pop      esi
			API_FUNC_NAKED_END(0)
		}

#pragma endregion

		//#pragma region OnPlayerExitDelegate
		__declspec(naked) static void __cdecl OnPlayerExitDelegate() {
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_GAME_REMOVE_PLAYER);

			API_FUNC_NAKED_START_()
			push   ebx      // ebx = s_network_game
			push   eax      // save eax just in case the compiler does some nasty stuff

			push   eax      // s_network_player
			call   OnPlayerExit

			pop      eax
			pop      ebx

			call   CALL_ADDR
			API_FUNC_NAKED_END_()
		}
		//endregion

		static void Initialize() {
			Yelo::MessageDeltas::Initialize();
			GameSpy::Initialize();

			// NOTE: Uncomment these if you wish to detect
			// when players enter and leave
			Memory::WriteRelativeCall(OnPlayerJoinDelegate, GET_FUNC_VPTR(NETWORK_GAME_SERVER_ADD_PLAYER_TO_GAME__HOOK_ADD_PLAYER));
			Memory::WriteRelativeCall(OnPlayerExitDelegate, GET_FUNC_VPTR(CLIENT_MACHINE_CLEANUP__HOOK_REMOVE_PLAYER));
		}

		static void Dispose() {
			Yelo::MessageDeltas::Dispose();
			GameSpy::Dispose();
		}

		//////////////////////////////////////////////////////////////////////////

		static __declspec(naked) bool NetworkConnectionWrite(const s_network_connection &connection,
																		  const void *data, size_t data_size_in_bits,
																		  const void *header, size_t header_size_in_bits,
																		  BOOL unbuffered, BOOL flush_queue, long buffer_priority) {
			static const uintptr_t CALL_ADDR = GET_FUNC_PTR(NETWORK_CONNECTION_WRITE);

			API_FUNC_NAKED_START()
			push   edi
			push   ebx

			push   buffer_priority
			push   flush_queue
			push   unbuffered
			push   header_size_in_bits
			push   header
			mov      ebx, data_size_in_bits
			push   data
			mov      edi, connection
			call   CALL_ADDR
			add      esp, 4 * 6

			pop      ebx
			pop      edi
			API_FUNC_NAKED_END(8)
		}

		// Writes [data_size_in_bits] of the packet buffer to the connection
		// returns true if it was successful
		bool ConnectionWrite(const s_network_connection &connection,
									const void *data, size_t data_size_in_bits,
									const void *header, size_t header_size_in_bits,
									bool unbuffered = false, bool flush_queue = false, long buffer_priority = Enums::k_message_highest_priority) {
			return NetworkConnectionWrite(connection, data, data_size_in_bits, header, header_size_in_bits, unbuffered, flush_queue, buffer_priority);
		}

		bool ClientSendMessageToServer(
			const void *data, size_t data_size_in_bits,
			Enums::network_messsage_type message_type = Enums::_network_messsage_type_message_delta,
			bool unbuffered = false, bool flush_queue = false, long buffer_priority = Enums::k_message_highest_priority) {
			s_network_game_client      *client            = NetworkGameClient();
			const s_network_connection &client_connection = *client->connection;
			unsigned long              flags              = client_connection.flags;

			if (!TEST_FLAG(flags, Flags::_connection_create_server_bit)) {
				Enums::network_messsage_type header = Enums::_network_messsage_type_message_delta;
				return ConnectionWrite(client_connection,
											  data, data_size_in_bits,
											  &message_type, 1,
											  unbuffered, flush_queue, buffer_priority);
			}

			return false;
		}

		__declspec(naked) bool ServerSendRejectionMessage(s_network_game_player &rejected_player, Enums::transport_rejection_code code) {
			static const uintptr_t CALL_ADDR = NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE;

			API_FUNC_NAKED_START()
			push   esi

			call   GameState::IsServer
			test   al, al
			jz      not_a_server // al will be our return value, which would be 0 if this jmp is hit

			call   NetworkGameServer
			mov      esi, eax

			mov      ecx, code
			mov      eax, rejected_player
			push   esi
			call   CALL_ADDR
			add      esp, 4 * 1
			not_a_server:
			pop      esi
			API_FUNC_NAKED_END(2)
		}

		__declspec(naked) bool ServerHoldupNewClient(Yelo::Networking::s_network_client_machine &client_machine) {
			static const uintptr_t CALL_ADDR = NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE;

			API_FUNC_NAKED_START()
			call   GameState::IsServer
			test   al, al
			jz      not_a_server

			push   client_machine
			// function takes the server as a parameter in debug builds, but param is unreferenced in release builds
			call   CALL_ADDR
			add      esp, 4 * 1
			not_a_server:
			API_FUNC_NAKED_END(1)
		}

		// Sends [data] of the packet buffer to [machine_index]
		bool SvSendMessageToMachine(long machine_index,
											 const void *data, size_t data_size_in_bits,
											 Enums::network_messsage_type message_type = Enums::_network_messsage_type_message_delta,
											 BOOL unbuffered = false, BOOL flush_queue = false, BOOL write_to_local_connection = false,
											 long buffer_priority = Enums::k_message_highest_priority) {
			static const uintptr_t CALL_ADDR = NETWORK_GAME_SERVER_SEND_MESSAGE_TO_MACHINE;

			API_FUNC_NAKED_START()
			push   esi

			push   buffer_priority
			push   write_to_local_connection
			push   flush_queue
			push   unbuffered
			push   data_size_in_bits
			push   data
			push   message_type
			call   NetworkGameServer
			mov      esi, eax
			mov      eax, machine_index
			call   CALL_ADDR
			add      esp, 4 * 7

			pop      esi
			API_FUNC_NAKED_END(8)
		}

		// Sends [data] of the packet buffer to all machines
		bool SvSendMessageToAll(
			const void *data, size_t data_size_in_bits,
			Enums::network_messsage_type message_type = Enums::_network_messsage_type_message_delta,
			BOOL unbuffered = false, BOOL flush_queue = false, BOOL write_to_local_connection = false,
			long buffer_priority = Enums::k_message_highest_priority,
			BOOL ingame_only = false) {
			static const uintptr_t CALL_ALL_MACHINES = NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES;
			static const uintptr_t CALL_ALL_MACHINES_INGAME = NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES_INGAME;

			API_FUNC_NAKED_START()
			push	edi

			push	buffer_priority
			push	write_to_local_connection
			push	flush_queue
			push	unbuffered
			push	data
			push	message_type
			call	NetworkGameServer
			mov		ecx, eax
			mov		eax, data_size_in_bits

			mov		edi, ingame_only
			test	edi, edi
			jnz		all_machines_ingame
			call	CALL_ALL_MACHINES
			jmp		cleanup
			all_machines_ingame:
			call	CALL_ALL_MACHINES_INGAME
			cleanup:
			add		esp, 4 * 6

			pop		edi
			API_FUNC_NAKED_END(8)
		}

		// Sends [data] of the packet buffer to all machines ingame
		inline bool SvSendMessageToAllIngame(
			const void *data, size_t data_size_in_bits,
			Enums::network_messsage_type message_type = Enums::_network_messsage_type_message_delta,
			BOOL unbuffered = false, BOOL flush_queue = false, BOOL write_to_local_connection = false,
			long buffer_priority = Enums::k_message_highest_priority) {
			return SvSendMessageToAll(
				data, data_size_in_bits,
				message_type,
				unbuffered, flush_queue, write_to_local_connection,
				buffer_priority,
				true);
		}

		Enums::network_game_generic_state GetNetworkGameState() {
			if (GameState::IsClient())		return CAST(Enums::network_game_generic_state, NetworkGameClient()->state - Enums::_network_game_client_state_pregame);
			else if (GameState::IsServer()) return CAST(Enums::network_game_generic_state, NetworkGameServer()->state - Enums::_network_game_server_state_pregame);

			return Enums::_network_game_generic_state_unknown;
		}
	};
};
