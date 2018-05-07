/*
	Yelo: Open Sauce SDK
	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

// [arg2] = documentation
#define TAG_FLAG8(name, ...)            Yelo::byte_flags name##_bit : 1

// [arg2] = documentation
#define TAG_FLAG16(name, ...)            Yelo::word_flags name##_bit : 1

// [arg2] = documentation
#define TAG_FLAG(name, ...)               Yelo::long_flags name##_bit : 1

// [arg2] = enum type
// [arg3] = documentation
#define TAG_ENUM8(name, ...)            Yelo::byte_enum name

// [arg2] = enum type
// [arg3] = documentation
#define TAG_ENUM(name, ...)               short name

// [arg2] = enum type
// [arg3] = documentation
#define TAG_ENUM32(name, ...)            long name

#define TAG_BLOCK_INDEX(block_type, name)   block_type::block_index_t name

#define TAG_BLOCK(name, block_type)         Yelo::tag_block name
// Used for blocks which need to allow non-const access
#define TAG_TBLOCK_(name, block_type)      Yelo::TagBlock<block_type> name
#define TAG_TBLOCK(name, block_type)   Yelo::TagBlock<const block_type> name

// [arg2] = units
// [arg3] = documentation
#define TAG_FIELD(type, name, ...)         type name

#define TAG_ARRAY(type, name, count)      type name[count]

#define TAG_PAD(type, count)            Yelo::byte BOOST_JOIN(pad, __COUNTER__)[sizeof(type)*(count)]

#define TAG_BLOCK_GET_ELEMENT(block_ptr, index, type)  &(block_ptr->Elements<type>()[index])
