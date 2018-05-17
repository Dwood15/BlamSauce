#pragma once


namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace Fade
	{
		struct s_shader_fade_definition : TagGroups::s_shader_postprocess_definition
		{
			TAG_FIELD(TagGroups::t_shader_variable_real,		fade_amount_handle);
		};
	};};};
};
