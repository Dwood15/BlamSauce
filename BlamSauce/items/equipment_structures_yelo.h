#pragma once

#include <precompile.h>

namespace Yelo::Objects {
	struct s_equipment_datum_yelo_network_data {};

	struct s_equipment_data_yelo {
		enum { k_max_size = 0x18 }; // size of the unknown/useless data in s_equipment_data
	};

	static_assert(sizeof(s_equipment_data_yelo) <= s_equipment_data_yelo::k_max_size);
};

