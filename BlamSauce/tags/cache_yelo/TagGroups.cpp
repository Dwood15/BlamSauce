/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#include "Common/Precompile.hpp"
#include "TagGroups/TagGroups.hpp"

#include <blamlib/Halo1/cache/cache_files_globals.hpp>
#include <blamlib/Halo1/cache/cache_files_structures.hpp>
#include <blamlib/Halo1/main/console.hpp>
#include <YeloLib/Halo1/open_sauce/project_yellow_scenario.hpp>
#include <YeloLib/Halo1/open_sauce/project_yellow_scenario_definitions.hpp>

#include "Memory/MemoryInterface.hpp"

#include "TagGroups/CacheFiles.hpp"

namespace Yelo
{
	namespace TagGroups
	{
#include "Memory/_EngineLayout.inl"

		Cache::s_cache_tag_header* Index()					{ return Cache::CacheFileGlobals()->tag_index; }
		Cache::s_cache_tag_instance const* Instances()		DPTR_IMP_GET(tag_instances);

		Cache::s_cache_tag_instance** GlobalTagInstancesReference()	DPTR_IMP_GET2(tag_instances);


		void Initialize()
		{
			Scenario::ProjectYellowInitialize();
		}

		void Dispose()
		{
			Scenario::ProjectYellowDispose();
		}

		void InitializeForNewMap()
		{
			// TODO: this will need to be changed/removed once our rewritten scenario_load code is in place
			Scenario::ProjectYellowInitializeForNewMap();
		}
	};

	namespace blam
	{
		const char * __cdecl tag_get_name(datum_index tag_index)
		{
			if (Scenario::GetYelo()->IsCacheProtected())
				return "PROTECTED";

			if (tag_index.IsNull())
				return "NONE";
			else if (tag_index.index >= TagGroups::Index()->count)
				return "INVALID";
			
			const char * name = TagGroups::Instances()[tag_index.index].name;

			return name != nullptr
				? name
				: "<unnamed tag>";
		}
	};
};
