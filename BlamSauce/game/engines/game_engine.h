#include <precompile.h>
#include <enginelayout/Game.inl>
#include <d3dx9math.inl>
#include "engine.hpp"
#include "engine_race.hpp"
#include "engine_king.hpp"
#include "engine_oddball.hpp"
#include "engine_slayer.hpp"
#include "engine_ctf.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum game_engine_custom : signed long
		{
			_game_engine_custom1 = k_number_of_game_engines,
			_game_engine_custom2,
			_game_engine_custom3,
			_game_engine_custom4,
			_game_engine_custom5,
			_game_engine_custom,
		};

		enum game_trait_custom : signed long
		{
			_game_custom_trait1 = _game_trait+1,
			_game_custom_trait2,
			_game_custom_trait3,
			_game_custom_trait4,
			_game_custom_trait5,
			_game_custom_trait,
		};

		enum game_engine_mode : signed long
		{
			_game_engine_mode_active,
			_game_engine_mode_postgame_delay,
			_game_engine_mode_postgame_rasterize_delay,
			_game_engine_mode_3,
		};
	};

	namespace GameEngine
	{

		s_ctf_globals* CtfGlobals()						{ return ctf_globals; }
		s_slayer_globals* SlayerGlobals()				{ return slayer_globals;}
		s_oddball_globals* OddballGlobals()				{ return oddball_globals;}
		s_king_globals* KingGlobals()						{ return king_globals;}
		s_race_globals* RaceGlobals()						{ return race_globals;}

		s_game_variant* GlobalVariant()					{ return (global_variant;}
		//s_vehicle_remapper
		// v1.08: 0x7FB300

		// List of old game engines which can be used
		const game_engine_definition* const* Definitions()	{ return game_engines };
		const game_engine_definition* Current()				{ game_engine; }

//#pragma region New Engines functions
		// List of original and custom made game engines
		static game_engine_definition* new_definitions[Enums::_game_engine_custom + 1] = {
// 			nullptr,
// 			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // old game engines
// 			nullptr, nullptr, nullptr, nullptr, nullptr, // space for new game engines
// 			nullptr, // terminator
		};
		static long new_definitions_count = Enums::k_number_of_game_engines;
#define GAME_ENGINE_REAL_COUNT (Enums::k_number_of_game_engines - 2)

		const game_engine_definition* const* NewDefinitions() { return new_definitions; }

		// How many total game engine definitions there are (that are valid and not null)
		long NewDefinitionsCount() { return new_definitions_count; }

		// Register a engine definition so that it may be used by the game code
		void RegisterNewGameEngine(game_engine_definition* engine)
		{
			if(new_definitions_count < Enums::_game_engine_custom)
				new_definitions[new_definitions_count++] = engine;
		}

		static void FixHudRenderUnitInterface()
		{
			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: need to modify pre-jump table code before this works the way we want it to

			// copy the game's jump table into our jmp table
			for (long x = 0; x < Enums::k_number_of_game_engines - GAME_ENGINE_REAL_COUNT; x++) {
				jmp_table[x] = *(void **) (HUD_RENDER_UNIT_INTERFACE_JMP_TABLE + (sizeof(void *) * x));
			}

			// just use the slayer variant of the code, it doesn't matter to us.
			for (long x = Enums::k_number_of_game_engines-GAME_ENGINE_REAL_COUNT; x < std::size(jmp_table); x++) {
				jmp_table[x] = *(void **) (HUD_RENDER_UNIT_INTERFACE_JMP_TABLE + (sizeof(void *) * (Enums::_game_engine_slayer - 1)));
			}

			// set the game's jump table address to our's
			hud_render_unit_interface_jmp_ptr = jmp_table;
		}

		static void FixFunc4F7440() // function for the engine vehicle remapper
		{
			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: reference jump table code for the changes to make this work the way we want it to

			// copy the game's jump table into our jmp table
			for (long x = 0; x < Enums::k_number_of_game_engines - GAME_ENGINE_REAL_COUNT; x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7440JmpTable) + (sizeof(void*) * x));

			// just use the slayer variant of the code, it doesn't matter to us.
			for (long x = Enums::k_number_of_game_engines-GAME_ENGINE_REAL_COUNT; x < std::size(jmp_table); x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7440JmpTable) + (sizeof(void*) * (Enums::_game_engine_slayer - 1)));

			// set the game's jump table address to our's
			Func4F7440JmpPtr = jmp_table;
		}

		static void FixFunc4F7580() // function for the engine vehicle remapper
		{
			static void* jmp_table[Enums::_game_engine_custom-1];

			// TODO: reference jump table code for the changes to make this work the way we want it to

			// copy the game's jump table into our jmp table
			for (long x = 0; x < Enums::k_number_of_game_engines - GAME_ENGINE_REAL_COUNT; x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7580JmpTable) + (sizeof(void*) * x));

			// just use the slayer variant of the code, it doesn't matter to us.
			for (long x = Enums::k_number_of_game_engines-GAME_ENGINE_REAL_COUNT; x < std::size(jmp_table); x++)
				jmp_table[x] = *(void**)(GET_FUNC_PTR(Func4F7580JmpTable) + (sizeof(void*) * (Enums::_game_engine_slayer - 1)));

			// set the game's jump table address to our's
			GET_PTR(Func4F7580JmpPtr) = jmp_table;
		}
//#pragma endregion

		__declspec(naked) static void GameEngineUpdate_Hook()
		{
			API_FUNC_NAKED_START_()
				call	GameEngine::Update
			API_FUNC_NAKED_END_()
		}

		void Initialize()
		{
			Memory::CreateHookRelativeCall(&GameEngine::InitializeForNewMap, GET_FUNC_VPTR(GAME_ENGINE_INITIALIZE_FOR_NEW_MAP_HOOK), Enums::_x86_opcode_ret);
			Memory::WriteRelativeJmp(&GameEngineUpdate_Hook, GET_FUNC_VPTR(GAME_ENGINE_UPDATE_HOOK), true);

//#pragma region New Engines implementation
			// copy the game engine pointers into our list
			for(long x = 0; x < new_definitions_count; x++)
				new_definitions[x] = GET_DPTR2(game_engines)[x];

			// replace the game's game_engines list with ours
			GET_PTR(game_engine_init_mod) = new_definitions;

			FixHudRenderUnitInterface();
			FixFunc4F7440();
			FixFunc4F7580();
//#pragma endregion
		}

		void Dispose()
		{
		}

		void __cdecl InitializeForNewMap()
		{
			if( GameEngine::Current() )
			{
				GameState::WriteEvent(GameState::GameGlobals()->options.map_name);
 				GameState::WriteEvent("", false);
			}
		}

		// Game components updated before the game_engine:
		//	* game allegiance
		//	* ai
		//	* players (if we're not the server)
		//	* effects
		//	* FP weapons
		// Everything else is updated after the game_engine (scripting, objects, etc).
		// Our update is performed AFTER the engine's update is done.
		void __cdecl Update()
		{
			const real k_update_normal = 1.6666668e-2f; // 0.016666668
			const real k_update_double_speed = 3.3333335e-2f; // 0.033333335

			real delta_time = !GameState::GameGlobals()->players_are_double_speed ? k_update_normal : k_update_double_speed;

			GameState::Update(delta_time);

			// NOTE: Place any update code in the GameState's Update function, or the 
			// Update function of the corresponding component (ie, Effect, Players, etc) 
			// Don't mess with the GameEngine Update function unless it's related to the game_engine
		}
	};
};
