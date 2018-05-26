#pragma once

#include <precompile.h>
#include "unit_structures.hpp"
#include "../objects.h"
#include "../../../items/weapons.h"
#include "../damage.hpp"
#include "units.hpp"
#include "units_yelo.hpp"
#include "../grenade_hooks.inl"
#include "../../../memory/upgrades/game_state_yelo.hpp"
#include "units_grenade_count_upgrade.inl"

namespace Yelo::Objects {
	using namespace Yelo::Animations;
	namespace SeatBoarding {
		static c_unit_seat_boarding_manager g_unit_seat_transition_manager;

		void UnitUpdate(const datum_index unit_index) {
			g_unit_seat_transition_manager.UnitUpdate(unit_index);
		}

		void UnitCanEnterBoardingSeat(const datum_index unit_index, const datum_index target_unit_index, const short target_seat_index, bool &result) {
			g_unit_seat_transition_manager.UnitCanEnterBoardingSeat(unit_index, target_unit_index, target_seat_index, result);
		}

		void UnitCanEnterTargetSeat(const datum_index unit_index, const datum_index target_unit_index, const short target_seat_index, bool &result) {
			g_unit_seat_transition_manager.UnitCanEnterTargetSeat(unit_index, target_unit_index, target_seat_index, result);
		}

		void Initialize() {
			Animations::SetAnimationStateKeyframeHandler(Enums::_unit_animation_state_yelo_seat_boarding,
																		[](const datum_index unit_index, const Enums::unit_animation_keyframe keyframe) {
																			g_unit_seat_transition_manager.UnitTriggerBoardingKeyframe(unit_index, keyframe);
																		});
			Animations::SetAnimationStateKeyframeHandler(Enums::_unit_animation_state_yelo_seat_ejecting,
																		[](const datum_index unit_index, const Enums::unit_animation_keyframe keyframe) {
																			g_unit_seat_transition_manager.UnitTriggerEjectingKeyframe(unit_index, keyframe);
																		});
			Animations::SetAnimationStateKeyframeHandler(Enums::_unit_animation_state_yelo_unit_mounted,
																		[](const datum_index unit_index, const Enums::unit_animation_keyframe keyframe) {
																			g_unit_seat_transition_manager.UnitTriggerMountedKeyframe(unit_index, keyframe);
																		});
		}
	};

	namespace SeatDamage {
		static c_unit_seat_damage_manager g_unit_seat_damage_manager;

		void UnitCauseSeatedPlayerMelee(const datum_index unit_index) {
			g_unit_seat_damage_manager.UnitCauseSeatedPlayerMelee(unit_index);
		}

		void UnitThrowSeatedPlayerGrenade(const datum_index unit_index) {
			g_unit_seat_damage_manager.UnitThrowSeatedPlayerGrenade(unit_index);
		}

		bool PreventSeatedPlayerGrenade(const datum_index unit_index, const datum_index weapon_index) {
			auto *unit_datum = blam::object_get_and_verify_type<s_unit_datum>(unit_index);

			if (unit_datum->unit.vehicle_seat_index == NONE) {
				return blam::weapon_prevents_grenade_throwing(weapon_index);
			}
			return g_unit_seat_damage_manager.PreventSeatedPlayerGrenade(unit_index, weapon_index);

		}
	};
};

namespace Yelo::Objects::Units {
	static void __cdecl UnitDamageAftermathHook(const datum_index unit_index, const s_damage_data *damage_data,
															  const Flags::object_damage_flags damage_flags,
															  const real shield_amount,
															  const real body_amount,
															  void *arg6,
															  const long damage_part) {

		blam::unit_damage_aftermath(unit_index, damage_data, damage_flags, shield_amount, body_amount, arg6, damage_part);

		AI::UnitDamageAftermath(unit_index, damage_data);
	}

	bool __cdecl UnitCanEnterSeat(datum_index unit_index, datum_index target_unit_index, short target_seat_index, _Out_opt_ datum_index* return_unit_in_seat) {

		bool result = true;

	Objects::UnitCanEnterSeatMultiteam(unit_index, target_unit_index, target_seat_index, return_unit_in_seat, result);
	SeatBoarding::UnitCanEnterBoardingSeat(unit_index, target_unit_index, target_seat_index, result);
	SeatBoarding::UnitCanEnterTargetSeat(unit_index, target_unit_index, target_seat_index, result);

	return result;
}

API_FUNC_NAKED static void __cdecl UnitCanEnterSeatHook()
{
	API_FUNC_NAKED_START_()
	push	ebx
	push	ecx
	push	edx

	mov		ecx, [esp+24]
	mov		ebx, [esp+20]
	push	ecx		// datum_index* unit_in_seat_index
	push	ebx		// short target_seat_index
	push	edx		// datum_index target_unit_index
	push	eax		// datum_index unit_index
	call	UnitCanEnterSeat
	add		esp, 10h

	pop		edx
	pop		ecx
	pop		ebx
	API_FUNC_NAKED_END_()
}

void UnitCausePlayerSeatedMelee(const datum_index unit_index)
{
	SeatDamage::UnitCauseSeatedPlayerMelee(unit_index);
}

API_FUNC_NAKED static void BipedSeatedMeleeHook()
{
	static uintptr_t RETN_ADDRESS = PTR_BIPED_SEATED_MELEE_RETN;

	_asm
	{
		push	esi
		pushad

		push	esi
		call	BipedSeatedMelee
		add		esp, 4

		popad
		pop		esi

		mov		esi, [ebp+8]
		push	esi
		lea		ecx, [ebp-4]
		jmp		RETN_ADDRESS
	}
}

void __cdecl UnitThrowGrenadeReleaseHook(const datum_index unit_index, const sbyte keyframe)
{
	auto* unit_datum = blam::object_get_and_verify_type<s_unit_datum>(unit_index);
	if(unit_datum->unit.vehicle_seat_index == NONE)
	{
		blam::unit_throw_grenade_release(unit_index, keyframe);
	}
	else
	{
		SeatDamage::UnitThrowSeatedPlayerGrenade(unit_index);
	}
}

bool __cdecl WeaponPreventsGrenadeThrowing(const datum_index unit_index, const datum_index weapon_index)
{
	auto* unit_datum = blam::object_get_and_verify_type<s_unit_datum>(unit_index);
	if(unit_datum->unit.vehicle_seat_index == NONE)
	{
		return blam::weapon_prevents_grenade_throwing(weapon_index);
	}
	else
	{
		return SeatDamage::PreventSeatedPlayerGrenade(unit_index, weapon_index);
	}
}

API_FUNC_NAKED bool WeaponPreventsGrenadeThrowingHook()
{
	static uintptr_t RETN_ADDRESS = PTR_WEAPON_PREVENTS_GRENADE_THROWING_RETN;

	_asm
		{
			push	ecx
		push	edi
		call	WeaponPreventsGrenadeThrowing
		add		esp, 8

		jmp		RETN_ADDRESS
		};
}

static void InitializeUnitGrenadeTypesForNewMap(GameState::s_yelo_header_data& yelo_header)
{
	static bool g_already_enabled = false;

	if (!yelo_header.flags.update_unit_grenade_types_count)
		return;

	uint count = yelo_header.unit_grenade_types_count;

	bool enabled = count > Enums::k_unit_grenade_types_count;
	// HACK: if the grenade count changes are already in place, don't repeat or undo them
	// There was a problem with clients getting disconnected from the server during a join attempt.
	// It puts you back at the mainmenu, but when you try to join again, this would executed again
	// without the changes from last time being undo'd, resulting in a ASSERT() failing on code bytes mismatch
	if (enabled != g_already_enabled)
	{
		InitializeGrenadeCounts_UnitZoomLevelRefs(enabled);
		InitializeGrenadeCounts_UnitDesiredZoomLevelRefs(enabled);
		InitializeGrenadeCounts_NumberOfUnitGrenadeTypes(count);
		InitializeGrenadeCounts_UnitGrenadeCounts(enabled);
		InitializeGrenadeCounts_MessageDeltaGrenadeCounts(enabled);

		g_already_enabled = enabled;
	}

	yelo_header.flags.update_unit_grenade_types_count = false;
}

	void Initialize() {
		Yelo::Animations::Initialize();
		SeatBoarding::Initialize();

		// Enables biped seats
		Memory::WriteMemory((reinterpret_cast<void *>(PTR_BIPED_UPDATE_CHECK_PARENT_UNIT_TYPE)), Enums::_x86_opcode_nop, 6);

		Memory::WriteRelativeCall(&UnitDamageAftermathHook, (reinterpret_cast<void *>(PTR_UNIT_DAMAGE_AFTERMATH_CALL)), true);
		Memory::CreateHookRelativeCall(&UnitCanEnterSeatHook, (reinterpret_cast<void *>(PTR_UNIT_CAN_ENTER_SEAT_HOOK)), Enums::_x86_opcode_ret);
		Memory::WriteRelativeJmp(&BipedSeatedMeleeHook, (reinterpret_cast<void *>(PTR_BIPED_SEATED_MELEE_HOOK)), true);
		Memory::WriteRelativeCall(&UnitThrowGrenadeReleaseHook, (reinterpret_cast<void *>(PTR_UNIT_THROW_GRENADE_RELEASE_HOOK)), true);
		Memory::WriteRelativeJmp(&WeaponPreventsGrenadeThrowingHook, (reinterpret_cast<void *>(PTR_WEAPON_PREVENTS_GRENADE_THROWING_HOOK)), true);
	}

	void Dispose() { }

void InitializeForNewMap()
{
	if(GameState::YeloGameStateEnabled())
	{
		GameState::s_yelo_header_data& yelo_header = GameState::GameStateGlobals()->header->yelo;

		// handle the grenade types upgrading, if needed
		InitializeUnitGrenadeTypesForNewMap(yelo_header);
	}
}

void DisposeFromOldMap() { }


void ObjectsUpdate() {
		Objects::c_object_iterator iter(Enums::_object_type_mask_unit);

		for(auto object_index : iter)
		{
			SeatBoarding::UnitUpdate(object_index.index);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Initialize the Units system for a new map before any of the actual initialize_for_new_map procedures are
	/// 	executed This way we're able to ascertain state changes from the old map with the new map. Eg, differing unit
	/// 	grenade type counts.
	/// </summary>
	void InitializeForNewMapPrologue() 		{
		const TagGroups::s_game_globals* game_globals = GameState::GlobalGameGlobals();
		GameState::s_yelo_header_data& yelo_header = GameState::GameStateGlobals()->header->yelo;

		// check this map's grenade count vs the previous map's
		if (game_globals->grenades.Count != yelo_header.unit_grenade_types_count)
		{
			// inform the unit grenade counts code to run an assembly update
			yelo_header.flags.update_unit_grenade_types_count = true;
			// figure out the new grenade count
			// defaulting to the stock count if there is suspicious number
			if (game_globals->grenades.Count <= Enums::k_unit_grenade_types_count_yelo)
				yelo_header.unit_grenade_types_count = CAST(byte, game_globals->grenades.Count);
			else
				yelo_header.unit_grenade_types_count = Enums::k_unit_grenade_types_count;
		}
	}

	void InitializeForYeloGameState(bool enabled) {}
};

