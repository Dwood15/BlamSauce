#pragma once

#include "Rasterizer/PostProcessing/PostProcessing.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing
	{
		/*!
		 * \brief
		 * Handles loading shader includes.
		 * 
		 * Used to control where shader includes are loaded from. This is
		 * necessary when loading an ASCII shader that is stored in memory
		 * since it has no path to use as a start point.
		 */
		class c_shader_include_manager : public ID3DXInclude
		{
			const char*		m_include_path;
		public:
			c_shader_include_manager(const char* path) : m_include_path(path) {}
		private:
			HRESULT API_FUNC Open(D3DXINCLUDE_TYPE IncludeType, 
				LPCSTR pFileName, 
				LPCVOID pParentData, 
				LPCVOID* ppData, 
				UINT* pBytes);
			HRESULT API_FUNC Close(LPCVOID pData);
		};
	};};
};
