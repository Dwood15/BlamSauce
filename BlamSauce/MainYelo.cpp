
#include <psapi.h>
#pragma comment (lib, "psapi.lib")

#include "Memory/MemoryInterface.hpp"
#include "Common/systems.hpp"

	#include "Game/EngineFunctions.hpp"
	#include "Rasterizer/DX9/DxWrapper.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum version_result_code : long_enum
		{
			_version_result_code_invalid,	// An unsupported program is trying to run us. Go to hell.
			_version_result_code_valid,		// A supported version of Halo is trying to run it
			_version_result_code_dx9_app,	// A known DX9 application, ie sapien, is trying to run this

			k_number_of_version_result_codes
		};
	};

	namespace Main
	{
		static struct {
			bool enabled;
			unsigned char : 8; unsigned short : 16;
			HMODULE module_handle;
		}_main_globals = {
			false,
			nullptr
		};

		bool IsYeloEnabled()
		{
			return _main_globals.enabled;
		}

		HMODULE& YeloModuleHandle()
		{
			return _main_globals.module_handle;
		}

		static Enums::version_result_code GetVersionResultCode()
		{
			Enums::version_result_code result_code = Enums::_version_result_code_invalid;

			char dir[MAX_PATH];
			GetCurrentDirectory(NUMBEROF(dir), dir);

			char name[64];
			GetModuleBaseName(GetCurrentProcess(), GetModuleHandle(nullptr), name, NUMBEROF(name));
			_strlwr_s(name);

			// Ok, the warning message will get annoying after a while for sapien (and tool) users
			if ( strstr(name,"sapien") != nullptr || strstr(name,"hobo") != nullptr || strstr(name,"tool") != nullptr )
				return Enums::_version_result_code_dx9_app;

			// Enable OS if the exe name is haloce/OS_ded
			_main_globals.enabled = (strcmp(name, PLATFORM_VALUE("haloce.exe","os_haloceded.exe")) == 0);

			return Enums::_version_result_code_valid;
		}
	};
};

bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved) {
	static bool g_initialized = false;

	if( dwReason == DLL_PROCESS_ATTACH ) {
		if(Yelo::Main::GetVersionResultCode() == Yelo::Enums::_version_result_code_invalid )
			return false;
	}

	if(dwReason == DLL_PROCESS_ATTACH && !g_initialized)
	{
		Yelo::Main::YeloModuleHandle() = hModule;

		if(!LoadDXProxy(&hModule))
		{
			char error[128];
			sprintf_s(error,
				"Open Sauce failed to load DirectXInput."
				"\n\n"
				"Nothing left to do but crash now, good bye!");
			Yelo::PrepareToDropError(error);
			return false;
		}

		if(Yelo::Main::IsYeloEnabled()) {
			Yelo::Main::InsertHooks();
		}
		g_initialized = true;
	}
	else if(dwReason == DLL_PROCESS_DETACH && g_initialized)
	{
		// component disposal occurs in GameSystems.cpp
		FreeDXProxy(hModule);
		Yelo::Main::YeloModuleHandle() = nullptr;
		g_initialized = false;
	}

	return true;
}
