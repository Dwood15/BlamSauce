#pragma once

#include "Interface/OpenSauceUI/Definitions/c_control_property_definition.hpp"
#include "Interface/OpenSauceUI/Definitions/c_page_definition.hpp"

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Definitions
	{
		class c_page_definition;

		/// <summary>	A control definition. </summary>
		class c_control_definition
			: public Configuration::c_configuration_container
		{
		public:

			Configuration::c_configuration_value<uint> m_id;
			Configuration::c_configuration_value<std::string> m_type;
			Configuration::c_configuration_container_list<c_control_property_definition> m_properties;
			Configuration::c_configuration_container_list<c_control_definition> m_controls;
			Configuration::c_configuration_container_list<c_page_definition> m_pages;

			/// <summary>	Default constructor. </summary>
			c_control_definition();

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets the resource id for the control. </summary>
			///
			/// <returns>	The controls resource id. </returns>
			const uint GetID();

		protected:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets a vector containing pointers to the containers members. </summary>
			///
			/// <returns>	A vector containing pointers to the containers members. </returns>
			const std::vector<Configuration::i_configuration_value* const> GetMembers() final override;
		};

		/// <summary>	Defines an alias representing a list of control definitions. </summary>
		typedef std::vector<Definitions::c_control_definition> control_definition_list_t;
	};};};
};
