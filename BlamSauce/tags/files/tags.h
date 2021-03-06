/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

namespace Yelo
{

	namespace Enums
	{
		enum {
			k_maximum_tag_files_per_index = 24000, // MAXIMUM_TAG_FILES_PER_INDEX
		};
	};

	namespace TagGroups
	{
		struct s_tag_file_globals;

		extern const char * K_TAG_FILES_DIRECTORY; /// "tags\"
		extern const char * K_DATA_FILES_DIRECTORY;/// "data\"

		s_tag_file_globals* TagFileGlobalsThreaded();
		s_tag_file_globals* TagFileGlobals();

		Memory::s_byte_swap_definition* TagHeaderBsDefinition();

		bool TagFileRequiresByteSwap();
	};
	namespace blam
	{
		void __cdecl tag_files_flush();


		bool __cdecl tag_file_open(tag group_tag, const char * filename,
			_Out_opt_ bool* is_readonly, _Out_opt_ uint* crc, bool from_file_system);
		template<typename T> inline
		bool tag_file_open(const char * filename,
			_Out_opt_ bool* is_readonly, _Out_opt_ uint* crc, bool from_file_system)
		{
			return tag_file_open(T::k_group_tag, filename, is_readonly, crc, from_file_system);
		}

		bool __cdecl tag_file_read(long file_position, size_t buffer_size, void* buffer);

		// Is the tag file read only?
		bool __cdecl tag_file_read_only(tag group_tag, const char * name);
		template<typename T> inline
		bool tag_file_read_only(const char * name)
		{
			return tag_file_read_only(T::k_group_tag, name);
		}

		// Does the tag file exist?
		bool __cdecl tag_file_exists(tag group_tag, const char * name);
		template<typename T> inline
		bool tag_file_exists(const char * name)
		{
			return tag_file_exists(T::k_group_tag, name);
		}

		bool __cdecl tag_file_get_file_reference(_Out_ s_file_reference& reference,
			tag group_tag, _In_opt_ const char * name);

		const char * tag_name_strip_path(const char * name);
	};
};
