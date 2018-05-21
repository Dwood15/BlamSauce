#include <precompile.h>
#include "../../../../../../BlamSauce/interface/input/player_control.h"

#pragma once
//	FUNC_PTR(INPUT_UPDATE_HOOK,						K_INPUT_UPDATE_HOOK, FUNC_PTR_NULL);
static auto const INPUT_UPDATE_HOOK = (uintptr_t)0x493856;
static auto * const InputStateFlags = CAST_PTR(byte*, 0x6AD572);
static auto * const ControlState = CAST_PTR(Yelo::Input::ControlStates*, 0x64C550);
static auto * const MousePositionState = CAST_PTR(Yelo::Input::PositionState*, 0x6B4008);
static auto * const Settings = CAST_PTR(Yelo::Input::ControlSettings*, 0x6AD802);
