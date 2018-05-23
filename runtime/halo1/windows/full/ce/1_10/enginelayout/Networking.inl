#include <memory_locations.h>
#include "../../../../../../../BlamSauce/memory/memory_interface_base.hpp"

#ifdef ENGINE_DPTR
#undef ENGINE_DPTR
#endif

#ifdef ENGINE_PTR
#undef ENGINE_PTR
#endif

#ifdef FUNC_PTR
#undef FUNC_PTR
#endif

#define ENGINE_DPTR(type, name, ...) static auto** const name = reinterpret_cast<type**>(__VA_ARGS__);
#define ENGINE_PTR(type, name, ...) static auto* const name = CAST_PTR(type*, __VA_ARGS__);

#define FUNC_PTR(name, value) static auto const name  =  value


//////////////////////////////////////////////////////////////////////////
// MDP.hpp
static auto const MDP_FIELD_ENCODE_ARRAY = (K_MDP_FIELD_ENCODE_ARRAY);
static auto const MDP_FIELD_DECODE_ARRAY = (K_MDP_FIELD_DECODE_ARRAY);

static auto *const pmessage_delta_field_integer_small = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_INTEGER_SMALL));;
static auto *const pmessage_delta_field_integer_medium = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_INTEGER_MEDIUM));;
static auto *const pmessage_delta_field_integer_large = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_INTEGER_LARGE));;
static auto *const pmessage_delta_field_real = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_REAL));;
static auto *const pmessage_delta_field_boolean = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_BOOLEAN));;
static auto *const pmessage_delta_field_ascii_character = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_ASCII_CHARACTER));;
static auto *const pmessage_delta_field_time = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_TIME));;
static auto *const pmessage_delta_field_grenade_counts = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_GRENADE_COUNTS));;
static auto *const pmessage_delta_field_locality_reference_position = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_LOCALITY_REFERENCE_POSITION));;
static auto *const pmessage_delta_field_digital_throttle = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_DIGITAL_THROTTLE));;
static auto *const pmessage_delta_field_fixed_width_weapon_index = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_WEAPON_INDEX));;
static auto *const pmessage_delta_field_fixed_width_grenade_index = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_GRENADE_INDEX));;
static auto *const pmessage_delta_field_item_placement_position = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_ITEM_PLACEMENT_POSITION));;

static auto *const pmessage_delta_field_local_player_update_sequence_number = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_LOCAL_PLAYER_UPDATE_SEQUENCE_NUMBER));;
static auto *const pmessage_delta_field_remote_player_update_sequence_number = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_REMOTE_PLAYER_UPDATE_SEQUENCE_NUMBER));;
static auto *const pmessage_delta_field_remote_player_action_update_baseline_id = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_REMOTE_PLAYER_ACTION_UPDATE_BASELINE_ID));;
static auto *const pmessage_delta_field_update_tick_count = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_UPDATE_TICK_COUNT));;
static auto *const pmessage_delta_field_update_id = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_UPDATE_ID));;
static auto *const pmessage_delta_field_fixed_width_3bits = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_3BITS));;
static auto *const pmessage_delta_field_fixed_width_6bits = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_6BITS));;
static auto *const pmessage_delta_field_fixed_width_1bit = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_1BIT));;
static auto *const pmessage_delta_field_fixed_width_normal_4bit = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_NORMAL_4BIT));;
static auto *const pmessage_delta_field_fixed_width_normal_8bit = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_NORMAL_8BIT));;
static auto *const pmessage_delta_field_fixed_width_normal_16bit = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_FIXED_WIDTH_NORMAL_16BIT));;
static auto *const pmessage_delta_field_object_index = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_OBJECT_INDEX));;
static auto *const pmessage_delta_field_player_index = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_PLAYER_INDEX));;
static auto *const pmessage_delta_field_definition_index = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_DEFINITION_INDEX));;
static auto *const pmessage_delta_field_point2d = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_POINT2D));;
static auto *const pmessage_delta_field_point3d = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_POINT3D));;
static auto *const pmessage_delta_field_vector2d = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_VECTOR2D));;
static auto *const pmessage_delta_field_vector3d = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_VECTOR3D));;
static auto *const pmessage_delta_field_control_flags = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_CONTROL_FLAGS));;
static auto *const pmessage_delta_field_angular_velocity = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_ANGULAR_VELOCITY));;
static auto *const pmessage_delta_field_translational_velocity = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_TRANSLATIONAL_VELOCITY));;
static auto *const pmessage_delta_field_map_name = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_MAP_NAME));;
static auto *const pmessage_delta_field_network_map = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_NETWORK_MAP));;
static auto *const pmessage_delta_field_network_player_name = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_NETWORK_PLAYER_NAME));;
static auto *const pmessage_delta_field_network_player = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_NETWORK_PLAYER));;
static auto *const pmessage_delta_field_network_game_name = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_NETWORK_GAME_NAME));;
static auto *const pmessage_delta_field_network_game_players = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_NETWORK_GAME_PLAYERS));;
static auto *const pmessage_delta_field_game_variant = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_GAME_VARIANT));;
static auto *const pmessage_delta_field_game_variant_human_readable_description = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_GAME_VARIANT_HUMAN_READABLE_DESCRIPTION));;
static auto *const pmessage_delta_field_universal_variant = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_UNIVERSAL_VARIANT));;
static auto *const pmessage_delta_field_universal_variant_flags = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_UNIVERSAL_VARIANT_FLAGS));;
static auto *const pmessage_delta_field_game_engine_variant = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_GAME_ENGINE_VARIANT));;
static auto *const pmessage_delta_field_game_variant_flags = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_GAME_VARIANT_FLAGS));;
static auto *const pmessage_delta_field_parameters_protocol_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_PARAMETERS_PROTOCOL_ARRAY));;
static auto *const pmessage_delta_field_hud_chat_message = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_HUD_CHAT_MESSAGE));;
static auto *const pmessage_delta_field_hud_chat_message_ptr = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_HUD_CHAT_MESSAGE_PTR));;
static auto *const pmessage_delta_field_object_change_colors = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_OBJECT_CHANGE_COLORS));;
static auto *const pmessage_delta_field_ctf_score_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_CTF_SCORE_ARRAY));;
static auto *const pmessage_delta_field_race_score_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_RACE_SCORE_ARRAY));;
static auto *const pmessage_delta_field_king_score_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_KING_SCORE_ARRAY));;
static auto *const pmessage_delta_field_oddball_score_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_ODDBALL_SCORE_ARRAY));;
static auto *const pmessage_delta_field_oddball_owner_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_ODDBALL_OWNER_ARRAY));;
static auto *const pmessage_delta_field_slayer_score_array = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_SLAYER_SCORE_ARRAY));;
static auto *const pmessage_delta_field_damage_data_flags = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_DAMAGE_DATA_FLAGS));;
static auto *const pmessage_delta_field_motd_text = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_MOTD_TEXT));;
static auto *const pmessage_delta_field_rcon_response = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_RCON_RESPONSE));;
static auto *const pmessage_delta_field_rcon_password = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_RCON_PASSWORD));;
static auto *const pmessage_delta_field_rcon_command = reinterpret_cast<field_properties_definition *>((K_MESSAGE_DELTA_FIELD_RCON_COMMAND));;

static auto *const pmessage_delta_empty_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_EMPTY_FIELD_SET));;

	//ENGINE_PTR(field_reference_set, message_delta_guaranteed_object_header_field_set,					0x0, 0x0);
	static auto *const pmessage_delta_game_object_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_GAME_OBJECT_HEADER_FIELD_SET));;
static auto *const pmessage_delta_game_object_timestamped_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_GAME_OBJECT_TIMESTAMPED_HEADER_FIELD_SET));;
static auto *const pmessage_delta_biped_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_BIPED_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_ctf_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_CTF_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_client_game_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_CLIENT_GAME_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_player_score_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_PLAYER_SCORE_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_remote_player_action_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_REMOTE_PLAYER_ACTION_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_remote_player_position_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_REMOTE_PLAYER_POSITION_UPDATE_HEADER_FIELD_SET));;
static auto *const pmessage_delta_remote_player_total_update_header_field_set = reinterpret_cast<field_reference_set *>((K_MESSAGE_DELTA_REMOTE_PLAYER_TOTAL_UPDATE_HEADER_FIELD_SET));;
	//ENGINE_PTR(field_reference_set, message_delta__header_field_set, 0, PTR_UNKNOWN);


//////////////////////////////////////////////////////////////////////////
// MessageDefinitions.cpp

	// Currently there is nothing to add here


//////////////////////////////////////////////////////////////////////////
// MessageDeltas.cpp
static auto *const pmessage_delta_parameters = reinterpret_cast<s_message_delta_parameters *>((K_MESSAGE_DELTA_PARAMETERS));;
static auto *const pmessage_delta_global_field_type_list = reinterpret_cast<field_type_definition *>((K_MESSAGE_DELTA_GLOBAL_FIELD_TYPE_LIST));;
static auto *const pg_message_delta_encoding_class = reinterpret_cast<Enums::message_delta_encoding_class *>((K_G_MESSAGE_DELTA_ENCODING_CLASS));;
static auto *const pg_exposed_params = reinterpret_cast<exposed_parameters_t *>((K_G_EXPOSED_PARAMS));;
static auto *const pmdp_parameters_protocol_globals = reinterpret_cast<s_parameters_protocol_globals *>((K_MDP_PARAMETERS_PROTOCOL_GLOBALS));;

static auto *const pmdp_packet_buffer_received_data = reinterpret_cast<byte *>((K_MDP_PACKET_BUFFER_RECEIVED_DATA));;
static auto *const pmdp_packet_buffer_sent_data = reinterpret_cast<byte *>((K_MDP_PACKET_BUFFER_SENT_DATA));;

static auto **const ppmessage_delta_packets = reinterpret_cast<message_delta_definition **>(K_MESSAGE_DELTA_PACKETS);
static_assert(K_MESSAGE_DELTA_PACKETS != 0);;

		#pragma region MessageDeltaPointerReferences
		static void** MessageDeltaPointerReferences[] = {
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_0),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_1),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_2),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_3),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_4),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_5),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_6),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_7),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_8),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_9),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_10),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_11),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_12),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_13),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_14),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_15),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_16),
			(reinterpret_cast<void **>K_MESSAGE_DELTA_POINTER_REFERENCE_17),
		};
		#pragma endregion

		#pragma region MessageDeltaPointerEndChecks
		static void** MessageDeltaPointerEndChecks[] = {
			(reinterpret_cast<void **>(K_MESSAGE_DELTA_POINTER_END_CHECK_0)),
			(reinterpret_cast<void **>(K_MESSAGE_DELTA_POINTER_END_CHECK_1)),
			(reinterpret_cast<void **>(K_MESSAGE_DELTA_POINTER_END_CHECK_2)),
		};

		static byte* MessageDeltaTypeCountChecks8bit[] = {
			(reinterpret_cast<byte *>(K_MESSAGE_DELTA_TYPE_COUNT_CHECK_8BIT_0)),
		};
		#pragma endregion

static auto const NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED = (K_NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED);
static auto const NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED_CALL1 = (K_NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED_CALL1);
static auto const NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED_CALL2 = (K_NETWORK_GAME_CLIENT_GAME_SETTINGS_UPDATED_CALL2);

static auto const NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY_CALL = (K_NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY_CALL);
enum DATA_PTR_DONT_SEND_OBJECT_NEW_MSG { PTR_DONT_SEND_OBJECT_NEW_MSG = K_DONT_SEND_OBJECT_NEW_MSG };
static_assert(PTR_DONT_SEND_OBJECT_NEW_MSG != 0);
static auto const NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY = K_NETWORK_GAME_CLIENT_HANDLE_MESSAGE_DELTA_MESSAGE_BODY;

static auto *const pglobal_network_game_server_data = reinterpret_cast<Networking::s_network_game_server *>(K_GLOBAL_NETWORK_GAME_SERVER_DATA);;
static auto *const pglobal_network_game_client_data = reinterpret_cast<Networking::s_network_game_client *>(K_GLOBAL_NETWORK_GAME_CLIENT_DATA);;

static auto const MDPI_ENCODE = (K_MDPI_ENCODE);
static auto const MDP_DECODE_STATELESS_ITERATED = (K_MDP_DECODE_STATELESS_ITERATED);
static auto const MDP_DECODE_INCREMENTAL_ITERATED = (K_MDP_DECODE_INCREMENTAL_ITERATED);
static auto const MDP_DISCARD_ITERATION_BODY = (K_MDP_DISCARD_ITERATION_BODY);


//////////////////////////////////////////////////////////////////////////
// Networking.cpp
static auto *const pupdate_client_globals = reinterpret_cast<s_update_client_globals *>(K_UPDATE_CLIENT_GLOBALS);;
static auto *const pupdate_server_globals = reinterpret_cast<s_update_server_globals *>(K_UPDATE_SERVER_GLOBALS);;
static auto *const pnetwork_update_globals = reinterpret_cast<network_update_globals *>(K_NETWORK_UPDATE_GLOBALS);;
static auto **const ppglobal_network_game_server = reinterpret_cast<s_network_game_server **>(K_GLOBAL_NETWORK_GAME_SERVER);
static_assert(K_GLOBAL_NETWORK_GAME_SERVER != 0);
static auto **const ppglobal_network_game_client = reinterpret_cast<s_network_game_client **>(K_GLOBAL_NETWORK_GAME_CLIENT);
static_assert(K_GLOBAL_NETWORK_GAME_CLIENT != 0);

static auto const NETWORK_GAME_ADD_PLAYER = (K_NETWORK_GAME_ADD_PLAYER);
static auto const NETWORK_GAME_SERVER_ADD_PLAYER_TO_GAME__HOOK_ADD_PLAYER = (K_NETWORK_GAME_SERVER_ADD_PLAYER_TO_GAME__HOOK_ADD_PLAYER);
static auto const NETWORK_GAME_REMOVE_PLAYER = (K_NETWORK_GAME_REMOVE_PLAYER);
	// just a few bytes after this gets called is another call to ngrp, but its for the s_network_client's game member
	static auto const CLIENT_MACHINE_CLEANUP__HOOK_REMOVE_PLAYER = (K_CLIENT_MACHINE_CLEANUP__HOOK_REMOVE_PLAYER);

static auto const NETWORK_CONNECTION_WRITE = (K_NETWORK_CONNECTION_WRITE);
static auto const NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE = (K_NETWORK_GAME_SERVER_SEND_REJECTION_MESSAGE);
static auto const NETWORK_GAME_SERVER_HOLDUP_NEW_CLIENT = (K_NETWORK_GAME_SERVER_HOLDUP_NEW_CLIENT);
static auto const NETWORK_GAME_SERVER_SEND_MESSAGE_TO_MACHINE = (K_NETWORK_GAME_SERVER_SEND_MESSAGE_TO_MACHINE);
static auto const NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES = (K_NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES);
static auto const NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES_INGAME = (K_NETWORK_GAME_SERVER_SEND_MESSAGE_TO_ALL_MACHINES_INGAME);


//////////////////////////////////////////////////////////////////////////
// Server.cpp
	namespace Networking
	{
		static auto *const psv_password = reinterpret_cast<wchar_t *>(K_SV_PASSWORD);;
		static auto *const psv_rcon_password = reinterpret_cast<char *>(K_SV_RCON_PASSWORD);;
		static auto *const psv_timelimit = reinterpret_cast<long *>(K_SV_TIMELIMIT);;
		static auto *const phalo_argv_port = reinterpret_cast<long *>(K_HALO_ARGV_PORT);;
		static auto *const phalo_argv_client_port = reinterpret_cast<long *>(K_HALO_ARGV_CLIENT_PORT);;
	};

	//////////////////////////////////////////////////////////////////////////
	// Server
	namespace Server
	{
		static auto *const pnetwork_sv_file_globals = reinterpret_cast<s_network_sv_file_globals *>((K_NETWORK_SV_FILE_GLOBALS));;
		static auto *const pnetwork_sv_mapcycle_globals = reinterpret_cast<s_network_sv_mapcycle_globals *>((K_NETWORK_SV_MAPCYCLE_GLOBALS));;
		static auto *const pnetwork_sv_globals = reinterpret_cast<s_network_sv_globals *>((K_NETWORK_SV_GLOBALS));;

		// ENGINE_PTR(long, server_instance,			PTR_NULL, K_SERVER_INSTANCE);
		//
		// FUNC_PTR(SV_EVENT_LOG_WITH_TIME,			FUNC_PTR_NULL, K_SV_EVENT_LOG_WITH_TIME);
		// FUNC_PTR(SV_EVENT_ECHO,						FUNC_PTR_NULL, K_SV_EVENT_ECHO);
		//
		// ENGINE_PTR(bool, event_type_logging,		PTR_NULL, K_EVENT_TYPE_LOGGING);
		// ENGINE_PTR(bool, event_type_echoing,		PTR_NULL, K_EVENT_TYPE_ECHOING);
		//
		// ENGINE_PTR(wcstring*, log_entry_titles,		PTR_NULL, K_LOG_ENTRY_TITLES);
		// ENGINE_PTR(wcstring*, log_entry_titles_ref,	PTR_NULL, K_LOG_ENTRY_TITLES_REF);
		//
		// static byte** K_EVENT_ENABLE_LOGGING_0_REFS[] =
		// {
		// 	CAST_PTR(byte**, K_EVENT_ENABLE_LOGGING_0_REF_0),
		// 	CAST_PTR(byte**, K_EVENT_ENABLE_LOGGING_0_REF_1)
		// };
		//
		// ENGINE_PTR(byte**, event_enable_logging_4_ref, PTR_NULL, K_EVENT_ENABLE_LOGGING_4_REF);
		// ENGINE_PTR(byte**, event_enable_logging_8_ref, PTR_NULL, K_EVENT_ENABLE_LOGGING_8_REF);
		// ENGINE_PTR(byte**, event_enable_logging_12_ref, PTR_NULL, K_EVENT_ENABLE_LOGGING_12_REF);
		//
		// static byte** K_EVENT_ENABLE_ECHOING_0_REFS[] =
		// {
		// 	CAST_PTR(byte**, K_EVENT_ENABLE_ECHOING_0_REF_0),
		// 	CAST_PTR(byte**, K_EVENT_ENABLE_ECHOING_0_REF_1),
		// 	CAST_PTR(byte**, K_EVENT_ENABLE_ECHOING_0_REF_2)
		// };
		//
		// ENGINE_PTR(byte**, event_enable_echoing_2_ref, PTR_NULL, K_EVENT_ENABLE_ECHOING_2_REF);
		// ENGINE_PTR(byte**, event_enable_echoing_3_ref, PTR_NULL, K_EVENT_ENABLE_ECHOING_3_REF);
		// ENGINE_PTR(byte**, event_enable_echoing_4_ref, PTR_NULL, K_EVENT_ENABLE_ECHOING_4_REF);
		// ENGINE_PTR(byte**, event_enable_echoing_8_ref, PTR_NULL, K_EVENT_ENABLE_ECHOING_8_REF);
		// ENGINE_PTR(byte**, event_enable_echoing_12_ref, PTR_NULL, K_EVENT_ENABLE_ECHOING_12_REF);
	};


//////////////////////////////////////////////////////////////////////////
// GameSpyApi.cpp
	namespace Networking
	{
		static auto **const ppgs_Socket = reinterpret_cast<s_gamespy_socket **>((K_GS_SOCKET));
		static_assert((K_GS_SOCKET) != 0);;
		static auto **const ppgs_LoopbackSocket = reinterpret_cast<s_gamespy_socket **>((K_GS_LOOPBACKSOCKET));
		static_assert((K_GS_LOOPBACKSOCKET) != 0);;
		static auto *const pgamespy_config = reinterpret_cast<s_gamespy_config *>((K_GAMESPY_CONFIG));;
		static auto *const pgamespy_globals = reinterpret_cast<s_gamespy_globals *>((K_GAMESPY_GLOBALS));;
		static auto *const pgamespy_server_browser_globals = reinterpret_cast<s_gamespy_server_browser_globals *>((K_GAMESPY_SERVER_BROWSER_GLOBALS));;
		static auto **const ppgamespy_qr2 = reinterpret_cast<s_gamespy_qr2 **>((K_GAMESPY_QR2));
		static_assert((K_GAMESPY_QR2) != 0);;
		static auto *const pg_gamespy_patch_check_for_updates = reinterpret_cast<bool *>(K_G_GAMESPY_PATCH_CHECK_FOR_UPDATES, 0x1337BEEF);;

		static auto *const pgamespy_products_list = reinterpret_cast<s_gamespy_product *>((K_GAMESPY_PRODUCTS_LIST));; // [4]

		enum DATA_PTR_compiler_null_string { PTR_compiler_null_string = PLATFORM_VALUE((K_COMPILER_NULL_STRING)) };static_assert(PTR_compiler_null_string != 0);; // TODO: not the best place for this...
		static auto const GAMESPY_GET_CLIENT_KEY_HASH = (K_GAMESPY_GET_CLIENT_KEY_HASH);
		DATA_PTR(GAMESPY_PATCH_SPAWN_CHECK_FOR_UPDATES_THREAD_CALL,					K_GAMESPY_PATCH_SPAWN_CHECK_FOR_UPDATES_THREAD_CALL, DATA_PTR_NULL);

		namespace GameSpy
		{
			static auto *const pMatchup1Hostname = reinterpret_cast<cstring *>((K_MATCHUP1_HOSTNAME));;
			static auto *const pMatchup2Hostname = reinterpret_cast<cstring *>((K_MATCHUP2_HOSTNAME));;
			static auto *const pMASTER_ADDR_REFERENCE = reinterpret_cast<cstring *>((K_MASTER_ADDR_REFERENCE));;
			static auto *const pMASTER_ADDR_SB_REFERENCE = reinterpret_cast<cstring *>((K_MASTER_ADDR_SB_REFERENCE));;
			static auto *const pPTA_DEFAULT_VERCHECK_URL_REFERENCE = reinterpret_cast<cstring *>((K_PTA_DEFAULT_VERCHECK_URL_REFERENCE));;

			static auto const CREATE_GAMESPY_QR2_HOOK = (K_CREATE_GAMESPY_QR2_HOOK);
			static auto const QR2_REGISTER_KEY = (K_QR2_REGISTER_KEY);
		};
	};


