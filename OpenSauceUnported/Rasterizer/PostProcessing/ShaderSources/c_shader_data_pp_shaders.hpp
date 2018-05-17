#pragma once

#include "Rasterizer/PostProcessing/ShaderSources/c_shader_data_base.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing
	{
		class c_shader_data_pp_shaders : public c_shader_data_base
		{
			char m_shader_id[MAX_PATH];

			void ClearMembers()
			{
				m_shader_id[0] = '\0';
			}

		public:
			void SetShaderID(const char* id) { strcpy_s(m_shader_id, MAX_PATH, id); }

			void Ctor()
			{
				ClearMembers();
			}
			void Dtor()
			{
				ClearMembers();
			}

			const char* DataSourceID();
			const void* GetData(uint32& data_size);
			void Dispose() {}
			const bool IsBinary() { return true; }
			const char* GetIncludePath() { return nullptr; }
			const D3DXMACRO* GetMacros() { return nullptr; }
		};
	};};
};
