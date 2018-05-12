#pragma once

#include "../cseries/cseries_base.h"

namespace Yelo {
	namespace Enums {
		enum {
			k_circular_queue_signature = 'circ',
		};
	};

	namespace Memory {
		struct s_circular_queue {
			cstring name;
			tag     signature;
			int32   read_offset;
			int32   write_offset;
			int32   buffer_size;
			void *buffer;
		};
	};
};
