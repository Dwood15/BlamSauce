#pragma once

//#include <YeloLib/Halo1/shaders/shader_postprocess_definitions.hpp>

#include "Rasterizer/PostProcessing/Generic/c_effect_generic.hpp"
#include "Rasterizer/PostProcessing/Generic/Internal/c_shader_internal.hpp"
#include "Rasterizer/PostProcessing/Generic/c_parameter_instance.hpp"

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace Generic { namespace Internal
	{
		class c_effect_internal : public c_effect_generic
		{
			/////////////////////////////////////////////////
			// members
		protected:
			struct
			{
				TagGroups::s_effect_postprocess_collection_effect* definition;
			}m_members_internal;

			/////////////////////////////////////////////////
			// member accessors
		public:
			void SetEffectReferenceDefinition(TagGroups::s_effect_postprocess_collection_effect* definition);
			const char* GetName();
			short GetScriptedVariableIndex(const char* name);

			/////////////////////////////////////////////////
			// initializers
		public:
			void Ctor()
			{
				c_effect_generic::Ctor();

				m_members_internal.definition = NULL;
			}

			void Dtor()
			{
				c_effect_generic::Dtor();

				m_members_internal.definition = NULL;
			}

			/////////////////////////////////////////////////
			// effect setup
		public:
			void SetupEffect();
		private:
			void SetupScriptedVariables();

			/////////////////////////////////////////////////
			// scripting
		public:
			void SetScriptedVariable(short index, real change_time, bool value);
			void SetScriptedVariable(short index, real change_time, long value);
			void SetScriptedVariable(short index, real change_time, real value0, real value1, real value2, real value3);
		};
	};};};};
};
