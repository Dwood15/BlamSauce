#pragma once
#include "Interface/OpenSauceUI/Definitions/c_control_definition.hpp"

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Definitions
	{
		class c_control_definition;

		/// <summary>	A page definition. </summary>
		class c_page_definition
			: public Configuration::c_configuration_container
		{
		public:
			Configuration::c_configuration_container_list<c_control_definition> m_controls;

			/// <summary>	Default constructor. </summary>
			c_page_definition();

		protected:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets a vector containing pointers to the containers members. </summary>
			///
			/// <returns>	A vector containing pointers to the containers members. </returns>
			const std::vector<Configuration::i_configuration_value* const> GetMembers() final override;
		};
	};};};
};
