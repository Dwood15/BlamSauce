#pragma once

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing
	{
		interface IPostProcessingUpdatable
			abstract
		{
			virtual void Update(real delta_time) {}
		};
	};};
};
