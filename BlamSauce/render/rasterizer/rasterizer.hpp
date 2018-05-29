/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <d3d9.h>
#include "../../effects/player/player_effects.hpp"
#include "../render.hpp"
#include "../cameras.hpp"
#include "../../cseries/base.h"
#include "../../math/integer_math.h"
#include "../../models/model_definitions.hpp"
#include "../constants.hpp"
#include "../../math/matrix_math.h"

namespace Yelo {
	namespace Enums {
		enum rasterizer_target_render {
			_rasterizer_target_render_d3d,
			_rasterizer_target_render_primary,
			_rasterizer_target_render_secondary,

			k_number_of_rasterizer_target_renders
		};
	};

	namespace Rasterizer {
		struct s_rasterizer_config {
			const BOOL  linear_texture_addressing;
			const BOOL  linear_texture_addressing_zoom;
			const BOOL  linear_texture_addressing_sun;
			const BOOL  use_fixed_function;
			const BOOL  disable_driver_management;
			const BOOL  unsupported_card;
			const BOOL  prototype_card;
			const BOOL  old_driver;
			const BOOL  old_sound_driver;
			const BOOL  invalid_driver;
			const BOOL  invalid_sound_driver;
			const BOOL  disable_buffering;
			const BOOL  enable_stop_start;
			const BOOL  head_relative_speech;
			const BOOL  safe_mode;
			const DWORD force_shader;
			const BOOL  use_anisotropic_filter;
			const BOOL  disable_specular;
			const BOOL  disable_render_targets;
			const BOOL  disable_alpha_render_targets;
			const BOOL  use_alternative_convolve_mask;
			const BOOL  min_max_blend_op_is_broken;
			const FLOAT decal_z_bias_value;
			const FLOAT transparent_decal_z_bias_value;
			const FLOAT decal_slope_z_bias_value;
			const FLOAT transparent_decal_slope_z_bias_value;
		};

		s_rasterizer_config* RasterizerConfig()			PTR_IMP_GET2(rasterizer_config);


		struct s_rasterizer_globals {
			bool initialized;
				  unsigned char : 8;
			UNKNOWN_TYPE(short);
			UNKNOWN_TYPE(rectangle2d);
			UNKNOWN_TYPE(rectangle2d);
			unsigned long : 32;
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(long);
			unsigned long : 32;
			unsigned long : 32;
			unsigned long : 32;
			UNKNOWN_TYPE(real);
			UNKNOWN_TYPE(real);
			UNKNOWN_TYPE(real);
			UNKNOWN_TYPE(real);
			IDirect3DBaseTexture9 **default_texture_white;
			IDirect3DBaseTexture9 **default_texture_2d_texture;
			IDirect3DBaseTexture9 **default_texture_3d_texture; // engine actually uses 2d for 3d cases
			IDirect3DBaseTexture9 **default_texture_cubemap;
			short                 lightmap_mode;
			short                 maximum_nodes_per_model;
			bool                  using_software_vertex_processing;
										 unsigned char : 8;
			UNKNOWN_TYPE(short); // only set, never read (in any meaningful way)
			uint fixed_function_ambient; // ambient light value for FF
			UNKNOWN_TYPE(bool); // active camo related
			UNKNOWN_TYPE(bool); // shadows related
			UNKNOWN_TYPE(bool); // render targets related
					 unsigned char : 8;
					 unsigned long : 32;
		};

		static_assert(sizeof(s_rasterizer_globals) == 0x60);

		s_rasterizer_globals* RasterizerGlobals()		PTR_IMP_GET2(rasterizer_globals);


		struct s_rasterizer_window_parameters {
			short rasterizer_target;
			short window_index;

			UNKNOWN_TYPE(bool); // mirror rendering related
			UNKNOWN_TYPE(bool);

													 unsigned short : 16;
			Render::s_render_camera        camera;
			Render::s_render_frustum       frustum;
			Render::s_render_fog           fog;
			Players::s_player_screen_flash screen_flash;
		};

		static_assert(sizeof(s_rasterizer_window_parameters) == 0x258);


		struct s_rasterizer_debug_options {
			bool  fps;
					unsigned char : 8;
			short stats;
			short mode;
			bool  wireframe;
			bool  debug_model_vertices;
			short debug_model_lod;
			bool  debug_transparents;
			bool  debug_meter_shader;
			bool  models;
			bool  model_transparents;
			bool  draw_first_person_weapon_first;
			bool  stencil_mask;
			bool  environment;
			bool  environment_lightmaps;
			bool  environment_shadows;
			bool  environment_diffuse_lights;
			bool  environment_diffuse_textures;
			bool  environment_decals;
			bool  environment_specular_lights;
			bool  environment_specular_lightmaps;
			bool  environment_reflection_lightmap_mask;
			bool  environment_reflection_mirrors;
			bool  environment_reflections;
			bool  environment_transparents;
			bool  environment_fog;
			bool  environment_fog_screen;
			bool  water;
			bool  lens_flares;
			bool  dynamic_unlit_geometry;
			bool  dynamic_lit_geometry;
			bool  dynamic_screen_geometry;
			bool  hud_motion_sensor;
			bool  detail_objects;
			bool  debug_geometry;
			bool  debug_geometry_multipass;
			bool  fog_atmosphere;
			bool  fog_plane;
			bool  bump_mapping;
					unsigned short : 16;
			real  lightmap_ambient;
					unsigned short : 16;
			short pad3;
			bool  lightmaps_incident;
			bool  lightmaps_filtering;
					unsigned short : 16;
			real  model_lightning_ambient;
			bool  environment_alpha_testing;
			bool  environment_specular_mask;
			bool  shadows_convolution;
			bool  shadows_debug;
			bool  water_mipmapping;
			bool  active_camouflage;
			bool  active_camouflage_multipass;
			bool  plasma_energy;
			bool  lens_flares_occlusion;
			bool  lens_flares_occlusion_debug;
			bool  ray_of_buddha;
			bool  screen_flashes;
			bool  screen_effects;
			bool  DXTC_noise;
			bool  soft_filter;
			bool  secondary_render_target_debug;
			bool  profile_log;
					unsigned char : 8; unsigned short : 16;
			real  detail_objects_offset_multiplier;
			real  zbias;
			real  zoffset;
			bool  force_all_player_views_to_default_player;
			bool  safe_frame_bounds;
			short freeze_flying_camera;
			bool  zsprites;
			bool  filthy_decal_fog_hack;
			bool  smart;
			bool  splitscreen_VB_optimization;
			bool  profile_print_locks;
					unsigned char : 8; unsigned short : 16;
			long profile_objectlook_time;
			short effects_level;
			short _unk1;
			short _unk2;
					unsigned short : 16;
			real  pad3_scale;
			real  f0;
			real  f1;
			real  f2;
			real  f3;
			real  f4;
			real  f5;
		}; static_assert(sizeof(s_rasterizer_debug_options) == 0x90);

		s_rasterizer_debug_options* DebugOptions()		PTR_IMP_GET2(rasterizer_debug_data);

		struct s_rasterizer_frame_parameters {
			double elapsed_time;

			real UNKNOWN(

			0);

			real UNKNOWN(

			1);
		};

		s_rasterizer_frame_parameters* FrameParameters()	PTR_IMP_GET2(rasterizer_frame_params);
		static char g_screenshot_folder[MAX_PATH] = "screenshots\\";
		static s_rasterizer_resolution g_resolution_list[64];
	};
};
namespace Yelo::Rasterizer {

	constexpr bool with_max_tri_upgrades = Enums::k_maximum_rendered_triangles_upgrade > Enums::k_maximum_rendered_triangles;

	static class c_render_upgrades {
	public:
		// If we're not compiling with any upgrades, then don't waste space in the compiled code

		void InitializeRenderedTrianglesUpgrade() {
			//ayyyy metaprogramming, thanks, c++ 17!
			if constexpr (with_max_tri_upgrades) {
				static uint rendered_triangles[Enums::k_maximum_rendered_triangles_upgrade];

				// redirect all rendered triangle pointers to the new array
				for (auto ptr : K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_LIST)
					*ptr = rendered_triangles;
				// change all references to the rendered triangle array to our new size
				for (auto ptr : K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_LIST)
					*ptr = Enums::k_maximum_rendered_triangles_upgrade;
			}
		}

		// Not actually an upgrade, but a fix (nodes at index >43 would get stretched). However, we fix it in both sapien and ingame so I put the code here
		static void InitializeMaximumNodesPerModelFixes() {
			static real_matrix3x4 vsh_constants__nodematrices[Enums::k_maximum_nodes_per_model + 1];

			for (auto ptr : K_VSH_CONSTANTS__NODEMATRICES_REFERENCES) {
				*ptr = &vsh_constants__nodematrices[0];
			}

			for (auto ptr : K_VSH_CONSTANTS__NODEMATRICES_REFERENCES_PLUS_8) {
				*ptr = reinterpret_cast<byte *>(&vsh_constants__nodematrices[0]) + 8;
			}

			for (auto ptr : K_RASTERIZER_GLOBALS_MAXIMUM_NODES_PER_MODEL_WRITE_VALUES) {
				*ptr = Enums::k_maximum_nodes_per_model;
			}
			RasterizerGlobals()->maximum_nodes_per_model = Enums::k_maximum_nodes_per_model;
		}
	}              g_render_upgrades;

}

