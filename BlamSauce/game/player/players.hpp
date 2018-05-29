#pragma once

#include <sal.h>
#include "../../memory/datum_index.h"
#include "../objects/units/unit_structures.hpp"
#include "../objects/objects.h"
#include "player_structures.hpp"
#include "player_control.hpp"
#include "../../hs/library/enums.h"
#include "../../tags/files/tags.h"
#include "../../scenario/yelo/yelo_scenario.h"
#include "../engines/game_engine.h"
#include "player_action.hpp"
#include "../../effects/player/player_effects.hpp"

namespace Yelo::ActionResults {
	static void* player_handle_action_jmp_table_yelo[Yelo::Enums::k_number_of_player_action_results_yelo];

	// Replaces PlayerHandleAction function's switch table with our own
	static void InitializePlayerHandleActionJmpTable()
	{
		// how much the stock jmp table is offset from the action_result enum
		const long offset = Yelo::Enums::_player_action_result_swap_equipment;

		// write the game's default jump case into our jump table
		for (auto& ptr : player_handle_action_jmp_table_yelo)
			ptr = PLAYER_HANDLE_ACTION_JMP_TABLE[1];

		// copy the game's jmp table to our own and account for the offset
		long handle_action_last_entry_type = (long)PLAYER_HANDLE_ACTION_LAST_ENTRY_TYPE;
		for (long x = offset; x <= handle_action_last_entry_type + offset; x++)
			player_handle_action_jmp_table_yelo[x] = PLAYER_HANDLE_ACTION_JMP_TABLE[x - offset];

		static const byte k_null_opcode[] = { Enums::_x86_opcode_nop, Enums::_x86_opcode_nop, Enums::_x86_opcode_nop };

		// nullify jmp table size adjustment
		Memory::WriteMemory((reinterpret_cast<void *>(PLAYER_HANDLE_ACTION_JMP_TABLE_ADJUST_SIZE)), k_null_opcode);
		// set the game's jump table count to our's
		(*PLAYER_HANDLE_ACTION_LAST_ENTRY_TYPE) = Yelo::Enums::k_number_of_player_action_results_yelo - 1;
		// set the game's jump table address to our's
		(*player_handle_action_jmp_ptr) = player_handle_action_jmp_table_yelo;
	}

	// Initialize custom yelo action results
	static void InitializeYeloActionResults()
	{
		// Example:
		//player_handle_action_jmp_table_yelo[Enums::_player_action_result_yelo] = &JMPFunction;
		static_assert(Yelo::Enums::k_number_of_player_action_results_yelo == Yelo::Enums::k_number_of_player_action_results, "New player_action_results were defined, but I don't think you've added handlers for them yet");
	}

	void Initialize()
	{
		InitializePlayerHandleActionJmpTable();
		InitializeYeloActionResults();
	}
};


namespace Yelo::NearbyObjects {
	static void* player_examine_nearby_objects_server_jmp_table_yelo[Yelo::Enums::_object_type_sound_scenery+1];
	static void* player_examine_nearby_objects_client_jmp_table_yelo[Yelo::Enums::_object_type_sound_scenery+1];

	// Replaces PlayerExamineNearbyObjectsServer function's switch table with our own
	static void InitializePlayerExamineNearbyObjectsServerJmpTable() {
		// copy the game's jmp table to our own
		for(long x = 0; x <= Yelo::Enums::_object_type_control; x++)
			player_examine_nearby_objects_server_jmp_table_yelo[x] = PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE[x];

		// write the game's default jump case into our jump table for cases 9-11
		for(long x = Yelo::Enums::_object_type_light_fixture; x <= Yelo::Enums::_object_type_sound_scenery; x++)
			player_examine_nearby_objects_server_jmp_table_yelo[x] = PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE[0];

		// set the game's client jump table count to our's
		(*PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_LAST_ENTRY_TYPE) = Yelo::Enums::_object_type_sound_scenery;
		// set the game's client jump table address to our's
		(*player_examine_nearby_objects_server_jmp_ptr) = player_examine_nearby_objects_server_jmp_table_yelo;
	}

	// Replaces PlayerExamineNearbyObjectsClient function's switch table with our own
	static void InitializePlayerExamineNearbyObjectsClientJmpTable() {
		// copy the game's jmp table to our own
		for(long x = 0; x <= Yelo::Enums::_object_type_control; x++){
			player_examine_nearby_objects_client_jmp_table_yelo[x] = PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE[x];
		}

		// write the game's default jump case into our jump table for cases 9-11
		for(long x = Yelo::Enums::_object_type_light_fixture; x <= Yelo::Enums::_object_type_sound_scenery; x++){
			player_examine_nearby_objects_client_jmp_table_yelo[x] = PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE[0];
		}

		// set the game's client jump table count to our's
		(*PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_LAST_ENTRY_TYPE) = Yelo::Enums::_object_type_sound_scenery;
		// set the game's client jump table address to our's
		(*player_examine_nearby_objects_client_jmp_ptr) = player_examine_nearby_objects_client_jmp_table_yelo;
	}

	static void PlayerExamineNearbyBiped(datum_index player_index, datum_index biped_index) {
		s_player_datum* player = Players::Players()[player_index];

		// Make sure we're not detecting ourself
		if (player->slave_unit_index != biped_index)
		{
			// Add check to see if biped is on our team to allow differentiation between unit seat entering and weapon swapping
			// Problem: when you enter a biped seat, their team changes to yours
			blam::player_examine_nearby_vehicle(player_index, biped_index);
		}
	}

	static __declspec(naked) void __cdecl PlayerExamineNearbyBipedServerJMP() {
		static const uintptr_t RETN_ADDRESS = PLAYER_EXAMINE_NEARBY_OBJECTS_SERVER_JMP_TABLE_RETN;

		__asm {
		push	ecx		push	edx

		push	ecx		// datum_index biped_index
		push	edi		// datum_index player_index
		call	PlayerExamineNearbyBiped

		pop		edx
		pop		ecx

		jmp		RETN_ADDRESS
		}
	}

	static __declspec(naked) void __cdecl PlayerExamineNearbyBipedClientJMP() {
		static const uintptr_t RETN_ADDRESS = PLAYER_EXAMINE_NEARBY_OBJECTS_CLIENT_JMP_TABLE_RETN;

		__asm {
		push	ecx
		push	edx

		push	ecx		// datum_index biped_index
		push	edi		// datum_index player_index
		call	PlayerExamineNearbyBiped

		pop		edx
		pop		ecx

		jmp		RETN_ADDRESS
		}
	}

	// Allows us to add objects to the player_examine_nearby_objects switch tables
	static void InitializeYeloNearbyObjects() {
		// Detect nearby biped objects server side for seat entry
		player_examine_nearby_objects_server_jmp_table_yelo[Yelo::Enums::_object_type_biped] =
			&PlayerExamineNearbyBipedServerJMP;
		// Detect nearby biped objects client side for seat entry
		player_examine_nearby_objects_client_jmp_table_yelo[Yelo::Enums::_object_type_biped] =
			&PlayerExamineNearbyBipedClientJMP;
	}

	void Initialize()
	{
		InitializePlayerExamineNearbyObjectsServerJmpTable();
		InitializePlayerExamineNearbyObjectsClientJmpTable();

		InitializeYeloNearbyObjects();
	}
};

namespace Yelo::Players {
	// NOTE: THE s_network_game_player_unit BLOCK IS CURRENTLY HIDDEN IN THE TAG DEFINITIONS
	// Looking at changing the struct, so consider this deprecated
	/*!
	 * \brief
	 * Determines the unit definition override for a player in Free For All games
	 */
	static datum_index PlayerFindUnitDefinitionOverride(const s_player_datum *player, datum_index unit_definition_index, const TagBlock<TagGroups::s_network_game_player_unit>(&player_units)) {
		// NOTE: currently don't override FFA players
		return unit_definition_index;
	}

	/*!
	 * \brief
	 * Determines the unit definition override for a player in Team-based games
	 */
	static datum_index
	PlayerFindTeamUnitDefinitionOverride(const s_player_datum *player, datum_index unit_definition_index, const TagBlock<Yelo::TagGroups::s_network_game_player_unit>(&player_units)) {
		// HACK: not the best way of doing this (hate hard coding stuff), but for now it works
		static cstring k_team_names[Enums::k_number_of_multiplayer_teams] = {"red_team", "blue_team"};

		long player_team_index = player->team_index;
		if (player_team_index >= 0 && player_team_index < std::size(k_team_names)) {
			const char *player_team_name = k_team_names[player_team_index];

			for (const auto &player_unit : player_units) {
				// Null definitions are removed by CheApe extensions, so tag_index should never be null (unless modified by non-OS tools)
				if (!strcmp(player_unit.name, player_team_name)) {
					unit_definition_index = player_unit.definition.tag_index;
				}
			}
		}

		return unit_definition_index;
	}

	/*!
	 * \brief
	 * Determines the unit definition override to use for a player based on their state and if any overrides exist in the PY globals definition
	 *
	 * \param player_index
	 * Player's index
	 *
	 * \param unit_definition_index
	 * Default unit definition for multiplayer games
	 *
	 * \returns
	 * The override unit definition, based on the player's state, or the default definition
	 */
	static datum_index PlayerSpawnCreateUnitMultiplayerGetDefinitionOverride(datum_index player_index, datum_index unit_definition_index) {
		const TAG_TBLOCK(&player_units, TagGroups::s_network_game_player_unit) = Scenario::GetYeloGlobals()->networking.player_units;
		if (player_units.Count == 0)
			return unit_definition_index;

		const s_player_datum *player = Players::Players()[player_index];

		unit_definition_index = GameEngine::GlobalVariant()->universal_variant.teams ?
										PlayerFindTeamUnitDefinitionOverride(player, unit_definition_index, player_units) :
										PlayerFindUnitDefinitionOverride(player, unit_definition_index, player_units);

		return unit_definition_index;
	}

	static __declspec(naked) void __cdecl PlayerSpawnCreateUnitMultiplayerHook() {
		static const uintptr_t RETN_ADDRESS = GET_FUNC_PTR(PLAYER_SPAWN__CREATE_UNIT_MP_HOOK_RETN);

		__asm {
		push   eax      // unit_definition_index
		push   ebx      // player_index
		call   PlayerSpawnCreateUnitMultiplayerGetDefinitionOverride

		jmp      RETN_ADDRESS
		}
	}
};

namespace Yelo::Players {
	static void* scripting_volume_test_player_team_evaluate(void** arguments)
	{
		struct s_arguments {
			short trigger_volume;
			unsigned short : 16;
			short team_index;
			unsigned short : 16;
		}* args = CAST_PTR(s_arguments*, arguments);
		TypeHolder result; result.pointer = nullptr;
		result.boolean = false;

		if(args->team_index >= 0 && GameEngine::GlobalVariant()->universal_variant.teams)
		{
			for(auto player : Players::Players())
			{
				if(player->team_index == args->team_index &&
					blam::scenario_trigger_volume_test_object(args->trigger_volume, player->slave_unit_index))
				{
					result.boolean = true;
					break;
				}
			}
		}

		return result.pointer;
	}

	static void* scripting_volume_test_player_team_all_evaluate(void** arguments)
	{
		struct s_arguments {
			short trigger_volume;
			unsigned short : 16;
			short team_index;
			unsigned short : 16;
		}* args = reinterpret_cast<s_arguments *>(arguments);
		TypeHolder result; result.pointer = nullptr;
		result.boolean = true;

		if(args->team_index >= 0 && GameEngine::GlobalVariant()->universal_variant.teams)
		{
			for(auto player : Players::Players())
			{
				if(player->team_index == args->team_index &&
					!blam::scenario_trigger_volume_test_object(args->trigger_volume, player->slave_unit_index))
				{
					result.boolean = false;
					break;
				}
			}
		}
		else result.boolean = false;

		return result.pointer;
	}

	static void* scripting_player_team_teleport_evaluate(void** arguments)
	{
		struct s_arguments {
			short team_index;
			unsigned short : 16;
			short cutscene_flag;
			unsigned short : 16;
		}* args = reinterpret_cast<s_arguments *>(arguments);

		if(args->team_index >= 0 && GameEngine::GlobalVariant()->universal_variant.teams)
		{
			for(auto player : Players::Players())
			{
				if(player->team_index == args->team_index)
				{
					TagGroups::scenario* scnr = Scenario::Scenario();
					blam::player_teleport(player.index, datum_index::null, scnr->cutscene_flags[args->cutscene_flag].position);
				}
			}
		}

		return nullptr;
	}

	static void* scripting_player_team_players_evaluate(void** arguments)
	{
		struct s_arguments {
			short team_index;
			unsigned short : 16;
		}* args = reinterpret_cast<s_arguments *>(arguments);
		TypeHolder result; result.datum = datum_index::null();

		if(args->team_index >= 0 && GameEngine::GlobalVariant()->universal_variant.teams)
		{
			// An object list will only be created if there is 1 or more players on the specified team
			datum_index object_list = datum_index::null();

			for(auto player : Players::Players())
			{
				if(player->team_index == args->team_index)
				{
					if(object_list.IsNull())
						object_list = blam::object_list_new();

					blam::object_list_add(object_list, player->slave_unit_index);
				}
			}

			// list will either be null or a handle to a object-list on return
			result.datum = object_list;
		}

		return result.pointer;
	}


	static long scripting_player_data_get_integer_by_name(s_player_datum* player, cstring data_name, bool for_team_data = false)
	{
		cstring s = data_name; // alias for keeping the code width down

		if( !strcmp(s,"kills_this_lifetime") )	return player->kills_this_lifetime;

		else if( !strcmp(s,"friendly_fire_kills") )	return player->friendly_fire_kills;
		else if( !strcmp(s,"deaths") )				return player->deaths;
		else if( !strcmp(s,"suicides") )			return player->suicides;

			//else if( !strcmp(s,"") )	return *player-;

		else if( !for_team_data )
		{
			if( !strcmp(s,"team_index") )			return player->team_index;
			else if( !strcmp(s,"current_spree_count") )	return player->current_spree_count;
			else if( !strcmp(s,"last_kill_time") )		return player->last_kill_time;
			else if( !strcmp(s,"ping") )				return player->ping;
			//else if( !strcmp(s,"") )	return *player-;
		}

		return NONE;
	}
	static void* scripting_player_data_get_integer_evaluate(void** arguments)
	{
		struct s_arguments {
			short player_list_index;
			unsigned short : 16;
			cstring data_name;
		}* args = reinterpret_cast<s_arguments *>(arguments);
		TypeHolder result;
		result.pointer = nullptr;
		result.long = NONE;

		if(args->player_list_index >= 0)
		{
			for(auto player : Players::Players())
			{
				if(player->network_player.player_list_index == args->player_list_index)
				{
					result.long = scripting_player_data_get_integer_by_name(player.datum, args->data_name);
					break;
				}
			}
		}

		return result.pointer;
	}
	static void* scripting_player_team_data_get_integer_evaluate(void** arguments)
	{
		struct s_arguments {
			short team_index;
			unsigned short : 16;
			cstring data_name;
		}* args = CAST_PTR(s_arguments*, arguments);
		TypeHolder result; result.pointer = nullptr;
		result.long = NONE;

		if(args->team_index >= 0 && Yelo::GameEngine::GlobalVariant()->universal_variant.teams)
		{
			for(auto player : Players::Players())
			{
				if(player->team_index == args->team_index)
					result.long += scripting_player_data_get_integer_by_name(player.datum, args->data_name, true);
			}
		}

		return result.pointer;
	}

	static datum_index scripting_player_data_get_object_by_name(s_player_datum* player, cstring data_name)
	{
		datum_index object_index = player->slave_unit_index;

		if(!object_index.IsNull()) // only get object data fields whenever this player is alive
		{
			cstring s = data_name; // alias for keeping the code width down

			if( !strcmp(s,"nearest_object") )	return player->nearest_object_action_result.action_object_index;
			else if( !strcmp(s,"slave_unit") )		return player->slave_unit_index;
			else if( !strcmp(s,"last_slave_unit") )	return player->last_slave_unit_index;
			else if( !strcmp(s,"target_player") )
			{
				datum_index target_player = player->target_player_index;
				if(!target_player.IsNull())
					return Players::Players()[target_player]->slave_unit_index;
			}
		}

		return datum_index::null();
	}
	static void* scripting_player_data_get_object_evaluate(void** arguments)
	{
		struct s_arguments {
			short player_list_index;
			unsigned short : 16;
			cstring data_name;
		}* args = CAST_PTR(s_arguments*, arguments);
		TypeHolder result; result.pointer = nullptr;
		result.datum = datum_index::null();

		if(args->player_list_index >= 0)
		{
			for(auto player : Players::Players())
			{
				if(player->network_player.player_list_index == args->player_list_index)
				{
					result.datum = scripting_player_data_get_object_by_name(player.datum, args->data_name);
					break;
				}
			}
		}

		return result.pointer;
	}

	static real* scripting_player_data_get_real_by_name(s_player_datum* player, cstring data_name, Enums::hs_type& out_type)
	{
		cstring s = data_name; // alias for keeping the code width down

		out_type = HS_TYPE(real);
		if( !strcmp(s,"speed") )	return &player->speed;
		//else if( !strcmp(s,"") )		return &player->;

		return nullptr;
	}
	static void* scripting_player_data_get_real_evaluate(void** arguments)
	{
		struct s_arguments {
			short player_list_index;
			unsigned short : 16;
			cstring data_name;
		}* args = CAST_PTR(s_arguments*, arguments);
		TypeHolder result; result.pointer = nullptr;
		result.real = -1.0f;

		if(args->player_list_index >= 0)
		{
			for(auto player : Players::Players())
			{
				if(player->network_player.player_list_index == args->player_list_index)
				{
					Enums::hs_type result_type;
					result.ptr.real = scripting_player_data_get_real_by_name(player.datum, args->data_name, result_type);
					Scripting::UpdateTypeHolderFromPtrToData(result, result_type);
					break;
				}
			}
		}

		return result.pointer;
	}
	static void* scripting_player_data_set_real_evaluate(void** arguments)
	{
		struct s_arguments {
			short player_list_index;
			unsigned short : 16;
			cstring data_name;
			real data_value;
		}* args = CAST_PTR(s_arguments*, arguments);

		if(args->player_list_index >= 0)
		{
			for(auto player : Players::Players())
			{
				if(player->network_player.player_list_index == args->player_list_index)
				{
					TypeHolder result;
					Enums::hs_type result_type;
					result.ptr.real = scripting_player_data_get_real_by_name(player.datum, args->data_name, result_type);
					Scripting::UpdateTypeHolderDataFromPtr(result, result_type, &args->data_value);
					break;
				}
			}
		}

		return nullptr;
	}

	static void* scripting_player_local_get_evaluate()
	{
		TypeHolder result; result.pointer = nullptr;
		result.long = NONE;

		auto* local_player = Yelo::Players::LocalPlayer();
		if(local_player != nullptr)
			result.long = local_player->network_player.player_list_index;

		return result.pointer;
	}
}

namespace Yelo::Players	{
	void __cdecl FollowingCameraGetUnitCameraInfoImpl(const short player_index, Players::s_unit_camera_info& camera_info) {
		auto& local_player = PlayerControlGlobals()->local_players[player_index];
		auto& player_unit_datum = *blam::object_get_and_verify_type<Objects::s_unit_datum>(local_player.unit_index);

		// If the player has been mounted, see if a third person camera should be used
		bool info_set = false;
		if(player_unit_datum.unit.animation.state == Enums::_unit_animation_state_yelo_unit_mounted)
		{
			auto& unit_definition = *blam::tag_get<TagGroups::s_unit_definition>(player_unit_datum.object.definition_index);
			if((unit_definition.unit.extensions.Count == 1)
				&& (unit_definition.unit.extensions[0].mounted_state.Count == 1))
			{
				auto& mounted_state_definition = unit_definition.unit.extensions[0].mounted_state[0];
				if(TEST_FLAG(mounted_state_definition.flags, Flags::_unit_mounted_state_flags_third_person_camera))
				{
					// Return the camera info for the mounted state camera
					Objects::s_object_marker marker;
					if(blam::object_get_marker_by_name(local_player.unit_index, mounted_state_definition.unit_camera.camera_marker_name, &marker, 1) == 1)
					{
						camera_info.unit_index = local_player.unit_index;
						camera_info.seat_index = NONE;
						camera_info.unit_camera_definition = &mounted_state_definition.unit_camera;
						camera_info.position = marker.transformed_matrix.Position;
						return;
					}
				}
			}
		}

		blam::player_control_get_unit_camera_info(player_index, camera_info);
	}

	__declspec(naked) void FollowingCameraGetUnitCameraInfoHook()
	{
		API_FUNC_NAKED_START()
		push	ecx

		xor	ecx, ecx
		movsx	cx, ax
		push	esi
		push	ecx
		call	FollowingCameraGetUnitCameraInfoImpl
		add		esp, 8

		pop		ecx
		pop		ebp
		API_FUNC_NAKED_END_()
	}

	datum_index s_player_datum::GetVehicleIndex() {
		datum_index vehicle_index = datum_index::null();

		Objects::s_unit_datum* unit = this->GetPlayerUnit();
		if(unit != nullptr) {
			datum_index parent_object_index = unit->object.parent_object_index;
			if(	!parent_object_index.IsNull() && unit->unit.vehicle_seat_index == NONE )
				vehicle_index = parent_object_index;
		}

		return vehicle_index;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Server side updates of players </summary>
	///
	/// <remarks>	called before core game update functions </remarks>
	void __cdecl UpdateForServer() {}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Client side updates of players </summary>
	///
	/// <remarks>	called before core game update functions </remarks>
	void __cdecl UpdateForClient() {}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <remarks>	called after core game update functions </remarks>
	void __cdecl Update(){}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the player data of the currently active local player </summary>
	///
	/// <returns>	NULL if there is none </returns>
	datum_index LocalPlayerIndex() {
		for(auto player : Players()) {
			if(player->local_player_index != NONE)
				return player.index;
		}

		return datum_index::null();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the player data of the currently active local player </summary>
	///
	/// <returns>	NULL if there is none </returns>
	s_player_datum* LocalPlayer() {
		for(auto player : Players()) {
			if(player->local_player_index != NONE){
				return player.datum;
			}
		}
		return nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the player data from a player number, and optionally their player_index </summary>
	///
	/// <param name="player_number">		 	The player number </param>
	/// <param name="player_index_reference">	[out] (Optional) the player index </param>
	///
	/// <returns>	NULL if player number is invalid or unused </returns>
	s_player_datum* GetPlayerFromNumber(byte player_number, _Out_ datum_index* player_index_reference = nullptr) {
	if(player_index_reference != nullptr) *player_index_reference = datum_index::null();
	if(player_number == NONE) return nullptr;

	for(auto player : Players()) {
	if(player->network_player.player_list_index == player_number) {
	if(player_index_reference != nullptr) {
	*player_index_reference = player.index;
}
return player.datum;
}
}

return nullptr;
}

Objects::s_unit_datum* GetPlayerUnit(datum_index player_index) {
	if(player_index.IsNull()) {
		return nullptr;
	}

	return Players::Players()[player_index]->GetPlayerUnit();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Use the handle to a player to get the active unit object which it controls </summary>
///
/// <param name="player_index">	 </param>
///
/// <returns>	NULL if player handle or the unit handle for the player is NONE. </returns>
Objects::s_unit_datum* s_player_datum::GetPlayerUnit() {
	datum_index object_index = this->slave_unit_index;
	if(object_index.IsNull()) return nullptr;

	return Objects::ObjectHeader()[object_index]->_unit;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Use the handle to a player to get the weapons held by it slave unit which they are in control of.
/// </summary>
///
/// <param name="player_index">		   	 </param>
/// <param name="current_weapon_index">	[out] (Optional) the readied weapon index. </param>
///
/// <returns>	NULL if player handle or the unit handle for the player is NONE. </returns>
datum_index* GetWeapons(datum_index player_index, _Out_ short* current_weapon_index = nullptr) {
	Objects::s_unit_datum* unit = GetPlayerUnit(player_index);

	if(unit == nullptr) return nullptr;

	if(current_weapon_index)
		*current_weapon_index = unit->unit.current_weapon_index;

	return unit->unit.weapon_object_indices;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 	Use the handle to a player to get the active unit object of the vehicle which the unit the player is
/// 	controlling is currently in
/// </summary>
///
/// <param name="player_index">		 	 </param>
/// <param name="current_seat_index">	[out] (Optional) the player's vehicle seat index </param>
///
/// <returns>
/// 	NULL if player handle or the unit handle for the player is NONE. Also returns NULL if player isn't in a
/// 	vehicle NOTE: "vehicle" is a loose term here, could be another unit derived. NOTE: "vehicle" is a loose term
/// 	here, could be another unit derived type, possibly even a biped, who knows!
/// </returns>
Objects::s_unit_datum* GetVehicle(datum_index player_index, _Out_ short* current_seat_index = nullptr) {
	Objects::s_unit_datum* unit = GetPlayerUnit(player_index);

	if(unit == nullptr) return nullptr;

	if(current_seat_index)
		*current_seat_index = unit->unit.vehicle_seat_index;

	datum_index parent_index = unit->object.parent_object_index;
	if(parent_index.IsNull())
		return nullptr;

	return Objects::ObjectHeader()[parent_index]->_unit;
	}
};


namespace Yelo::Players {
	void Initialize() {
		Yelo::Scripting::InitializeScriptFunctionWithParams(Yelo::Enums::_hs_function_volume_test_player_team, scripting_volume_test_player_team_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_volume_test_player_team_all, scripting_volume_test_player_team_all_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_team_teleport, scripting_player_team_teleport_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_team_players, scripting_player_team_players_evaluate);

		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_data_get_integer, scripting_player_data_get_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_team_data_get_integer, scripting_player_team_data_get_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_data_get_object, scripting_player_data_get_object_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_data_get_real, scripting_player_data_get_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_player_data_set_real, scripting_player_data_set_real_evaluate);
		Scripting::InitializeScriptFunction(Enums::_hs_function_player_local_get, scripting_player_local_get_evaluate);

		Memory::WriteRelativeJmp(PlayerSpawnCreateUnitMultiplayerHook, (reinterpret_cast<void *>(PLAYER_SPAWN__CREATE_UNIT_MP_HOOK)));
		Memory::WriteRelativeJmp(UpdateForServer, (reinterpret_cast<void *>(PLAYERS_UPDATE_BEFORE_GAME_SERVER_HOOK)), true);
		Memory::WriteRelativeJmp(UpdateForClient, (reinterpret_cast<void *>(PLAYERS_UPDATE_BEFORE_GAME_CLIENT_HOOK)), true);
		Memory::WriteRelativeJmp(Update, (reinterpret_cast<void *>(PLAYERS_UPDATE_AFTER_GAME_HOOK)), true);

		Memory::WriteRelativeCall(&FollowingCameraGetUnitCameraInfoHook, (reinterpret_cast<void *>(FOLLOWING_CAMERA_GET_UNIT_CAMERA_INFO_CALL)), true);

		NearbyObjects::Initialize();
		ActionResults::Initialize();
	}

	void Dispose() {}


};
