#include <precompile.h>
#include "hs.hpp"
#include "../memory/upgrades/blam_memory_upgrades.hpp"
#include "../scenario/yelo/yelo_global_definitions.h"

#pragma once

namespace Yelo::Enums {
	// stock sizes
	enum {
		k_total_scenario_hs_syntax_data         = sizeof(Memory::s_data_array) + (sizeof(Scripting::hs_syntax_node) * Enums::k_maximum_hs_syntax_nodes_per_scenario),
		k_total_scenario_hs_syntax_data_upgrade = sizeof(Memory::s_data_array) + (sizeof(Scripting::hs_syntax_node) * Enums::k_maximum_hs_syntax_nodes_per_scenario_upgrade),
	};
};


#define HS_TYPE(hstype) Yelo::Enums::_hs_type_##hstype


//////////////////////////////////////////////////////////////////////////
// Macro glue for declaring/defining a hs function which takes no arguments
#define DECLARE_HS_FUNCTION(name) extern Yelo::Scripting::hs_function_definition function_##name##_definition

//////////////////////////////////////////////////////////////////////////
// Macro glue for declaring/defining a hs function which takes various arguments for input
#define DECLARE_HS_FUNCTION_WITH_PARAMS(name) extern hs_function_definition function_##name##_definition

#define GET_HS_FUNCTION(name) Yelo::Scripting::function_##name##_definition

//////////////////////////////////////////////////////////////////////////
// Macro glue for declaring/defining a normal hs global
#define DECLARE_HS_GLOBAL(name) extern Yelo::Scripting::hs_global_definition global_##name##_definition

//////////////////////////////////////////////////////////////////////////
// Macro glue for declaring/defining an hs global with special flags
#define DECLARE_HS_GLOBAL_EX(name) extern Yelo::Scripting::hs_global_definition global_##name##_definition

//////////////////////////////////////////////////////////////////////////
// Macro glue for declaring/defining a hs global whose value is stored
// in the engine itself. Was useful in the case of 'gravity'
#define DECLARE_HS_GLOBAL2(name) extern Yelo::Scripting::hs_global_definition global_##name##_definition

#define GET_HS_GLOBAL(name) Yelo::Scripting::global_##name##_definition

namespace Yelo
{
	namespace Flags
	{
		enum hs_yelo_definition_flags : word_flags
		{
			_hs_yelo_definition_internal_bit,
			// changes to the global are sync'd
			_hs_yelo_definition_is_synchronized_bit,
			// hs_function is actually an hs_function_definition_yelo
			_hs_yelo_definition_is_yelo_function_bit,
		};
	};

	namespace Scripting
	{
		typedef void* (__stdcall* proc_hs_yelo_function)();
		typedef void* (__stdcall* proc_hs_yelo_function_with_params)(void** arguments);

		// This is the name of a blam global which isn't used in release builds of the game.
		// We use this global to expose the build version to scripts without causing harm when not using OS.
		// It was chosen due to the hs_type being a 'real', which allows us to specify the version number as "MAJ.MIN"
		// See: K_OPENSAUCE_VERSION
		static const cstring k_external_global_opensauce_override_name = "ai_debug_path_maximum_radius";

		size_t GetTotalScenarioHsSyntaxData()  { return Enums::k_total_scenario_hs_syntax_data; }
		size_t GetTotalScenarioHsSyntaxDataUpgrade() { return Enums::k_total_scenario_hs_syntax_data_upgrade; }

		// Interpret [data] as [type] data. Takes the [data].pointer and sets [data] to the dereferenced value.
		// If [data].pointer is NULL, then this sets [data] to [type]'s NONE equivalent.
		void UpdateTypeHolderFromPtrToData(TypeHolder& data, const Enums::hs_type type) {
			if (data.pointer != nullptr) {
				TypeHolder copy;
				copy.pointer = data.pointer;
				data.pointer = nullptr;
				switch (type) {
					//case HS_TYPE(byte):
					case HS_TYPE(bool):
						data.byte = *copy.ptr.byte;
						break;
						//////////////////////////////////////////////////////////////////////////
						// block index based types
					case HS_TYPE(script):
					case HS_TYPE(trigger_volume):
					case HS_TYPE(cutscene_flag):
					case HS_TYPE(cutscene_camera_point):
					case HS_TYPE(cutscene_title):
					case HS_TYPE(cutscene_recording):
					case HS_TYPE(device_group):
					case HS_TYPE(ai_command_list):
					case HS_TYPE(starting_profile):
					case HS_TYPE(conversation):
						//////////////////////////////////////////////////////////////////////////
					case HS_TYPE(object_name):
					case HS_TYPE(short):
						data.uint16 = *copy.ptr.uint16;
						break;
					case HS_TYPE(real):
					case HS_TYPE(ai):
						//////////////////////////////////////////////////////////////////////////
						// datum_index based types
					case HS_TYPE(object_list):
					case HS_TYPE(sound):
					case HS_TYPE(effect):
					case HS_TYPE(damage):
					case HS_TYPE(looping_sound):
					case HS_TYPE(animation_graph):
					case HS_TYPE(actor_variant):
					case HS_TYPE(damage_effect):
					case HS_TYPE(object_definition):
					case HS_TYPE(object):
					case HS_TYPE(unit):
					case HS_TYPE(vehicle):
					case HS_TYPE(weapon):
					case HS_TYPE(device):
					case HS_TYPE(scenery):
						//////////////////////////////////////////////////////////////////////////
					case HS_TYPE(long):
						data.uint32 = *copy.ptr.uint32;
						break;

						//////////////////////////////////////////////////////////////////////////
						//				case HS_TYPE(string): data.ptr.ascii = copy.ptr.ascii; break;
				}
			} else // the pointer is null, so default to NONE
			{
				data.pointer = nullptr;

				switch (type) {
					//case HS_TYPE(byte):
					case HS_TYPE(bool):
						data.byte = NONE;
						break;
						//////////////////////////////////////////////////////////////////////////
						// block index based types
					case HS_TYPE(script):
					case HS_TYPE(trigger_volume):
					case HS_TYPE(cutscene_flag):
					case HS_TYPE(cutscene_camera_point):
					case HS_TYPE(cutscene_title):
					case HS_TYPE(cutscene_recording):
					case HS_TYPE(device_group):
					case HS_TYPE(ai_command_list):
					case HS_TYPE(starting_profile):
					case HS_TYPE(conversation):
						//////////////////////////////////////////////////////////////////////////
					case HS_TYPE(object_name):
					case HS_TYPE(short):
						data.int16 = NONE;
						break;
					case HS_TYPE(real):
						data.real = -1.0f;
						break;
					case HS_TYPE(ai):
						//////////////////////////////////////////////////////////////////////////
						// datum_index based types
					case HS_TYPE(object_list):
					case HS_TYPE(sound):
					case HS_TYPE(effect):
					case HS_TYPE(damage):
					case HS_TYPE(looping_sound):
					case HS_TYPE(animation_graph):
					case HS_TYPE(actor_variant):
					case HS_TYPE(damage_effect):
					case HS_TYPE(object_definition):
					case HS_TYPE(object):
					case HS_TYPE(unit):
					case HS_TYPE(vehicle):
					case HS_TYPE(weapon):
					case HS_TYPE(device):
					case HS_TYPE(scenery):
						//////////////////////////////////////////////////////////////////////////
					case HS_TYPE(long):
						data.int32 = NONE;
						break;

						//////////////////////////////////////////////////////////////////////////
						//				case HS_TYPE(string): data.ptr.ascii = nullptr; break;
				}
			}
		}
		// Interpret [ptr] as a [type] pointer. Takes [ptr], deferences it and sets [data] to the value.
		// [data] is 'const' as this doesn't modify the pointer, but the data which it points to.
		void UpdateTypeHolderDataFromPtr(const TypeHolder& data, const Enums::hs_type type, void* ptr);


		// currently defined in Halo1_CE's ScriptLibrary.cpp
		bool DefinitionsMatch(const TagGroups::s_scripting_definitions& data);
	};
};

namespace Yelo::Scripting {
	void UpdateTypeHolderDataFromPtr(const TypeHolder &data, const Enums::hs_type type, void *ptr) {
		if (data.pointer != nullptr && ptr != nullptr) {
			switch (type) {
				//case HS_TYPE(byte):
				case HS_TYPE(bool):
					*data.ptr.byte = *CAST_PTR(byte * , ptr);
					break;
					//////////////////////////////////////////////////////////////////////////
					// block index based types
				case HS_TYPE(script):
				case HS_TYPE(trigger_volume):
				case HS_TYPE(cutscene_flag):
				case HS_TYPE(cutscene_camera_point):
				case HS_TYPE(cutscene_title):
				case HS_TYPE(cutscene_recording):
				case HS_TYPE(device_group):
				case HS_TYPE(ai_command_list):
				case HS_TYPE(starting_profile):
				case HS_TYPE(conversation):
					//////////////////////////////////////////////////////////////////////////
				case HS_TYPE(object_name):
				case HS_TYPE(short):
					*data.ptr.uint16 = *CAST_PTR(uint16 * , ptr);
					break;
				case HS_TYPE(real):
				case HS_TYPE(ai):
					//////////////////////////////////////////////////////////////////////////
					// datum_index based types
				case HS_TYPE(object_list):
				case HS_TYPE(sound):
				case HS_TYPE(effect):
				case HS_TYPE(damage):
				case HS_TYPE(looping_sound):
				case HS_TYPE(animation_graph):
				case HS_TYPE(actor_variant):
				case HS_TYPE(damage_effect):
				case HS_TYPE(object_definition):
				case HS_TYPE(object):
				case HS_TYPE(unit):
				case HS_TYPE(vehicle):
				case HS_TYPE(weapon):
				case HS_TYPE(device):
				case HS_TYPE(scenery):
					//////////////////////////////////////////////////////////////////////////
				case HS_TYPE(long):
					*data.ptr.uint32 = *CAST_PTR(uint32 * , ptr);
					break;

					//////////////////////////////////////////////////////////////////////////
					//				case HS_TYPE(string): *data.ptr.ascii = CAST_PTR(cstring, ptr); break;
			}
		}
	}
};
