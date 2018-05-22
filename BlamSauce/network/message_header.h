/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../cseries/base.h"
#include "../cseries/yelo_base.h"

namespace Yelo {
	namespace Enums {
		enum {
			k_maximum_message_size = 4095,
		};

		enum {
			_message_type_none,
			_message_type_lowlevel_error,
			_message_type_data, // unused
			_message_type_packet,

			k_number_of_message_types,
		};
	};

	namespace Flags {
		// no code actually uses these flags
		enum {
			_message_encrypted_bit,
			_message_unknown1_bit, // compressed?

			k_number_of_message_flags,
		};
	};

	namespace Networking {
		struct s_message_header {
			unsigned short flags : bitfield_size(Flags::k_number_of_message_flags);
			unsigned short type : bitfield_enum_size(Enums::k_number_of_message_types);
			unsigned short size : bitfield_size(Enums::k_maximum_message_size);
		}; static_assert(sizeof(s_message_header) == 0x2);

		struct s_message_lowlevel_error {
			char error_string[128];
			byte error;
		}; static_assert(sizeof(s_message_lowlevel_error) == 0x81);
	};
};
