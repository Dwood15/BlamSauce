#pragma once

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Control
	{
		/// <summary>	A property value union struct. </summary>
		struct s_interface_value
		{
			union
			{
				byte m_data[16];
				bool m_bool;
				byte m_byte;
				sbyte m_sbyte;
				unsigned short m_uint16;
				short m_int16;
				uint m_uint;
				long m_int32;
				uint64 m_uint64;
				__int64 m_int64;
				real m_real;
				char* m_const char *;
				wchar_t* m_wstring;
				point2d m_point2d;
				rectangle2d m_rectangle2d;
				real_vector2d m_real_vector2d;
				real_vector3d m_real_vector3d;
				real_point2d m_real_point2d;
				real_point3d m_real_point3d;
				real_quaternion m_real_quaternion;
				rgb_color m_rgb_color;
				argb_color m_argb_color;
				real_rgb_color m_real_rgb_color;
				real_argb_color m_real_argb_color;
			};
			
#pragma region String Handling
		private:
			bool is_const char *;
			bool is_wstring;
			bool is_string_owner;
			unsigned char : 8;

			/// <summary>	Deletes the string value data if present. </summary>
			void DeleteString();

		public:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Copies a string to the const char * value. </summary>
			///
			/// <param name="value">	The string to copy. </param>
			void SetString(const std::string& value);
			
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Copies a string to the wstring value. </summary>
			///
			/// <param name="value">	The string to copy. </param>
			void SetString(const std::wstring& value);
#pragma endregion

		public:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	The union memory is zero'd in the default constructor. </remarks>
			s_interface_value();

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Destructor. </summary>
			///
			/// <remarks>	Deletes any owned string memory. </remarks>
			~s_interface_value();

		private:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Constructor. </summary>
			///
			/// <remarks>
			/// 	This private constructor copies data from the supplied pointer to the union'd members.
			/// </remarks>
			///
			/// <param name="data">	[in] A pointer to the data to copy. </param>
			/// <param name="size">	The size of the data to copy. </param>
			s_interface_value(void* data, const long size);

		public:
			s_interface_value(bool value);
			s_interface_value(byte value);
			s_interface_value(sbyte value);
			s_interface_value(unsigned short value);
			s_interface_value(short value);
			s_interface_value(uint value);
			s_interface_value(long value);
			s_interface_value(uint64 value);
			s_interface_value(__int64 value);
			s_interface_value(real value);
			s_interface_value(const char * value);
			s_interface_value(wstring value);
			s_interface_value(point2d value);
			s_interface_value(rectangle2d value);
			s_interface_value(real_vector2d value);
			s_interface_value(real_vector3d value);
			s_interface_value(real_point2d value);
			s_interface_value(real_point3d value);
			s_interface_value(real_quaternion value);
			s_interface_value(rgb_color value);
			s_interface_value(argb_color value);
			s_interface_value(real_rgb_color value);
			s_interface_value(real_argb_color value);
		};
	};};};
};
