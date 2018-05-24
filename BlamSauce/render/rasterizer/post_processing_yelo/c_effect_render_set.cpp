#include "Common/Precompile.hpp"
#include "Rasterizer/PostProcessing/c_effect_render_set.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing
	{
		void c_effect_render_set::SetCount(uint effect_count)
		{
			if(effect_count == 0)
				return;

			// +1 because a null pointer is used to indicate the end of the list
			m_effect_list = new c_effect_instance*[effect_count + 1];

			ZeroMemory(m_effect_list, sizeof(c_effect_instance*) * (effect_count + 1));
		}

		void c_effect_render_set::SetEffectInstance(uint index, c_effect_instance* effect)
		{
			m_effect_list[index] = effect;
		}

		bool c_effect_render_set::RenderSet(IDirect3DDevice9* render_device)
		{
			c_effect_instance** current = m_effect_list;

			HRESULT success = S_OK;
			while(current && (*current))
			{
				success &= (*current)->Render(render_device);
				current++;
			}

			return SUCCEEDED(success);
		}
	};};
};
