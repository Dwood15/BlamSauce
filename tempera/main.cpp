/**
 *	Project: Tempera
 *	Copyright � 2018 Dwood15 (Dason Woodhouse) (me)
 *	In no particular order, I must thank:
 * 
 *  - Zbe - Giving me the second wind, and general reversing advice
 *
 * 	- Halogen002 - Making Chimera, letting me have a channel in 
 *  their discord
 *  
 *  - SilentK and Abyll - For trying to make forge on pc in 2008, and
 *  providing the basis for this version of forge mode. The old code
 *  for this project is long gone.
 *   
 *  - Kornman, for writing Open Sauce, another codebase this project
 *  is based off of.
 *
 *********************************************************************
 *
 * File main.cpp
 *
 * This file is part of the primary portions of the Tempera codebase.
 *
 * Tempera is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tempera is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details. *
 *
 * - Tempera contains no Microsoft code, is not created by nor is it 
 * affiliated with Microsoft, Bungie, Gearbox, 343 Industries, or any
 * other entity who has been associated with or granted license to the 
 * Halo Intellectual Property (IP) 
 *
 * - Tempera, as a mod for games based on the blam! engine on personal
 * computing platforms, is **not** under jurisdiction of Microsft Content
 * Usage Guidelines, if it is covered under any license, it would be
 * associated with the licences for Halo Custom Edition, Halo PC, Stubbz
 * the Zombie, or possibly the Halo for Macintosh games.
 *
 * - Tempera is protected under the GNU General Public License, or GPLv3.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tempera. If not, see <http://www.gnu.org/licenses/>.
 **/

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//#include <precompile.h>
#include <dbghelp.h>


static bool loaded = false;

static void *orig_DirectInput8Create;

//Used so we can proxy direct input.
__declspec(naked) void WINAPI Tempera_DirectInput8Create() {
	__asm { jmp orig_DirectInput8Create };
}

static inline void *init(HMODULE *reason) {
	//h = AddVectoredExceptionHandler(CALL_FIRST, CEInternalExceptionHandler);

	char path[MAX_PATH];
	GetSystemDirectory(path, sizeof(path));
	strcat(path, "\\dinput8.dll");

	*reason = LoadLibraryA(path);

	if (!*reason) return false;

	orig_DirectInput8Create = GetProcAddress(*reason, "DirectInput8Create");

	//InitAddLog(*reason);
	// some debug outputz
	//if (::AllocConsole() != 0) {
	//	freopen_s(&debug_out, "CONOUT$", "w", stdout);
	//}

	//printf("init_for_new_map_overwrite addr: 0x%x\n", 0xBEEF);//init_for_new_map_overwrite);

	//DWORD old;
	VirtualProtect((void *) 0x400000, 0x215000, PAGE_EXECUTE_READWRITE, &old);
	//spcore::memory::get_mem_and_patch();

	return orig_DirectInput8Create;
}

static inline void detach(HMODULE reason) {
	ExitAddLog();
	//RemoveVectoredExceptionHandler(h);
	FreeLibrary(reason); //Frees dinput8
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH && !loaded) {
		if (!init(&hinstDLL)) {
			//Print(true, "Failed to Initialize properly, I guess. Exiting");
			return false;
		}
		//Rip forge mode, lol. Gonna have to figure something else out now.
		DisableThreadLibraryCalls(hinstDLL);
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE) forgeMain, 0, 0, 0);
		//Print(true, "Created LPTHREAD\n");
		loaded = true;

	} else if (fdwReason == DLL_PROCESS_DETACH && loaded) {
		detach(hinstDLL);
		loaded = false;
	}
	return true;
}
