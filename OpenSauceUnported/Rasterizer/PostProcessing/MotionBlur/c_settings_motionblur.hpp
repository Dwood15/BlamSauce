#pragma once

//#include <YeloLib/configuration/c_configuration_container.hpp>
//#include <YeloLib/configuration/c_configuration_value.hpp>
//#include <YeloLib/open_sauce/settings/c_settings_singleton.hpp>

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace MotionBlur
	{
		class c_settings_container
			: public Configuration::c_configuration_container
		{
		public:
			Configuration::c_configuration_value<bool> m_enabled;
			Configuration::c_configuration_value<real> m_blur_amount;

			c_settings_container();

		protected:
			const std::vector<i_configuration_value* const> GetMembers() final override;
		};

		class c_settings_motionblur
			: public Settings::c_settings_singleton<c_settings_container, c_settings_motionblur>
		{
		public:
			void PostLoad() final override;
			void PreSave() final override;
		};
	};};};
};
