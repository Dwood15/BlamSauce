/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <precompile.h>

namespace Yelo {
	struct datum_index;

	/// <summary>	Handle to data allocated by the engine's data-array construct. </summary>
	struct datum_index {
		typedef short index_t;
		typedef short salt_t;

		union {
			uint handle;
			struct {
				////////////////////////////////////////////////////////////////////////////////////////////////////
				/// <summary>
				/// 	absolute index Note: This is actually suppose to be a unsigned short but it's not until
				/// 	Halo 3 where data starts breaking past the 0x7FFF cap, so for Halo 1 and Halo 2 projects
				/// 	this should still hold safe. Maybe I'll update the code to unsigned short one day...
				/// </summary>
				index_t index;
				/// <summary>	salted index, gives the handle a certain uniqueness. </summary>
				salt_t  salt;
			};
		};

		static constexpr datum_index null() { return { static_cast<uint>(-1) }; };

		bool IsNull() const { return -1 == handle; }

		static datum_index Create(index_t index, salt_t salt) {
			datum_index result;
			result.handle = (static_cast<uint>(salt) << 16) | index;
			return result;
		}

		// [header] should be a pointer to the start of a datum instance in a data array
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates a new datum_index based on an absolute index and datum pointer. </summary>
		///
		/// <param name="index"> 	Zero-based index of the datum. </param>
		/// <param name="header">	[in] should be a pointer to the start of a datum instance in a data array </param>
		///
		/// <returns>	[datum_index::null] if this fails </returns>
		static datum_index Create(index_t index, const void *header) {
			if (header == nullptr) return null();

			return Create(index, *reinterpret_cast<const salt_t*>(header));
		}

		//Something something deprecated and removed in C++17 pita to get around don't really care enough nor am I certain it's going to be used.
		// struct std_hash : public std::unary_function<datum_index, size_t> {
		// 	// logic copied and pasted from xstddef's _Bitwise_hash
		// 	size_t operator ()(const datum_index &_Keyval) const {   // hash _Keyval to size_t value by pseudorandomizing transform
		// 		return std::_Hash_seq((const unsigned char *) &_Keyval, sizeof(datum_index));
		// 	}
		// };

		OVERRIDE_OPERATOR_CAST_THIS(uint);

		datum_index& operator = (uint arg) {
			this->handle = arg;
			return *this;
		}

		inline bool operator ==(const datum_index& rhs) const { return this->handle == rhs.handle; }
		inline bool operator !=(const datum_index& rhs) const { return this->handle != rhs.handle; }

	private:

		inline bool operator ==(const uint& rhs) const { return this->handle == rhs; }
		inline bool operator !=(const uint& rhs) const { return this->handle != rhs; }
	};

	static_assert(sizeof(datum_index) == 0x4);
#define pad_datum_index unsigned short : 16; unsigned short : 16
#define DATUM_INDEX_TO_IDENTIFIER(datum)      (datum & 0xFFFF0000)
#define DATUM_INDEX_TO_ABSOLUTE_INDEX(datum)   (datum & 0x0000FFFF)
};
