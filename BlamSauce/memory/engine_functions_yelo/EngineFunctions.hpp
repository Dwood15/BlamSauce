/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo
{
	namespace Memory
	{
		struct s_data_array;
	};

	namespace MessageDeltas
	{
		struct s_index_resolution_table;
	};
};

namespace Yelo
{
	namespace Engine
	{
		void GatherException(const void* data = nullptr, long arg_0 = 0x89, long arg_4 = 0x7E, long arg_8 = 1);


		// NOTE: we should just use GS's md5.c functions, but the GS SDK is no longer 'open' heh
		void GSMD5Digest(byte* input, unsigned int input_length, char output[33]);
		bool CompareMD5(byte* input, unsigned int input_length, const char* comparison_md5);

		namespace Networking
		{
#ifndef YELO_NO_NETWORK
			// TODO:
			// TranslatedIndexClientRegister
			// TranslatedIndexUnregister

			// Translate a local object_index to a translated_index (ie, network)
			long TranslateObject(datum_index local_object_index);
			// Translate a local player_index to a translated_index (ie, network)
			long TranslatePlayer(datum_index local_player_index);

			long TranslatedIndexRegister(MessageDeltas::s_index_resolution_table& table, datum_index local_index);
#endif
		};
	};

	//////////////////////////////////////////////////////////////////////////
	// bink
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// bink_playback.c
		void __cdecl bink_playback_start(const char * bik_path);
	};
};
