#pragma once

#include "Interface/OpenSauceUI/Control/i_control.hpp"
#include "Interface/OpenSauceUI/Screen/i_screen.hpp"

namespace Yelo
{
	namespace Interface { namespace OpenSauceUI { namespace Screen
	{
		/// <summary>	A screen implementation. </summary>
		class c_screen final
			: public i_screen
		{
		private:
			Control::control_ptr_t m_root_control;
			std::map<uint, Control::control_ptr_t> m_control_resource_list;

		public:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Constructor. </summary>
			///
			/// <param name="root_control">	The screen's root control. </param>
			c_screen(Control::control_ptr_t root_control);

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets the root control of the screen. </summary>
			///
			/// <returns>	The root control of the screen. </returns>
			Control::control_ptr_t GetRootControl() const override;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets a control based on it's resource id. </summary>
			///
			/// <param name="resource_id">	Identifier for the control resource. </param>
			///
			/// <returns>	The found control or nullptr if not found. </returns>
			Control::control_ptr_t GetControl(const uint resource_id) override;

			/// <summary>	Shows the screen. </summary>
			void Show() override;

			/// <summary>	Hides the screen. </summary>
			void Hide() override;

		private:
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Adds a control to the resource list if it has an id defined. </summary>
			///
			/// <param name="control">	The control to add. </param>
			void AddControlResource(Control::control_ptr_t control);
		};
	};};};
};
