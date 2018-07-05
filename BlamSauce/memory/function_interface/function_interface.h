#include <precompile.h>
#include "../memory_interface_base.hpp"

#pragma once

namespace Enums {
	enum CallingConventions {
		m_cdecl, //Everything goes onto the stack - stack is cleaned up by the caller.
		m_stdcall, //Everything goes onto the stack, but stack is cleaned up by callee.
		m_fastcall, //Example: __fastcall void Foo(int iGoInto_ECX, int iGoInto_EDX, int iGetPushed_Last, int iGetPushed_2nd, int iGetPushed_First);
		m_thiscall
	};
}

namespace Tempera::FunctionInterface {
	/**********
	 * Tempera
	 */

	typedef Enums::CallingConventions Convention;

	template <Convention conv, typename retType, typename ...argTypes>
	inline retType DoCall(uintptr_t addr, argTypes... args) {
		// typedef retType (__stdcall *function_t)(argTypes...);
		using ufunc_t = retType(__cdecl *)(argTypes...);

		if constexpr(conv == Convention::m_stdcall) {
			using ufunc_t = retType(__stdcall *)(argTypes...);

		} else if constexpr(conv == Convention::m_fastcall) {
			using ufunc_t = retType(__fastcall *)(argTypes...);

		} else if constexpr(conv == Convention::m_thiscall) {
			using ufunc_t = retType(__thiscall *)(argTypes...);

		} else if constexpr(conv == Convention::m_cdecl) {
			using ufunc_t = retType(__cdecl *)(argTypes...);

		} else {
			throw "Invalid return type specified!";
		}

		static const ufunc_t func_to_call = reinterpret_cast<ufunc_t>( addr );
		return func_to_call(args...);
	};
};

namespace Yelo::Memory {
	typedef void (__stdcall *function_process_proc)();

	//////////////////////////////////////////////////////////////////////////
	// t_function_process
	template <const void *TAddress, bool TIsDisabled = false>
	struct t_function_process {
		static const void *k_address;
		static bool       g_is_disabled;

		static void FunctionHook() {
			if (!g_is_disabled)
				__asm call k_address
		}
	};
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// t_function_process_block
	template <const void *TAddress,
		const function_process_proc TBlockPreprocess[], const size_t TBlockPreprocessCount,
		const function_process_proc TBlockPostprocess[], const size_t TBlockPostprocessCount,
		bool TIsDisabled = false>
	struct t_function_process_block {
	private:
		static void CallPreprocesses() {
			if (TBlockPreprocessCount == 0) return;

			const function_process_proc *proc = &TBlockPreprocess[0];
			for (size_t                 x     = 0; x < TBlockPreprocessCount; proc++, x++)
				if (proc != nullptr)
					(*proc)();
		}

		static void CallPostprocesses() {
			if (TBlockPostprocessCount == 0) {
				return;
			}

			const function_process_proc *proc = &TBlockPostprocess[0];
			for (size_t                 x     = 0; x < TBlockPostprocessCount; proc++, x++) {
				if (proc != nullptr) {
					(*proc)();
				}
			}
		}

	public:
		static const void *k_address;
		static bool       g_is_disabled;

		static void FunctionHook() {
			CallPreprocesses();

			if (!g_is_disabled)
				__asm call k_address

			CallPostprocesses();
		}
	};
	//////////////////////////////////////////////////////////////////////////

#include "function_interface.inl"
#include "function_interface_macros.inl"

	// define these in the project implementation, if used
	class c_function_interface_system {
	public:
		static void Initialize() {
			//TODO: reduce abstraction for these particular hooks.
			//Note: These addresses are mostly just hooks. Not very likely to be the full functions we were looking for.
			// Still need to double check, just to be sure, though. :)
			// WRITE_HOOK_BLOCK_PROCESS(render_sky, 0x50F9A2);
			// WRITE_HOOK_BLOCK_PROCESS(render_objects, 0x50F9B1);
			// WRITE_HOOK_BLOCK_PROCESS(render_structure, 0x50F9BB);
			// WRITE_HOOK_BLOCK_PROCESS(weather_particle_systems_render, 0x50FD3C);
			// WRITE_HOOK_BLOCK_PROCESS(render_hud, 0x50FE61);
			// WRITE_HOOK_BLOCK_PROCESS(render_ui,0x50FE6D);
			// WRITE_HOOK_BLOCK_PROCESS(render_cursor,  0x49B520);
			// WRITE_HOOK_BLOCK_PROCESS(update_ui_widgets, 0x4CAF57);
		}

		static void Dispose() {}
	};
};
