#include <precompile.h>
#include "../memory_interface_base.hpp"

#pragma once

namespace Yelo
{
	namespace Memory
	{
		typedef void (API_FUNC* function_process_proc)();

		//////////////////////////////////////////////////////////////////////////
		// t_function_process
		template<const void* TAddress, bool TIsDisabled = false> struct t_function_process
		{
			static const void* k_address;
			static bool g_is_disabled;

			static void FunctionHook()
			{
				if(!g_is_disabled)
					__asm	call k_address
			}
		};
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// t_function_process_block
		template<const void* TAddress, 
			const function_process_proc TBlockPreprocess[], const size_t TBlockPreprocessCount,
			const function_process_proc TBlockPostprocess[], const size_t TBlockPostprocessCount,
			bool TIsDisabled = false> 
		struct t_function_process_block
		{
		private:
			static void CallPreprocesses()
			{
				if(TBlockPreprocessCount == 0) return;

				const function_process_proc* proc = &TBlockPreprocess[0];
				for(size_t x = 0; x < TBlockPreprocessCount; proc++, x++)
					if(proc != nullptr)
						(*proc)();
			}
			static void CallPostprocesses()
			{
				if(TBlockPostprocessCount == 0) return;

				const function_process_proc* proc = &TBlockPostprocess[0];
				for(size_t x = 0; x < TBlockPostprocessCount; proc++, x++)
					if(proc != nullptr)
						(*proc)();
			}
		public:
			static const void* k_address;
			static bool g_is_disabled;

			static void FunctionHook()
			{
				CallPreprocesses();

				if(!g_is_disabled)
					__asm	call k_address

				CallPostprocesses();
			}
		};
		//////////////////////////////////////////////////////////////////////////
#include "function_interface.inl"
#include "function_interface_macros.inl"
		// define these in the project implementation, if used
		class c_function_interface_system
		{
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
};
