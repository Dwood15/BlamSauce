#pragma once

#include <precompile.h>
#include "../main/configuration/yelo_shared_settings.hpp"
#include "../main/main.h"
#include "../memory/memory_interface_base.hpp"

namespace Yelo::Enums {
	enum data_file_reference_type : short;
};

namespace Yelo::Cache {
	struct s_cache_header;
	struct s_cache_tag_header;
	struct s_cache_tag_instance;

	// The type of cache file which a map_path refers to
	enum class e_map_path_file_type : signed long {
		invalid = NONE,

		map = 0,
		yelo,

		k_number_of
	};

	enum class e_cache_read_header_result : signed long {
		success,

		file_not_found,
		open_failed,
		read_failed,
		header_invalid,
		yelo_header_invalid,

		k_number_of
	};

	constexpr const char * K_MAP_FILE_EXTENSION_YELO = ".yelo";

	class c_map_file_finder {
		struct {
			const char * environment;   // The 'normal' path, usually a folder relative to the EXE or CWD
			const char * user_profile;   // The path defined by or in the user's profile
			const char * game_exe;      // The "EXE Path" value from the registry. DEDI ONLY!

			const char * final; // The path which the finder first found all the data files in, or NULL if it couldn't
		} m_maps_path;

		const char * m_map_name;
		const char * m_map_extension;

		bool SearchPath(const char * maps_path) {
			char map_path[MAX_PATH] = "";
			strcpy_s(map_path, maps_path);
			// pointer into map_file_path that starts after the maps_path string
			char *map_file_name = map_path + strlen(maps_path);

			const char * first_map_extension  = g_search_for_yelo_first ? K_MAP_FILE_EXTENSION_YELO : K_MAP_FILE_EXTENSION;
			const char * second_map_extension = g_search_for_yelo_first ? K_MAP_FILE_EXTENSION : K_MAP_FILE_EXTENSION_YELO;

			*map_file_name = '\0';
			strcat(map_file_name, m_map_name);
			strcat(map_file_name, first_map_extension);
			if (FileIO::PathExists(map_path)) {
				m_map_extension = first_map_extension;
				return true;
			}

			*map_file_name = '\0';
			strcat(map_file_name, m_map_name);
			strcat(map_file_name, second_map_extension);
			if (FileIO::PathExists(map_path)) {
				m_map_extension = second_map_extension;
				return true;
			}

			return false;
		}

		bool SearchEnvironment() {
			if (SearchPath(m_maps_path.environment))
				m_maps_path.final = m_maps_path.environment;

			return m_maps_path.final == m_maps_path.environment;
		}

		bool SearchUserProfile() {
			if (SearchPath(m_maps_path.user_profile))
				m_maps_path.final = m_maps_path.user_profile;

			return m_maps_path.final == m_maps_path.user_profile;
		}

		bool SearchExePath() {
			if (SearchPath(m_maps_path.game_exe))
				m_maps_path.final = m_maps_path.game_exe;

			return m_maps_path.final == m_maps_path.game_exe;
		}

	public:
		c_map_file_finder(const char * map_name) : m_map_name(map_name), m_map_extension(nullptr) {
			m_maps_path.environment  = Cache::MapsDirectory();
			m_maps_path.user_profile = Settings::PlatformUserMapsPath();
			m_maps_path.game_exe     = nullptr;
			m_maps_path.final        = nullptr;

			m_maps_path.game_exe = Main::RegistryGetGameExePath().c_str();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Attempts to and find the map_name. </summary>
		///
		/// <param name="map_path">			[out] Full pathname of the map file, or empty if it wasn't found. </param>
		/// <param name="return_access">	[out] (Optional) If non-null, the result a call to _access() would return. </param>
		///
		/// <returns>	true if the map_name was resolved, false if it wasn't. </returns>
		bool TryAndFind(_Out_ std::string &map_path, _Out_opt_ errno_t

		*
		return_access = nullptr
		) {
			bool file_found = false;

			if (SearchExePath() || SearchEnvironment() || SearchUserProfile()) {
				map_path.reserve(MAX_PATH);

				map_path.append(m_maps_path.final);
				map_path.append(m_map_name);
				map_path.append(m_map_extension);

				map_path.shrink_to_fit();

				file_found = true;
			} else
				map_path.clear();

			// populate the emulated _access() result
			if (return_access != nullptr) {
				*return_access = file_found
									  ? k_errnone
									  : ENOENT; // File name or path not found.
			}

			return file_found;
		}

		// Should the finder search for .yelo files before .map?
		// This should be set when the user settings are loaded, else it is always false
		static bool g_search_for_yelo_first;
	};

	// utility for blam::cache_file_data_load
	struct s_cache_file_data_load_state {
		byte   *base_address;
		size_t memory_available;

		s_cache_file_data_load_state(s_cache_header *cache_header, s_cache_tag_header *tag_header) : base_address(reinterpret_cast<byte *>(tag_header) + cache_header->tag_memory_size),
																																	memory_available(Enums::k_tag_allocation_size_upgrade - cache_header->tag_memory_size) {
		}

	private:
		byte *Alloc(s_cache_tag_instance *tag_instance, size_t bytes) {
			byte *address = base_address;
			if (bytes > memory_available) {
				YELO_ASSERT_DISPLAY(false, "need to log the tag which we can't load here");
			}

			memory_available -= bytes;
			base_address += bytes;
			return address;
		}

	public:
		byte *ReadExternalData(s_cache_tag_instance *tag_instance, Enums::data_file_reference_type data_file) {
			long data_offset, data_size;

			if (!DataFileGetItemDataInfo(data_file, tag_instance->index_in_data_file, data_offset, data_size)) {
				return nullptr;
			}

			size_t buffer_size = CAST(size_t, data_size);
			byte   *buffer     = Alloc(tag_instance, buffer_size);

			if (buffer != nullptr && !DataFileReadItemData(data_file, CAST(uint, data_offset), buffer, buffer_size)) {
				return nullptr;
			}

			return buffer;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the name of a map from a file path. </summary>
	///
	/// <param name="map_name">	[out] The (lowercase) name of the map, sans directory and extension </param>
	/// <param name="map_path"> Full pathname of the map file. </param>
	///
	/// <returns>	The type of cache file the path refers to, or invalid if it isn't a valid map path. </returns>
	e_map_path_file_type GetMapNameFromPath(_Out_ char (&map_name)[_MAX_FNAME], const char * map_path) {
		auto map_file_type = e_map_path_file_type::invalid;

		char map_extension[_MAX_EXT];
		_splitpath_s(map_path, nullptr, 0, nullptr, 0, map_name, std::size(map_name), map_extension, std::size(map_extension));

		_strlwr_s(map_name);

		if (!strcmp(map_extension, Cache::K_MAP_FILE_EXTENSION)) {
			map_file_type = e_map_path_file_type::map;

		} else if (!strcmp(map_extension, Cache::K_MAP_FILE_EXTENSION_YELO)) {
			map_file_type = e_map_path_file_type::yelo;

		}

		return map_file_type;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reads a header. </summary>
	///
	/// <param name="map_path">	Full pathname of the map file. </param>
	/// <param name="header">  	[out] The file's header. </param>
	///
	/// <returns>	success if it reads the header, and the header is valid; else non-success. </returns>
	e_cache_read_header_result ReadHeader(const char * map_path, _Out_ s_cache_header &header) {
		FileIO::s_file_info map_file_info;

		auto open_error = FileIO::OpenFile(map_file_info, map_path, Yelo::Enums::_file_io_open_access_type_read, file_io_open_create_option::_file_io_open_create_option_open_existing);
		if (open_error != Enums::_file_io_open_error_none) {
			return e_cache_read_header_result::open_failed;
		}

		// try to read a buffer the size of a header
		auto read_error = FileIO::ReadFileToInfoMemory(map_file_info, 0, sizeof(header));

		if (map_file_info.data_length == sizeof(header)) {
			memcpy(&header, map_file_info.data_pointer, sizeof(header));
		}

		FileIO::CloseFile(map_file_info);

		if (read_error != Enums::_file_io_read_error_none) {
			return e_cache_read_header_result::read_failed;
		}

		bool valid = header.ValidForYelo();

		if (!valid) {
			return e_cache_read_header_result::header_invalid;
		}

		if (header.yelo.HasHeader() && !header.yelo.IsValid()) {
			return e_cache_read_header_result::yelo_header_invalid;
		}

		return e_cache_read_header_result::success;

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Searches for the first map file with the given name and tries to read its header. </summary>
	///
	/// <remarks>Searches the CWD and user profile (order is defined by user settings) maps folder for a map file (.map,
	/// 	etc) with the given name.
	/// </remarks>
	///
	/// <param name="map_name">	Name of the map. </param>
	/// <param name="header">  	[out] The file's header. </param>
	///
	/// <returns>	true if it finds the map, reads the header, and the header is valid; else non-success. </returns>
	e_cache_read_header_result FindMapFileAndReadHeader(const char * map_name, _Out_ s_cache_header &header) {
		// first, try to find the map file
		std::string map_path;
		{
			auto map_finder = c_map_file_finder(map_name);

			if (!map_finder.TryAndFind(map_path))
				return e_cache_read_header_result::file_not_found;
		}

		return ReadHeader(map_path.c_str(), header);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Calculates a map cache's crc using a memory mapped view of the cache file. </summary>
	///
	/// <param name="cache_file">	The memory map view base address of the cache file. </param>
	///
	/// <returns>	The calculated checksum (CRC32) of the cache file. </returns>
	static uint CalculateChecksumFromMemoryMap(const byte *cache_file) {
		uint crc = NONE;

		// get pointers to the necessary cache data
		auto *header        =
				  reinterpret_cast<const s_cache_header *>(cache_file);
		auto *tag_header    =
				  reinterpret_cast<const s_cache_tag_header *>(cache_file + header->offset_to_index);
		auto *tag_instances =
				  reinterpret_cast<const s_cache_tag_instance *>(reinterpret_cast<const byte *>(tag_header) + sizeof(s_cache_tag_header));

		// the tag address needs correcting to match the data's starting point
		// we need to remove the actual runtime base address and instead apply the address we're using in our memory map (the virtual address)
		uintptr_t base_address    = (uintptr_t) tag_header->tags_address;
		uintptr_t virtual_address = (uintptr_t) tag_instances;

		// get the scenario tag
		const s_cache_tag_instance &scenario_tag_instance = tag_instances[tag_header->scenario_index.index];
		auto                       *scnr                  = Memory::RebasePointer(
			scenario_tag_instance.Definition<const TagGroups::scenario>(), base_address, virtual_address);

		int bsp_count = scnr->structure_bsps.Count;
		if (bsp_count > 0) {
			// can't access the block normally as its pointer is not correct for the cache's starting point
			auto *structure_bsps_block = Memory::RebasePointer(
				scnr->structure_bsps.Definitions, base_address, virtual_address);

			// this isn't correct for non-PC maps apparently, but we ARE on a pc...AREN'T we
			const byte *bsp_data_start = cache_file + sizeof(s_cache_header);

			// crc the data for all bsp's
			size_t   bsp_data_offset = 0;
			for (int i               = 0; i < bsp_count; i++) {
				long bsp_data_size = structure_bsps_block[i].bsp_data_size;
				Memory::CRC(crc, bsp_data_start + bsp_data_offset, bsp_data_size);
				bsp_data_offset += bsp_data_size;
			}
		}

		// crc model vertices and indices data
		Memory::CRC(crc, cache_file + tag_header->vertices.offset, tag_header->model_data_size);

		// crc tag data
		Memory::CRC(crc, tag_header, header->tag_memory_size);

		return crc;
	}

	uint CalculateChecksum(const char * map_path) {
		uint map_crc = NONE;

		FileIO::s_file_info map_file;
		//do-while-false for simpler cleanup
		do {
			if (Enums::_file_io_open_error_none != FileIO::OpenFile(map_file, map_path, Enums::_file_io_open_access_type_read, Enums::_file_io_open_create_option_open_existing))
				break;

			if (Enums::_file_io_read_error_none != FileIO::MemoryMapFile(map_file))
				break;

			map_crc = CalculateChecksumFromMemoryMap(reinterpret_cast<const byte *>(map_file.data_pointer));
		} while (false);

		FileIO::CloseFile(map_file);

		return map_crc;
	}

	uint FindMapFileAndCalculateChecksum(const char * map_name) {
		uint map_crc = NONE;

		// first, try to find the map file
		std::string map_path;
		{
			auto map_finder = c_map_file_finder(map_name);

			if (!map_finder.TryAndFind(map_path))
				return map_crc;
		}

		map_crc = CalculateChecksum(map_path.c_str());
		return map_crc;
	}
};
