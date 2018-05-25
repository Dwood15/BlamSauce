#pragma once

#include "Common/GameSystemDefinitions.hpp"

namespace Yelo::Main {
	/*
	  Yes, there's a reason why we return component_count minus 1.
	  For most components, there's a dispose/shutdown pattern that can be ran.
	  So we can easily do for loops that are:
		'x <= count' for initialize
		'x >= 0' for dispose
	  In both cases 'x' will be a valid index into the components array.
	  Then since we use NONE for component arrays that don't exist, the for loops will never run
	  (thus the arrays will never get dereferenced. they're null in said conditions after all)
	*/

	// [out_components] - Returns a list of components, or NULL if no components exist
	// returns: Number of components in [out_components] minus 1, or NONE if no components exist in this build
	long GetProjectComponents(s_project_component *&out_components) {
		out_components        = nullptr;
		long components_count = NONE;

		static s_project_component k_components[] = {
			//#include "Common/GameSystemComponent.Definitions.inl"
			{}
		};

		out_components   = k_components;
		components_count = NUMBEROF(k_components) - 1 - 1;

		return components_count;
	}

	// [out_components] - Returns a list of components, or NULL if no components exist
	// returns: Number of components in [out_components] minus 1, or NONE if no components exist in this build
	long GetProjectComponents(s_project_map_component *&out_components) {
		out_components        = nullptr;
		long components_count = NONE;

		static s_project_map_component k_components[] = {
			//#include "Common/GameSystemComponent.Definitions.inl"
			{}
		};

		out_components   = k_components;
		components_count = NUMBEROF(k_components) - 1 - 1;

		return components_count;
	}

	// [out_components] - Returns a list of components, or NULL if no components exist
	// returns: Number of components in [out_components] minus 1, or NONE if no components exist in this build
	long GetProjectComponents(s_project_bsp_component *&out_components) {
		out_components        = nullptr;
		long components_count = NONE;

		//NOTE: There are currently no bsp components in the dedicated server
		static s_project_bsp_component k_components[] = {
			//#include "Common/GameSystemComponent.Definitions.inl"
		};

		out_components   = k_components;
		components_count = NUMBEROF(k_components) - 1;

		return components_count;
	}

	// [out_components] - Returns a list of components, or NULL if no components exist
	// returns: Number of components in [out_components] minus 1, or NONE if no components exist in this build
	long GetProjectComponents(s_project_game_state_component *&out_components) {
		out_components = nullptr;
		long components_count = NONE;

		static s_project_game_state_component k_components[] = {
//#include "Common/GameSystemComponent.Definitions.inl"
			{}
		};

		out_components = k_components;
		components_count = NUMBEROF(k_components)-1 - 1;

		return components_count;
	}

	// [out_components] - Returns a list of components, or NULL if no components exist
	// returns: Number of components in [out_components] minus 1, or NONE if no components exist in this build
	long GetDXComponents(s_dx_component *&out_components) {
		out_components = nullptr;
		long components_count = NONE;

		static s_dx_component k_components[] = {
//#include "Common/GameSystemComponent.Definitions.inl"
			{}
		};

		out_components = k_components;
		components_count = NUMBEROF(k_components)-1 - 1;

		return components_count;
	}

	void InsertHooks();

	static void __cdecl InitializeOnStartup() {
		s_project_component* components;
		const long component_count = GetProjectComponents(components);

		Settings::InitializeSettings();

		for(Yelo::long x = 0; x <= component_count; x++)
			components[x].Initialize();

		Settings::Load();
	}

	static void __cdecl DisposeOnExit()
	{
		s_project_component* components;
		const long component_count = GetProjectComponents(components);

		Settings::Save();

		for(long x = component_count; x >= 0; x--)
			components[x].Dispose();

		Settings::DisposeSettings();
	}

	// hooks the call that starts the main game loop to init OS beforehand
	static void __cdecl InitializeOnStartupHook()
	{
		static uintptr_t TEMP_ADDRESS = GET_FUNC_PTR(QUERY_EXITFLAG_REG);

		_asm push ebx

		InitializeOnStartup();

		_asm pop ebx

		_asm call TEMP_ADDRESS;

	}

	// hooks the call that release resources to dispose of OS systems afterwards
	static void __cdecl DisposeOnExitHook()
	{
		static uintptr_t TEMP_ADDRESS = GET_FUNC_PTR(RELEASE_RESOURCES_ON_EXIT);

		_asm call TEMP_ADDRESS;

		DisposeOnExit();
	}

	void InsertHooks()
	{
		//////////////////////////////////////////////////////////////////////////
		// Unprotect the exe's code so we can freely modify it
		DWORD old;
		VirtualProtect(reinterpret_cast<void *>(0x400000),GET_DATA_PTR(PE_DATA_SIZE),PAGE_EXECUTE_READWRITE,&old);
		//////////////////////////////////////////////////////////////////////////

		Memory::WriteRelativeCall(&InitializeOnStartupHook, GET_FUNC_VPTR(QUERY_EXITFLAG_REG_CALL), true);
		Memory::WriteRelativeCall(&DisposeOnExitHook, GET_FUNC_VPTR(RELEASE_RESOURCES_ON_EXIT_CALL), true);
	}


};
