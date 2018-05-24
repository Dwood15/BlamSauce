/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo
{
	namespace Render { namespace Lightmaps
	{
		void Initialize();
		void Dispose();
		
		void SetLightmaps(const datum_index standard_tag_index);
		void SetLightmaps(const datum_index standard_tag_index
			, const datum_index directional_1_tag_index
			, const datum_index directional_2_tag_index
			, const datum_index directional_3_tag_index);

		void SetLightmapSamplers(const bool use_directional);
		const bool HasDirectional();
	};};
};
