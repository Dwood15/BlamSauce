#pragma once

#include <precompile.h>
#include <enginelayout/Rasterizer.inl>
#include "cameras.hpp"

namespace Yelo
{
	namespace Render
	{
		struct s_render_window
		{
			short local_player_index;
			UNKNOWN_TYPE(bool);
			unsigned char : 8;
			s_render_camera render_camera, rasterizer_camera;
		}; static_assert( sizeof(s_render_window) == 0xAC );

		static constexpr s_render_window* RenderWindow() { return reinterpret_cast<Yelo::Render::s_render_window *>(K_RENDER_WINDOW); }

		struct s_render_fog
		{
			unsigned short flags; // same flags as in the tag definition
			unsigned short : 16;
			real_rgb_color atmospheric_color;
			real atmospheric_maximum_density,
				atmospheric_minimum_distance,
				atmospheric_maximum_distance;
			UNKNOWN_TYPE(short);
			unsigned short : 16;
			real_plane3d plane; // copied from the bsp's fog planes
			real_rgb_color color; // copied from tag definition
			real max_density; // copied from tag definition
			real planar_maximum_distance;
			real opaque_depth; // copied from tag definition
			const void* screen_layers_definition; // pointer to the tag definition data
			UNKNOWN_TYPE(real);
		}; static_assert( sizeof(s_render_fog) == 0x50 );

		struct s_render_globals
		{
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(long);
			short local_player_index;
			UNKNOWN_TYPE(short);
			UNKNOWN_TYPE(long);
			UNKNOWN_TYPE(real);
			s_render_camera camera;
			s_render_frustum frustum;
			s_render_fog fog;
			long leaf_index;
			long cluster_index;
			unsigned char : 8; // probably an unused bool
			bool visible_sky_model;
			short visible_sky_index;

			struct {
				unsigned long cluster_pvs[BIT_VECTOR_SIZE_IN_DWORDS(512)];
				byte clusters[0x1A0][Enums::k_maximum_rendered_clusters];
				short count;
				unsigned short : 16;
			}rendered_clusters;

			struct {
				uint visibility_bitvector[0x20000];
				long count;
				uint triangles[Enums::k_maximum_rendered_triangles];
			}rendered_triangles;
		}; static_assert( sizeof(s_render_globals) == 0x9D298 );
		s_render_globals* RenderGlobals() {return reinterpret_cast<Yelo::Render::s_render_globals *>(K_RENDER_GLOBALS); }

		struct s_structure_render_globals
		{
			bool render_bsp;
			unsigned char : 8; unsigned short : 16;
			long dynamic_triangle_buffer_index;
			bool unk;
			unsigned char : 8; unsigned short : 16;
			float x, y, z;
		}; static_assert( sizeof(s_structure_render_globals) == 0x18 );
		s_structure_render_globals* StructureRenderGlobals() { reinterpret_cast<Yelo::Render::s_structure_render_globals *>(K_STRUCTURE_RENDER_GLOBALS);}
	};

	namespace blam
	{
		void __cdecl render_window(const unsigned short local_player_index
			, void* render_camera
			, void* render_frustum
			, void* rasterizer_camera
			, void* rasterizer_frustum
			, void* rasterizer_target
			, const bool is_mirror);
	};
};
