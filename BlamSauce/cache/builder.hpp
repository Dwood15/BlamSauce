#pragma once
#include <precompile.h>

#include "../cseries/yelo_base.h"
#include "../primary.h"
#include "data_file_structures.hpp"
#include "cache_base.hpp"
#include "cache_files.hpp"
#include "../scenario/scenario.h"
#include "../scenario/definitions.h"
#include "../effects/sound/sound_definitions.hpp"
#include "../memory/upgrades/blam_memory_upgrades.hpp"
#include "../memory/memory_yelo.hpp"
#include "../models/structure/bsp_definitions.hpp"
#include "../main/main.h"
#include "../tags/files/structures.h"
#include "../memory/memory_interface_base.hpp"
#include "../scenario/yelo/yelo_scenario_definite.h"

namespace Yelo {
	namespace Enums {
		enum {
			k_cache_file_page_alignment_bit = Flags::k_alignment_4096bit,
			k_cache_file_page_size = FLAG(k_cache_file_page_alignment_bit),
			k_cache_file_page_size_mask     = FLAG(k_cache_file_page_alignment_bit) - 1,
		};
	};

	namespace Flags {
		enum {
			_build_cache_file_begin_building_yelo_bit,
			_build_cache_file_begin_mod_sets_create_anew_bit,
			_build_cache_file_begin_mod_sets_store_scenario_resources_bit,
			_build_cache_file_begin_use_memory_upgrades_bit,
			_build_cache_file_begin_dump_tag_group_allocation_stats_bit,

			k_number_of_build_cache_file_begin_flags
		}; static_assert(k_number_of_build_cache_file_begin_flags <= BIT_COUNT(byte));
	}

	namespace Cache {
		struct s_build_cache_file_globals {
			static const char *  k_temp_cache_file_name;
			static const char *  k_cache_file_extension;

			bool       building;
			char       scenario_name[Enums::k_max_tag_name_length + 1];
			byte_flags begin_flags; // NOTE: non-standard member
			bool       canceled; // NOTE: non-standard member
			unsigned char : 8;
			uint              crc;
			HANDLE              file_handle;
			long               cache_stream_size;
			s_data_file_globals data_files;

			DWORD GetFileSize() const;

			bool WriteToFile(const void *buffer, long buffer_size);

			bool TemporaryFileOpen(const char *  filename = k_temp_cache_file_name);

			void TemporaryFileClose(const char *  filename = k_temp_cache_file_name);

			bool TemporaryFileCopy(const char *  new_filename, cstring filename = k_temp_cache_file_name);

			void ScenarioNameToCacheFilePath(_Out_ std::string &cache_file_path);
		};

		//////////////////////////////////////////////////////////////////////////
		/* xbox cache headers were here */
		//////////////////////////////////////////////////////////////////////////

		s_build_cache_file_globals *BuildCacheFileGlobals();

		// Is the cache file that is being built in the .yelo format?
		bool BuildCacheFileForYelo();

		bool ScenarioLoadForCacheBuild(cstring scenario_name);
	};

	namespace blam {
		long build_cache_file_size();

		uint build_cache_file_checksum();

		bool build_cache_file_begin(cstring scenario_name,
											 byte_flags flags);

		bool build_cache_file_add_resource(const void *buffer, long buffer_size,
													  long *return_file_offset = nullptr, bool include_in_crc = true);

		void build_cache_file_cancel();

		bool build_cache_file_end(Cache::s_cache_header &header);

		size_t stream_tag_to_buffer(datum_index tag_index, void *stream, size_t &return_stream_offset, uintptr_t virtual_base_address, tag_reference_name_reference *tag_names);

		bool __cdecl scenario_load_all_structure_bsps();

		void build_cache_file_for_scenario(cstring scenario_path,
													  byte_flags begin_flags);
	};
};

namespace Yelo::blam {
	typedef std::array<char *, Enums::k_maximum_simultaneous_tag_instances_upgrade> build_cache_file_tag_names_t;

	static bool           building_single_player_scenario;
	static const size_t   k_build_cache_file_scratch_buffer_size = 40 * Enums::k_mega;
	static const unsigned k_cache_file_tag_memory_alignment_bit  = Flags::_alignment_32_bit;
	static const double   k_byte_to_megabyte_fraction            = 1.0 / Enums::k_mega;

	static const size_t k_cache_file_minimum_fixed_size =
								  sizeof(TagGroups::structure_bsp_header) +
								  Enums::k_tag_allocation_size_upgrade;
	static_assert(k_build_cache_file_scratch_buffer_size >= k_cache_file_minimum_fixed_size);


	// "return_stream" - the new stream pointer, positioned after the data which was written to it/"stream" before the stream operation started

	template <typename T>
	static T *stream_blob_to_buffer(T *&stream, const void *blob, size_t blob_size,
											  unsigned alignment_bit = k_cache_file_tag_memory_alignment_bit) {
		std::memcpy(stream, blob, blob_size);
		stream = reinterpret_cast<byte *>(stream) + blob_size;
		stream = Yelo::Memory::AlignPointer(stream, alignment_bit);
		return stream;
	}

	void *stream_tag_block_to_buffer(tag_block *block,
												void *stream, uintptr_t stream_base_address, uintptr_t virtual_base_address,
												build_cache_file_tag_names_t &tag_names);


	
	void *stream_tag_to_buffer(datum_index tag_index,
										void *stream, size_t &return_tag_size, uintptr_t virtual_base_address,
										build_cache_file_tag_names_t &tag_names) {
		tag_block *block = tag_get_root_block(tag_index);

		void *return_stream = stream_tag_block_to_buffer(block,
																		 stream, reinterpret_cast<uintptr_t>(stream), virtual_base_address,
																		 tag_names);

		return_tag_size = reinterpret_cast<uintptr_t>(return_stream) - reinterpret_cast<uintptr_t>(stream);
		return return_stream;
	}

	static size_t stream_structure_bsp_to_buffer(TagGroups::scenario_structure_bsp_reference &reference,
																void *stream, build_cache_file_tag_names_t &tag_names, uintptr_t virtual_base_address) {
		using namespace TagGroups;

		assert(!reference.structure_bsp.tag_index.IsNull());

		auto *bsp_header = reinterpret_cast<structure_bsp_header *>(stream);
		auto *bsp_stream = reinterpret_cast<structure_bsp *>(AlignPointer(bsp_header + 1, k_cache_file_tag_memory_alignment_bit));

		memset(bsp_header, 0, sizeof(*bsp_header));
		bsp_header->signature = structure_bsp::k_group_tag;
		bsp_header->bsp       = RebasePointer(bsp_stream, reinterpret_cast<uintptr_t>(bsp_header), virtual_base_address);

		size_t bsp_tag_size;
		stream_tag_to_buffer(reference.structure_bsp.tag_index,
									bsp_stream, bsp_tag_size, virtual_base_address, tag_names);

		size_t bsp_stream_size;
		bsp_stream_size = AlignValue(reinterpret_cast<uintptr_t>(bsp_stream) + bsp_tag_size, k_cache_file_tag_memory_alignment_bit);
		bsp_stream_size -= reinterpret_cast<uintptr_t>(bsp_header);
		bsp_stream_size = AlignValue(bsp_stream_size, Enums::k_cache_file_page_alignment_bit);

		return bsp_stream_size;
	}

	using namespace Cache;

	static __declspec(naked) bool __cdecl build_cache_file_cull_tags() {
		static const uintptr_t FUNCTION = 0x453260;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool __cdecl build_cache_file_last_minute_changes() {
		static const uintptr_t FUNCTION = 0x454280;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool __cdecl build_object_predicted_resources() {
		static const uintptr_t FUNCTION = 0x453680;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool __cdecl build_first_person_weapon_predicted_resources() {
		static const uintptr_t FUNCTION = 0x453700;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool __cdecl build_scenario_predicted_resources() {
		static const uintptr_t FUNCTION = 0x4537A0;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool __cdecl build_structure_bsp_predicted_resources() {
		static const uintptr_t FUNCTION = 0x453860;

		__asm jmp   FUNCTION
	}

	static bool build_cache_file_predicted_resources() {
		return
			build_object_predicted_resources() &&
			build_first_person_weapon_predicted_resources() &&
			build_scenario_predicted_resources() &&
			build_structure_bsp_predicted_resources();
	}

	static __declspec(naked) void *__cdecl build_cache_file_add_model_vertices_and_triangles(
		s_cache_tag_header *cache_tag_header, void *scratch) {
		static const uintptr_t FUNCTION = 0x454360;

		__asm jmp   FUNCTION
	}

	static void build_cache_file_add_model_vertices_and_triangles_resources(s_cache_tag_header *cache_tag_header) {
		printf_s("streaming model vertex and index buffers...");
		void *vertex_y_index_buffer     = YELO_MALLOC(Enums::k_max_cache_vertex_y_index_buffer_size_upgrade, false);
		void *vertex_y_index_buffer_end =
				  build_cache_file_add_model_vertices_and_triangles(cache_tag_header, vertex_y_index_buffer);
		cache_tag_header->model_data_size =
			reinterpret_cast<byte *>(vertex_y_index_buffer_end) - reinterpret_cast<byte *>(vertex_y_index_buffer);
		printf_s("done\n");

		printf_s("writing vertex and index buffers...");
		if (!build_cache_file_add_resource(vertex_y_index_buffer, cache_tag_header->model_data_size,
													  &cache_tag_header->vertices.offset))
			printf_s("FAILED!\n");
		else {
			printf_s("done %3.2fM\n",
						CAST(float, k_byte_to_megabyte_fraction * cache_tag_header->model_data_size));
		}

		YELO_FREE(vertex_y_index_buffer);
	}

	
	static void *build_cache_file_add_tag_to_stream(datum_index tag_index,
																	uintptr_t stream_base_address,
																	s_cache_tag_instance *tag_instances, long tag_instance_index,
																	void *stream, build_cache_file_tag_names_t &tag_names) {
		YELO_ASSERT_DISPLAY(false, "this isn't implemented yet");
		auto *tag_instance = &tag_instances[tag_instance_index];
		tag_instance->bool_in_data_file = false;

		switch (tag_instance->group_tag) {
			case TagGroups::sound_definition::k_group_tag:
				goto default_case;
				break;

			case TagGroups::s_bitmap_group::k_group_tag:
				goto default_case;
				break;

			case 'ustr':
			case 'font':
			case TagGroups::hud_state_messages::k_group_tag:
				goto default_case;
				break;

			case TagGroups::scenario::k_group_tag:
				goto default_case;
				break;

			case TagGroups::structure_bsp::k_group_tag:
				tag_instance->base_address = nullptr;
				break;

			default:
			default_case:
				size_t tag_stream_size;
				void   *tag_base_address   = stream_tag_to_buffer(tag_index,
																				  stream, tag_stream_size, Enums::k_tag_base_address,
																				  tag_names);
				tag_instance->base_address = tag_base_address;
				stream = tag_base_address;
				break;
		}

		return stream;
	}
	

	static __declspec(naked) bool __cdecl build_cache_file_add_tags(
		s_cache_header &cache_header, void *scratch, build_cache_file_tag_names_t &tag_names, long largest_structure_bsp_size) {
		static const uintptr_t FUNCTION = 0x454D40;

		__asm jmp   FUNCTION
	}

	static __declspec(naked) bool build_cache_file_add_structure_bsps(
		void *scratch, build_cache_file_tag_names_t &tag_names, long &largest_structure_bsp_size) {
		static const uintptr_t FUNCTION = 0x454B70;

		API_FUNC_NAKED_START()
		push                   largest_structure_bsp_size
		push                   tag_names
		mov                    eax, scratch
		call                   FUNCTION
		add
		esp, 4 * 2
		API_FUNC_NAKED_END(3)
	}

	static bool build_cache_file_add_tags(build_cache_file_tag_names_t &tag_indexes,
													  s_cache_header &cache_header, void *scratch) {
		long largest_structure_bsp_size = 0;
		return
			build_cache_file_add_tags(cache_header, nullptr, tag_indexes, 0) &&
			build_cache_file_add_structure_bsps(scratch, tag_indexes, largest_structure_bsp_size) &&
			build_cache_file_add_tags(cache_header, scratch, tag_indexes, largest_structure_bsp_size);
	}

	static bool build_cache_file_write_header_and_compress(s_cache_header &cache_header) {
		cache_header.file_length = build_cache_file_size();
		cache_header.crc         = build_cache_file_checksum();

		long maximum_cache_file_length = Enums::k_max_cache_size_upgrade;
		if (!BuildCacheFileForYelo()) {
			switch (cache_header.cache_type) {
				case Enums::_cache_file_type_campaign:
					maximum_cache_file_length = Enums::k_max_cache_size;
					break;
				case Enums::_cache_file_type_multiplayer:
					maximum_cache_file_length = 0x8000000;
					break;
				case Enums::_cache_file_type_main_menu:
					maximum_cache_file_length = 0x2300000;
					break;
			}
		}

		if (cache_header.file_length > maximum_cache_file_length) {
			printf_s("cache file %.2fM too large (should be %.2fM but was %.2fM)\n",
						CAST(float, k_byte_to_megabyte_fraction * (cache_header.file_length - maximum_cache_file_length)),
						CAST(float, k_byte_to_megabyte_fraction * maximum_cache_file_length),
						CAST(float, k_byte_to_megabyte_fraction * cache_header.file_length));
			return false;
		}

		printf_s("compressing %.2fM...",
					CAST(float, k_byte_to_megabyte_fraction * cache_header.file_length));
		if (!build_cache_file_end(cache_header)) {
			printf_s("FAILED!\n");
			return false;
		} else
			printf_s("done\n");

		return true;
	}

	void build_cache_file_for_scenario(cstring scenario_path, byte_flags begin_flags) {
		cstring scenario_name = tag_name_strip_path(scenario_path);

		void *scratch = YELO_MALLOC(k_build_cache_file_scratch_buffer_size, false);
		assert(scratch);
		assert(!((uintptr_t) scratch & 31));

		building_single_player_scenario =
			_stricmp(scenario_name, "ui") == 0 || main_get_campaign_level_from_name(scenario_name) != NONE;

		_mkdir(K_MAP_FILES_DIRECTORY);
		memset(scratch, 0x11, 4); // yeah, IDK why they used these parameters. sizeof typo?

		do {
			if (!ScenarioLoadForCacheBuild(scenario_path) ||
				 !scenario_load_all_structure_bsps() ||
				 !errors_handle()) {
				printf_s("### FAILED TO LOAD SCENARIO.\n\n");
				break;
			}

			if (!hs_scenario_postprocess(true)) {
				printf_s("### FAILED TO COMPILE SCRIPTS FOR SCENARIO.\n\n");
				break;
			}

			s_cache_header cache_header;
			memset(&cache_header, 0, sizeof(cache_header));
			cache_header.header_signature = s_cache_header::k_header_signature;
			cache_header.footer_signature = s_cache_header::k_footer_signature;
			cache_header.version          = s_cache_header::k_version;

			strncpy_s(cache_header.name, scenario_name, Enums::k_tag_string_length);
			strncpy_s(cache_header.build_string, "01.00.00.0609", Enums::k_tag_string_length);
			cache_header.cache_type = CAST(Enums::cache_file_type, global_scenario_get()->type);

			build_cache_file_tag_names_t tag_names;
			tag_names.fill(nullptr);

			printf_s("successfully built cache file.\n");

		} while (false);

		YELO_FREE(scratch);
	}
};

#include <direct.h> // fucking _mkdir

namespace Yelo::Cache {
	void s_data_file_globals::Save() {
		sounds.Save();
		locale.Save();
		bitmaps.Save();
	}

	void s_data_file_globals::PreprocessForSave() {
		sounds.PreprocessForSave();
		locale.PreprocessForSave();
		bitmaps.PreprocessForSave();
	}

	static void FixGameGlobals(datum_index globals_index, Enums::scenario_type scenario_type) {
		auto *globals = blam::tag_get<TagGroups::s_game_globals>(globals_index);

		switch (scenario_type) {
			case Enums::_scenario_type_main_menu: {
				globals->player_info[0].unit.clear();
				globals->materials.resize(0);
				globals->falling_damage.resize(0);
			} // fall through
			case Enums::_scenario_type_campaign: {
				globals->cheat_powerups.resize(0);
				globals->weapons_list.resize(0);
				globals->multiplayer_info.resize(0);
			}
				break;
		}

		// not done in the stock code, but it's unused anyway so fuck it
		globals->playlist_members.resize(0);
	}

	static void FixScenarioYelo(datum_index project_yellow_index) {
		if (project_yellow_index.IsNull())
			return;

		auto *yelo = blam::tag_get<Yelo::TagGroups::project_yellow>(project_yellow_index);

		bool has_globals_override = yelo->LoadGameGlobalsOverride();
	}

	static void InitializeYeloCacheHeaderForNewScenario(TagGroups::scenario *scnr, datum_index project_yellow_index) {
		if (project_yellow_index.IsNull())
			return;

		auto *yelo = blam::tag_get<TagGroups::project_yellow>(project_yellow_index);

		// If the scenario's yelo specifies build info, update the yelo header with that info, else use the defaults
		if (yelo->build_info.Count > 0) {
			const Yelo::TagGroups::s_project_yellow_scenario_build_info &build_info = yelo->build_info[0];

			//BuildCacheFileYeloCacheHeader().InitializeBuildInfo(build_info);
		} else {
			//BuildCacheFileYeloCacheHeader().InitializeBuildInfo();
		}
	}

	bool ScenarioLoadForCacheBuild(cstring scenario_name) {
		// NOTE: the Scenario::GetYelo(), etc APIs won't be valid until the call to scenario_load

		datum_index scenario_index = blam::tag_load<TagGroups::scenario>(scenario_name,
																							  FLAG(Flags::_tag_load_from_file_system_bit));
		// the engine code returns true even if the tags fail to load
		if (scenario_index.IsNull())
			return true;

		auto *scenario = blam::tag_get<TagGroups::scenario>(scenario_index);

		// perform the initial project_yellow fixups and associated changes here
		if (BuildCacheFileForYelo()) {
			const tag_reference &yelo_reference = scenario->GetYeloReferenceHack();

			FixScenarioYelo(yelo_reference.tag_index);
			InitializeYeloCacheHeaderForNewScenario(scenario, yelo_reference.tag_index);
		}

		// they use non-resolving references as FixGameGlobals clears select tag blocks for certain scenario types,
		// thus any references the blocks have wouldn't need to be used
		datum_index globals_index = blam::tag_load<TagGroups::s_game_globals>(Scenario::K_GAME_GLOBALS_TAG_NAME,
																									 FLAG(Flags::_tag_load_from_file_system_bit) | FLAG(Flags::_tag_load_non_resolving_references_bit));
		// the engine code returns true even if the tags fail to load
		if (globals_index.IsNull()){
			return true;
		}

		FixGameGlobals(globals_index, scenario->type);
		// the child of the globals tags can now be loaded, as all unnecessary references have been cleared
		blam::tag_load_children(globals_index);

		return blam::scenario_load(scenario_name);
	}
};
