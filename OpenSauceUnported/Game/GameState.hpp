/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "Memory/MemoryInterface.hpp" // for CRC

#include <blamlib/Halo1/cache/physical_memory_map.hpp>
#include <blamlib/Halo1/game/game_allegiance.hpp>
#include <blamlib/Halo1/game/game_globals.hpp>
#include <blamlib/Halo1/game/game_time.hpp>
#include <blamlib/Halo1/main/main.hpp>
#include <blamlib/Halo1/physics/physics.hpp>
#include <blamlib/Halo1/physics/point_physics.hpp>
#include <blamlib/Halo1/saved_games/game_state.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum {
			// How many values we allow in the runtime data game state for each type (ie, integers, real, etc)
			k_runtime_data_max_values_count = 64,
		};

		enum {
			// This is a partially made up constant, though when dev-mode is >= this, it outputs messages to the console
			k_developer_mode_level_debug_output = 4,
		};
	};

	namespace GameState
	{
		void WriteEvent(cstring str = "", bool write_time_stamp = true);

		
		byte*		DeveloperMode();
		bool		DevmodeEnabled();

		void Initialize();
		void Dispose();
		// Don't call me unless your name is GameEngine!
		void Update(real delta_time);

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

		// Called from ScriptingLibrary's Initialize (since the GameState is initialized before Scripting is)
		void InitializeScripting();
	};
};
