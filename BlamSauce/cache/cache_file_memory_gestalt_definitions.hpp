#pragma once

#include <precompile.h>
#include "cache_file_memory_layout_table_definitions.hpp"

namespace Yelo::TagGroups
	{
		class c_cache_file_memory_layout_table;

		class c_cache_file_memory_gestalt
		{
		public:
			enum { k_group_tag = 'memg' };

			struct s_tag_allocation_definition
			{
				typedef short block_index_t;

				Enums::tag_allocation_type type;
				unsigned short : 16;
				size_t name_offset;

				void* definition_code_address;
			};
			struct s_tag_allocation
			{
				unsigned long : 32;
				byte checksum_buffer[20];
			};

			struct s_tag_instance
			{
				size_t name_offset;
				tag group_tag;
				uint tag_file_checksum;
				uint modified_date;
			};

			tag_reference layout_reference;
			tag_reference scenario_reference;

			tag_string cache_name;
			uint cache_build_date;
			unsigned long : 32;
			unsigned long : 32;
			unsigned long : 32;

			TagData<char> definition_names;
			TagData<char> tag_names;

			Yelo::TagBlock<const s_tag_allocation_definition> allocation_definitions;
			Yelo::TagBlock<const s_tag_allocation> allocations;

			Yelo::TagBlock<const s_tag_instance> tag_instances;
		};
	};
