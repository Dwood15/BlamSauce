/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

namespace Yelo::Flags {
	enum {
		_tag_database_entry_skipped_bit,
		_tag_database_entry_error_missing_bit,
		_tag_database_entry_error_invalid_version_bit,
		_tag_database_entry_error_failure_bit,
	};
};

namespace Yelo::TagGroups {
	struct s_tag_database_entry // tag_database_entry_block
	{
		typedef int32 block_index_t;

		TagData<char> name;
		union {
			ULARGE_INTEGER handle_data;

			tag group_tag; // the group_tag is actually the low-word of the handle.
		};
		uint32        flags;
		// Indexes to entries which this entry references
		TAG_TBLOCK(child_ids, s_tag_database_entry::block_index_t);
		// Entries which reference this entry
		TAG_TBLOCK(reference_ids, s_tag_database_entry::block_index_t);

		TAG_PAD(db_pad0, int32, 3); // 12
		//void NameToBlockNameBuffer(char formatted_buffer[Enums::k_tag_block_format_buffer_size]);

	}; static_assert(sizeof(s_tag_database_entry) == 0x44);

	struct s_tag_database {
		enum {
			k_version   = 1,
			k_group_tag = 'tag+',
		};

		TAG_TBLOCK(entries, s_tag_database_entry);

		TAG_PAD(db_pad_01, int32, 6); // 24


		// static void Initialize();
		// static void Dispose();
	};
	// cstring __cdecl tag_database_entry_reference_block_format(
	// 	datum_index tag_index,
	// 	tag_block* block,
	// 	int32 element,
	// 	char formatted_buffer[Enums::k_tag_block_format_buffer_size]);
	//
	// cstring __cdecl tag_database_entry_block_format(
	// 	datum_index tag_index,
	// 	tag_block* block,
	// 	int32 element,
	// 	char formatted_buffer[Enums::k_tag_block_format_buffer_size]);
};
