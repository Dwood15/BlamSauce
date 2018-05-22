/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include "../memory/datum_index.h"

//C++ 17, bitchez
namespace Yelo::blam {
	bool __cdecl weapon_prevents_melee_attack(const datum_index weapon_index);

	bool __cdecl weapon_prevents_grenade_throwing(const datum_index weapon_index);

	void __cdecl weapon_stop_reload(const datum_index weapon_index);

	void __cdecl first_person_weapon_message_from_unit(const datum_index unit_index, const long weapon_message_type);

	short __cdecl weapon_get_first_person_animation_time(const datum_index weapon_index, const short frame_type, Enums::first_person_weapon_animation animation, const long arg3);
};
