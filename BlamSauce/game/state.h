#pragma once

#include <precompile.h>
#include <enginelayout/Game.inl>
#include "../cseries/base.h"
#include "../memory/upgrades/game_state_yelo.hpp"
#include "../main/main_structures.h"
#include "../cache/physical_memory_map_structures.hpp"
#include "physics.h"
#include "point_physics.h"
#include "objects/units/unit_hooks.h"
#include "system/system_definitions.h"
#include "system/systems.h"
#include "yelo_extra/gamestate_procs.inl"
#include "../hs/script_extensions/hs_base.h"

namespace Yelo::GameState
	{
		namespace Enums
		{
			enum {
				// How many values we allow in the runtime data game state for each type (ie, integers, real, etc)
					k_runtime_data_max_values_count = 64,
				// This is a partially made up constant, though when dev-mode is >= this, it outputs messages to the console
					k_developer_mode_level_debug_output = 4,
			};
		};

		namespace GameState {
			s_game_state_globals* GameStateGlobals();
		};

		namespace blam
		{
			void* __cdecl game_state_malloc(const char * name, const char * type, size_t size);
		};

		struct s_header_data
		{
			uint allocation_crc;
			char level[256];
			tag_string version;
			short player_spawn_count;
			short game_difficulty;
			uint cache_crc;

			union {
				byte _unused[32];
				s_yelo_header_data yelo;
			};
		}; static_assert( sizeof(s_header_data) == 0x14C );

		struct s_game_state_globals
		{
			void* base_address;
			uint cpu_allocation_size;
			uint gpu_allocation_size; // unused
			uint crc;
			bool locked;
			bool saved;
					 unsigned short : 16;
			uint revert_time;
			s_header_data* header;
			HANDLE autosave_thread;
			bool buffer_allocated;
			unsigned char : 8; unsigned short : 16;
			void* buffer;
			uint buffer_size;
			bool file_open;
			bool file_valid_for_read;
					 unsigned short : 16;
			HANDLE file_handle;
			char file_path[256];
			char core_path[256];
			HANDLE autosave_event;
			bool autosave_finished;
			bool creating_autosave;
					 unsigned short : 16;
		}; static_assert( sizeof(s_game_state_globals) == 0x23C );
};


namespace Yelo::GameState {
	void DataArrayInfoDumpToConsole(const char *);

	void WriteEvent(const char * str = "", bool write_time_stamp = true);

	s_main_globals* MainGlobals()								{ return main_globals; }
	s_physical_memory_map_globals* PhysicalMemoryMapGlobals()	{ return physical_memory_globals; }


	s_game_state_globals* GameStateGlobals()						{ return game_state_globals; }
	s_game_globals* GameGlobals()									{ return game_globals; }
	s_game_time_globals* GameTimeGlobals()							 { return game_time_globals; }
	s_game_allegiance_globals* GameAllegianceGlobals()				{ return game_allegiance_globals; }


	TagGroups::s_game_globals* GlobalGameGlobals()					{ return global_game_globals; }
	TagGroups::s_game_globals** GlobalGameGlobalsReference()		{ return global_game_globals; }
	s_physics_globals* Physics()									{ return global_physics; }
	s_point_physics_globals* PointPhysics()							{ return global_point_physics; }


	byte* DeveloperMode()											{ return developer_mode; }

	static bool* TransportDumping()									{ return transport_dumping; }
	bool DevmodeEnabled()											{ return devmode_enabled; }

	static bool g_yelo_game_state_enabled;

	bool YeloGameStateEnabled() {
		return g_yelo_game_state_enabled;
	}

	static void InitializeForYeloGameState() {
		// TODO: change game_state_init build-numbers string code to reference ours
		// TODO: change game save code to use our build-number checks
	}

	__declspec(naked) static void __cdecl InitializeForNewGameStateHook()
	{
		__asm {
		pop		esi
		pop		ebx
		pop		ecx
		jmp		GameState::InitializeForNewGameState
		}
	}
	__declspec(naked) static void __cdecl InitializeForNewMapHook()
	{
		__asm {
		pop		ecx
		jmp		GameState::InitializeForNewMap
		}
	}
	static bool __cdecl InitializeForNewBSPHook()
	{
		static short bsp_index = 0;

		__asm
			{
				mov		bsp_index, si
			};

		bool return_value = Yelo::blam::scenario_switch_structure_bsp((short)bsp_index);

		InitializeForNewBSP();

		return return_value;
	}

	void* GameStateMalloc(const bool k_update_allocation_crc, const size_t size_of)
	{
		s_game_state_globals* gsg = GameStateGlobals();

		byte* base_addr = reinterpret_cast<byte *>(gsg->base_address) + gsg->cpu_allocation_size;

		// Debug check that we don't allocate more memory than the game state has available
		YELO_ASSERT_DISPLAY((base_addr + size_of) <= blam::physical_memory_map_get_tag_cache_address(),
								  "Bit off more game-state than the game could chew!");

		gsg->cpu_allocation_size += size_of;
		// If the allocation crc is updated, game states won't be loadable by stock games
		if (k_update_allocation_crc)
			Memory::CRC(gsg->header->allocation_crc, &size_of, sizeof(size_of));

		return base_addr;
	}


	static void InitializeForDebug()
	{
		*Yelo::GameState::DeveloperMode() = Enums::k_developer_mode_level_debug_output; // make console messages appear

		// increment the game build by one so all games (hosted or browsed) aren't
		// from the normal, non-Yelo, game pool.
		Yelo::BuildNumber::GameBuildString()[Yelo::Enums::k_game_build_string_build_offset+1] += 7;
	}
	static void InitializeInitTextFix()
	{
		// FFFFFFFFuck you. This enables the client to have it's own init.txt (also was causing crashes)
		// Obviously this isn't ran in Dedi builds
		strcpy_s(GET_PTR2(init_txt_filename), 12, "initc.txt"); // 10 characters (including '\0')
	}


	static void InitializeForNewMapPrologue()
	{
		Physics()->Reset(); // Reset the physics constants on each new map load since these are engine globals, not game state globals.

		s_yelo_header_data& yelo_header = GameStateGlobals()->header->yelo;
		const TagGroups::s_game_globals* game_globals = Yelo::GameState::GlobalGameGlobals();
		if(!yelo_header.flags.initialized)
		{
			yelo_header.flags.initialized = true;
			yelo_header.unit_grenade_types_count = Yelo::Enums::k_unit_grenade_types_count;
		}

		yelo_header.flags.game_state_upgrades_on = YeloGameStateEnabled();

		Yelo::Random::InitializeSeed(GameGlobals()->options.game_random_seed);

		Objects::Units::InitializeForNewMapPrologue();
	}
	static void InitializeForNewMapEpilogue()
	{
		// Update the gravity based on the scenario's yelo tag settings
		if(!Scenario::GetYelo()->IsNull())
		{
			real gravity_scale = Scenario::GetYelo()->physics.gravity_scale;
			if(gravity_scale > 0 && gravity_scale != 1.0f)
				Physics()->SetGravityScale(gravity_scale);
		}
	}

	void __cdecl InitializeForNewMap()
	{
		InitializeForNewMapPrologue();

		Main::s_project_map_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if( components[x].InitializeForNewMap != nullptr )
				components[x].InitializeForNewMap();

		InitializeForNewMapEpilogue();
	}

	static void DisposeFromOldMapPrologue()
	{
	}

	void __cdecl DisposeFromOldMap()
	{
		DisposeFromOldMapPrologue();

		Main::s_project_map_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = component_count; x >= 0; x--)
			if( components[x].DisposeFromOldMap != nullptr )
				components[x].DisposeFromOldMap();
	}

	void __cdecl InitializeForNewBSP()
	{
		Yelo::Main::s_project_bsp_component* components;
		const long component_count = Yelo::Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if (components[x].InitializeForNewBSP != nullptr)
				components[x].InitializeForNewBSP();
	}

	void __cdecl DisposeFromOldBSP()
	{
		Yelo::Main::s_project_bsp_component* components;
		const long component_count = Yelo::Main::GetProjectComponents(components);

		for(long x = component_count; x >= 0; x--)
			if (components[x].DisposeFromOldBSP != nullptr)
				components[x].DisposeFromOldBSP();
	}

	void __cdecl InitializeForNewGameState()
	{
		Main::s_project_game_state_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if( components[x].InitializeForNewGameState != nullptr )
				components[x].InitializeForNewGameState();
	}

	void InitializeForYeloGameState(bool enabled)
	{
		Main::s_project_game_state_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if( components[x].InitializeForYeloGameState != nullptr )
				components[x].InitializeForYeloGameState(enabled);
	}

	static void HandleGameStateLifeCycle(Yelo::Enums::game_state_life_cycle life_cycle)
	{
		YELO_ASSERT_DISPLAY( IN_RANGE_ENUM(life_cycle, Enums::k_number_of_game_state_life_cycles), "What fucking life cycle is this shit?");

		Main::s_project_game_state_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if( components[x].HandleGameStateLifeCycle != nullptr )
				components[x].HandleGameStateLifeCycle(life_cycle);
	}

	void __cdecl HandleBeforeSaveLifeCycle()
	{
		HandleGameStateLifeCycle(Yelo::Enums::_game_state_life_cycle_before_save);
	}

	void __cdecl HandleBeforeLoadLifeCycle()
	{
		HandleGameStateLifeCycle(Yelo::Enums::_game_state_life_cycle_before_load);
	}

	void __cdecl HandleAfterLoadLifeCycle()
	{
		HandleGameStateLifeCycle(Yelo::Enums::_game_state_life_cycle_after_load);
	}


	void Initialize()
	{
		InitializeProcs();
		MemoryUpgradesInitialize();
		if(!CMDLINE_GET_PARAM(no_os_gamestate).ParameterSet())
		{
			InitializeForYeloGameState(g_yelo_game_state_enabled = true);
		}
		else {
			g_yelo_game_state_enabled = false;
		}

		*TransportDumping() = false;

		InitializeInitTextFix();

		EventLogInitialize();

		Memory::WriteRelativeJmp(&InitializeForNewGameStateHook, GET_FUNC_VPTR(GAME_INITIALIZE_HOOK), true);
		Memory::WriteRelativeJmp(&InitializeForNewMapHook, GET_FUNC_VPTR(GAME_INITIALIZE_FOR_NEW_MAP_HOOK), true);
		Memory::CreateHookRelativeCall(&DisposeFromOldMap, GET_FUNC_VPTR(GAME_DISPOSE_FROM_OLD_MAP_HOOK), Yelo::Enums::_x86_opcode_ret);

		for(auto& call : K_GAME_SCENARIO_SWITCH_BSP_CALLS)
			Memory::WriteRelativeCall(InitializeForNewBSPHook, call, true);

		Memory::CreateHookRelativeCall(&DisposeFromOldBSP, GET_FUNC_VPTR(GAME_DISPOSE_FROM_OLD_BSP_HOOK), Yelo::Enums::_x86_opcode_ret);

		ServerListInitialize();
	}

	void Dispose()
	{
		EventLogDispose();
		MemoryUpgradesDispose();
	}
	// Don't call me unless your name is GameEngine!
	void Update(real delta_time) {
		Main::s_project_component* components;
		const long component_count = Main::GetProjectComponents(components);

		for(long x = 0; x <= component_count; x++)
			if( components[x].Update != nullptr )
				components[x].Update(delta_time);
	}

	void __cdecl InitializeForNewMap();
	void __cdecl DisposeFromOldMap();
	void __cdecl InitializeForNewBSP();
	void __cdecl DisposeFromOldBSP();

	// Called only once: after all other game systems have been initialized at game startup.
	void __cdecl InitializeForNewGameState();
	// Called in Initialize(). Don't call me from anywhere else for now.
	void InitializeForYeloGameState(bool enabled);
	// These handlers are called by internal game state procs code. Don't touch.
	void __cdecl HandleBeforeSaveLifeCycle();
	void __cdecl HandleBeforeLoadLifeCycle();
	void __cdecl HandleAfterLoadLifeCycle();

	static void DataArrayInfoDumpToConsole(const char * data_array_name) {
		std::string name(data_array_name);
		const Memory::s_data_array* array = nullptr;

		if (!name.compare("part"))			array = &Effects::Particles().Header;
		else if (!name.compare("partsys"))		array = &Effects::ParticleSystems().Header;
		else if (!name.compare("partsysparts"))	array = &Effects::ParticleSystemParticles().Header;
		else if (!name.compare("effe"))			array = &Effects::Effects().Header;
		else if (!name.compare("effelocs"))		array = &Effects::EffectLocations().Header;
		else if (!name.compare("cont"))			array = &Effects::Contrails().Header;
		else if (!name.compare("contpoints"))	array = &Effects::ContrailPoints().Header;
		else if (!name.compare("lightvol"))		array = &Objects::LightVolumes().Header;
		else if (!name.compare("obje"))			array = &Objects::ObjectHeader().Header;
		else return; // user gave an unrecognized name

		int active_count = array->NumberOfValidDatums();
		float active_percentage = CAST(float, active_count);
		active_percentage /= array->max_datum;
		active_percentage *= 100.f;
		blam::console_response_printf(false, "%3.2f full; %d / %d", active_percentage, active_count, array->max_datum);
	}

	// Called from ScriptingLibrary's Initialize (since the GameState is initialized before Scripting is)
	void InitializeScripting() {
		Scripting::InitializeScriptFunction(Enums::_hs_function_physics_get_gravity, scripting_physics_get_gravity_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_physics_set_gravity, scripting_physics_set_gravity_evaluate);
		Scripting::InitializeScriptFunction(Enums::_hs_function_physics_constants_reset, scripting_physics_constants_reset_evaluate);

		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_data_array_info, scripting_data_array_info_evaluate);
	}
};
