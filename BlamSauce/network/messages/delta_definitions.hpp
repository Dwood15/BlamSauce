/* See LICENSE for specific license information */
#pragma once

#include "../../cseries/base.h"

namespace Yelo {
	namespace Memory {
		struct s_bitstream;
	};

	namespace Enums {
#pragma region field_type
		enum network_field_type : signed long {
			_field_type_integer,
			_field_type_real,
			_field_type_boolean,
			_field_type_ascii_character,
			_field_type_wide_character,
			_field_type_ascii_string,
			_field_type_wide_string,
			_field_type_arbitary_data,
			_field_type_array,
			_field_type_structure,
			_field_type_pointer,
			_field_type_enumeration,
			_field_type_bounded_index,
			_field_type_translated_index,

			/*!
			* \brief
			* real point 2d\3d
			*
			* parameter specifies if its 2d or 3d.
			* bit count = (parameter << 5) + parameter
			*/
				_field_type_point,

			/*!
			* \brief
			* real vector 2d\3d
			*
			* parameter specifies if its 2d or 3d.
			* bit count = (parameter << 5) + parameter
			*/
				_field_type_vector,
				_field_type_angle,
				_field_type_flags,
				_field_type_time,
				_field_type_grenade_counts,
				_field_type_fixed_width,
				_field_type_fixed_width_normal_vector,
				_field_type_locality_reference_position,
				_field_type_digital_throttle,
				_field_type_fixed_width_weapon_index,
				_field_type_fixed_width_grenade_index,
				_field_type_smart_vector,
				_field_type_item_placement_position,

			NUMBER_OF_MESSAGE_DELTA_FIELD_TYPES,
		};
#pragma endregion

#pragma region field_type_bit_size
		/*!
		* \brief
		* Bit sizes of some message delta fields
		* 
		* Each enumeration has the value of a message
		* delta's constant field bit count (unlike
		* the integer which has various bit sizes)
		*/
		enum field_type_bit_size {
			_field_type_bit_size_real                      = 32,
			_field_type_bit_size_boolean                   = 1,
			_field_type_bit_size_ascii_character           = 8,
			_field_type_bit_size_wide_character            = 16,
			_field_type_bit_size_angle                     = 32,
			_field_type_bit_size_time                      = 32,
			_field_type_bit_size_grenade_counts            = 6,
			_field_type_bit_size_digital_throttle          = 4,
			_field_type_bit_size_fixed_width_weapon_index  = 3,
			_field_type_bit_size_fixed_width_grenade_index = 2,
			_field_type_bit_size_item_placement_position   = 20 /*X*/ + 20 /*Y*/ + 30 /*Z*/,
		};
#pragma endregion

#pragma region integer_width_type
		enum integer_width_type : signed long {
			_integer_width_type_8bits,
			_integer_width_type_16bits,
			_integer_width_type_32bits,
			_integer_width_type_1bit,
			_integer_width_type_3bits,
			_integer_width_type_5bits,
			_integer_width_type_6bits,
		};
#pragma endregion

		enum enumeration_width_type : signed long {
			_enumeration_width_type_1byte,
			_enumeration_width_type_2byte,
			_enumeration_width_type_4byte,
		};

		enum message_delta_parameter_type : signed long {
			_message_delta_parameter_type_real,
			_message_delta_parameter_type_long,
		};

		enum message_delta_mode : signed long {
			_message_delta_mode_stateless, // no baselines
			_message_delta_mode_incremental, // requires baselines
		};

		enum message_delta_encoding_class : signed long {
			_message_delta_encoding_class_lan,
			_message_delta_encoding_class_internet,
		};

		enum {
			k_mdp_maximum_string_length = 0x7FF,
			k_mdp_maximum_flags         = 32,

			k_bits_in_grenade_counts_type         = 6,
			k_bits_in_grenade_counts_type_upgrade = k_bits_in_grenade_counts_type * 2,
		};
	};

	namespace MessageDeltas {
		struct message_delta_parameter {
			const char *                             name;
			Enums::message_delta_parameter_type type;
			union {
				void  *address;
				real  *real;
				long *integer;
			} value;
		}; static_assert(sizeof(message_delta_parameter) == 0xC);

		// Essentially a hash table
		struct s_index_resolution_table {
			struct s_entry {
				datum_index key;// local_index
				long       value;   // translated_index, what we get from the network
				s_entry *next;
			}; static_assert(sizeof(s_entry) == 0xC);

			struct s_entry_pool {
				enum { k_entry_count = 50 };

				s_entry entries[k_entry_count];
			}; static_assert(sizeof(s_entry_pool) == 0x258);
			struct s_entry_pool_list {
				s_entry_pool *pool;
				s_entry      *next_entry;
			}; static_assert(sizeof(s_entry_pool_list) == 0x8);

			struct s_slot {
				long count;
				s_entry *first_entry;
			}; static_assert(sizeof(s_slot) == 0x8);

			bool  is_initialized;
					unsigned char : 8; unsigned short : 16;
			long number_of_slots;
			s_slot *slots;                  // [number_of_slots]
			long slots_in_use;
			s_entry           *entry_free_list;
			s_entry_pool_list *entry_pool_list;
		};

#pragma region field_type_definition

		typedef long (__cdecl *mdp_field_type_maximum_size_calculator)(struct field_properties_definition *properties_definition);

		typedef bool  (__cdecl *mdp_field_type_initialize)(struct field_properties_definition *properties_definition);

		typedef void  (__cdecl *mdp_field_type_dispose)(struct field_properties_definition *properties_definition);

		struct field_type_definition {
			Enums::network_field_type                      type;
			bool                                   requires_parameters;
																unsigned char : 8; unsigned short : 16;
			mdp_field_type_maximum_size_calculator proc_maximum_size_calculator;
			mdp_field_type_initialize              proc_initialize;
			mdp_field_type_dispose                 proc_dispose;
			bool                                   initialized;
																unsigned char : 8; unsigned short : 16;
		};
#pragma endregion

#pragma region field_properties_definition

		// returns the amount of bits written
		// If [source_data] == [baseline_data], [source_data] isn't encoded
		typedef long (__cdecl *mdp_field_encode)(struct field_properties_definition *field_properties, const void *baseline_data, const void *source_data, Memory::s_bitstream *output_stream);

		// returns the amount of bits read
		typedef long (__cdecl *mdp_field_decode)(struct field_properties_definition *field_properties, void *baseline_data, void *destination_data, Memory::s_bitstream *input_stream);

		struct field_properties_definition {
			Enums::network_field_type type;
			char              name[76];
			mdp_field_encode  proc_encode;
			mdp_field_decode  proc_decode;
			union field_type_definition_parameters *parameters;
			long maximum_size; ///< in bits
			long header_bit_size;
			bool  initialized;
					unsigned char : 8; unsigned short : 16;
		};
#pragma endregion

		struct field_reference {
			field_properties_definition *properties;
			uint offset; ///< in bytes
			uint baseline_offset; ///< in bytes
			bool   initialized;
					 unsigned char : 8; unsigned short : 16;
		};

		struct field_reference_set {
			long field_count;
			long max_data_size; ///< in bits
#pragma warning( push )
#pragma warning( disable : 4200 ) // nonstandard extension used : zero-sized array in struct/union, Cannot generate copy-ctor or copy-assignment operator when UDT contains a zero-sized array
			field_reference fields[];
#pragma warning( pop )
		};

#pragma region field_type_definition_parameters
		struct field_type_translated_index_parameters {
			// On initialization:
			// NONE is registered with network_index '0'
			// [translated_index_allocations] are memset to NONE (datum_index::null())
			// First element of [translated_index_allocations] is set to '1'

			long                    maximum_active_at_once; // should be +1 of actual max, for the 'null' entry (which is always the first)
			long                    number_of_slots;
			long                    bits_needed;
			s_index_resolution_table table;
			long                    cursor;
			// allocations[translated_index] == local_index (eg, player_index)
			datum_index *translated_index_allocations; // [maximum_active_at_once]. These are the local indexes
			long peak;
			long codings;
			long none;
		};

		union field_type_definition_parameters // Note: engine code doesn't actually use unions, so be sure you're accessing the right structure!
		{
			struct {
				Enums::integer_width_type width;
			} integer;
			struct {
				long maximum_length;
			} ascii_string, wide_string;
			struct {
				long max_size;
			} arbitrary_data;
			struct {
				Enums::network_field_type width;
										unsigned long : 32; // unknown
				field_properties_definition *member_properties;
			} array;
			struct {
				long field_count;
#pragma warning( push )
#pragma warning( disable : 4200 ) // nonstandard extension used : zero-sized array in struct/union, Cannot generate copy-ctor or copy-assignment operator when UDT contains a zero-sized array
				field_reference members_references[];
#pragma warning( pop )
			} structure;
			struct {
				field_properties_definition *referent_properties;
			}                                      pointer;
			struct {
				Enums::enumeration_width_type width;
			}                                      enumeration;
			struct {
				long minimum_value;
				long maximum_value;
			}                                      bounded_index;
			field_type_translated_index_parameters translated_index;
			struct {
				long component_count;
			}                                      point, vector;
			struct {
				long count;
				bool  valid_bits[Enums::k_mdp_maximum_flags]; // I guess
			}                                      flags;
			struct {
				long number_of_bits;
				long range_of_values;
			}                                      fixed_width;
			struct {
				long number_of_bits_theta_internet;
				long number_of_bits_phi_internet;
				long number_of_bits_theta_lan;
				long number_of_bits_phi_lan;
			}                                      fixed_width_normal_vector;
			struct {
				real          minimum_value;
				real          maximum_value;
				long         number_of_bits_theta_internet;
				long         number_of_bits_phi_internet; // unused
				long         number_of_bits_theta_lan;
				long         number_of_bits_phi_lan; // unused
				long         vectors_count;
				real_vector3d decode_vectors[32];
				real_vector3d encode_vectors[32];
			}                                      smart_vector;
		};
#pragma endregion

#pragma region message_delta_definition
		struct message_delta_definition {
			signed long definition_type;            // 0x0 [Enums::message_delta]
			long     message_dependent_header_size;   // 0x4 body_size + body field count
			long     iteration_size;               // 0x8
			long     iteration_independent_header_size;// 0xC
			long     total_size;                  // 0x10
			long     max_iterations;               // 0x14
			bool      initialized;
						 unsigned char : 8; unsigned short : 16;         // 0x18
			field_reference_set *header_field_set;   // 0x1C
			field_reference_set body_field_set;      // 0x20
		};
#pragma endregion

		struct decoding_information_data {
			Enums::message_delta_mode mode;      // 0x0
			signed long                 definition_type;         // 0x4 [Enums::message_delta]
			long                     iteration_count;            // 0x8
			long                     state;                  // 0xC
			Memory::s_bitstream *input_stream;   // 0x10
			long unknown1;                  // 0x14
			long current_iteration;         // 0x18
			bool  iteration_header_decoded;      // 0x1C
			bool  iteration_body_decoded;      // 0x1D
					unsigned short : 16;
			long : 32;   // 0x20, iteration_independent_overhead_type = 3
			long : 32;   // 0x24, iteration_independent_overhead_type = 2
			long : 32;   // 0x28, iteration_independent_overhead_type = 1
			long : 32;   // 0x2C, iteration_independent_overhead_type = 0

			// This structure may have 8 more bytes of data, but I haven't seen them used in code yet...
		};

		struct message_dependant_header {
			decoding_information_data *decoding_information;
			bool body_field_exists[64];
			void *custom_header_destination; // max size 0x84
		}; static_assert(sizeof(message_dependant_header) == 0x48);
	};
};
