#pragma once

namespace Yelo
{
	namespace Rasterizer { namespace PostProcessing { namespace Bloom
	{
		class c_settings_container
			: public Configuration::c_configuration_container
		{
		public:
			Configuration::c_configuration_value<bool> m_enabled;

			c_settings_container();

		protected:
			const std::vector<Configuration::i_configuration_value* const> GetMembers() final override;
		};

		class c_settings_bloom
			: public Settings::c_settings_singleton<c_settings_container, c_settings_bloom>
		{
		public:
			void PostLoad() final override;
			void PreSave() final override;
		};
	};};};
};
