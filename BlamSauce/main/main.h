/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>
// TODO: current_engine and levels.h should be reference-able via <> tag

//#include <levels.h>
//#include <current_engine.h>
#include "main_structures.h"
#include "../../runtime/halo1/windows/full/levels.h"
#include "../../runtime/halo1/windows/full/ce/1_10/current_engine.h"

namespace Yelo {
	namespace Enums {
		enum game_connection : short {
			_game_connection_local,
			_game_connection_network_client,
			_game_connection_network_server,
			_game_connection_film_playback,
		};
	};

	namespace GameState {
		s_main_globals * MainGlobals();

		// Is the game *only* running the simulation locally? (ie, campaign or splitscreen)
		bool IsLocal() { return MainGlobals()->game_connection == Yelo::Enums::_game_connection_local; }

		// Is this machine a server?
		bool IsServer() { return MainGlobals()->game_connection == Yelo::Enums::_game_connection_network_server; }

		// Is this machine a client?
		bool IsClient() { return MainGlobals()->game_connection == Yelo::Enums::_game_connection_network_client; }
	};

	namespace Main {
		////////////////////////////////////////////////////////////////////////////////////////////////////
		///		Vanilla Open Sauce, which this is all copy pasta'd from, uses macros like RegQueryValueEx or
		///	ERROR_SUCCESS. Why use the macro and slow down compilation when losing the macro doesn't affect
		///	readability?
		///		We leave HKEY_LOCAL_MACHINE, KEY_READ, and CAST_PTR alone b/c those help readability.
		///	It should be common knowledge that a nonzero exit number indicates some type of failure for the
		///	majority of windows library functions, where removing ERROR_SUCCESS in favor of 0 is probably okay.
		///		Maybe this is an unfair assumption, in which case, add ERROR_SUCCESS back and tell Dwood he's
		///	a fool. Anyway, this comment's long enough to the point where the comment itself is probably
		///	decreasing readability.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Get the HaloCE executable path as it is defined in the registry ("EXE Path"). </summary>
		/// <returns>	The EXE Path value with an ending '\', or an empty string if the registry query failed </returns>
		const inline std::string &RegistryGetGameExePath() {
			static std::string g_exe_path = std::string();
			static bool        initialized;

			if (initialized) {
				return g_exe_path;
			}

			initialized           = true;
			HKEY hkey;
			auto success          = RegOpenKeyExA(HKEY_LOCAL_MACHINE, GAME_REGISTRY_PATH, 0, KEY_READ, &hkey);

			if (success != 0) {
				return g_exe_path;;
			}

			char  local_path[MAX_PATH];
			// engine uses 255, but the key is a string, which means the length includes any terminating null char
			DWORD local_path_size = sizeof(local_path);

			success = RegQueryValueExA(hkey, "EXE Path", nullptr, nullptr, reinterpret_cast<byte *>(local_path), &local_path_size);
			RegCloseKey(hkey);

			if (success != 0) {
				return g_exe_path;
			}

			g_exe_path.assign(local_path);
			char last_char = g_exe_path.back();

			if (last_char != '\\') {
				g_exe_path.append("\\");
			}

			return g_exe_path;
		}
	};

	namespace blam {
		// Gets the current connection type
		inline Enums::game_connection game_connection() { return GameState::MainGlobals()->game_connection; }

		// Gets the name of the current map. Actually the scenario path usually.
		// If map_name was specified via the console, it of course won't be the scenario path.
		inline const char *  main_get_map_name() { return GameState::MainGlobals()->scenario_tag_path; }

		// Connect to a multiplayer server using it's ip:port and password
		inline bool __cdecl main_connect(const char *  address, const char *  password);

		inline short __cdecl main_get_campaign_level_from_name(const char *  level_name) {
			char name[128] = {};

			// NOTE: engine doesn't do this, but level_name is usually a scenario path
			if (const char *  last_slash = strrchr(level_name, '\\')) {
				level_name = last_slash + 1;
			}

			//Open Sauce had this as a _countof macro, but CLion can't into countof, and constexpr's are way better than macros.
			//https://stackoverflow.com/questions/42388077/constexpr-vs-macros#42388687
			strncpy_s(name, level_name, std::size(name) - 1);
			name[std::size(name) - 1] = '\0';

			_strlwr(name);

			using namespace Enums;

			//Genericized for swapping out game engine versions, woot woot.
			return get_level_from_name(name);
		}
	};
};
