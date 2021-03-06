#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_network_machine_count = k_multiplayer_maximum_players / k_maximum_number_of_local_players,
		};

		// profile offset: 0xFC0
		enum network_connection_type : byte_enum {
			_network_connection_type_56k,
			_network_connection_type_low,		// DSL/Cable
			_network_connection_type_average,	// DSL/Cable
			_network_connection_type_high,		// DSL/Cable
			_network_connection_type_lan,

			k_number_of_network_connection_types
		};

		// engine fails to properly convert 'connection type' enum (which matches the UI setting list)
		// to this class enum, which maps to a
		enum network_connection_class : signed long
		{								//  gBitRatesPerConnectionClass
			_network_connection_class_0, // 35,000
			_network_connection_class_1, // 70,000
			_network_connection_class_2, // 140,000
			_network_connection_class_3, // 280,000
			_network_connection_class_4, // 560,000
			_network_connection_class_5, // 1,120,000
			_network_connection_class_6, // 2,240,000
			_network_connection_class_7, // 4,480,000
			_network_connection_class_8, // 8,960,000

			k_number_of_network_connection_classes,
		};
	};

	namespace Flags
	{
		enum network_connection_flags
		{
			_connection_create_server_bit,
			_connection_create_clientside_client_bit,
			_connection_create_serverside_client_bit,
		};
	};

	namespace Networking
	{
		struct s_network_server_connection;

		struct s_message_stream
		{
			enum { k_protocol_bits = 0x2880 };

			Memory::s_bitstream bitstream;
			bool empty;
			byte buffer[k_protocol_bits / BIT_COUNT(byte)]; // 0x1D
			unsigned char : 8; unsigned short : 16;
			unsigned long : 32;
		}; static_assert( sizeof(s_message_stream) == 0x534 );

		struct s_connection_message // made up name, nothing to verify name with
		{
			bool has_data; unsigned char : 8; unsigned short : 16; // engine sets this to false after the message stream has been flushed
			long priority;
			long headerMaxSizeInBytes;
			long dataMaxSizeInBytes;
			long header_size_in_bits;
			long data_size_in_bits;
			byte* header_buffer;
			byte* data_buffer;
		}; static_assert( sizeof(s_connection_message) == 0x20 );
		struct s_connection_prioritization_buffer
		{
			long numMessages;				// 0xA78
			s_connection_message* messages;	// 0xA7C
			UNKNOWN_TYPE(uint);			// 0xA80, I've only seen this as 0xE0
			DWORD time_of_last_flush;		// 0xA84, initialize by GetTickCount
		}; static_assert( sizeof(s_connection_prioritization_buffer) == 0x10 );


		struct s_network_connection
		{
			typedef void (__cdecl* proc_connection_reject)(s_transport_endpoint* ep, signed long rejection_code);

			s_transport_endpoint* reliable_endpoint;
			uint keep_alive_time;
			proc_connection_reject connection_rejection_proc;
			Memory::s_circular_queue* incoming_queue;
			s_message_stream reliable_outgoing_sled;					// 0x10
			s_message_stream unreliable_outgoing_sled;					// 0x544
			s_connection_prioritization_buffer prioritization_buffer;	// 0xA78
			Enums::network_connection_class connection_class;			// 0xA88
			unsigned long flags; // Flags::network_connection_flags
			UNUSED_TYPE(long);
			s_network_server_connection* server_connection;
			bool is_local_connection; unsigned char : 8; unsigned short : 16;
		}; static_assert( sizeof(s_network_connection) == 0xA9C );
		
		struct s_network_server_connection
		{
			s_network_connection connection;
			s_transport_endpoint_set* endpoint_set;
			s_network_connection* client_list[Enums::k_maximum_network_machine_count];
			UNKNOWN_TYPE(bool);
			bool has_local_connection; unsigned short : 16;
		}; static_assert( sizeof(s_network_server_connection) == 0xAE4 );
	};
};
