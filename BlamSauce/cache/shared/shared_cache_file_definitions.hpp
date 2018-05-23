#pragma once

#include <precompile.h>

namespace Yelo::TagGroups {
	struct s_shared_cache_file_definition {
		short version;
		enum { k_version = 1, k_group_tag = 'cher' };
		struct _flags {
			unsigned short unused_bit:1;
		}     flags; static_assert(sizeof(_flags) == sizeof(unsigned short));
		uint base_address;
		long starting_tag_index;
		unsigned long : 32;

		tag_reference explicit_references;
	};
};

