#include <precompile.h>

#pragma once

namespace Yelo {
	namespace GameUI {
		struct s_hud_scripted_globals {
			bool show_hud;
			bool show_hud_help_text;
			PAD16;
		};

		s_hud_scripted_globals *HudScriptedGlobals();
	};

	namespace blam {
		wcstring __cdecl hud_get_item_string(int16 reference_index);
	};
};
