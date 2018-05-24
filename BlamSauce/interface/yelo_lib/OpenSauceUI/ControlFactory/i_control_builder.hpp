#pragma once

#include "Interface/OpenSauceUI/Control/i_control.hpp"
#include "Interface/OpenSauceUI/ControlFactory/c_control_factory.hpp"
#include "Interface/OpenSauceUI/Definitions/c_control_definition.hpp"

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace ControlFactory
	{
		class c_control_factory;

		/// <summary>	A control builder interface. </summary>
		class i_control_builder
			abstract
		{
		public:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Builds a control from the specified definition. </summary>
			///
			/// <param name="control_registry">  	[in] The control registry. </param>
			/// <param name="control_definition">	[in] The control definition. </param>
			/// <param name="parent">			 	[in] The parent control. </param>
			///
			/// <returns>	A shared pointer to the new control. </returns>
			virtual Control::control_ptr_t Build(c_control_factory& control_registry
				, Definitions::c_control_definition& control_definition
				, Control::i_control& parent) const = 0;
		};

		/// <summary>	Defines an alias representing a control builder shared pointer. </summary>
		typedef std::shared_ptr<i_control_builder> control_builder_ptr_t;
	};};};
};
