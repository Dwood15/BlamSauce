#pragma once

//#include <YeloLib/Halo1/shaders/shader_postprocess_definitions.hpp>

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace MotionBlur
	{
		struct s_shader_motionblur_definition : TagGroups::s_shader_postprocess_definition
		{
			TAG_FIELD(TagGroups::t_shader_variable_real,	blur_amount_var);
			TAG_FIELD(TagGroups::t_shader_variable_real,	vignette_amount_var);
		};
	}; }; };
};
