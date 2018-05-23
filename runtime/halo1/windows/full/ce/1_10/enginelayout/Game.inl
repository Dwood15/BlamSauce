#pragma once

#include <rpcndr.h>
#include <cstdint>
#include "../../../../../../../BlamSauce/effects/particle/particle_systems.hpp"
#include "../../../../../../../BlamSauce/effects/contrail/contrails.hpp"
#include "../../../../../../../BlamSauce/memory/memory_interface_base.hpp"
#include "../../../../../../../BlamSauce/ai/actors/actor_structures.hpp"


#ifdef ENGINE_DPTR
#undef ENGINE_DPTR
#endif

#ifdef ENGINE_PTR
#undef ENGINE_PTR
#endif

#ifdef FUNC_PTR
#undef FUNC_PTR
#endif

#define ENGINE_PTR(type, name, ...) static auto* const name = CAST_PTR(type*, __VA_ARGS__);
#define DUO_PTR(...) __VA_ARGS__
#define FUNC_PTR(name, value, ...) static auto const name  =  value
#define CAST_PTR(type, ptr)      reinterpret_cast<type>(ptr)

//////////////////////////////////////////////////////////////////////////
// AI.cpp
static auto **const ai_globals = reinterpret_cast<s_ai_globals_data **>(K_AI_GLOBALS);;
static auto **const actors = reinterpret_cast<actor_data_t **>(K_ACTORS);;
static auto **const swarms = reinterpret_cast<swarm_data_t **>(K_SWARMS);;
static auto **const swarm_components = reinterpret_cast<swarm_component_data_t **>(K_SWARM_COMPONENTS);;
static auto **const props = reinterpret_cast<prop_data_t **>(K_PROPS);;
static auto **const encounters = reinterpret_cast<encounter_data_t **>(K_ENCOUNTERS);;
static auto **const squads = reinterpret_cast<squads_data_t **>(K_SQUADS);;
static auto **const platoons = reinterpret_cast<platoons_data_t **>(K_PLATOONS);;
static auto **const ai_pursuits = reinterpret_cast<ai_pursuit_data_t **>(K_AI_PURSUITS);;
	//ai_communication_dialogue_events_t
	static auto **const ai_communication_replies = reinterpret_cast<ai_communication_reply_events_t **>(K_AI_COMMUNICATION_REPLIES);;
static auto **const ai_conversations = reinterpret_cast<ai_conversation_data_t **>(K_AI_CONVERSATIONS);;

static auto const AI_UPDATE_HOOK = K_AI_UPDATE_HOOK;
static auto const ACTOR_ACTION_HANDLE_VEHICLE_EXIT_HOOK = K_ACTOR_ACTION_HANDLE_VEHICLE_EXIT_HOOK;
static auto const ACTOR_ACTION_HANDLE_VEHICLE_EXIT_RETN = K_ACTOR_ACTION_HANDLE_VEHICLE_EXIT_RETN;
static auto const PROP_STATUS_REFRESH_HOOK = K_PROP_STATUS_REFRESH_HOOK;
static auto const PROP_STATUS_REFRESH_RETN = K_PROP_STATUS_REFRESH_RETN;
static auto const ACTOR_INPUT_UPDATE_HOOK = K_ACTOR_INPUT_UPDATE_HOOK;
static auto const ACTOR_INPUT_UPDATE_RETN = K_ACTOR_INPUT_UPDATE_RETN;


//////////////////////////////////////////////////////////////////////////
// Camera.cpp
namespace Camera
{
	static auto *const observers = CAST_PTR;;
	static auto *const camera_script_globals = CAST_PTR;;
	static auto **const director_scripting = reinterpret_cast<s_director_scripting_data **>(K_DIRECTOR_SCRIPTING);;
	static auto **const cinematic_globals = reinterpret_cast<s_cinematic_globals_data **>(K_CINEMATIC_GLOBALS);;
	static auto *const global_director = CAST_PTR;;

	static auto const DIRECTOR_CHOOSE_GAME_PERSPECTIVE_HOOK = K_DIRECTOR_CHOOSE_GAME_PERSPECTIVE_HOOK;

	#if 0 // enable for old 3rd person camera hack
		FUNC_PTR(OBSERVER_UPDATE_COMMAND_HOOK,						K_OBSERVER_UPDATE_COMMAND_HOOK, FUNC_PTR_NULL);

		FUNC_PTR(DIRECTOR_GET_PERSPECTIVE_DEFAULT_SET,				K_DIRECTOR_GET_PERSPECTIVE_DEFAULT_SET, FUNC_PTR_NULL);
		FUNC_PTR(HUD_INITIALIZE_FOR_NEW_MAP_DEFAULT_SET_SHOW_HUD,	K_HUD_INITIALIZE_FOR_NEW_MAP_DEFAULT_SET_SHOW_HUD, FUNC_PTR_NULL);
		FUNC_PTR(HUD_ADD_ITEM_MESSAGE_DEFAULT_SET_SHOW_MSG,			K_HUD_ADD_ITEM_MESSAGE_DEFAULT_SET_SHOW_MSG, FUNC_PTR_NULL);
	#endif
};

namespace Fov
{
	static auto const OBSERVER_UPDATE_COMMAND_HOOK = K_OBSERVER_UPDATE_COMMAND_HOOK;

	static auto const OBSERVER_UPDATE_POSITIONS = K_OBSERVER_UPDATE_POSITIONS;
	static auto *const OBSERVER_UPDATE_POSITIONS_no_scope_blur = CAST_PTR;;
	// Address of the call opcodes to [OBSERVER_UPDATE_POSITIONS] inside the function
	// known as [OBSERVER_TICK]
	static auto const OBSERVER_TICK_CALL_HOOK_OBSERVER_UPDATE_POSITIONS = K_OBSERVER_TICK_CALL_HOOK_OBSERVER_UPDATE_POSITIONS;

	static auto *const MAX_FOV_CHECK_JMP = CAST_PTR;;
};

//////////////////////////////////////////////////////////////////////////
// Campaign.cpp. CLIENT BUILDS ONLY
	#pragma region Scenario Paths
	static cstring** ScenarioPathsReferences[] = {
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE_0),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE_1),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE_2),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE_3),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE_4),
		//CAST_PTR(cstring**, K_SCENARIO_PATHS_REFERENCE_5),
	};

	static cstring** ScenarioPathsReferences2[] = {
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE2_0),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE2_1),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE2_2),
		reinterpret_cast<cstring **>(K_SCENARIO_PATHS_REFERENCE2_3),
	};
	#pragma endregion

	#pragma region Scenario Help
static auto const DISPLAY_SCENARIO_HELP_HOOK = K_DISPLAY_SCENARIO_HELP_HOOK;
static auto const DISPLAY_SCENARIO_HELP_SUCCESS = K_DISPLAY_SCENARIO_HELP_SUCCESS;
static auto const DISPLAY_SCENARIO_HELP_FAIL = K_DISPLAY_SCENARIO_HELP_FAIL;
	#pragma endregion

	#pragma region Campaign Level Data
	static void** CampaignLevelDataReferences[] = {
		reinterpret_cast<void **>(K_CAMPAIGN_LEVEL_DATA_REFERENCE_0),
		reinterpret_cast<void **>(K_CAMPAIGN_LEVEL_DATA_REFERENCE_1),
		reinterpret_cast<void **>(K_CAMPAIGN_LEVEL_DATA_REFERENCE_2),
		reinterpret_cast<void **>(K_CAMPAIGN_LEVEL_DATA_REFERENCE_3),
		//CAST_PTR(void**, K_CAMPAIGN_LEVEL_DATA_REFERENCE_4),
		//CAST_PTR(void**, K_CAMPAIGN_LEVEL_DATA_REFERENCE_5),
		//CAST_PTR(void**, K_CAMPAIGN_LEVEL_DATA_REFERENCE_6),
	};

	static size_t* CampaignLevelDataSizeReferences[] = {
		reinterpret_cast<size_t *>(K_CAMPAIGN_LEVEL_DATA_SIZE_REFERENCE_0),
		reinterpret_cast<size_t *>(K_CAMPAIGN_LEVEL_DATA_SIZE_REFERENCE_1),
		reinterpret_cast<size_t *>(K_CAMPAIGN_LEVEL_DATA_SIZE_REFERENCE_2),
	};
	#pragma endregion

	#pragma region Campaign Level Count
	static byte* CampaignLevelCountReferences_8bit[] = {
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE_8BIT_0),
		//CAST_PTR(byte*, K_CAMPAIGN_LEVEL_COUNT_REFERENCE_8BIT_1),
	};

	static short* CampaignLevelCountReferences_16bit[] = {
		reinterpret_cast<short *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE_16BIT_0),
	};

	static long* CampaignLevelCountReferences_32bit[] = {
		reinterpret_cast<long *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE_32BIT_0),
		//CAST_PTR(long*, K_CAMPAIGN_LEVEL_COUNT_REFERENCE_32BIT_1),
	};

	//////////////////////////////////////////////////////////////////////////

	static byte* CampaignLevelCountReferences2_8bit[] = {
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_0),
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_1),
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_2),
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_3),
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_4),
		reinterpret_cast<byte *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_5),
		//CAST_PTR(byte*, K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_8BIT_6),
	};

	static short* CampaignLevelCountReferences2_16bit[] = {
		reinterpret_cast<short *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_16BIT_0),
		reinterpret_cast<short *>(K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_16BIT_1),
		//CAST_PTR(short*, K_CAMPAIGN_LEVEL_COUNT_REFERENCE2_16BIT_2),
	};
	#pragma endregion


//////////////////////////////////////////////////////////////////////////
// Console.cpp
static auto **const terminal_globals = reinterpret_cast<s_terminal_globals **>(K_TERMINAL_GLOBALS);;
static auto *const console_globals = reinterpret_cast<s_console_globals *>(K_CONSOLE_GLOBALS);;

static auto const CONSOLE_UPDATE_HOOK = K_CONSOLE_UPDATE_HOOK;


//////////////////////////////////////////////////////////////////////////
// Effects.cpp
static auto **const contrails = reinterpret_cast<contrail_data_t **>(K_CONTRAILS);;
static auto **const contrail_points = reinterpret_cast<contrail_point_data_t **>(K_CONTRAIL_POINTS);;
static auto **const particles = reinterpret_cast<particle_data_t **>(K_PARTICLES);;
static auto **const effects = reinterpret_cast<effect_data_t **>(K_EFFECTS);;
static auto **const effect_locations = reinterpret_cast<effect_location_data_t **>(K_EFFECT_LOCATIONS);;
static auto **const particle_systems = reinterpret_cast<particle_systems_data_t **>(K_PARTICLE_SYSTEMS);;
static auto **const particle_system_particles = reinterpret_cast<particle_system_particles_data_t **>(K_PARTICLE_SYSTEM_PARTICLES);;
static auto **const structure_detail_objects = reinterpret_cast<s_structure_detail_objects_data **>(K_STRUCTURE_DETAIL_OBJECTS);;
static auto **const structure_decals = reinterpret_cast<s_structure_decals_data **>(K_STRUCTURE_DECALS);;
static auto **const breakable_surface_globals = reinterpret_cast<s_breakable_surface_globals_data **>(K_BREAKABLE_SURFACE_GLOBALS);;
static auto **const decals = reinterpret_cast<decals_data_t **>(K_DECALS);;
static auto **const decal_globals = reinterpret_cast<s_decal_globals_data **>(K_DECAL_GLOBALS);;
static auto **const decal_vertex_cache = reinterpret_cast<s_decal_vertex_cache_data **>(K_DECAL_VERTEX_CACHE);;

static auto const EFFECTS_UPDATE_HOOK = K_EFFECTS_UPDATE_HOOK;

		static void* K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[] = {
			reinterpret_cast<void *>(K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_0),
			reinterpret_cast<void *>(K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_1),
			reinterpret_cast<void *>(K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_2),
			reinterpret_cast<void *>(K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_3),
			reinterpret_cast<void *>(K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_4),
		};

static auto const GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLES = K_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLES;
static auto const GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECTS = K_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECTS;
static auto const GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECT_LOCATIONS = K_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECT_LOCATIONS;
static auto const GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLE_SYSTEM_PARTICLES = K_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLE_SYSTEM_PARTICLES;


//////////////////////////////////////////////////////////////////////////
// EngineFunctions.cpp


//////////////////////////////////////////////////////////////////////////
// GameBuildNumber.cpp
static auto *const game_build_version = reinterpret_cast<char *>(K_GAME_BUILD_VERSION);;
static auto *const game_build_version_gamespy = reinterpret_cast<char *>(K_GAME_BUILD_VERSION_GAMESPY);;

static auto *const network_version_id1 = reinterpret_cast<Enums::network_game_protocol_id *>(K_NETWORK_VERSION_ID1);;
static auto *const network_version_id2 = reinterpret_cast<Enums::network_game_protocol_id *>(K_NETWORK_VERSION_ID2);;
static auto *const network_version_id3 = reinterpret_cast<Enums::network_game_protocol_id *>(K_NETWORK_VERSION_ID3);;

static auto const GAME_STATE_HEADER_IS_VALID_HOOK = K_GAME_STATE_HEADER_IS_VALID_HOOK;
static auto const GAME_STATE_HEADER_IS_VALID_HOOK_RET = K_GAME_STATE_HEADER_IS_VALID_HOOK_RET;
static auto const GAME_STATE_HEADER_TRY_AND_LOAD_HOOK = K_GAME_STATE_HEADER_TRY_AND_LOAD_HOOK;
static auto const GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_TRUE = K_GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_TRUE;
static auto const GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_FALSE = K_GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_FALSE;


//////////////////////////////////////////////////////////////////////////
// GameEngine.cpp
static auto *const ctf_globals = reinterpret_cast<s_ctf_globals *>(K_CTF_GLOBALS);;
static auto *const slayer_globals = reinterpret_cast<s_slayer_globals *>(K_SLAYER_GLOBALS);;
static auto *const oddball_globals = reinterpret_cast<s_oddball_globals *>(K_ODDBALL_GLOBALS);;
static auto *const king_globals = reinterpret_cast<s_king_globals *>(K_KING_GLOBALS);;
static auto *const race_globals = reinterpret_cast<s_race_globals *>(K_RACE_GLOBALS);;

static auto *const global_variant = reinterpret_cast<s_game_variant *>(K_GLOBAL_VARIANT);;

static auto **const game_engines = reinterpret_cast<game_engine_definition **>(K_GAME_ENGINES);;
static auto **const game_engine = reinterpret_cast<game_engine_definition **>(K_GAME_ENGINE);;

	#pragma region New Engines functions
	//////////////////////////////////////////////////////////////////////////
	// FixHudRenderUnitInterface()
	static auto const HUD_RENDER_UNIT_INTERFACE_JMP_TABLE = K_HUD_RENDER_UNIT_INTERFACE_JMP_TABLE;
static auto *const hud_render_unit_interface_jmp_ptr = CAST_PTR;;

	//////////////////////////////////////////////////////////////////////////
	// FixFunc4F7440()
	static auto const Func4F7440JmpTable = K_FUNC4F7440JMPTABLE;
static auto *const Func4F7440JmpPtr = reinterpret_cast<void ***>(K_FUNC4F7440JMPPTR);;

	//////////////////////////////////////////////////////////////////////////
	// FixFunc4F7580()
	static auto const Func4F7580JmpTable = K_FUNC4F7580JMPTABLE;
static auto *const Func4F7580JmpPtr = reinterpret_cast<void ***>(K_FUNC4F7580JMPPTR);;

	//////////////////////////////////////////////////////////////////////////
	// Initialize()
	static auto *const game_engine_init_mod = reinterpret_cast<game_engine_definition ***>(K_GAME_ENGINE_INIT_MOD);;
	#pragma endregion

static auto const GAME_ENGINE_INITIALIZE_FOR_NEW_MAP_HOOK = K_GAME_ENGINE_INITIALIZE_FOR_NEW_MAP_HOOK;
static auto const GAME_ENGINE_UPDATE_HOOK = K_GAME_ENGINE_UPDATE_HOOK;


//////////////////////////////////////////////////////////////////////////
// GameState.cpp
	static uintptr_t K_GAME_STATE_BEFORE_SAVE_PROCS_CALLS[] = {
		K_GAME_STATE_BEFORE_SAVE_PROCS_CALL_0,
		K_GAME_STATE_BEFORE_SAVE_PROCS_CALL_1,
	};
	static uintptr_t K_GAME_STATE_BEFORE_LOAD_PROCS_CALLS[] = {	
		K_GAME_STATE_BEFORE_LOAD_PROCS_CALL_0,
		K_GAME_STATE_BEFORE_LOAD_PROCS_CALL_1,
		K_GAME_STATE_BEFORE_LOAD_PROCS_CALL_2,
	};
	static uintptr_t K_GAME_STATE_AFTER_LOAD_PROCS_REFS[] = {
		K_GAME_STATE_AFTER_LOAD_PROCS_REF_0,
		K_GAME_STATE_AFTER_LOAD_PROCS_REF_1,
		K_GAME_STATE_AFTER_LOAD_PROCS_REF_2,
	};
	static uintptr_t K_GAME_STATE_AFTER_LOAD_PROCS_COUNTS[] = {
		K_GAME_STATE_AFTER_LOAD_PROCS_COUNT_0,
		K_GAME_STATE_AFTER_LOAD_PROCS_COUNT_1,
		K_GAME_STATE_AFTER_LOAD_PROCS_COUNT_2,
	};

static auto *const main_globals = reinterpret_cast<s_main_globals *>(K_MAIN_GLOBALS);;

static auto *const physical_memory_globals = reinterpret_cast<s_physical_memory_map_globals *>(K_PHYSICAL_MEMORY_GLOBALS);;
static auto const PHYSICAL_MEMORY_INITIALIZE = K_PHYSICAL_MEMORY_INITIALIZE;
	DATA_PTR(PHYSICAL_MEMORY_ALLOCATION_SIZE,							K_PHYSICAL_MEMORY_ALLOCATION_SIZE);

static auto *const game_state_globals = reinterpret_cast<s_game_state_globals *>(K_GAME_STATE_GLOBALS);;
static auto **const game_globals = reinterpret_cast<s_game_globals **>(K_GAME_GLOBALS);;
static auto **const game_time_globals = reinterpret_cast<s_game_time_globals **>(K_GAME_TIME_GLOBALS);;
static auto **const game_allegiance_globals = reinterpret_cast<s_game_allegiance_globals **>(K_GAME_ALLEGIANCE_GLOBALS);;

static auto *const global_game_globals = reinterpret_cast<TagGroups::s_game_globals **>(K_GLOBAL_GAME_GLOBALS);;
static auto *const global_physics = reinterpret_cast<s_physics_globals *>(K_GLOBAL_PHYSICS);;
static auto *const global_point_physics = reinterpret_cast<s_point_physics_globals *>(K_GLOBAL_POINT_PHYSICS);;

static auto *const developer_mode = reinterpret_cast<byte *>(K_DEVELOPER_MODE);;
static auto *const transport_dumping = reinterpret_cast<bool *>(K_TRANSPORT_DUMPING);;
static auto *const init_txt_filename = CAST_PTR;
static auto *const devmode_enabled = reinterpret_cast<bool *>(K_DEVMODE_ENABLED);;

static auto const GAME_INITIALIZE_HOOK = K_GAME_INITIALIZE_HOOK;
static auto const GAME_INITIALIZE_FOR_NEW_MAP_HOOK = K_GAME_INITIALIZE_FOR_NEW_MAP_HOOK;
static auto const GAME_DISPOSE_FROM_OLD_MAP_HOOK = K_GAME_DISPOSE_FROM_OLD_MAP_HOOK;
	static void** K_GAME_SCENARIO_SWITCH_BSP_CALLS[] =
	{
		reinterpret_cast<void **>(K_GAME_SCENARIO_SWITCH_BSP_CALL_0),
		reinterpret_cast<void **>(K_GAME_SCENARIO_SWITCH_BSP_CALL_1),
		reinterpret_cast<void **>(K_GAME_SCENARIO_SWITCH_BSP_CALL_2),
		reinterpret_cast<void **>(K_GAME_SCENARIO_SWITCH_BSP_CALL_3),
		reinterpret_cast<void **>(K_GAME_SCENARIO_SWITCH_BSP_CALL_4),
	};
static auto const GAME_DISPOSE_FROM_OLD_BSP_HOOK = K_GAME_DISPOSE_FROM_OLD_BSP_HOOK;

static auto const GAME_SERVER_QR2_STRING_MATCHES_GAMEVER_CALL = K_GAME_SERVER_QR2_STRING_MATCHES_GAMEVER_CALL;

static auto const GAME_CREATE_NETWORK_SERVER = K_GAME_CREATE_NETWORK_SERVER;
static auto const GAME_CREATE_NETWORK_CLIENT = K_GAME_CREATE_NETWORK_CLIENT;
static auto const GAME_CREATE_NETWORK_SERVER_CALL = K_GAME_CREATE_NETWORK_SERVER_CALL;

	static void** K_GAME_CREATE_NETWORK_CLIENT_CALL[] =
	{
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_0),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_1),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_2),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_3),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_4),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_5),
		reinterpret_cast<void **>(K_GAME_CREATE_NETWORK_CLIENT_CALL_6),
	};

//////////////////////////////////////////////////////////////////////////
// Lights.cpp
static auto **const lights = reinterpret_cast<lights_data_t **>(K_LIGHTS);;
static auto **const light_game_globals = reinterpret_cast<s_lights_globals_data **>(K_LIGHT_GAME_GLOBALS);;
static auto **const light_cluster = reinterpret_cast<s_light_cluster_data **>(K_LIGHT_CLUSTER);;
static auto **const cluster_light_reference = reinterpret_cast<cluster_light_reference_data_t **>(K_CLUSTER_LIGHT_REFERENCE);;
static auto **const light_cluster_reference = reinterpret_cast<light_cluster_reference_data_t **>(K_LIGHT_CLUSTER_REFERENCE);;


//////////////////////////////////////////////////////////////////////////
// Players.cpp
static auto **const players = reinterpret_cast<players_data_t **>(K_PLAYERS);;
static auto **const teams = reinterpret_cast<teams_data_t **>(K_TEAMS);;
static auto **const players_globals = reinterpret_cast<s_players_globals_data **>(K_PLAYERS_GLOBALS);;
static auto **const player_control_globals = reinterpret_cast<s_player_control_globals_data **>(K_PLAYER_CONTROL_GLOBALS);;
static auto **const player_effects = reinterpret_cast<s_player_effects_data **>(K_PLAYER_EFFECTS);;
static auto *const machine_to_player_table = reinterpret_cast<datum_index *>(K_MACHINE_TO_PLAYER_TABLE);;

static auto const PLAYER_SPAWN__CREATE_UNIT_MP_HOOK = K_PLAYER_SPAWN__CREATE_UNIT_MP_HOOK;
static auto const PLAYER_SPAWN__CREATE_UNIT_MP_HOOK_RETN = K_PLAYER_SPAWN__CREATE_UNIT_MP_HOOK_RETN;

static auto const PLAYERS_UPDATE_BEFORE_GAME_SERVER_HOOK = K_PLAYERS_UPDATE_BEFORE_GAME_SERVER_HOOK;
static auto const PLAYERS_UPDATE_BEFORE_GAME_CLIENT_HOOK = K_PLAYERS_UPDATE_BEFORE_GAME_CLIENT_HOOK;
static auto const PLAYERS_UPDATE_AFTER_GAME_HOOK = K_PLAYERS_UPDATE_AFTER_GAME_HOOK;
	
//////////////////////////////////////////////////////////////////////////
// Players.NearbyObjects
static auto const PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE_RETN = K_PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE_RETN;
static auto *const player_examine_nearby_objects_server_jmp_ptr = reinterpret_cast<void ***>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_PTR);;
static auto *const PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_LAST_ENTRY_TYPE = reinterpret_cast<byte *>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_LAST_ENTRY_TYPE);;
static auto *const PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE = reinterpret_cast<void ***>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE);;

static auto const PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE_RETN = K_PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE_RETN;
static auto *const player_examine_nearby_objects_client_jmp_ptr = reinterpret_cast<void ***>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_PTR);;
static auto *const PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_LAST_ENTRY_TYPE = reinterpret_cast<byte *>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_LAST_ENTRY_TYPE);;
static auto *const PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE = reinterpret_cast<void ***>(K_PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE);;
	
//////////////////////////////////////////////////////////////////////////
// Players.ActionResults
static auto const PLAYER_HANDLE_ACTION_JMP_TABLE_ADJUST_SIZE = K_PLAYER_HANDLE_ACTION_JMP_TABLE_ADJUST_SIZE;
static auto const PLAYER_HANDLE_ACTION_JMP_TABLE_RETN = K_PLAYER_HANDLE_ACTION_JMP_TABLE_RETN;
static auto *const PLAYER_HANDLE_ACTION_LAST_ENTRY_TYPE = reinterpret_cast<byte *>(K_PLAYER_HANDLE_ACTION_LAST_ENTRY_TYPE);;
static auto *const player_handle_action_jmp_ptr = reinterpret_cast<void ***>(K_PLAYER_HANDLE_ACTION_JMP_PTR);;
static auto *const PLAYER_HANDLE_ACTION_JMP_TABLE = reinterpret_cast<void ***>(K_PLAYER_HANDLE_ACTION_JMP_TABLE);;

static auto const FOLLOWING_CAMERA_GET_UNIT_CAMERA_INFO_CALL = K_FOLLOWING_CAMERA_GET_UNIT_CAMERA_INFO_CALL;
