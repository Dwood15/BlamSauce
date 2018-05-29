#pragma once

namespace Yelo::Rasterizer::Textures {
	/// <summary>	Loader for packed textures. </summary>
	class c_packed_texture_loader final {
		c_packed_file &m_packed_file;

	public:
		/// <summary>	Default constructor. </summary>
		c_packed_texture_loader(c_packed_file &packed_file) : m_packed_file(packed_file) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Loads a texture. </summary>
		///
		/// <param name="texture_id">	 	Identifier for the texture. </param>
		/// <param name="target_texture">	[out] The target texture pointer. </param>
		/// <param name="image_info">	 	[out] If non-null, information describing the image. </param>
		///
		/// <returns>	true if it succeeds, false if it fails. </returns>
		bool LoadTexture(const std::string &texture_id, IDirect3DTexture9 **target_texture, D3DXIMAGE_INFO *image_info = nullptr) {

			uint data_size = 0;
			auto *texture_file = m_packed_file.GetDataPointer(texture_id.c_str(), &data_size);

			if (!texture_file) {
				target_texture = nullptr;
				return false;
			}

			IDirect3DTexture9 *created_texture = nullptr;
			return S_OK ==
					 D3DXCreateTextureFromFileInMemoryEx(DX9::Direct3DDevice(), texture_file, data_size, 0, 0, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, image_info,
																	 NULL, target_texture);
		}
	};
};
