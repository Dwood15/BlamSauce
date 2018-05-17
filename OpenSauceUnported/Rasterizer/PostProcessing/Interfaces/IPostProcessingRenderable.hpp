#pragma once

#include "Rasterizer/PostProcessing/PostProcessing.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing 
	{
		interface IPostProcessingRenderable
			abstract
		{
			virtual bool Render(Enums::postprocess_render_stage render_stage) { return false; }
		};
	};};
};
