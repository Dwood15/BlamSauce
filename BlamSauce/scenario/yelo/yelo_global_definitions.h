#pragma once

#include "../tags/group/markup.h"
#include "../tags/group/base.h"
#include "project_yellow_scenario_definitions.hpp"

namespace Yelo::Flags {
	enum project_yellow_globals_flags {
		_project_yellow_globals_hide_health_when_zoomed_bit,
		_project_yellow_globals_hide_shield_when_zoomed_bit,
		_project_yellow_globals_hide_motion_sensor_when_zoomed_bit,
		_project_yellow_globals_force_game_to_use_stun_jumping_penalty_bit,
		// TODO:
		_project_yellow_globals_allow_grenade_chain_reactions_in_mp_bit,

		k_number_of_project_yellow_globals_flags,
	};
};

namespace Yelo::TagGroups {
	/* !-- UI --! */
	struct s_project_yellow_scripted_ui_widget {
		TAG_FIELD(tag_string, name);
		TAG_FIELD(tag_reference, definition, 'DeLa');

		PAD32; // future flags
		TAG_PAD(spy_suiw_p0, tag_block, 2);
	};
	/* !-- UI --! */


	/* !-- Netgame --! */
	struct s_network_game_player_unit {
		TAG_FIELD(tag_string, name, "", "name of this block definition");
		TAG_FIELD(tag_reference, definition, "unit", "unit definition for this player's biped");
		TAG_PAD(s_ngpu_p0, long, 8); // 32
	};
	/* !-- Netgame --! */


	/* !-- Scripting --! */
	struct s_script_construct_definition {
		TAG_FIELD(tag_string, name[2]
		); // So we can have at most 62 characters for the name
		TAG_FIELD(short, index
		);

	};

	struct s_script_function_definition : public s_script_construct_definition {
		TAG_ENUM(return_type, Enums::hs_type);
		TAG_TBLOCK(parameters, short); // 32
	};
	struct s_script_global_definition : public s_script_construct_definition {
		TAG_ENUM(type, Enums::hs_type);
	};
	struct s_scripting_definitions {
		TAG_TBLOCK(new_functions, s_script_function_definition);
		TAG_TBLOCK(new_globals, s_script_global_definition);
	};
	/* !-- Scripting --! */


	// yelo for globals
	struct project_yellow_globals {
		enum {
			k_group_tag = 'gelo',
			k_version   = 2,
		};

		// internal name of the cache's Yelo Globals when the user doesn't supply a definition
		static cstring k_default_name = "there they are all standing in a row";

		const short version;
		TAG_FIELD(unsigned short, flags, Flags::project_yellow_globals_flags);
		TAG_FIELD(uint32, base_address);

		TAG_FIELD(tag_string, mod_name, "", "name of the engine 'mod' these globals and, inheriting scenario, are for");

		TAG_FIELD(tag_reference, explicit_references, 'tagc');
		TAG_PAD(pyg_p0, long, 8);

		TAG_PAD(pyg_p1, tag_block, 1);

		/* !-- UI --! */
		struct {
			TAG_PAD(pyg_p2, tag_reference, 3); // 48
			PAD32;
			TAG_TBLOCK(scripted_widgets, s_project_yellow_scripted_ui_widget); // 128
		}           ui;
		/* !-- UI --! */


		/* !-- Netgame --! */
		struct {
			TAG_TBLOCK(player_units, s_network_game_player_unit); // 32

			TAG_PAD(pyg_p2, long, 5); // 20
		}           networking;
		/* !-- Netgame --! */


		/* !-- Scripting --! */
		TAG_TBLOCK(yelo_scripting, s_scripting_definitions); // 1
		/* !-- Scripting --! */


		TAG_PAD(pyg_p3, long, 20); // 80

		project_yellow_globals() : version(project_yellow::k_version) {
			flags = FLAG(Flags::_project_yellow_null_definition_bit) | FLAG(Flags::_project_yellow_invalid_version_bit);
			explicit_references.tag_index = datum_index::null();
		}

	private:
		void CullInvalidNetworkPlayerUnits() {
			for (long x = networking.player_units.Count - 1; x >= 0; x--) {
				const TagGroups::s_network_game_player_unit &player_unit = networking.player_units[x];
				bool remove_element = true;

				if (player_unit.name[0] == '\0')
					YELO_WARN("CheApe: Culling unnamed network_game_player_unit element #%n\n", x);
				else if (player_unit.definition.tag_index.IsNull())
					YELO_WARN("CheApe: Culling invalid network_game_player_unit element #%n (%s)\n", x, player_unit.name);
				else
					remove_element = false;

				if (remove_element)
					blam::tag_block_delete_element(networking.player_units, x);
			}
		}

	public:
		void Cull() {
			CullInvalidNetworkPlayerUnits();
		}
	};
};

