#pragma once

#ifndef WIN32
#define WIN32
#endif

#define NOMINMAX

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _X86_
#define _X86_
#endif




#define _USE_MATH_DEFINES // hurrrrrrrrrr, i like math!

#include <algorithm>
#include <array>
#include <assert.h>
#include <crtdbg.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <Dinput.h>

#include <d3dx9.h>
#include <d3dx9math.h>

#define DIRECTINPUT_VERSION 0x0800

//////////////////////////////////////////////////////////////////////////
// STD C includes
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <io.h>
#include <errno.h>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// STL includes
#include <array>
#include <iterator>
#include <memory> // std::unique_ptr
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>
#include <thread>
#include <random>
//////////////////////////////////////////////////////////////////////////

#include <functional>

#include <handleapi.h>
#include <math.h>

#include <minwindef.h>
#include <minwinbase.h>

#include <rpc.h>

#include <sal.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <stdio.h>

#include <time.h>
#include <type_traits>
#include <vector>

#include <winnt.h>
#include <WinSock2.h>

//////////////////////////////////////////////////////////////////////////
// GameSpy includes & definitions

// Comment out this if you don't have access to the Open SDK
// You'll also need to remove the code file references from the project
// TODO: use msbuild to define this since we can now detect the presence of required libraries?
#define YELO_USE_GAMESPY_OPEN

#if defined(YELO_USE_GAMESPY_OPEN)

/*
	GameSpy SDK bug fix:
	There is a bug in GHTTP that causes HTTP redirects to fail if both
	the 'Content-Location' and 'Location' headers are returned by the server.

	Use the following on line 1695 in ghttpProcess.c to fix this:

		// Find the new location.
			/////////////////////////
			location = strstr(headers, "\r\nLocation:");// YELO: UPDATE THIS LINE
			if(location)
			{
				 char * end;

				 // Find the start of the URL.
				 /////////////////////////////
				 location += 11;							// YELO: UPDATE THIS LINE

*/
static_assert(false); // comment this out once the fix is applied

// Just to make sure we're always using ASCII
#undef GSI_UNICODE

//#include <GameSpyOpen/ghttp/ghttp.h>

#define YELO_VERSION_CHECK_ENABLE

#endif
//////////////////////////////////////////////////////////////////////////










//Our defined includes below:
#include <versions.h>
#include <stdexcept>

#include "../../BlamSauce/cseries/MacrosCpp.h"
#include "../../BlamSauce/cseries/base.h"
#include "../../BlamSauce/math/real_math.h"
#include "../../BlamSauce/memory/datum_index.h"
#include "../../BlamSauce/tags/group/base.h"
#include "../../BlamSauce/tags/group/markup.h"


