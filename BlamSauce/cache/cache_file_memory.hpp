#pragma once

#include <precompile.h>

namespace Yelo::Cache {
	class c_cache_file_memory_controller {
		TagGroups::c_cache_file_memory_layout_table *m_layout;
		TagGroups::c_cache_file_memory_gestalt      *m_gesalt;

		short RegisterBlockDefinition(const tag_block_definition *block_definition);

		short RegisterDataDefinition(const tag_data_definition *data_definition);

	public:
		uintptr_t GetVirtualBaseAddress() const;

		void SetVirtualBaseAddress(uintptr_t base_address);

		uintptr_t RegisterBlockElements(const tag_block *block, uintptr_t cache_address);
	};
};
