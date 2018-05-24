#pragma once

#include <precompile.h>

namespace Yelo {
	namespace Lights {
		struct s_lights_datum : TStructImpl(124) {
		};

		typedef Memory::DataArray<s_lights_datum, 896> lights_data_t;

		lights_data_t &Lights();

		struct s_lights_globals_data {
			bool enabled;
			unsigned char : 8;
			unsigned short : 16;
		};

		s_lights_globals_data *LightsGlobals();

		struct s_light_cluster_data : TStructImpl(2048) {
		};

		s_light_cluster_data *LightCluster();

		struct s_cluster_light_reference_datum : TStructImpl(12) {
		};
		typedef Memory::DataArray<s_cluster_light_reference_datum, 2048> cluster_light_reference_data_t;

		cluster_light_reference_data_t &ClusterLightReference();

		struct s_light_cluster_reference_datum : TStructImpl(12) {
		};
		typedef Memory::DataArray<s_light_cluster_reference_datum, 2048> light_cluster_reference_data_t;

		light_cluster_reference_data_t &LightClusterReference();

		lights_data_t &Lights() DPTR_IMP_GET_BYREF(lights);

		s_lights_globals_data *LightsGlobals() DPTR_IMP_GET(light_game_globals);

		s_light_cluster_data *LightCluster() DPTR_IMP_GET(light_cluster);

		cluster_light_reference_data_t &ClusterLightReference() DPTR_IMP_GET_BYREF(cluster_light_reference);

		light_cluster_reference_data_t &LightClusterReference() DPTR_IMP_GET_BYREF(light_cluster_reference);
	};
};
