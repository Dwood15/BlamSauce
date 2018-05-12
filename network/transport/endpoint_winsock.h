//License: GNU GPLv3
#pragma once

#include <rpc.h>
#include "../../cseries/cseries_base.h"
#include "address.h"
#include "../../memory/circular_queue.h"

namespace Yelo::Networking {
	struct s_gamespy_connection;

	struct s_transport_endpoint {
		s_gamespy_connection *gs_connection;
		bool                 is_listening_endpoint;   // 0x4
		UNKNOWN_TYPE(bool);         // 0x5, bool
		PAD16;

		SOCKET                          socket;            // 0x8, unused in PC, use gs_connection
		byte_flags                      flags;         // 0xC
		Enums::transport_type           type;   // 0xD
		int16                           error_code;         // 0xE
		Memory::s_circular_queue        *received_data_queue;
		int32                           gamespy_log_column;
		Enums::transport_rejection_code rejection_code;

	}; static_assert(sizeof(s_transport_endpoint) == 0x1C);
};
