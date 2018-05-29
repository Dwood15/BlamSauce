#pragma once

#include <precompile.h>

namespace Yelo::Players {
	struct s_player_screen_flash {
		short type;
		unsigned short : 16;
		real intensity;
		UNKNOWN_TYPE(real);
		UNKNOWN_TYPE(real); UNKNOWN_TYPE(real); UNKNOWN_TYPE(real);
		UNKNOWN_TYPE(long); // unused?
		UNKNOWN_TYPE(long); // unused?
	}; static_assert(sizeof(s_player_screen_flash) == 0x20);


	struct s_player_effects_data : TStructImpl(0x128) {
	};

	s_player_effects_data *PlayerEffects() DPTR_IMP_GET(player_effects);
};


namespace Yelo::blam {

	__declspec(naked) void __cdecl player_examine_nearby_vehicle(datum_index player_index, datum_index vehicle_index)
	{
		static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(PLAYER_EXAMINE_NEARBY_VEHICLE);

		API_FUNC_NAKED_START()
		push	vehicle_index
		push	player_index
		call	FUNCTION
		add		esp, 4 * 2
		API_FUNC_NAKED_END_NO_STACK_POP()
	}
	__declspec(naked) void __cdecl player_set_action_result(datum_index player_index, datum_index action_object_index, long action_result, long action_seat_index)
	{
		static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(PLAYER_SET_ACTION_RESULT);

		API_FUNC_NAKED_START()
		push	ebx

		push	action_seat_index
		push	action_result
		mov		ebx, action_object_index
		mov		eax, player_index
		call	FUNCTION
		add		esp, 4 * 2

		pop		ebx
		API_FUNC_NAKED_END_NO_STACK_POP()
	}
	__declspec(naked) void __cdecl player_set_action_result_to_network(datum_index player_index, datum_index action_object_index, long action_result_type, long action_result, long action_seat_index, datum_index next_weapon_index)
	{
		static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(PLAYER_SET_ACTION_RESULT_TO_NETWORK);

		API_FUNC_NAKED_START()
		push	edi

		push	next_weapon_index
		push	action_seat_index
		push	action_result
		push	action_result_type
		mov		edi, action_object_index
		mov		ecx, player_index
		call	FUNCTION
		add		esp, 4 * 4

		pop		edi
		API_FUNC_NAKED_END_NO_STACK_POP()
	}

	datum_index __cdecl player_index_from_unit_index(datum_index unit_index)
	{
		return Engine::Players::IndexFromUnitIndex(unit_index);
	}
	bool __cdecl player_teleport(datum_index player_index, datum_index source_unit_index, const real_point3d& position)
	{
		return Engine::Players::Teleport(player_index, position, source_unit_index);
	}
	void __cdecl player_over_shield_screen_effect(datum_index player_index)
	{
		Engine::Players::ScreenEffectOvershield(player_index);
	}
	void __cdecl player_active_camo_screen_effect(datum_index player_index)
	{
		Engine::Players::ScreenEffectCamo(player_index);
	}

	void __cdecl player_health_pack_screen_effect(datum_index player_index)
	{
		Engine::Players::ScreenEffectHealth(player_index);
	}


}
