#include <precompile.h>
#include "../../../../../../BlamSauce/interface/input/player_control.h"
#include "../../../../../../BlamSauce/interface/hud/hud.hpp"
#include "../../../../../../BlamSauce/interface/hud/hud_messaging.hpp"
#include "../../../../../../BlamSauce/interface/hud/hud_unit.hpp"
#include "../../../../../../BlamSauce/interface/hud/hud_weapon.hpp"
#include "../../../../../../BlamSauce/interface/hud/hud_nav_points.hpp"
#include "../../../../../../BlamSauce/interface/hud/motion_sensor.hpp"
#include "../../../../../../BlamSauce/interface/hud/first_person_weapons.hpp"
#include "../../../../../../BlamSauce/interface/strings/draw_string.hpp"
#include "../../../../../../BlamSauce/interface/hud/hud_chat.hpp"
#include "../../../../../../BlamSauce/models/animations/recorded_animations.hpp"
#include "../../../../../../BlamSauce/hs/object_lists.hpp"
#include "../../../../../../BlamSauce/hs/structures.hpp"

#pragma once
// TODO: Make this whole thing _not_ suck as bad as it does. :)
//	FUNC_PTR(INPUT_UPDATE_HOOK,						K_INPUT_UPDATE_HOOK, FUNC_PTR_NULL);
static auto const INPUT_UPDATE_HOOK = (uintptr_t) 0x493856;
static auto *const InputStateFlags    = CAST_PTR(byte*, 0x6AD572);
static auto *const ControlState       = CAST_PTR(Yelo::Input::ControlStates*, 0x64C550);
static auto *const MousePositionState = CAST_PTR(Yelo::Input::PositionState*, 0x6B4008);
static auto *const Settings           = CAST_PTR(Yelo::Input::ControlSettings*, 0x6AD802);

namespace Yelo::GameUI {
	//#define FUNC_PTR(name, ...)  enum FUNC_PTR_##name  { PTR_##name = PLATFORM_VALUE_HACK_((__VA_ARGS__)) }; static_assert( GET_FUNC_PTR(name) != NULL );


	//FUNC_PTR(HUD_UPDATE,										K_HUD_UPDATE, FUNC_PTR_NULL);
	//FUNC_PTR(HUD_UPDATE_CALL,									K_HUD_UPDATE_CALL, FUNC_PTR_NULL);
	//FUNC_PTR(FIRST_PERSON_WEAPONS_UPDATE,						K_FIRST_PERSON_WEAPONS_UPDATE, FUNC_PTR_NULL);
	//FUNC_PTR(FIRST_PERSON_WEAPONS_UPDATE_CALL,					K_FIRST_PERSON_WEAPONS_UPDATE_CALL, FUNC_PTR_NULL);
	//FUNC_PTR(FIRST_PERSON_WEAPON_SET_STATE_HOOK,				K_FIRST_PERSON_WEAPON_SET_STATE_HOOK, FUNC_PTR_NULL);

	enum HUD_UPDATE {
		PTR_HUD_UPDATE  = 0x512360,
		HUD_UPDATE_CALL = 0x45C1A2
	};

	enum FIRST_PERSON_WEAPONS {
		FIRST_PERSON_WEAPONS_UPDATE        = 0x45AFA0,
		FIRST_PERSON_WEAPONS_UPDATE_CALL   = 0x45C17E,
		FIRST_PERSON_WEAPON_SET_STATE_HOOK = 0x495E19
	};

	static auto *const text_bounds_globals  = CAST_PTR(s_text_bounds_globals_data*, 0x67F6D4);
	static auto *const font_drawing_globals = CAST_PTR(s_font_drawing_globals_data*, 0x67F6E8);
	static auto *const hud_chat_globals     = CAST_PTR(s_hud_chat_globals*, 0x64E788);
	static auto *const hud_chat_line_count  = CAST_PTR(long*, 0x6B44B4);

	//ENGINE_DPTR(type, name, ...) static auto** const pp##name = CAST_PTR(type**, PLATFORM_VALUE(__VA_ARGS__)); static_assert( PLATFORM_VALUE(__VA_ARGS__) != NULL );
	static auto **const hud_scripted_globals = CAST_PTR(Yelo::GameUI::s_hud_scripted_globals**, 0x6B44A8);
	static auto **const hud_messaging        = CAST_PTR(s_hud_messaging**, 0x64E970);
	static auto **const hud_unit_interface   = CAST_PTR(s_hud_unit_interface**, 0x6B44BC);
	static auto **const hud_weapon_interface = CAST_PTR(s_hud_weapon_interface**, 0x6B44C0);
	static auto **const hud_nav_points       = CAST_PTR(s_hud_nav_points**, 0x64E974);
	static auto **const motion_sensor        = CAST_PTR(s_motion_sensor**, 0x6B44C8);
	static auto **const first_person_weapons = CAST_PTR(s_first_person_weapons**, 0x64DCC8);

}

namespace Yelo::Hud {

#pragma region ShowCrosshair
	static auto *const RENDER_CROSSHAIRS_DISABLE_MOD = CAST_PTR(unsigned short*, 0x4B60F1);
#pragma endregion

#pragma region Scale
	// FUNC_PTR(RENDER_WIDGET_RECURSIVE,							K_RENDER_WIDGET_RECURSIVE, PTR_NULL);
	enum RENDER_WIDGET_RECURSIVE { PTR_RENDER_WIDGET_RECURSIVE = 0x49D850 };
	static void **K_RENDER_WIDGET_RECURSIVE_CALLS[]  = {
		CAST_PTR(void**, 0x49B42A),
		CAST_PTR(void**, 0x49B506),
		CAST_PTR(void**, 0x49DB4E),
		CAST_PTR(void**, 0x49E589),
		CAST_PTR(void**, 0x49EA81),
		CAST_PTR(void**, 0x49EABF),
	};

	static void *K_RASTERIZER_RENDER_UI_SET_SCREENPROJ_CALLS[] = {
		CAST_PTR(void*, 0x520485),
		CAST_PTR(void*, 0x534C57),
		CAST_PTR(void*, 0x52F429),
	};
#pragma endregion
	//#define FUNC_PTR(name, ...)
	//enum FUNC_PTR_##name  { PTR_##name = PLATFORM_VALUE_HACK_((__VA_ARGS__)) }; static_assert( GET_FUNC_PTR(name) != NULL );

#pragma region render nav points
	// FUNC_PTR(HUD_RENDER_NAV_POINTS,								K_HUD_RENDER_NAV_POINTS, PTR_NULL);
	enum FUNC_PTR_HUD_RENDER_NAV_POINTS { PTR_HUD_RENDER_NAV_POINTS = 0x4B2F80 };

	enum FUNC_PTR_HUD_RENDER_NAV_POINTS_CALL { PTR_HUD_RENDER_NAV_POINTS_CALL = 0x4ACAED };

	static auto *const HUD_RENDER_NAV_POINT_ANCHOR_HALF_X = CAST_PTR(uint*, 0x4B2B01);
	static auto *const HUD_RENDER_NAV_POINT_ANCHOR_HALF_Y = CAST_PTR(uint*, 0x4B2B0B);

	static auto *const HUD_ANCHOR_SCREEN_X = CAST_PTR(real*, 0x612268);
	static auto *const HUD_ANCHOR_SCREEN_Y = CAST_PTR(real*, 0x000124);

	static auto *const HUD_ANCHOR_SCREEN_HALF_X = CAST_PTR(real*, 0x000028);
	static auto *const HUD_ANCHOR_SCREEN_HALF_Y = CAST_PTR(real*, 0x000020);
#pragma endregion

#pragma region render team indicator
	//enum FUNC_PTR_HUD_RENDER_NAV_POINTS_CALL { PTR_HUD_RENDER_NAV_POINTS_CALL = 0x4ACAED};
	enum FUNC_PTR_HUD_RENDER_PLAYERS { PTR_HUD_RENDER_PLAYERS = 0x4AD830 };
	enum FUNC_PTR_HUD_RENDER_PLAYERS_CALL { PTR_HUD_RENDER_PLAYERS_CALL = 0x4ACA6E };
#pragma endregion

#pragma region render scoreboard
	//enum FUNC_PTR_HUD_RENDER_NAV_POINTS_CALL { PTR_HUD_RENDER_NAV_POINTS_CALL = 0x4ACAED};
	enum FUNC_PTR_HUD_RENDER_SCOREBOARD_INGAME { PTR_HUD_RENDER_SCOREBOARD_INGAME = 0x45FC50 };
	enum FUNC_PTR_HUD_RENDER_SCOREBOARD_INGAME_CALL { PTR_HUD_RENDER_SCOREBOARD_INGAME_CALL = 0x497892 };
	enum FUNC_PTR_HUD_RENDER_SCOREBOARD_POSTGAME { PTR_HUD_RENDER_SCOREBOARD_POSTGAME = 0x45E090 };
	enum FUNC_PTR_HUD_RENDER_SCOREBOARD_POSTGAME_CALL { PTR_HUD_RENDER_SCOREBOARD_POSTGAME_CALL = 0x497889 };
#pragma endregion

#pragma region hud
	static auto *const HUD_POINT_ANCHOR_WIDTH       = CAST_PTR(uint*, 0x4AEAF0);
	static auto *const HUD_POINT_ANCHOR_HEIGHT      = CAST_PTR(uint*, 0x4AEB22);
	static auto *const HUD_POINT_ANCHOR_HALF_WIDTH  = CAST_PTR(uint*, 0x4AEB42);
	static auto *const HUD_POINT_ANCHOR_HALF_HEIGHT = CAST_PTR(uint*, 0x4AEB66);

	static auto *const HUD_POINT_DAMAGE_ANCHOR_WIDTH       = CAST_PTR(uint*, 0x4B49A5);
	static auto *const HUD_POINT_DAMAGE_ANCHOR_HEIGHT      = CAST_PTR(uint*, 0x4B497E);
	static auto *const HUD_POINT_DAMAGE_ANCHOR_HALF_HEIGHT = CAST_PTR(real*, 0x4B49BF);

	static void **K_HUD_POINT_DAMAGE_ANCHOR_HALF_WIDTH_PTRS[] = {CAST_PTR(void**, 0x4B499A), CAST_PTR(void**, 0x4B495A)};
#pragma endregion

#pragma region multiplayer icons
	static auto *const HUD_MULTIPLAYER_ICON_CTF_x = CAST_PTR(unsigned short*, 0x4B4684);
	static auto *const HUD_MULTIPLAYER_ICON_CTF_Y = CAST_PTR(unsigned short*, 0x4B468B);

	static auto *const HUD_MULTIPLAYER_ICON_KING_X = CAST_PTR(unsigned short*, 0x4B46B6);

	static auto *const HUD_MULTIPLAYER_ICON_ODDBALL_x = CAST_PTR(unsigned short*, 0x4B46E1);
	static auto *const HUD_MULTIPLAYER_ICON_ODDBALL_Y = CAST_PTR(unsigned short*, 0x4B46E8);

	static auto *const HUD_MULTIPLAYER_ICON_RACE_X = CAST_PTR(unsigned short*, 0x4B4710);
	static auto *const HUD_MULTIPLAYER_ICON_RACE_Y = CAST_PTR(unsigned short*, 0x4B4717);

	static auto *const HUD_MULTIPLAYER_ICON_SLAYER_X = CAST_PTR(unsigned short*, 0x4B473F);

	static auto *const HUD_MULTIPLAYER_ICON_BACKGROUND_x = CAST_PTR(unsigned short*, 0x4B47EA);
	static auto *const HUD_MULTIPLAYER_ICON_BACKGROUND_Y = CAST_PTR(unsigned short*, 0x4B47F1);
#pragma endregion

	static auto **const hud_globals = CAST_PTR(void**, 0x6B44A4);

};

namespace Yelo::Keystone {
	enum FUNC_PTR_KEYSTONE_CHATLOG_ADD_ITEM_SEND_MESSAGE { PTR_KEYSTONE_CHATLOG_ADD_ITEM_SEND_MESSAGE = 0x4AE8A0 };

	static auto const ChatLogName = CAST_PTR(wchar_t*, 0x4B47EA);

	//#define ENGINE_PTR(type, name, ...) static auto* const p##name = CAST_PTR(type*, PLATFORM_VALUE(__VA_ARGS__));  static_assert( PLATFORM_VALUE(__VA_ARGS__) != NULL );
	//The Triple pointer here is _on purpose_.
	static auto *const MainWindow = CAST_PTR(void***, 0x4B47EA);

	enum FUNC_PTR_KS_TRANSLATEACCELERATOR_CALL { PTR_KS_TRANSLATEACCELERATOR_CALL = 0x4AE8A0 };
	enum FUNC_PTR_KS_TRANSLATEACCELERATOR { PTR_KS_TRANSLATEACCELERATOR = 0x4AE8A0 };
	enum FUNC_PTR_KS_GETWINDOW { PTR_KS_GETWINDOW = 0x4AE8A0 };
	enum FUNC_PTR_KW_RELEASE { PTR_KW_RELEASE = 0x4AE8A0 };
	enum FUNC_PTR_KW_GETCONTROLBYID { PTR_KW_GETCONTROLBYID = 0x4AE8A0 };
	enum FUNC_PTR_KC_SENDMESSAGE { PTR_KC_SENDMESSAGE = 0x4AE8A0 };

}

namespace Yelo::GameUI::Widget {
	enum FUNC_PTR_UI_WIDGET_LOAD_BY_NAME_OR_TAG { PTR_UI_WIDGET_LOAD_BY_NAME_OR_TAG = 0x49AA00 };
}

#ifdef ENGINE_DPTR
#undef ENGINE_DPTR
#endif

#ifdef ENGINE_PTR
#undef ENGINE_PTR
#endif

#ifdef FUNC_PTR
#undef FUNC_PTR
#endif

#define ENGINE_PTR(type, name, value) static auto* const name = CAST_PTR(type*, value); static_assert( value != NULL )
#define FUNC_PTR(name, value) static auto const name  =  value

ENGINE_PTR(const void*, gather_exception_data, 0x6BDE8C);
FUNC_PTR(GATHER_EXCEPTION, 0x582060);
FUNC_PTR(RASTERIZER_SET_TEXTURE_BITMAP_DATA, 0x51BF30);

FUNC_PTR(RESOLUTION_LIST_ADD_RESOLUTION, 0x4BE1B0);

FUNC_PTR(ANIMATION_CHOOSE_RANDOM_PERMUTATION_INTERNAL, 0x4D9680);

FUNC_PTR(GSMD5DIGEST, 0x5BF440);

FUNC_PTR(SHELL_GET_COMMAND_LINE_ARGUMENT, 0x545B70);

//////////////////////////////////////////////////////////////////////////
// AI
FUNC_PTR(ACTOR_DELETE, 0x427E60);
FUNC_PTR(ACTOR_UPDATE, 0x429160);
FUNC_PTR(ACTOR_CUSTOMIZE_UNIT, 0x426CF0);
FUNC_PTR(ACTOR_SET_ACTIVE, 0x4276E0);
FUNC_PTR(ACTOR_SET_DORMANT, 0x427860);
FUNC_PTR(ACTOR_DELETE_PROPS, 0x427E00);
FUNC_PTR(ACTOR_FREEZE, 0x429000);
FUNC_PTR(ACTOR_CREATE_FOR_UNIT, 0x426AC0);
FUNC_PTR(ACTOR_ACTION_CHANGE, 0x40D8D0);
FUNC_PTR(AI_SCRIPTING_ATTACH_FREE, 0x435420);

//////////////////////////////////////////////////////////////////////////
// Cache
FUNC_PTR(CACHE_FILE_READ_REQUEST, 0x443410);
FUNC_PTR(SOUND_CACHE_SOUND_REQUEST, 0x444770);
FUNC_PTR(TEXTURE_CACHE_BITMAP_GET_HARDWARE_FORMAT, 0x444EB0);
FUNC_PTR(PHYSICAL_MEMORY_MAP_PREDICT_RESOURCES, 0x445350);

//////////////////////////////////////////////////////////////////////////
// Camera
FUNC_PTR(DIRECTOR_DESIRED_PERSPECTIVE, 0x446480);

//////////////////////////////////////////////////////////////////////////
// Console
FUNC_PTR(CONSOLE_PROCESS_COMMAND, 0x4C9DC0);
FUNC_PTR(CONSOLE_PRINTF, 0x4C9BC0);
FUNC_PTR(CONSOLE_RESPONSE_PRINTF, 0x4C9C60);
FUNC_PTR(CONSOLE_WARNING, 0x4C9D20);

//////////////////////////////////////////////////////////////////////////
// Cheats
FUNC_PTR(CHEAT_ALL_WEAPONS, 0x45AEA0);
FUNC_PTR(CHEAT_SPAWN_WARTHOG, 0x47FA50);
FUNC_PTR(CHEAT_TELEPORT_TO_CAMERA, 0x45AFA0);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE, 0x45B030);
FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE_LOCAL_PLAYER, 0x45B090);
FUNC_PTR(CHEAT_PLAYER_INDEX, 0x45B110);
FUNC_PTR(DIRECTOR_SAVE_CAMERA, 0x4461E0);
FUNC_PTR(DIRECTOR_LOAD_CAMERA, 0x4462A0);

//////////////////////////////////////////////////////////////////////////
// Effects
FUNC_PTR(EFFECT_NEW_ON_OBJECT_MARKER, 0x48B520);

//////////////////////////////////////////////////////////////////////////
// Game
FUNC_PTR(SCENARIO_SWITCH_STRUCTURE_BSP, 0x542210);
FUNC_PTR(BINK_PLAYBACK_START, 0x43ED20);
FUNC_PTR(GAME_ENGINE_RASTERIZE_MESSAGE, 0x462A80);
FUNC_PTR(GAME_TEAM_IS_ENEMY, 0x45C6C0);
FUNC_PTR(GAME_ENGINE_PLAY_MULTIPLAYER_SOUND, 0x46EA60);

//////////////////////////////////////////////////////////////////////////
// HS
FUNC_PTR(OBJECT_LIST_ADD, 0x48DEE0);

//////////////////////////////////////////////////////////////////////////
// Input
FUNC_PTR(INPUT_KEY_IS_DOWN, 0x493910);

//////////////////////////////////////////////////////////////////////////
// Interface
FUNC_PTR(KEYSTONE_CHAT_LOG_ADD_STRING, 0x4AE8A0); // I forget if the dedicated has a chat log equivalent...
FUNC_PTR(HUD_PRINT_MESSAGE, 0x4B1570);
FUNC_PTR(HUD_GET_ITEM_MESSAGE, 0x4AD400);
FUNC_PTR(HUD_DRAW_METER, 0x4AEFB0);
FUNC_PTR(HUD_DRAW_NUMBERS, 0x4AF4A0);
// FUNC_PTR(HUD_DRAW_STATIC_ELEMENT,				K_HUD_DRAW_STATIC_ELEMENT);
FUNC_PTR(HUD_DRAW_BITMAP, 0x4AFEC0);
FUNC_PTR(MAINMENU_LOAD, 0x4CBDC0);

//////////////////////////////////////////////////////////////////////////
// Items
FUNC_PTR(WEAPON_PREVENTS_MELEE_ATTACK, 0x4C62A0);
FUNC_PTR(WEAPON_PREVENTS_GRENADE_THROWING, 0x4C62F0);
FUNC_PTR(WEAPON_STOP_RELOAD, 0x4C7F10);
FUNC_PTR(FIRST_PERSON_WEAPON_MESSAGE_FROM_UNIT, 0x4954F0);
FUNC_PTR(WEAPON_GET_FIRST_PERSON_ANIMATION_TIME, 0x4C6340);

//////////////////////////////////////////////////////////////////////////
// Math
FUNC_PTR(PERIODIC_FUNCTION_EVALUATE, 0x4CFDB0);
FUNC_PTR(TRANSITION_FUNCTION_EVALUATE, 0x4CFEC0);

//////////////////////////////////////////////////////////////////////////
// Memory
FUNC_PTR(DATA_NEW, 0x4D3770);
FUNC_PTR(DATUM_NEW_AT_INDEX, 0x4D37D0);
FUNC_PTR(DATUM_NEW, 0x4D3880);
FUNC_PTR(DATUM_DELETE, 0x4D3910);
FUNC_PTR(DATA_DELETE_ALL, 0x4D3980);
FUNC_PTR(DATA_ITERATOR_NEXT, 0x4D39D0);
FUNC_PTR(DATA_NEXT_INDEX, 0x4D3A30);
FUNC_PTR(DATUM_TRY_AND_GET, 0x4D3A80);
FUNC_PTR(DATUM_INITIALIZE, 0x4D3AC0);

//////////////////////////////////////////////////////////////////////////
// Models
FUNC_PTR(MODEL_FIND_MARKER, 0x4DABC0);

//////////////////////////////////////////////////////////////////////////
// Networking
FUNC_PTR(HUD_CHAT_TO_NETWORK, 0x4ADD40);
FUNC_PTR(INDEX_RESOLUTION_TABLE_TRANSLATE, 0x4F3EF0);
FUNC_PTR(MAIN_CONNECT, 0x4CB800);

//////////////////////////////////////////////////////////////////////////
// Objects
FUNC_PTR(HS_OBJECT_ORIENT, 0x48AB80);

FUNC_PTR(OBJECT_HEADER_BLOCK_ALLOCATE, 0x4FB760);
FUNC_PTR(OBJECT_ITERATOR_NEXT, 0x4FA830);

FUNC_PTR(OBJECT_PLACEMENT_DATA_NEW, 0x4F8CB0);
FUNC_PTR(OBJECT_NEW, 0x4F8D70);
FUNC_PTR(OBJECT_NEW_WITH_ROLE, 0x4F8DC0);
FUNC_PTR(OBJECT_DELETE_TO_NETWORK, 0x4F93B0);
FUNC_PTR(OBJECT_DELETE, 0x4F94E0);
FUNC_PTR(OBJECT_ATTACH_TO_MARKER, 0x4F9A90);
FUNC_PTR(OBJECT_DETACH, 0x4F9F20);
FUNC_PTR(OBJECTS_FIND_IN_SPHERE, 0x4FA8F0);
FUNC_PTR(OBJECT_START_INTERPOLATION, 0x4FA480);
FUNC_PTR(OBJECT_RESET, 0x4F8A70);
FUNC_PTR(OBJECT_RECONNECT_TO_MAP, 0x4F9540);
FUNC_PTR(OBJECT_DISCONNECT_FROM_MAP, 0x4F96F0);
FUNC_PTR(OBJECT_GET_ORIGIN, 0x4FA210);
FUNC_PTR(OBJECT_GET_ORIENTATION, 0x4FA280);
FUNC_PTR(OBJECT_GET_LOCATION, 0x4FA420);
FUNC_PTR(OBJECT_SET_POSITION, 0x4F8AD0);
FUNC_PTR(OBJECT_SET_POSITION_NETWORK, 0x4F8BD0);
FUNC_PTR(OBJECT_RESTORE_BODY, 0x4F12E0);
FUNC_PTR(OBJECT_DEPLETE_BODY, 0x4F1330);
FUNC_PTR(OBJECT_DEPLETE_SHIELD, 0x4F1420);
FUNC_PTR(OBJECT_DOUBLE_CHARGE_SHIELD, 0x4F14B0);
FUNC_PTR(OBJECT_CAUSE_DAMAGE, 0x4F1EF0);
FUNC_PTR(OBJECT_DEFINITION_PREDICT, 0x4FB3E0);
FUNC_PTR(OBJECT_SET_SCALE, 0x4FCFB0);
FUNC_PTR(OBJECT_GET_LEVEL_OF_DETAIL_PIXELS, 0x512FB0);
FUNC_PTR(OBJECT_RENDER_STATE_REFRESH, 0x512B80);
FUNC_PTR(OBJECTS_UPDATE, 0x4F87A0);
FUNC_PTR(OBJECT_UPDATE, 0x4FB800);
FUNC_PTR(OBJECT_GET_MARKER_BY_NAME, 0x4F9990);
FUNC_PTR(OBJECT_DESTROY, 0x4F1590);

//////////////////////////////////////////////////////////////////////////
// Units
FUNC_PTR(UNIT_UPDATE, 0x565A70);
FUNC_PTR(UNIT_GET_CAMERA_POSITION, 0x56C440);
FUNC_PTR(UNIT_SET_ANIMATION, 0x5722D0);
FUNC_PTR(UNIT_ANIMATION_START_ACTION, 0x5692C0);
FUNC_PTR(UNIT_GET_CUSTOM_ANIMATION_TIME, 0x5738B0);
FUNC_PTR(UNIT_CAN_ENTER_SEAT, 0x569D00);
FUNC_PTR(UNIT_ENTER_SEAT, 0x569E30);
FUNC_PTR(UNIT_EXIT_VEHICLE, 0x56ECF0);
FUNC_PTR(UNIT_OPEN, 0x56E210);
FUNC_PTR(UNIT_CLOSE, 0x56E230);
FUNC_PTR(UNIT_FIND_NEARBY_SEAT, 0x569A20);
FUNC_PTR(UNIT_EXIT_SEAT_END, 0x56FD40);
FUNC_PTR(UNIT_CAN_SEE_POINT, 0x56F800);
FUNC_PTR(UNIT_TRY_AND_EXIT_SEAT, 0x56FB70);
FUNC_PTR(UNIT_DETACH_FROM_PARENT, 0x570140);
FUNC_PTR(UNIT_START_USER_ANIMATION, 0x5739A0);
FUNC_PTR(UNIT_DROP_CURRENT_WEAPON, 0x5715C0);
FUNC_PTR(UNIT_DAMAGE_AFTERMATH, 0x56A960);
FUNC_PTR(UNIT_SCRIPTING_SET_CURRENT_VITALITY, 0x565040);
FUNC_PTR(UNIT_ANIMATION_SET_STATE, 0x569450);
FUNC_PTR(UNIT_INVENTORY_GET_WEAPON, 0x56D070);
FUNC_PTR(UNIT_THROW_GRENADE_RELEASE, 0x571B40);
FUNC_PTR(UNIT_CAUSE_PLAYER_MELEE_DAMAGE, 0x572C50);
FUNC_PTR(UNIT_SET_ACTIVELY_CONTROLLED, 0x56D2F0);
FUNC_PTR(UNIT_READY_DESIRED_WEAPON, 0x570DE0);

//////////////////////////////////////////////////////////////////////////
// Physics
FUNC_PTR(COLLISION_TEST_VECTOR, 0x509190);

//////////////////////////////////////////////////////////////////////////
// Players
FUNC_PTR(PLAYER_INDEX_FROM_UNIT_INDEX, 0x477970);
FUNC_PTR(PLAYER_TELEPORT, 0x478820);
FUNC_PTR(PLAYER_OVER_SHIELD_SCREEN_EFFECT, 0x47C250);
FUNC_PTR(PLAYER_CAMO_SCREEN_EFFECT, 0x47C310);
FUNC_PTR(PLAYER_HEALTH_PACK_SCREEN_EFFECT, 0x47C3D0);
FUNC_PTR(FIND_CLOSEST_PLAYER_INDEX, 0x45ECD0);
FUNC_PTR(PLAYER_EXAMINE_NEARBY_VEHICLE, 0x47B140);
FUNC_PTR(PLAYER_SET_ACTION_RESULT, 0x47B940);
FUNC_PTR(PLAYER_SET_ACTION_RESULT_TO_NETWORK, 0x47BB30);
FUNC_PTR(PLAYER_CONTROL_GET_UNIT_CAMERA_INFO, 0x474C00);



//////////////////////////////////////////////////////////////////////////
// Render
FUNC_PTR(RENDER_FRAME, 0x50F7B0);
FUNC_PTR(RENDER_WINDOW, 0x50F8C0);

//////////////////////////////////////////////////////////////////////////
// Scenario
FUNC_PTR(SCENARIO_TRIGGER_VOLUME_TEST_POINT, 0x542380);

//////////////////////////////////////////////////////////////////////////
// TagGroups
FUNC_PTR(TAG_LOADED, 0x442990);
FUNC_PTR(TAG_ITERATOR_NEXT, 0x442A10);
FUNC_PTR(UNICODE_STRING_LIST_GET_STRING, 0x55AD90);

//////////////////////////////////////////////////////////////////////////
// Scripting.cpp
static auto **const recorded_animations = CAST_PTR(Yelo::Scripting::recorded_animations_data_t**, 0x64B940);
static auto **const object_list_header = CAST_PTR(Yelo::Scripting::object_list_header_data_t**, 0x815904);

static auto **const list_object_reference = CAST_PTR(Yelo::Scripting::list_object_reference_data_t**, 0x815908);
static auto **const hs_syntax = CAST_PTR(Yelo::Scripting::hs_syntax_data_t**, 0x815914);
static auto **const hs_globals = CAST_PTR(Yelo::Scripting::hs_globals_data_t**, 0x81590C);
static auto **const hs_threads = CAST_PTR(Yelo::Scripting::hs_thread_data_t**, 0x815910);

static_assert(0x64B940 != NULL);
static_assert(0x815914 != NULL);
static_assert(0x815904 != NULL);
static_assert(0x815908 != NULL);
static_assert(0x81590C != NULL);
static_assert(0x815910 != NULL);

FUNC_PTR(HS_UPDATE_HOOK, 0x48CE78);

static uint *K_MAX_HS_SYNTAX_NODES_PER_SCENARIO_UPGRADE_ADDRESS_LIST[] = {
	CAST_PTR(uint*, 0x485D7B),
};

static uint *K_TOTAL_SCENARIO_HS_SYNTAX_DATA_UPGRADE_ADDRESS_LIST[] = {
	//CAST_PTR(uint*, PLATFORM_VALUE(0x485E93, 0x47D783)), // don't modify this one, modify the size check using the address below
	CAST_PTR(uint*, 0x485DCA),
};

static byte *ADDRESS_OF_SCENARIO_HS_SYNTAX_DATA_SIZE_CHECK = CAST_PTR(byte*, 0x485D77);


//////////////////////////////////////////////////////////////////////////
// ScriptLibrary.cpp
FUNC_PTR(HS_MACRO_FUNCTION_PARSE, 0x48A070);
FUNC_PTR(HS_COMPILE_AND_EVALUATE, 0x487030); // currently unused
FUNC_PTR(HS_NULL_EVALUATE, 0x483F40);
FUNC_PTR(HS_NULL_WITH_PARAMS_EVALUATE, 0x483430);

//////////////////////////////////////////////////////////////////////////
// script functions related
ENGINE_PTR(long, hs_function_table_count, 0x5F9C10);

static auto** const hs_function_table = reinterpret_cast<Yelo::Scripting::hs_function_definition**>(0x624118);

#pragma region hs function table references
static short *K_HS_FUNCTION_TABLE_COUNT_REFERENCES_16bit[] = {
	CAST_PTR(short*, 0x4861E1),
	CAST_PTR(short*, 0x486F14),
};
static long *K_HS_FUNCTION_TABLE_COUNT_REFERENCES_32bit[] = {
	CAST_PTR(long*, 0x4864FA),
};

// really hs_function_definition***
static void *K_HS_FUNCTION_TABLE_REFERENCES[] = { // RIVERSIDE MOTHER FUCKER! *techno beat*
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_0),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_1),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_2),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_3),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_4),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_5),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_6),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_7),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_8),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_9),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_10),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_11),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_12),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_13),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_14),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_15),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_16),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_17),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_18),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_19),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_20),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_21),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_22),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_23),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_24),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_25),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_26),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_27),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_28),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_29),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_30),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_31),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_32),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_33),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_34),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_35),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_36),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_37),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_38),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_39),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_40),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_41),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_42),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_43),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_44),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_45),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_46),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_47),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_48),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_49),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_50),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_51),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_52),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_53),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_54),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_55),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_56),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_57),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_58),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_59),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_60),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_61),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_62),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_63),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_64),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_65),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_66),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_67),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_68),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_69),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_70),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_71),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_72),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_73),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_74),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_75),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_76),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_77),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_78),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_79),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_80),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_81),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_82),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_83),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_84),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_85),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_86),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_87),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_88),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_89),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_90),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_91),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_92),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_93),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_94),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_95),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_96),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_97),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_98),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_99),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_100),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_101),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_102),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_103),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_104),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_105),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_106),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_107),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_108),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_109),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_110),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_111),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_112),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_113),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_114),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_115),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_116),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_117),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_118),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_119),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_120),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_121),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_122),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_123),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_124),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_125),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_126),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_127),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_128),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_129),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_130),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_131),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_132),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_133),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_134),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_135),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_136),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_137),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_138),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_139),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_140),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_141),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_142),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_143),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_144),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_145),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_146),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_147),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_148),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_149),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_150),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_151),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_152),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_153),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_154),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_155),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_156),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_157),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_158),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_159),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_160),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_161),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_162),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_163),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_164),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_165),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_166),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_167),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_168),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_169),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_170),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_171),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_172),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_173),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_174),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_175),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_176),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_177),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_178),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_179),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_180),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_181),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_182),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_183),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_184),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_185),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_186),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_187),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_188),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_189),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_190),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_191),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_192),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_193),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_194),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_195),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_196),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_197),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_198),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_199),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_200),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_201),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_202),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_203),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_204),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_205),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_206),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_207),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_208),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_209),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_210),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_211),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_212),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_213),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_214),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_215),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_216),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_217),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_218),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_219),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_220),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_221),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_222),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_223),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_224),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_225),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_226),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_227),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_228),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_229),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_230),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_231),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_232),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_233),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_234),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_235),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_236),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_237),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_238),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_239),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_240),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_241),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_242),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_243),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_244),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_245),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_246),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_247),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_248),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_249),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_250),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_251),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_252),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_253),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_254),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_255),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_256),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_257),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_258),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_259),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_260),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_261),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_262),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_263),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_264),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_265),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_266),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_267),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_268),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_269),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_270),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_271),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_272),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_273),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_274),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_275),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_276),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_277),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_278),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_279),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_280),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_281),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_282),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_283),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_284),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_285),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_286),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_287),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_288),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_289),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_290),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_291),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_292),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_293),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_294),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_295),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_296),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_297),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_298),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_299),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_300),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_301),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_302),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_303),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_304),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_305),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_306),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_307),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_308),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_309),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_310),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_311),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_312),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_313),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_314),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_315),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_316),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_317),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_318),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_319),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_320),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_321),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_322),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_323),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_324),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_325),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_326),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_327),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_328),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_329),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_330),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_331),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_332),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_333),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_334),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_335),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_336),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_337),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_338),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_339),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_340),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_341),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_342),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_343),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_344),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_345),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_346),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_347),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_348),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_349),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_350),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_351),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_352),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_353),
	reinterpret_cast<void*>(K_HS_FUNCTION_TABLE_REFERENCE_354),
};
#pragma endregion

//////////////////////////////////////////////////////////////////////////
// script globals related
ENGINE_PTR(long, hs_external_globals_count, 0x5F9D0C);

static auto** const hs_external_globals = reinterpret_cast<Yelo::Scripting::hs_global_definition**>(0x626988);

static short *K_HS_EXTERNAL_GLOBALS_COUNT_REFERENCES_16bit[] = {
	CAST_PTR(short*, 0x4860F1),
};
static long *K_HS_EXTERNAL_GLOBALS_COUNT_REFERENCES_32bit[] = {
	reinterpret_cast<long*>(0x4865AA),
	reinterpret_cast<long*>(0x48BCDA),
	reinterpret_cast<long*>(0x48CAFB),
	reinterpret_cast<long*>(0x48CC0F),
	reinterpret_cast<long*>(0x48CC6D),
	reinterpret_cast<long*>(0x48CD70),
	reinterpret_cast<long*>(0x48D38A),
};
static void  *K_HS_EXTERNAL_GLOBALS_REFERENCES[]             = {
	reinterpret_cast<void*>(0x48607C),
	reinterpret_cast<void*>(0x4860AC),
	reinterpret_cast<void*>(0x4860D9),
	reinterpret_cast<void*>(0x486410),
	reinterpret_cast<void*>(0x4865A5),
	reinterpret_cast<void*>(0x4891E2),
	reinterpret_cast<void*>(0x48BC6E),
	reinterpret_cast<void*>(0x48D1E6),
	reinterpret_cast<void*>(0x48DB1B),
	reinterpret_cast<void*>(0x48DC87),
};

//////////////////////////////////////////////////////////////////////////

FUNC_PTR(HS_VALID_ACCESS_FLAGS, 0x486220);

//////////////////////////////////////////////////////////////////////////
// InitializeCreateScriptFunction()
FUNC_PTR(HS_ARGUMENTS_EVALUATE, 0x48D480);
FUNC_PTR(HS_RETURN, 0x48D270);




//////////////////////////////////////////////////////////////////////////
// Scenario.cpp
static auto** const scenario_globals = reinterpret_cast<Yelo::Scenario::s_scenario_globals**>(0x6E2254);



static auto* const global_scenario = reinterpret_cast<Yelo::TagGroups::scenario**>(0x6E224C);
static auto* const global_bsp3d = reinterpret_cast<Yelo::TagGroups::collision_bsp**>(0x6E2250);
#include "../../../../../../BlamSauce/models/collision/bsp_definitions.hpp"
#include "../../../../../../BlamSauce/models/structure/bsp_definitions.hpp"

static auto* const global_collision_bsp = reinterpret_cast<Yelo::TagGroups::collision_bsp**>(0x6E2258);
static auto* const global_structure_bsp = reinterpret_cast<Yelo::TagGroups::structure_bsp**>(0x6E225C);
static auto* const global_scenario_index = reinterpret_cast<datum_index*>(0x6397CC);
static auto* const structure_bsp_index = reinterpret_cast<short*>(0x6397D0);

static_assert( 0x626988 != NULL );
static_assert( 0x6E2254 != NULL );
static_assert( 0x6E224C != NULL );
static_assert( 0x6E2250 != NULL );
static_assert( 0x6E2258 != NULL );
static_assert( 0x6E225C != NULL );
static_assert( 0x6397CC != NULL );
static_assert( 0x6397D0 != NULL );

FUNC_PTR(OBJECT_TYPES_PLACE_OBJECTS_MOD_PROCESSED_BSPS__READ, 0x4F8207);
FUNC_PTR(OBJECT_TYPES_PLACE_OBJECTS_MOD_PROCESSED_BSPS__WRITE, 0x4F83CE);
FUNC_PTR(OBJECTS_INITIALIZE_FOR_NEW_MAP_MOD_PROCESSED_BSPS, 0x4F84E2);
//////////////////////////////////////////////////////////////////////////

#define ENGINE_DPTR(type, name, value) static auto** const name = CAST_PTR(type**, value); static_assert( value != NULL )


#undef ENGINE_DPTR
#undef ENGINE_PTR
#undef FUNC_PTR
