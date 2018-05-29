#pragma once

#include <precompile.h>

namespace Yelo::DX9 {
	/////////////////////////////////////////////////////////////////////
	// Used to prevent reading and writing to a single render target by
	// flipping between two on each pass.
	/////////////////////////////////////////////////////////////////////
	struct s_render_target_chain {
		bool m_first_render;
		unsigned char : 8;
		unsigned short          : 16;
		// 2 render targets
		Render::s_render_target m_targets[2];
		// pointers to the current setup of targets
		struct {
			// current holds the target currently being rendered to
			Render::s_render_target *current;
			// next hold the next (also last) target rendered to
			Render::s_render_target *next;
		} m_target_setup;

		// returns true if both of the extra render targets are ok to use
		bool IsAvailable() const {
			return m_targets[0].IsEnabled() &&
					 m_targets[1].IsEnabled();
		}

		// create the render targets
		virtual bool AllocateResources(IDirect3DDevice9 *device, uint width, uint height, D3DFORMAT format) {
			HRESULT  success = 0;
			for (int i       = 0; i < 2; i++) {
				success |= m_targets[i].CreateTarget(device, width, height, format);
			}

			ResetTargets();

			return SUCCEEDED(success);
		}

		// resets the target setup
		void ResetTargets() {
			m_target_setup.current = &m_targets[0];
			m_target_setup.next    = &m_targets[1];
		}

		// release the render targets
		void ReleaseResources() {
			for (int i = 0; i < 2; i++)
				m_targets[i].ReleaseTarget();
		}

		// swaps the pointers for current and next
		void Flip() {
			std::swap(m_target_setup.current, m_target_setup.next);
		}

		IDirect3DSurface9 *GetCurrentSurface() const { return m_target_setup.current->surface; }

		IDirect3DTexture9 *GetCurrentTexture() const { return m_target_setup.current->texture; }

		IDirect3DSurface9 *GetNextSurface() const { return m_target_setup.next->surface; }

		IDirect3DTexture9 *GetNextTexture() const { return m_target_setup.next->texture; }
	};

	struct s_render_target_chain_scene : public s_render_target_chain {
		struct {
			// scene holds the scene as it was before an effect is started
			Render::s_render_target *scene;
		} m_target_setup_scene;

		// create the render targets
		bool AllocateResources(IDirect3DDevice9 *device, uint width, uint height) {
			bool success = s_render_target_chain::AllocateResources(
				device,
				width, height,
				Render::GlobalRenderTargets()[Enums::_rasterizer_target_render_primary].format);

			return success;
		}

		// resets the target setup to the default of halos primary buffer as the scene texture
		void ResetTargets() {
			m_target_setup_scene.scene = &Render::GlobalRenderTargets()[Enums::_rasterizer_target_render_primary];

			s_render_target_chain::ResetTargets();
		}

		// swaps the pointers for scene and next
		void SetSceneToLast() {
			std::swap(m_target_setup.next, m_target_setup_scene.scene);
		}

		IDirect3DSurface9 *GetSceneSurface() const { return m_target_setup_scene.scene->surface; }

		IDirect3DTexture9 *GetSceneTexture() const { return m_target_setup_scene.scene->texture; }
	};
};
