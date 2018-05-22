#ifndef WIN32
#define WIN32
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _X86_
#define _X86_
#endif

#include <algorithm>
#include <array>
#include <assert.h>
#include <crtdbg.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <d3dx9math.h>
#include <functional>

#include <handleapi.h>

#include <minwindef.h>
#include <minwinbase.h>

#include <rpc.h>
#include <rpc.h>

#include <sal.h>
#include <string>
#include <stdio.h>

#include <time.h>
#include <type_traits>
#include <vector>

#include <winnt.h>

//Our defined includes below:
#include <versions.h>
#include <stdexcept>

#include "../../BlamSauce/cseries/MacrosCpp.h"
#include "../../BlamSauce/cseries/base.h"
#include "../../BlamSauce/math/real_math.h"
#include "../../BlamSauce/memory/datum_index.h"
#include "../../BlamSauce/tags/group/base.h"
#include "../../BlamSauce/tags/group/markup.h"

#pragma once
