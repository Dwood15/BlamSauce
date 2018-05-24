#pragma once


namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Definitions
	{
		/// <summary>	A screen definition. </summary>
		class c_screen_definition
			: public Configuration::c_configuration_container
		{
		public:
			Configuration::c_configuration_value<std::string> m_screen_name;
			c_control_definition m_control_definition;

			/// <summary>	Default constructor. </summary>
			c_screen_definition();

		protected:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets a vector containing pointers to the containers members. </summary>
			///
			/// <returns>	A vector containing pointers to the containers members. </returns>
			const std::vector<Configuration::i_configuration_value* const> GetMembers() final override;
		};
	};};};
};
