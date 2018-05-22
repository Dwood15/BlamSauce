/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/memory/data.hpp>

namespace Yelo
{
	namespace Objects
	{
		struct s_device_groups_datum : Memory::s_datum_base
		{
			unsigned short flags;
			real value;
		};
	};
};
