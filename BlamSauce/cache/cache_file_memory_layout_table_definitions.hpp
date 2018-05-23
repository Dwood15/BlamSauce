#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Enums
	{
		enum tag_allocation_type : short {
			_tag_allocation_type_block,
			_tag_allocation_type_data,

			k_number_of_tag_allocation_types
		};

		enum tag_block_child_type : short {
			_tag_block_child_type_tag_reference,
			_tag_block_child_type_block_index,
			_tag_block_child_type_string_id,

			k_number_of_tag_block_child_types
		};
	};

	namespace TagGroups
	{
		class c_cache_file_memory_layout_table
		{
		public:
			enum { k_group_tag = 'meml' };

			//////////////////////////////////////////////////////////////////////////
			// allocations
			struct s_tag_allocation_definition
			{
				typedef short block_index_t;

				size_t element_runtime_size;
				unsigned short flags;
				short alignment_bit;
			};
			struct s_tag_allocation
			{
				typedef long block_index_t;

				TAG_BLOCK_INDEX(s_tag_allocation_definition, allocation_index);
				unsigned short : 16;
				size_t size;
				uintptr_t rva;
			};

			struct s_tag_block_allocation
			{
				typedef long block_index_t;

				TAG_BLOCK_INDEX(s_tag_allocation, allocation_index);
				Yelo::TagBlock<const s_tag_allocation::block_index_t> child_allocations;
			};

			struct s_tag_data_allocation
			{
				TAG_BLOCK_INDEX(s_tag_allocation, allocation_index);
			};

			//////////////////////////////////////////////////////////////////////////
			// child data locations
			struct s_tag_block_child_definition
			{
				typedef short block_index_t;

				TAG_BLOCK_INDEX(s_tag_allocation_definition, parent_definition_index);
				unsigned short parent_offset;
				short type;
				unsigned short : 16;
			}; static_assert( sizeof(s_tag_block_child_definition) == 8 );

			struct s_tag_block_child_instance
			{
				typedef long block_index_t;

				TAG_BLOCK_INDEX(s_tag_block_child_definition, definition_index);
				TAG_BLOCK_INDEX(s_tag_allocation_definition, owner_block_index);
			}; static_assert( sizeof(s_tag_block_child_instance) == 4 );

			//////////////////////////////////////////////////////////////////////////
			typedef TagBlock<s_tag_block_child_instance::block_index_t>
				string_id_set_entry_location_t;
			struct s_string_id_set
			{
				long set_index;

				Yelo::TagBlock<const byte> ids_bitvector;
				Yelo::TagBlock<const string_id_set_entry_location_t> id_locations;
			};

			struct s_tag_instance
			{
				TAG_BLOCK_INDEX(s_tag_block_allocation, header_block_index);
				Yelo::TagBlock<const s_tag_block_child_instance::block_index_t> references; // indices to [tag_reference_locations]
				uintptr_t name_offset; // offset of the tag name from the start of the tag name buffer
			};

			uint tags_checksum;
			uintptr_t virtual_base_address;
			PAD64;

			Yelo::TagBlock<const s_tag_allocation_definition> allocation_definitions;
			Yelo::TagBlock<const s_tag_allocation> allocations;
			Yelo::TagBlock<const s_tag_block_allocation> block_allocations;
			Yelo::TagBlock<const s_tag_data_allocation> data_allocations;

			PAD_TYPE(tag_block);

			Yelo::TagBlock<const s_tag_block_child_definition> children_definitions;
			Yelo::TagBlock<const s_tag_block_child_instance> tag_reference_locations;
			Yelo::TagBlock<const s_tag_block_child_instance> string_id_locations;

			Yelo::TagBlock<const s_string_id_set> string_id_sets;

			Yelo::TagBlock<const s_tag_instance> tag_instances;
		};
	};
};
