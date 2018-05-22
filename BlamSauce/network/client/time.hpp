/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo
{
	namespace Networking
	{
		struct s_network_client_time
		{
			enum { TIME_SYNCH_SAMPLES = 0x1E };
			struct s_time_sample : TStructImpl(0x14)
			{
			};

			long time_delta;
			long number_of_time_samples;
			unsigned long : 32; // unknown
			s_time_sample samples[TIME_SYNCH_SAMPLES];
		}; static_assert( sizeof(s_network_client_time) == 0x264 );
	};
};
