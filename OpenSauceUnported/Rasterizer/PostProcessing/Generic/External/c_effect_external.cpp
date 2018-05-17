#include "Common/Precompile.hpp"
#include "Rasterizer/PostProcessing/Generic/External/c_effect_external.hpp"
#include "Rasterizer/PostProcessing/Generic/c_effect_generic.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace Generic { namespace External
	{
		/////////////////////////////////////////////////
		// member accessors
		void c_effect_external::SetEffectID(const char* id)
		{
			strncpy_s(m_members_external.effect_id, sizeof(m_members_external.effect_id), id, sizeof(m_members_external.effect_id));
		}
		const char* c_effect_external::GetEffectID()
		{
			return m_members_external.effect_id;
		}
	};};};};
};
