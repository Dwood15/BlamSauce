/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <d3d9.h>
#include "../../tags/bitmap_grp.h"

struct IDirect3DVertexDeclaration9;

namespace Yelo {
	namespace Enums {
		enum {
			k_rasterizer_maximum_texture_stages = 4,
		};

		//////////////////////////////////////////////////////////////////////////
		// rasterizer_dx9_shaders_vdecl9

		enum {
			_vsdecl_environment, // _rasterizer_vertex_type_environment_uncompressed
			_vsdecl_environment_c, // _rasterizer_vertex_type_environment_compressed
			_vsdecl_environment_lightmap, // _rasterizer_vertex_type_environment_lightmap_uncompressed
			_vsdecl_environment_lightmap_c, // _rasterizer_vertex_type_environment_lightmap_compressed
			_vsdecl_model,
			_vsdecl_model_c,
			_vsdecl_unlit, // _rasterizer_vertex_type_dynamic_unlit (yes, this is #6)
			_vsdecl_dynamic_unlit,
			_vsdecl_screen, // _rasterizer_vertex_type_dynamic_screen
			_vsdecl_debug, // _rasterizer_vertex_type_debug
			_vsdecl_decal, // _rasterizer_vertex_type_decal
			_vsdecl_detail_object, // _rasterizer_vertex_type_detail_object
			_vsdecl_environment_ff, // _rasterizer_vertex_type_environment_uncompressed_ff
			_vsdecl_environment_lightmap_ff, // _rasterizer_vertex_type_environment_lightmap_uncompressed_ff
			_vsdecl_model_uncompressed_ff,
			_vsdecl_model_processed,
			_vsdecl_unlit_zsprite,
			_vsdecl_screen_transformed_lit,
			_vsdecl_screen_transformed_lit_specular,
			_vsdecl_environment_single_stream_ff,
			//NUM_VERTEX_SHADER_DECLARATIONS
		};
	};

	namespace blam {
		bool __cdecl rasterizer_set_texture_bitmap_data(short stage, TagGroups::s_bitmap_data *bitmap);
	};

	namespace DX9 {
		struct s_vertex_shader_declaration {
			IDirect3DVertexDeclaration9 *decl;
			long_enum format; // D3DFVF
			long_enum processing_method; // D3DUSAGE
		}; static_assert(sizeof(s_vertex_shader_declaration) == 0xC);
	};
};

namespace Yelo::Render {
	// (Korn): yeah, I fucked up, this should have stayed in the Rasterizer namespace!
	struct s_render_target {
		uint32    width, height;
		D3DFORMAT format;

		IDirect3DSurface9 *surface;
		IDirect3DTexture9 *texture;

		// returns whether the texture and surface are valid
		bool IsEnabled() const { return surface && texture; }

		// Create the render target texture and surface. If either of those fails [enabled] will be false
		HRESULT CreateTarget(IDirect3DDevice9 *device, uint32 rt_width, uint32 rt_height, D3DFORMAT rt_format) {
			width      = rt_width;
			height     = rt_height;
			format     = rt_format;
			HRESULT hr = device->CreateTexture(
				width,
				height,
				1,
				D3DUSAGE_RENDERTARGET,
				format,
				D3DPOOL_DEFAULT,
				&texture,
				nullptr);

			if (SUCCEEDED(hr))
				hr = texture->GetSurfaceLevel(0, &surface);

			if (FAILED(hr))
				this->ReleaseTarget();
			return hr;
		}

		// Release the texture and surface
		void ReleaseTarget() {
			Yelo::safe_release(surface);
			Yelo::safe_release(texture);
		}

		// Set the device target to [surface] then clear it
		void ClearTarget(IDirect3DDevice9 *device, D3DCOLOR color = 0x00000000, DWORD flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL) {
			if (!IsEnabled()) return;

			device->SetRenderTarget(0, surface);
			device->Clear(0L, nullptr, flags, color, 1.0f, 0L);
		}
	};

	s_render_target *GlobalRenderTargets();
};
