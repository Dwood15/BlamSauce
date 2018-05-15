/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#include "Common/Precompile.hpp"
#include <YeloLib/Halo1/ai/ai_yelo.hpp>

#include <blamlib/Halo1/ai/actor_structures.hpp>
#include <blamlib/Halo1/ai/prop_structures.hpp>
#include <blamlib/Halo1/objects/objects.hpp>
#include <blamlib/Halo1/objects/object_structures.hpp>
#include <blamlib/Halo1/units/unit_structures.hpp>

#include <YeloLib/Halo1/units/units_yelo.hpp>

namespace Yelo
{
	namespace AI
	{
		bool PLATFORM_API ActorPropShouldCauseExitVehicle(const s_actor_datum* actor_datum, const s_prop_datum* prop_datum, const bool is_enemy)
		

		bool PLATFORM_API ActorShouldIgnoreSeatedProp(const s_prop_datum* prop)
		

		bool PLATFORM_API ActorShouldPanicAboutMountedUnit(const datum_index unit_index)
		
	};
};