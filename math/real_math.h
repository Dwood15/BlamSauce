/*
	CppBlamSauce SDK

	See <../README.md> for information
	See <../LICENSE> for license information
*/
#pragma once

#include "../cseries/cseries_base.h"
#include "../cseries/MacrosCpp.h"
#include <d3dx9math.h>

#define MATH_FLOAT_FUNC(func) (real)func
#define MATH_DOUBLE_FUNC(func) func
#define MATH_FLOAT_TO_LONG(...) ( __VA_ARGS__ )

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

		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR2);
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

		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR3);
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

		OVERRIDE_OPERATOR_CAST_THIS(D3DXVECTOR2);

		real Magnitude() const { return MATH_FLOAT_FUNC(sqrt)(this->i * this->i + this->j * this->j); }

		API_FUNC_NAKED void DotProduct2D() const {
			API_FUNC_NAKED_START()
			push   ecx
			push   esi

			mov      ecx, a
			mov      esi, b
			fld      dword ptr[ecx]real_vector2d.i
			fmul   dword ptr[esi]real_vector2d.i

			fld      dword ptr[ecx]real_vector2d.j
			fmul   dword ptr[esi]real_vector2d.j

			fadd
			fstp   out_value

			pop      esi
			pop      ecx
			API_FUNC_NAKED_END(3)
		}

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

		real Magnitude() const { return MATH_FLOAT_FUNC(sqrt)(this->i * this->i + this->j * this->j + this->k * this->k); }

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

	//////////////////////////////////////////////////////////////////////////
	// real_quaternion
	static const real k_rad_to_deg = 57.2957795f;

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

		void Compress64bit(uint16 out[4]) const {
			out[0] = (uint16) MATH_FLOAT_TO_LONG(this->i * 32767.0f);
			out[1] = (uint16) MATH_FLOAT_TO_LONG(this->j * 32767.0f);
			out[2] = (uint16) MATH_FLOAT_TO_LONG(this->k * 32767.0f);
			out[3] = (uint16) MATH_FLOAT_TO_LONG(this->w * 32767.0f);
		}

		void Decompress64bit(int16 in[4]) {
			this->i = (real) (in[0] / 32767.0f);
			this->j = (real) (in[1] / 32767.0f);
			this->k = (real) (in[2] / 32767.0f);
			this->w = (real) (in[3] / 32767.0f);
		}

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

		void FromAngles(struct real_euler_angles3d *angles) {
			real   angle;
			double sr, sp, sy, cr, cp, cy;

			angle = angles->roll * 0.5f;
			sy    = MATH_DOUBLE_FUNC(sin)(angle);
			cy    = MATH_DOUBLE_FUNC(cos)(angle);
			angle = angles->pitch * 0.5f;
			sp    = MATH_DOUBLE_FUNC(sin)(angle);
			cp    = MATH_DOUBLE_FUNC(cos)(angle);
			angle = angles->yaw * 0.5f;
			sr    = MATH_DOUBLE_FUNC(sin)(angle);
			cr    = MATH_DOUBLE_FUNC(cos)(angle);

			double crcp = cr * cp;
			double srsp = sr * sp;

			this->i = (real) (sr * cp * cy - cr * sp * sy);
			this->j = (real) (cr * sp * cy + sr * cp * sy);
			this->k = (real) (crcp * sy - srsp * cy);
			this->w = (real) (crcp * cy + srsp * sy);
		}

		void Lerp(real_quaternion *q1, real_quaternion *q2, real interp) {
			real_quaternion start = *q1; // copy
			start.Conjugate();

			real cosOmega =
					  start.i * q2->i +
					  start.j * q2->j +
					  start.k * q2->k +
					  start.w * q2->w;

			if (cosOmega < 0) {
				cosOmega *= -1;
				start.Inverse();
			}

			if (MATH_DOUBLE_FUNC(abs)(MATH_FLOAT_TO_LONG(1.0f + cosOmega)) < 1.0e-6f) {
				real tx = interp * start.i;
				real ty = interp * start.j;
				real tz = interp * start.k;
				real tw = interp * start.w;

				this->i = start.i - tx - ty;
				this->j = start.j - ty + tx;
				this->k = start.k - tz - tw;
				this->w = start.w;
			} else {
				this->i = start.i + interp * (q2->i - start.i);
				this->j = start.j + interp * (q2->j - start.j);
				this->k = start.k + interp * (q2->k - start.k);
				this->w = start.w + interp * (q2->w - start.w);
			}
		}

		void SLerp(real_quaternion *q1, real_quaternion *q2, real interp) {
			// Decide if one of the quaternions is backwards
			real a = 0, b = 0;

			a += (q1->i - q2->i) * (q1->i - q2->i);
			b += (q1->i + q2->i) * (q1->i + q2->i);

			a += (q1->j - q2->j) * (q1->j - q2->j);
			b += (q1->j + q2->j) * (q1->j + q2->j);

			a += (q1->k - q2->k) * (q1->k - q2->k);
			b += (q1->k + q2->k) * (q1->k + q2->k);

			a += (q1->w - q2->w) * (q1->w - q2->w);
			b += (q1->w + q2->w) * (q1->w + q2->w);

			if (a > b)
				q2->Inverse();

			real   cosom =
						 q1->i * q2->i +
						 q1->j * q2->j +
						 q1->k * q2->k +
						 q1->w * q2->w;
			double sclq1, sclq2;

			if ((1.0f + cosom) > 0.00000001f) {
				if ((1.0f - cosom) > 0.00000001f) {
					double omega = MATH_DOUBLE_FUNC(acos)(cosom);
					double sinom = MATH_DOUBLE_FUNC(sin)(omega);
					sclq1 = MATH_DOUBLE_FUNC(sin)((1.0 - interp) * omega) / sinom;
					sclq2 = MATH_DOUBLE_FUNC(sin)(interp * omega) / sinom;
				} else {
					sclq1 = 1.0f - interp;
					sclq2 = interp;
				}
				this->i = (real) (sclq1 * q1->i + sclq2 * q2->i);
				this->j = (real) (sclq1 * q1->j + sclq2 * q2->j);
				this->k = (real) (sclq1 * q1->k + sclq2 * q2->k);
				this->w = (real) (sclq1 * q1->w + sclq2 * q2->w);
			} else {
				this->i = -q1->j;
				this->j = q1->i;
				this->k = -q1->w;
				this->w = q1->k;

				sclq1 = MATH_DOUBLE_FUNC(sin)((1.0f - interp) * 0.5f * 3.14159);
				sclq2 = MATH_DOUBLE_FUNC(sin)(interp * 0.5f * 3.14159);
				this->i = (real) (sclq1 * q1->i + sclq2 * this->i);
				this->j = (real) (sclq1 * q1->j + sclq2 * this->j);
				this->k = (real) (sclq1 * q1->k + sclq2 * this->k);
			}
		}

		void ToAxisAngle(real_point3d *axis, real &angle) {
			// The quaternion representing the rotation is
			//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

			double SqrLength =
						 this->i * this->i +
						 this->j * this->j +
						 this->k * this->k;
			if (SqrLength > 0.0) {
				angle           = (real) (k_rad_to_deg * 2.0f * MATH_DOUBLE_FUNC(acos)(this->w));
				real fInvLength = (real) (1.0 / MATH_DOUBLE_FUNC(sqrt)(SqrLength));
				axis->x = this->i * fInvLength;
				axis->y = this->j * fInvLength;
				axis->z = this->k * fInvLength;
			} else {
				// angle is 0 (mod 2*pi), so any axis will do
				angle = 0.0f;
				axis->x = 1.0f;
				axis->y = 0.0f;
				axis->z = 0.0f;
			}
		}

		void Normalize() {
			real mag = MATH_FLOAT_FUNC(sqrt)(
				this->i * this->i +
				this->j * this->j +
				this->k * this->k +
				this->w * this->w);

			this->i /= mag;
			this->j /= mag;
			this->k /= mag;
			this->w /= mag;
		};
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

		inline void Normalize() {
			real mag = MATH_FLOAT_FUNC(sqrt)(
				this->i * this->i +
				this->j * this->j
			);

			this->i /= mag;
			this->j /= mag;
			this->d /= mag;
		}
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

		inline void Normalize() {
			real mag = MATH_FLOAT_FUNC(sqrt)(
				this->i * this->i +
				this->j * this->j +
				this->k * this->k
			);

			this->i /= mag;
			this->j /= mag;
			this->k /= mag;
			this->d /= mag;
		}
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
