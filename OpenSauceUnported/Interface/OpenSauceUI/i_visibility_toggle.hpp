#pragma once
namespace Yelo
{
	namespace Interface { namespace OpenSauceUI
	{
		/// <summary>	Interface for toggling a ui objects visibility. </summary>
		class i_visibility_toggle
			abstract
		{
		public:
			/// <summary>	Shows the object. </summary>
			virtual void Show() = 0;

			/// <summary>	Hides the object. </summary>
			virtual void Hide() = 0;
		};
	};};
};
