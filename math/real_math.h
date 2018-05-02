#pragma once

/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include "../cseries/cseries_base.h"
#include "../cseries/MacrosCpp.h"
#include <d3dx9math.h>

namespace Yelo {
	// a floating number in degrees
	typedef float angle;
#define pad_angle PAD32

	// a fraction represented in a floating-point number
	typedef float real_fraction;

	struct real_vector2d;
	struct real_vector3d;

	// a point in real 2d space.
	/*union*/ struct real_point2d {
		// X-Axis
		real x;

		// Y-Axis
		real y;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS(real_vector2d);
#if PLATFORM_TARGET != PLATFORM_TARGET_XBOX
		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR2);
#endif
	};

#define pad_real_point2d PAD32 PAD32

	// a point in real 3d space
	/*union*/ struct real_point3d {
		// X-Axis
		real x;

		// Y-Axis
		real y;

		// Z-Axis
		real z;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS(real_point2d);

		OVERRIDE_OPERATOR_CAST_THIS(real_vector3d);
#if PLATFORM_TARGET != PLATFORM_TARGET_XBOX
		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR3);
#endif
	};

#define pad_real_point3d PAD32 PAD32 PAD32

	// A 2d real vector
	/*union*/ struct real_vector2d {
		// X-Component
		real i;

		// Y-Component
		real j;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS_REF(real_point2d);
#if PLATFORM_TARGET != PLATFORM_TARGET_XBOX
		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR2);
#endif

		real Magnitude() const;

		inline void Normalize() {
			real len = this->Magnitude();
			this->i /= len;
			this->j /= len;
		}

		inline void Inverse() {
			this->i = -this->i;
			this->j = -this->j;
		}

		inline void Set(real _i, real _j) {
			this->i = _i;
			this->j = _j;
		}

		inline real_vector2d &operator +=(const real_vector2d &v) {
			this->i += v.i;
			this->j += v.j;
			return *this;
		}

		inline real_vector2d &operator -=(const real_vector2d &v) {
			this->i -= v.i;
			this->j -= v.j;
			return *this;
		}

		inline real_vector2d &operator *=(real scalar) {
			this->i *= scalar;
			this->j *= scalar;
			return *this;
		}

		inline real_vector2d &operator /=(real scalar) {
			this->i /= scalar;
			this->j /= scalar;
			return *this;
		}

		///< Conjugate
		inline real_vector2d operator -() const {
			return real_vector2d{-this->i, -this->j};
		}

		///< Addition
		inline real_vector2d operator +(const real_vector2d &rh) const {
			return real_vector2d{this->i + rh.i, this->j + rh.j};
		}

		///< Addition
		inline real_vector2d operator +(const real_point2d &rh) const {
			return real_vector2d{this->i + rh.x, this->j + rh.y};
		}

		///< Subtraction
		inline real_vector2d operator -(const real_vector2d &rh) const {
			return real_vector2d{this->i - rh.i, this->j - rh.j};
		}

		///< Subtraction
		inline real_vector2d operator -(const real_point2d &rh) const {
			return real_vector2d{this->i - rh.x, this->j - rh.y};
		}

		///< Dot Product
		inline real operator *(const real_vector2d &rh) const { return this->i * rh.i + this->j * rh.j; }

		///< Dot Product
		inline real operator *(const real_point2d &rh) const { return this->i * rh.x + this->j * rh.y; }

		///< Scalar Multiplication
		inline real_vector2d operator *(real rh) const {
			return real_vector2d{this->i * rh, this->j * rh};
		}

		///< Scalar Division
		inline real_vector2d operator /(real rh) const {
			return real_vector2d{this->i / rh, this->j / rh};
		}

		static void DotProduct2D(real_vector2d *a, real_vector2d *b, real &out_value);
	};

#define pad_real_vector2d PAD32 PAD32

	// a 3d real vector
	/*union*/ struct real_vector3d {
		// X-Component
		real i;

		// Y-Component
		real j;

		// Z-Component
		real k;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS(real_vector2d);

		OVERRIDE_OPERATOR_CAST_THIS_REF(real_point3d);

		//TODO: DirectX!
		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR3);

		real Magnitude() const;

		inline void Normalize() {
			real len = this->Magnitude();
			this->i /= len;
			this->j /= len;
			this->k /= len;
		}

		inline void Inverse() {
			this->i = -this->i;
			this->j = -this->j;
			this->k = -this->k;
		}

		inline void Set(real _i, real _j, real _k) {
			this->i = _i;
			this->j = _j;
			this->k = _k;
		}

		inline real_vector3d &operator +=(const real_vector3d &v) {
			this->i += v.i;
			this->j += v.j;
			this->k += v.k;
			return *this;
		}

		inline real_vector3d &operator -=(const real_vector3d &v) {
			this->i -= v.i;
			this->j -= v.j;
			this->k -= v.k;
			return *this;
		}

		inline real_vector3d &operator *=(real scalar) {
			this->i *= scalar;
			this->j *= scalar;
			this->k *= scalar;
			return *this;
		}

		inline real_vector3d &operator /=(real scalar) {
			this->i /= scalar;
			this->j /= scalar;
			this->k /= scalar;
			return *this;
		}

		///< Conjugate
		inline real_vector3d operator -() const {
			return real_vector3d{-this->i, -this->j, -this->k};
		}

		///< Addition
		inline real_vector3d operator +(const real_vector3d &rh) const {
			return real_vector3d{this->i + rh.i, this->j + rh.j, this->k + rh.k};
		}

		///< Addition
		inline real_vector3d operator +(const real_point3d &rh) const {
			return real_vector3d{this->i + rh.x, this->j + rh.y, this->k + rh.z};
		}

		///< Subtraction
		inline real_vector3d operator -(const real_vector3d &rh) const {
			return real_vector3d{this->i - rh.i, this->j - rh.j, this->k - rh.k};
		}

		///< Subtraction
		inline real_vector3d operator -(const real_point3d &rh) const {
			return real_vector3d{this->i - rh.x, this->j - rh.y, this->k - rh.z};
		}

		///< Cross Product
		inline real_vector3d operator ^(const real_vector3d &rh) const {
			return real_vector3d{
				this->j * rh.k - this->k * rh.j,
				-this->i * rh.k + this->k * rh.i,
				this->i * rh.j - this->j * rh.i
			};
		}

		///< Cross Product
		inline real_vector3d operator ^(const real_point3d &rh) const {
			return real_vector3d{
				this->j * rh.z - this->k * rh.y,
				-this->i * rh.z + this->k * rh.x,
				this->i * rh.y - this->j * rh.x
			};
		}

		///< Dot Product
		inline real operator *(const real_vector3d &rh) const { return this->i * rh.i + this->j * rh.j + this->k * rh.k; }

		///< Dot Product
		inline real operator *(const real_point3d &rh) const { return this->i * rh.x + this->j * rh.y + this->k * rh.z; }

		///< Scalar Multiplication
		inline real_vector3d operator *(real rh) const {
			return real_vector3d{this->i * rh, this->j * rh, this->k * rh};
		}

		///< Scalar Division
		inline real_vector3d operator /(real rh) const {
			return real_vector3d{this->i / rh, this->j / rh, this->k / rh};
		}
	};

#define pad_real_vector3d PAD32 PAD32 PAD32

	// a 3d real vector with ?
	struct real_quaternion {
		// X-Component
		real i;

		// Y-Component
		real j;

		// Z-Component
		real k;

		// ?
		real w;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		//TODO: D39 import things.
		//OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR4);
		//OVERRIDE_OPERATOR_CAST_THIS(D3DXQUATERNION);

		void Compress64bit(uint16 out[4]) const;

		void Decompress64bit(int16 in[4]);

		inline void Inverse() {
			this->i = -this->i;
			this->j = -this->j;
			this->k = -this->k;
			this->w = -this->w;
		}

		inline void Conjugate() {
			this->i = -this->i;
			this->j = -this->j;
			this->k = -this->k;
		}

		void FromAngles(struct real_euler_angles3d *angles);

		void Lerp(real_quaternion *q1, real_quaternion *q2, real interp);

		void SLerp(real_quaternion *q1, real_quaternion *q2, real interp);

		void ToAxisAngle(real_point3d *axis, real &angle);

		void Normalize();
	};

#define pad_real_quaternion PAD32 PAD32 PAD32 PAD32

	// real Euler angles in 2d space
	/*union*/ struct real_euler_angles2d {
		// Up, Down offset degrees
		angle yaw;

		// Side to Side offset degrees
		angle pitch;

		OVERRIDE_OPERATOR_CAST_THIS(float);
	};

#define pad_real_euler_angles2d PAD32 PAD32

	// real Euler angles in 3d space
	/*union*/ struct real_euler_angles3d {
		// Up, Down offset degrees
		angle yaw;

		// Side to Side offset degrees
		angle pitch;

		// Left to Right offset degrees
		angle roll;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS(real_euler_angles2d);
	};

#define pad_real_euler_angles3d PAD32 PAD32 PAD32

	//
	struct real_plane2d {
		// X-Component of plane's normal
		real i;

		// Y-Component of plane's normal
		real j;

		// Distance the plane is from the origin
		real d;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS_REF(real_vector2d);

		inline void Normalize();
	};

#define pad_real_plane2d PAD32 PAD32 PAD32

	//
	struct real_plane3d {
		// X-Component of plane's normal
		real i;

		// Y-Component of plane's normal
		real j;

		// Z-Component of plane's normal
		real k;

		// Distance the plane is from the origin
		real d;

		OVERRIDE_OPERATOR_CAST_THIS(float);

		OVERRIDE_OPERATOR_CAST_THIS(real_plane2d);

		OVERRIDE_OPERATOR_CAST_THIS_REF(real_vector3d);

		//TODO: DirectX includes.
		//OVERRIDE_OPERATOR_CAST_THIS(D3DXPLANE);

		inline void Normalize();
	};

#define pad_real_plane3d PAD32 PAD32 PAD32 PAD32

	/*union*/ struct real_rectangle2d {
		real x0, x1; // top, bottom
		real y0, y1; // left, right
	};
#define pad_real_rectangle2d   PAD32 PAD32 PAD32 PAD32

	/*union*/ struct real_rectangle3d {
		real x0, x1;
		real y0, y1;
		real z0, z1;
	};

#define pad_real_rectangle3d   PAD32 PAD32 PAD32 PAD32 PAD32 PAD32

	struct real_orientation3d {
		real_quaternion rotation;
		real_point3d    translation;
		real            scale;
	};
#define pad_real_orientation3d   PAD_TYPE(real_quaternion)   PAD_TYPE(real_point3d)      PAD32

	// bounding in real angle values
	struct angle_bounds {
		angle lower;
		angle upper;

		OVERRIDE_OPERATOR_CAST_THIS(float);
	};

	// bounding in real values
	struct real_bounds {
		real lower;
		real upper;

		OVERRIDE_OPERATOR_CAST_THIS(float);
	};

#define pad_real_bounds PAD32 PAD32

	// bounding in real values
	struct real_fraction_bounds {
		real lower;
		real upper;

		OVERRIDE_OPERATOR_CAST_THIS(float);
	};
};
