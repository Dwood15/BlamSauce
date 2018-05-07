/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _X86_
#define _X86_
#endif

#include <rpc.h>
#include <minwindef.h>
#include <string>

#include "../cseries/cseries_base.h"
#include "levels.h"
#include "../cseries/MacrosCpp.h"
#include "main_structures.h"

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
		struct s_main_globals;

		s_main_globals *MainGlobals();

		// Is the game *only* running the simulation locally? (ie, campaign or splitscreen)
		bool IsLocal() { return MainGlobals()->game_connection == Enums::_game_connection_local; }

		// Is this machine a server?
		bool IsServer() { return MainGlobals()->game_connection == Enums::_game_connection_network_server; }

		// Is this machine a client?
		bool IsClient() { return MainGlobals()->game_connection == Enums::_game_connection_network_client; }
	};

	namespace Main {
		static cstring k_halo1_campaign_level_names[Enums::k_number_of_halo1_campaign_levels] = {
			R"(levels\a10\a10)",
			R"(levels\a30\a30)",
			R"(levels\a50\a50)",
			R"(levels\b30\b30)",
			R"(levels\b40\b40)",
			R"(levels\c10\c10)",
			R"(levels\c20\c20)",
			R"(levels\c40\c40)",
			R"(levels\d20\d20)",
			R"(levels\4d0\d40)",
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Get the HaloCE executable path as it is defined in the registry ("EXE Path"). </summary>
		///
		/// <returns>	The EXE Path value with an ending '\', or an empty string if the registry query failed </returns>
		const inline std::string &RegistryGetGameExePath() {
			static std::string g_exe_path = std::string();
			static bool        initialized;

			do {
				if (initialized)
					break;

				initialized           = true;

				HKEY hkey;
				auto success          = RegOpenKeyEx(HKEY_LOCAL_MACHINE, R"(Software\Microsoft\Microsoft Games\Halo CE)", 0, KEY_READ, &hkey);
				if (success != ERROR_SUCCESS)
					break;

				char  local_path[MAX_PATH];
				// engine uses 255, but the key is a string, which means the length includes any terminating null char
				DWORD local_path_size = sizeof(local_path);
				success = RegQueryValueEx(hkey, "EXE Path", nullptr, nullptr, CAST_PTR(byte *, local_path), &local_path_size);
				RegCloseKey(hkey);
				if (success != ERROR_SUCCESS)
					break;

				g_exe_path.assign(local_path);
				char last_char = g_exe_path.back();
				if (last_char != '\\')
					g_exe_path.append("\\");

			} while (false);

			return g_exe_path;
		}
	};

	namespace blam {
		// Gets the current connection type
		inline Enums::game_connection game_connection() { return GameState::MainGlobals()->game_connection; }

		// Gets the name of the current map. Actually the scenario path usually.
		// If map_name was specified via the console, it of course won't be the scenario path.
		inline cstring main_get_map_name() { return GameState::MainGlobals()->scenario_tag_path; }

		// Connect to a multiplayer server using it's ip:port and password
		inline bool __cdecl main_connect(cstring address, cstring password);

		inline int16 __cdecl main_get_campaign_level_from_name(cstring level_name) {
			char name[128] = {};

			// NOTE: engine doesn't do this, but level_name is usually a scenario path
			if (cstring last_slash = strrchr(level_name, '\\'))
				level_name = last_slash + 1;

			strncpy_s(name, level_name, _countof(name) - 1);
			name[_countof(name) - 1] = '\0';

			_strlwr(name);

			using namespace Enums;

			if (strstr(name, "a10")) return _halo1_campaign_level_a10;
			else if (strstr(name, "a30")) return _halo1_campaign_level_a30;
			else if (strstr(name, "a50")) return _halo1_campaign_level_a50;
			else if (strstr(name, "b30")) return _halo1_campaign_level_b30;
			else if (strstr(name, "b40")) return _halo1_campaign_level_b40;
			else if (strstr(name, "c10")) return _halo1_campaign_level_c10;
			else if (strstr(name, "c20")) return _halo1_campaign_level_c20;
			else if (strstr(name, "c40")) return _halo1_campaign_level_c40;
			else if (strstr(name, "d20")) return _halo1_campaign_level_d20;
			else if (strstr(name, "d40")) return _halo1_campaign_level_d40;

			return NONE;
		}
	};
};
};
