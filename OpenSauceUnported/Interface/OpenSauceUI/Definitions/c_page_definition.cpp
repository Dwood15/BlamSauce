namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Definitions
	{
#pragma region c_page_definition
		c_page_definition::c_page_definition()
			: Configuration::c_configuration_container("Page")
			, m_controls("Control", [](){ return c_control_definition(); })
		{ }

		const std::vector<Configuration::i_configuration_value* const> c_page_definition::GetMembers()
		{
			return std::vector<Configuration::i_configuration_value* const> { &m_controls };
		}
#pragma endregion
	};};};
};
