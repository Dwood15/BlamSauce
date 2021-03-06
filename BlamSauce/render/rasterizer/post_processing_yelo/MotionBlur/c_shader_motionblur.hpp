#pragma once

#include "Rasterizer/PostProcessing/c_shader_postprocess.hpp"
#include "Rasterizer/PostProcessing/MotionBlur/s_shader_motionblur_definition.hpp"

#ifdef EXTERNAL_SUBSYSTEM_SHADERS
	#include "Rasterizer/PostProcessing/ShaderSources/c_shader_data_external.hpp"
#else
	#include "Rasterizer/PostProcessing/ShaderSources/c_shader_data_pp_shaders.hpp"
#endif

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace MotionBlur
	{
		class c_shader_motionblur : public c_shader_postprocess
		{
			/////////////////////////////////////////////////
			// members
		protected:
			struct
			{
				s_shader_motionblur_definition* definition;

#ifdef EXTERNAL_SUBSYSTEM_SHADERS
				c_shader_data_external* shader_data;
#else
				c_shader_data_pp_shaders* shader_data;
#endif
			}m_members_motionblur;

			/////////////////////////////////////////////////
			// member accessors
		public:
			void SetShaderDefinition(TagGroups::s_shader_postprocess_definition* definition);

			/////////////////////////////////////////////////
			// initializers
		public:
			void Ctor()
			{
				c_shader_postprocess::Ctor();

				m_members_motionblur.definition = NULL;
				m_members_motionblur.shader_data = NULL;
			}

			void Dtor()
			{
				c_shader_postprocess::Dtor();

				m_members_motionblur.definition = NULL;

				m_members_motionblur.shader_data->Dtor();
				delete m_members_motionblur.shader_data;
				m_members_motionblur.shader_data = NULL;
			}

			/////////////////////////////////////////////////
			// shader setup
		public:
			void SetupShader();
		protected:
			void GetHandles();
			void ClearHandles();
			bool ValidateImpl();
		};
	}; }; };
};
