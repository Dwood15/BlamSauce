#pragma once

#include <const char *>
#include <minwinbase.h>
#include <stdio.h>
#include "../cseries/base.h"
#include "../cseries/yelo_base.h"
#include "../cache/cache_files_structures.hpp"
#include "../cache/cache_files.hpp"

namespace Yelo::Enums {
	// The stock engine uses a hard-coded list of known maps. These "system maps" are what was shipped with the game.
	enum {
		_system_multiplayer_map__first = 0,
		_system_multiplayer_map__last  = 18,
		// i.e., non-system mp map, "Unknown Level"
		_system_multiplayer_map_user_created,

		k_number_of_system_multiplayer_maps = _system_multiplayer_map__last + 1,
	};
};

namespace Yelo::Interface {
	struct s_map_list_map_info {
		long   system_map_index; // index used for things like the UI map list
		const char * name;
		bool    is_original; // ie, bungie made it
		unsigned char : 8; unsigned short : 16;
	}; static_assert(sizeof(s_map_list_map_info) == 0xC);
};

namespace Yelo::blam {
	static const const char * k_map_list_mp_names_unicode_string_list_name = R"(ui\shell\main_menu\mp_map_list)";

	static const const char * k_map_list_ignored_map_names[10 + 1 + 3] = {
		"a10",
		"a30",
		"a50",
		"b30",
		"b40",
		"c10",
		"c20",
		"c40",
		"d20",
		"d40",
		"ui",
		"bitmaps",
		"sounds",
		"loc",
	};

	static const Yelo::Interface::s_map_list_map_info k_map_list_mp_maps[Enums::k_number_of_system_multiplayer_maps] = {
		{0,  "beavercreek",    true},
		{1,  "sidewinder",     true},
		{2,  "damnation",      true},
		{3,  "ratrace",        true},
		{4,  "prisoner",       true},
		{5,  "hangemhigh",     true},
		{6,  "chillout",       true},
		{7,  "carousel",       true},
		{8,  "boardingaction", true},
		{9,  "bloodgulch",     true},
		{10, "wizard",         true},
		{11, "putput",         true},
		{12, "longest",        true},

		{13, "icefields"},
		{14, "deathisland"},
		{15, "dangercanyon"},
		{16, "infinity"},
		{17, "timberland"},
		{18, "gephyrophobia"},
	};
};

namespace Yelo {
	namespace Interface {

		// This is the engine's struct for representing maps it found in the maps\ folder.
		// We don't define an actual ctor\dtor because of this
		struct s_map_list_map {
			char  *name;
			long system_map_index;
			bool  valid;
			struct {
				// is this a multiplayer map?
				byte_flags is_mp_map : 1;
				// does this map have a header with yelo data?
				byte_flags has_yelo_header : 1;
				// does corresponding file use the .yelo extension?
				byte_flags is_yelo_file : 1;

				// has the crc already been calculated yet?
				byte_flags valid_crc : 1;
			}     yelo_flags;
			unsigned short : 16;
			uint crc;

			// Our ctor initializer for this engine struct
			void Initialize(long system_map_index) {
				memset(this, 0, sizeof(*this)); // engine doesn't do this, it does explicit field init, but we have custom fields
				this->system_map_index = system_map_index;
				this->valid            = true; // engine defaults valid to true...
				this->crc              = NONE;
			}

			// Initializes the name field and related flags from a map_path
			bool InitializeNameFromPath(const char * map_path) {
				char local_map_name[_MAX_FNAME];
				auto map_file_type = Yelo::Cache::GetMapNameFromPath(local_map_name, map_path);

				// we were somehow given an invalid map_path...this should never happen through normal map_list APIs
				if (map_file_type == Yelo::Cache::e_map_path_file_type::invalid)
					return false;

				// allocate and set this entry's name
				size_t map_name_length = strlen(local_map_name);
				char   *map_name       = reinterpret_cast<char *>(Yelo::blam::system_malloc((map_name_length + 1)));
				this->name = map_name;

				strcpy(map_name, local_map_name);

				// calculate the flags related to the input map_path
				this->yelo_flags.is_yelo_file = map_file_type == Cache::e_map_path_file_type::yelo;

				return true;
			}

			// Verifies the map's header and calculates yelo-only specific information from the header
			// returns whether the map, and thus this entry, is valid
			bool ReadHeader(const char * map_path) {
				Cache::s_cache_header cache_header;
				this->valid = Yelo::Cache::ReadHeader(map_path, cache_header) == Yelo::Cache::e_cache_read_header_result::success;

				this->yelo_flags.has_yelo_header = cache_header.yelo.HasHeader();
				this->yelo_flags.is_mp_map       = cache_header.cache_type == Enums::_cache_file_type_multiplayer;

				return this->valid;
			}

			void InitializeFromHeader(const Yelo::Cache::s_cache_header &header);

			// Our dtor disposer for this engine struct
			void Dispose() {
				BLAM_FREE(this->name);
				this->name = nullptr;
			}
		};

		static_assert(sizeof(s_map_list_map) == 0x10);
		typedef Yelo::Memory::GbxArray<s_map_list_map> map_list_data_t;

		map_list_data_t *MultiplayerMaps();

		bool MultiplayerMapIsSystemMap(const char * map_name) {
			for (auto mp_map : blam::k_map_list_mp_maps)
				if (!strcmp(map_name, mp_map.name))
					return true;

			return false;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Add a map via components of a full map pathname. </summary>
		///
		/// <param name="maps_path">	   Full pathname of the maps folder, with a directory slash at the end. Or empty if
		/// 	map_file_name behaves like a map_path.
		/// </param>
		/// <param name="map_file_name">   Filename of the map file (name and extension). Or full map_path if maps_path is
		/// 	empty.
		/// </param>
		/// <param name="system_map_index">	(Optional) zero-based index of the map. </param>
		///
		/// <returns>	Index of the new s_map_list_map, or NONE if it failed to add. </returns>
		long MapListAddMapFromPath(const char * maps_path, const char * map_file_name, long system_map_index) {
			assert(maps_path);
			assert(map_file_name);

			auto &multiplayer_maps = *MultiplayerMaps();

			if (multiplayer_maps.count >= multiplayer_maps.capacity) {
				// engine resizes by 0x19, which just so happens to be the same size as this list, so...
				multiplayer_maps.capacity += std::size(Yelo::blam::k_map_list_mp_maps);

				size_t new_size = sizeof(s_map_list_map) * multiplayer_maps.capacity;
				multiplayer_maps.elements = reinterpret_cast<s_map_list_map *>(Yelo::blam::system_realloc((multiplayer_maps.elements), (new_size)));
			}
			int  mp_map_index      = multiplayer_maps.count++;

			s_map_list_map *entry = multiplayer_maps[mp_map_index];
			entry->Initialize(system_map_index);
			bool name_initialized = entry->InitializeNameFromPath(map_file_name);
			assert(name_initialized);

			// default full_map_path to map_file_name. If maps_path is empty, then map_file_name should actually be a map_path,
			// in which case we don't need to waste time sprintf'ing an empty string with another string
			const char * full_map_path                  = map_file_name;
			char    full_map_path_buffer[MAX_PATH] = "";
			if (!is_null_or_empty(maps_path)) {
				sprintf_s(full_map_path_buffer, "%s%s", maps_path, map_file_name);
				full_map_path = full_map_path_buffer;
			}

			if (entry->ReadHeader(full_map_path) && entry->yelo_flags.is_mp_map) {
				// this is where the engine would have calculated the map's checksum.
				// we would only want to do checksums for MP maps only too. unless co-op somehow became a thing...
			}
				// system maps must ALWAYS be added to the map list, so only remove invalid custom maps
			else if (system_map_index == Enums::_system_multiplayer_map_user_created) {
				// not a playable MP map. undefine the entry from the mp list
				entry->Dispose();
				multiplayer_maps.count--;
				mp_map_index = NONE;
			}

			return mp_map_index;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Lookup the index of a s_map_list_map by a map_name. </summary>
		///
		/// <param name="map_name">	Name of the map; lowercase and without any path components. </param>
		///
		/// <returns>	Index of the found s_map_list_map, or NONE if the map isn't registered in the map list. </returns>
		long MapListMapGetIndexFromName(const char * map_name) {
			auto& multiplayer_maps = *MultiplayerMaps();

			for (long x = 0; x < multiplayer_maps.count; x++)
			{
				const auto* entry = multiplayer_maps[x];

				// NOTE: engine uses strstr().
				// We don't use _stricmp as it performs a lowercase comparison however, map_name's should always lowercase
				if (!strcmp(map_name, entry->name))
					return x;
			}

			return NONE;
		}


		static void MapListAddSystemMultiplayerMaps(const char * root_path = "")
		{
			// the full pathname to the "maps\" directory, relative to root_path
			auto maps_path = std::string();
			// the full pathname to the system map file
			auto map_path = std::string();

			maps_path.reserve(MAX_PATH);
			maps_path.append(root_path);
			maps_path.append(Cache::K_MAP_FILES_DIRECTORY);

			map_path.reserve(MAX_PATH);
			map_path.append(maps_path);
			// cache the position of the end of the maps_path portion of the string
			// and use it as the map_name insertion index
			auto map_file_name_index = map_path.length();

			for (const auto& info : blam::k_map_list_mp_maps)
			{
				map_path.erase(map_file_name_index);
				map_path.append(info.name);
				map_path.append(Cache::K_MAP_FILE_EXTENSION);

				// engine uses info.name and assumes CWD, but we use the full path in case we use a different root_path
				const char * map_file_name = &map_path[map_file_name_index];
				MapListAddMapFromPath(maps_path.c_str(), map_file_name, info.system_map_index);
			}
		}

		// Add all the map files that appear in the "maps\" directory under a specified root path
		static void MapListAddMapsInPath(WIN32_FIND_DATA& fd, const char * root_path, const char * map_extension)
		{
			assert(root_path);

			// the full pathname to the "maps\" directory, relative to root_path
			auto maps_path = std::string();
			// the find files search pattern string
			auto find_filename = std::string();

			maps_path.reserve(MAX_PATH);
			// we assume root_path is empty or ends with a path separator
			maps_path.append(root_path);
			assert(maps_path.length() == 0 || maps_path.back() == '\\');
			maps_path.append(Cache::K_MAP_FILES_DIRECTORY);

			find_filename.reserve(MAX_PATH);
			find_filename.append(maps_path);
			find_filename.append("*"); // search pattern. we want all files that use the desired extension
			find_filename.append(map_extension);

			// TODO: FindExInfoBasic was only introduced in WINS2008 and W7. Need to test the executing platform and change which API we call when it is XP (ugh) or Vista (meh)
			// Ex() is only in WinXP+, but using FindExInfoBasic we can skip querying the short names of files
			// The engine uses FindFirstFile
			HANDLE h = FindFirstFileEx(find_filename.c_str(), FindExInfoBasic, &fd, FindExSearchNameMatch, nullptr, 0);
			if (h != INVALID_HANDLE_VALUE)
			{
				do {
					// FindFile results will all be relative, so just 'filename.extension', no root path
					const char * map_file_name = fd.cFileName;

					if (!Yelo::blam::map_list_should_ignore(map_file_name))
						MapListAddMapFromPath(maps_path.c_str(), map_file_name);
				} while (FindNextFile(h, &fd));

				FindClose(h);
			}
		}

		// Add all the map file types (.map, .yelo) that appear in the "maps\" directory under a specified root path
		static void MapListAddMapTypessInPath(WIN32_FIND_DATA& fd, const char * root_path)
		{
			// .map
			MapListAddMapsInPath(fd, root_path, Cache::K_MAP_FILE_EXTENSION);
			// .yelo
			MapListAddMapsInPath(fd, root_path, Cache::K_MAP_FILE_EXTENSION_YELO);
		}


	};

	namespace blam {

		const char * map_list_map_name(long index);

		long map_list_map_index(long index);

		bool map_list_map_valid(long index);

		uint map_list_map_get_crc(long index);

		bool map_list_map_is_original(long index);

		long map_list_map_get_index(const char * map_path) {
			char map_name[_MAX_FNAME] = "";
			auto map_file_type        = Yelo::Cache::GetMapNameFromPath(map_name, map_path);

			return Interface::MapListMapGetIndexFromName(map_name);
		}

		long map_list_map_count();

		void map_list_add_map(const char * map_name, long map_index);

		bool map_list_should_ignore(const char * map_path) {
			assert(map_path);

			char map_name[_MAX_FNAME] = "";
			auto map_file_type        = Cache::GetMapNameFromPath(map_name, map_path);

			if (map_file_type == Cache::e_map_path_file_type::invalid)
				return true;

			for (const char * name : k_map_list_ignored_map_names) {
				// NOTE: engine uses _stricmp()
				// We don't use _stricmp as it performs a lowercase comparison however, map_name's should always lowercase
				if (!_stricmp(map_name, name))
					return true;
			}

			int index = Interface::MapListMapGetIndexFromName(map_name);
			return index != NONE;
		}

		void map_list_initialize() {
			auto &multiplayer_maps = *Yelo::Interface::MultiplayerMaps();

			//assert(multiplayer_maps != nullptr);
			assert(multiplayer_maps.count == 0);
			assert(multiplayer_maps.capacity == 0);

			Interface::MapListAddSystemMultiplayerMaps();

			// first add maps from the current working directory, then try adding from the user profile
			WIN32_FIND_DATA fd;
			Interface::MapListAddMapTypessInPath(fd, "");

			// only try adding maps from the user profile if we detected the presence of an actual maps directory
			if (Settings::UserProfileMapsPathExists()) {
				const char * user_profile_path = Settings::UserProfilePath();

				Interface::MapListAddMapTypessInPath(fd, user_profile_path);
			}
		}

		void map_list_dispose() {
			auto &multiplayer_maps = *Interface::MultiplayerMaps();

			//assert(multiplayer_maps != nullptr);

			for (int x = 0; x < multiplayer_maps.count; x++)
				multiplayer_maps[x]->Dispose();

			BLAM_FREE(multiplayer_maps.elements);
			memset(&multiplayer_maps, 0, sizeof(multiplayer_maps));
		}
	};
};
