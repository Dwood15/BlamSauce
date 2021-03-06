#pragma once

#include <precompile.h>
#include "../main/console.hpp"

namespace Yelo::Console {

	s_terminal_globals *TerminalGlobals() {
		{
			auto terminal_globals = reinterpret_cast<s_terminal_globals **>(0x64DE2C);
			(void) ((!!(reinterpret_cast<void *>(0) != terminal_globals && reinterpret_cast<void *>(0x1337BEEF) != terminal_globals)) ||
					  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != terminal_globals && CAST_PTR(void*,PTR_NULL) != terminal_globals", L"_file_name_", (unsigned) (8)), 0));
		}
		auto terminal_globals = (*reinterpret_cast<s_terminal_globals **>(0x64DE2C));
		return terminal_globals;
	};

	s_console_globals *Globals() { reinterpret_cast<s_console_globals *>(0x651F50); }

	__declspec(naked) void __cdecl Update(unsigned long access_flags) {
		// our hook is placed where the update function calls console_process_command, so we have to call it
		API_FUNC_NAKED_START()
		push edi // the command string buffer is given to us in edi
		push access_flags
		call   blam::console_process_command
		add
		esp, 4 * 2
		// do any custom stuff after here
		API_FUNC_NAKED_END(0)
	}

	void Initialize() {
		Memory::WriteRelativeCall(&Yelo::Console::Update, (reinterpret_cast<void *>(CONSOLE_UPDATE_HOOK)));
	}

	void Dispose() {
	}

};
