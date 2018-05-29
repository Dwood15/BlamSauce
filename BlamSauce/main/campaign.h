
#pragma once

// Campaign upgrades as of 1.10 are unsupported/deprecated/fuck off
#define YELO_CAMPAIGN_UPGRADES_ENABLED FALSE
//////////////////////////////////////////////////////////////////////////
// ADD NEW SCENARIO DEFINITIONS HERE
//
// For custom scenario help screens in your custom campaign missions,
// you must have a widget definition called the following:
//		"ui\shell\solo_game\player_help\player_help_screen_<name>"
// Where <name> is the name of your campaign mission. Example:
//		"ui\shell\solo_game\player_help\player_help_screen_s88"
// Would map with the following macro glue:
//		DEFINE_CAMPAIGN_LEVEL(s88, "levels\\s88\\s88");
//////////////////////////////////////////////////////////////////////////



// Note: Only use 'Campaign.inl' (in the "Impl" virtual folder) for declaring campaign levels,
// all other definitions should be automated via 'DEFINE_CAMPAIGN_LEVEL'
namespace Yelo {
	namespace Enums {
		enum campaign_level {
#define DEFINE_CAMPAIGN_LEVEL(name, path) _campaign_level_##name,
			DEFINE_CAMPAIGN_LEVEL(a10, "levels\\a10\\a10")
			DEFINE_CAMPAIGN_LEVEL(a30, "levels\\a30\\a30")
			DEFINE_CAMPAIGN_LEVEL(a50, "levels\\a50\\a50")
			DEFINE_CAMPAIGN_LEVEL(b30, "levels\\b30\\b30")
			DEFINE_CAMPAIGN_LEVEL(b40, "levels\\b40\\b40")
			DEFINE_CAMPAIGN_LEVEL(c10, "levels\\c10\\c10")
			DEFINE_CAMPAIGN_LEVEL(c20, "levels\\c20\\c20")
			DEFINE_CAMPAIGN_LEVEL(c40, "levels\\c40\\c40")
			DEFINE_CAMPAIGN_LEVEL(d20, "levels\\d20\\d20")
			DEFINE_CAMPAIGN_LEVEL(d40, "levels\\d40\\d40")
			//DEFINE_CAMPAIGN_LEVEL(demob30, "levels\\b30\\demob30")

			_campaign_level,
#undef DEFINE_CAMPAIGN_LEVEL

			// Original amount of campaign levels the engine expected
				k_campaign_level_base_count = 10,

			// How many campaign levels we've added to the original count
				k_campaign_level_new_count = _campaign_level - k_campaign_level_base_count,

			// How many campaign levels we've defined
			// 			k_campaign_level_total_count = k_campaign_level_new_count >= 0 ?
			// 				k_campaign_level_base_count + k_campaign_level_new_count
			// 				:
			// 				_campaign_level,
		};

		// Make sure the user heeded our warning and didn't remove existing campaign
		// levels
		static_assert(_campaign_level >= k_campaign_level_base_count);
	};

	namespace Campaign {

#include <enginelayout/Game.inl>

#pragma region Scenario Paths

#define DEFINE_CAMPAIGN_LEVEL(name, path) path,
		static cstring ScenarioPaths[]        = { // this is needed for displaying the title\bitmap in the campaign selection in the UI
			DEFINE_CAMPAIGN_LEVEL(a10, "levels\\a10\\a10")
			DEFINE_CAMPAIGN_LEVEL(a30, "levels\\a30\\a30")
			DEFINE_CAMPAIGN_LEVEL(a50, "levels\\a50\\a50")
			DEFINE_CAMPAIGN_LEVEL(b30, "levels\\b30\\b30")
			DEFINE_CAMPAIGN_LEVEL(b40, "levels\\b40\\b40")
			DEFINE_CAMPAIGN_LEVEL(c10, "levels\\c10\\c10")
			DEFINE_CAMPAIGN_LEVEL(c20, "levels\\c20\\c20")
			DEFINE_CAMPAIGN_LEVEL(c40, "levels\\c40\\c40")
			DEFINE_CAMPAIGN_LEVEL(d20, "levels\\d20\\d20")
			DEFINE_CAMPAIGN_LEVEL(d40, "levels\\d40\\d40")
			//DEFINE_CAMPAIGN_LEVEL(demob30, "levels\\b30\\demob30")

		};
#undef DEFINE_CAMPAIGN_LEVEL

		static void ScenarioPathsInitialize() {
			for (auto ptr : ScenarioPathsReferences)
				*ptr = ScenarioPaths;

			for (auto ptr : ScenarioPathsReferences2)
				*ptr = ScenarioPaths;
		}

#pragma endregion

#pragma region Scenario Help
#define DEFINE_CAMPAIGN_LEVEL(name, path) {#name, "ui\\shell\\solo_game\\player_help\\player_help_screen_" #name},
		static struct s_scenario_help_mapping {
			cstring name;
			cstring widget_definition;
		}              ScenarioHelpMappings[] = { // this is needed for displaying the title\bitmap in the campaign selection in the UI

			DEFINE_CAMPAIGN_LEVEL(a10, "levels\\a10\\a10")
			DEFINE_CAMPAIGN_LEVEL(a30, "levels\\a30\\a30")
			DEFINE_CAMPAIGN_LEVEL(a50, "levels\\a50\\a50")
			DEFINE_CAMPAIGN_LEVEL(b30, "levels\\b30\\b30")
			DEFINE_CAMPAIGN_LEVEL(b40, "levels\\b40\\b40")
			DEFINE_CAMPAIGN_LEVEL(c10, "levels\\c10\\c10")
			DEFINE_CAMPAIGN_LEVEL(c20, "levels\\c20\\c20")
			DEFINE_CAMPAIGN_LEVEL(c40, "levels\\c40\\c40")
			DEFINE_CAMPAIGN_LEVEL(d20, "levels\\d20\\d20")
			DEFINE_CAMPAIGN_LEVEL(d40, "levels\\d40\\d40")
			//DEFINE_CAMPAIGN_LEVEL(demob30, "levels\\b30\\demob30")
			// create a path list of our campaign levels

		};
#undef DEFINE_CAMPAIGN_LEVEL

		static cstring ScenarioHelpMappingGetWidgetName(char *scenario_name) {
			for (auto &mapping : ScenarioHelpMappings)
				if (strstr(scenario_name, mapping.name))
					return mapping.widget_definition;

			return nullptr;
		}

		__declspec(naked) static void __cdecl DisplayScenarioHelpHack() {
			static const uintptr_t SUCCESS_CALL_ADDR = GET_FUNC_PTR(DISPLAY_SCENARIO_HELP_SUCCESS);

			static const uintptr_t FAIL_CALL_ADDR = GET_FUNC_PTR(DISPLAY_SCENARIO_HELP_FAIL);

			__asm {
			// edx = char scenario_name[256]
			// Note: The code we jump back to in display_scenario_help doesn't expect any
			// registers to have a specific value (save for 'eax', which we return)
			// so we don't have to worry about the compiler overwriting ecx or esi
			// without preserving them on the stack in 'ScenarioHelpMappingGetWidgetName's code

			push   edx
			call   ScenarioHelpMappingGetWidgetName
			test   eax, eax
			jz      mapping_not_found
			jmp      SUCCESS_CALL_ADDR

			mapping_not_found:
			jmp      FAIL_CALL_ADDR
			}
		}

		static void DisplayScenarioHelpInitialize() {
			Memory::WriteRelativeJmp(Campaign::DisplayScenarioHelpHack, GET_FUNC_VPTR(DISPLAY_SCENARIO_HELP_HOOK), true);
		}
#pragma endregion

		struct {
			cstring ScenarioPath;
			unsigned char : 8; // bools
			unsigned char : 8;
			unsigned char : 8;
			unsigned char : 8;
		} CampaignLevelData[Enums::_campaign_level];

		static void CampaignLevelDataInitialize() {
			for (auto ptr : CampaignLevelDataReferences)
				*ptr = CampaignLevelData;

			for (auto ptr : CampaignLevelDataSizeReferences)
				*ptr = sizeof(CampaignLevelData) / 4;
		}

		static void CampaignLevelCountInitialize() {
			for (auto ptr : CampaignLevelCountReferences_8bit)
				*ptr = Enums::_campaign_level - 1;
			for (auto ptr : CampaignLevelCountReferences_16bit)
				*ptr = Enums::_campaign_level - 1;
			for (auto ptr : CampaignLevelCountReferences_32bit)
				*ptr = Enums::_campaign_level - 1;

			for (auto ptr : CampaignLevelCountReferences2_8bit)
				*ptr = Enums::_campaign_level;
			for (auto ptr : CampaignLevelCountReferences2_16bit)
				*ptr = Enums::_campaign_level;
		}

		void Initialize() {
			//KM Had this in an if _campaign_level > k_campaign_level_base_count but we want the code active by default possible.
			ScenarioPathsInitialize();
			DisplayScenarioHelpInitialize();
			CampaignLevelDataInitialize();
			CampaignLevelCountInitialize();
		}

		void Dispose() {
		}
	};
};
