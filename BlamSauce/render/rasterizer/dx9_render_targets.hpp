/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <d3d9.h>

namespace Yelo {
	namespace Render {
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
};
