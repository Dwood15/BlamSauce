#pragma once

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	CRC's a string. </summary>
		///
		/// <param name="str">	The string to CRC. </param>
		///
		/// <returns>	The CRC for the string. </returns>
		const uint32 CRCString(const char* str);
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Verifies that the CRC for the provided string is correct. </summary>
		///
		/// <param name="str">	The string to verify. </param>
		/// <param name="crc">	The CRC to verify. </param>
		///
		/// <returns>	The provided CRC. </returns>
		const uint32 VerifyCRC(const char* str, uint32 crc);

		#define RESOURCE_ID_DEBUG(str) Yelo::Interface::OpenSauceUI::CRCString( (str) )
		#define RESOURCE_ID(str, crc) Yelo::Interface::OpenSauceUI::VerifyCRC( (str), (crc) )
		//#define RESOURCE_ID(str, crc) crc
		#define RESOURCE_ID_NONE 0xFFFFFFFF
	};};
};
