#pragma once
#include "precompile.h"

namespace Yelo::Cache {
	struct s_cache_header_base {
		enum {
			k_header_signature = 'head',
			k_footer_signature = 'foot',
		};
	};
};

namespace Yelo::Cache {
	struct s_cache_header_yelo_base {
		enum {
			k_signature = 'yelo',
		};

		tag   signature;
		int16 version;
	};
};
