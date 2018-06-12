#pragma once

#include <precompile.h>
#include "field_definitions.inl"
#include "impl_objects.inl"
#include "impl_weapon.inl"
#include "impl_units.inl"
#include "../object_definitions.hpp"
#include "../units/unit_structures.hpp"
#include "../../../items/weapon_definitions.h"
#include "../../../items/weapon_structures.h"

namespace Yelo::Enums {
	enum object_field_index : short {
		_object_field_real_function_out,
		_object_field_real_radius,
		_object_field_real_scale,
		_object_field_real_maximum_vitality, // Keep for backwards compatibility ONLY, value is incorrect
		_object_field_real_current_vitality, // Keep for backwards compatibility ONLY, value is incorrect
		_object_field_real_maximum_health,
		_object_field_real_maximum_shield,
		_object_field_real_current_health,
		_object_field_real_current_shield,

		_object_field_vector_position,
		_object_field_vector_transitional_velocity,
		_object_field_vector_forward,
		_object_field_vector_up,
		_object_field_vector_angular_velocity,
		_object_field_vector_center,

		_unit_field_vector_desired_facing,
		_unit_field_vector_desired_aiming,
		_unit_field_vector_aiming,
		_unit_field_vector_aiming_velocity,
		_unit_field_vector_looking,
		_unit_field_vector_looking_angles,
		_unit_field_vector_looking_velocity,

		_weapon_field_real_heat,
		_weapon_field_real_age,
		_weapon_field_real_light_power,

		_weapon_field_integer_magazine_state,
		_weapon_field_integer_magazine_reload,
		_weapon_field_integer_magazine_rounds,

		_weapon_tag_field_real_trigger_spew_time,
		_weapon_tag_field_real_trigger_rounds_per_second,

		_unit_field_object_index_throwing_grenade_projectile,
		_unit_field_object_index_weapon,
		_unit_field_object_index_equipment,
		_unit_field_object_index_40C, // TBD, when we verify the full extent of the field at 0x40C
		_unit_field_object_index_damage_responsible_flamer_object,
		_unit_field_object_index_recent_damage_unit,

		_unit_field_integer_ticks_until_flame_to_death,
		_unit_field_integer_throwing_grenade_state,
		_unit_field_integer_total_grenade_count_frag,
		_unit_field_integer_total_grenade_count_plasma,
		_unit_field_integer_total_grenade_count_custom2,
		_unit_field_integer_total_grenade_count_custom3,
		_unit_field_integer_current_grenade_index,
		_unit_field_integer_zoom_level,
		_unit_field_integer_desired_zoom_level,

		_unit_field_integer_vehicle_seat_index,
		_unit_field_integer_current_weapon_index,
		_unit_field_integer_feign_death_timer,
		_unit_field_integer_killing_spree_count,

		_unit_field_real_driver_power,
		_unit_field_real_gunner_power,
		_unit_field_real_integrated_light_power,
		_unit_field_real_integrated_light_toggle_power,
		_unit_field_real_integrated_night_vision_toggle_power,
		_unit_field_real_camo_power,
		_unit_field_real_full_spectrum_vision_power,
	};
};

namespace Yelo::Objects {
	struct s_object_field_definition {
		const char *        name;
		size_t         name_length;
		Enums::hs_type hs_type;
		short          definition_index;

		BOOL is_networked : 1;
		BOOL is_readonly : 1;
		// field is subscripted, so we only bsearch compare the first [name_length] characters
		// eg, weapon2 would be compare as equal to "weapon"
		BOOL is_subscripted : 1;

		static int __cdecl qsort_proc(void *, const s_object_field_definition *lhs, const s_object_field_definition *rhs) {
			return _stricmp(lhs->name, rhs->name);
		}

		template <size_t _SizeOfArray>
		static void qsort_list(s_object_field_definition (&list)[_SizeOfArray]) {
			Qsort(list, _SizeOfArray, qsort_proc);
		}

		static int __cdecl bsearch_proc(void *, const char * key, const s_object_field_definition *field_definition) {
			auto rhs = reinterpret_cast<const s_object_field_definition *>(field_definition);

			return field_definition->is_subscripted
					 ? _strnicmp(key, field_definition->name, field_definition->name_length)
					 : _stricmp(key, field_definition->name);
		}

		template <size_t _SizeOfArray>
		static const s_object_field_definition *bsearch_list(const s_object_field_definition (&list)[_SizeOfArray], const char * name) {
			return Bsearch(name, list, _SizeOfArray, bsearch_proc);
		}
	};

	static_assert(sizeof(s_object_field_definition) == 0x10);

	static int ObjectFunctionNameToIndex(const char * function_name) {
		using namespace Enums;

		if (function_name != nullptr) {
			switch (function_name[0]) {
				case 'a':
					return _outgoing_object_function_a;
				case 'b':
					return _outgoing_object_function_b;
				case 'c':
					return _outgoing_object_function_c;
				case 'd':
					return _outgoing_object_function_d;
			}
		}

		return NONE;
	}

	static bool ObjectFieldIndexIsVector(short definition_index) {
		using namespace Enums;

		return
			(definition_index >= _object_field_vector_position && definition_index <= _object_field_vector_center) ||
			(definition_index >= _unit_field_vector_desired_facing && definition_index <= _unit_field_vector_looking_velocity);
	}

	static int VectorFieldNameToIndex(const char * field_name, size_t vector_size) {
		int field_index = 0; // default to the first field ie: 'x', 'i', etc

		if (field_name != nullptr) {
			switch (field_name[0]) {
				case 'y':
				case 'j':
					if (vector_size >= sizeof(real_vector2d))
						field_index = 1;
					break;
				case 'z':
				case 'k':
					if (vector_size >= sizeof(real_vector3d))
						field_index = 2;
					break;
				case 'w':
				case 'd':
					if (vector_size >= sizeof(real_quaternion))
						field_index = 3;
					break;
			}
		}

		return field_index;
	}

	// NOTE: currently only supports subscripts 0 through 9
	// e.g., weapon2 would return 2
	static int SubscriptStringToIndex(const char * subscripted_name) {
		int index = 0;

		if (subscripted_name != nullptr && subscripted_name[0] != '\0') {
			size_t last_char_index = strlen(subscripted_name) - 1;
			char   last_char       = subscripted_name[last_char_index];

			if (last_char >= '0' && last_char <= '9')
				index = last_char - '0';
		}

		return index;
	}

	template <size_t _SizeOfArray, typename TObjectDatum, typename TGetterParam>
	static void ObjectFieldGetImpl(const s_object_field_definition (&list)[_SizeOfArray], const char * name, TObjectDatum &obj, _Inout_ TypeHolder &result,
											 TGetterParam getter_param, bool (__stdcall *getter_proc)(const s_object_field_definition &, TObjectDatum &, _Inout_ TypeHolder &, TGetterParam)) {
		const auto *field = s_object_field_definition::bsearch_list(list, name);

		if (field != nullptr) {
			Enums::hs_type result_type = field->hs_type;

			if (getter_proc(*field, obj, result, getter_param))
				Scripting::UpdateTypeHolderFromPtrToData(result, result_type);
		}
	}

	template <size_t _SizeOfArray, typename TObjectDatum, typename TGetterParam, typename TDataType>
	static void ObjectFieldSetImpl(
		const s_object_field_definition (&list)[_SizeOfArray], const char * name, TObjectDatum &obj,
		TDataType data_value,
		TGetterParam getter_param,
		bool (__stdcall *getter_proc)(const s_object_field_definition &, TObjectDatum &, _Inout_ TypeHolder &, TGetterParam)
	) {
		const auto *field = s_object_field_definition::bsearch_list(list, name);

		if (field != nullptr &&
			 !field->is_readonly &&
			 (GameState::IsLocal() || field->is_networked)) {
			Enums::hs_type result_type = field->hs_type;
			TypeHolder     result;

			if (getter_proc(*field, obj, result, getter_param))
				Scripting::UpdateTypeHolderDataFromPtr(result, result_type, &data_value);
		}
	}

	real_vector3d *ObjectDataGetVectorByName(s_object_header_datum *header, const char * data_name) {
		const auto *field = s_object_field_definition::bsearch_list(g_object_real_fields, data_name);

		if (field != nullptr && ObjectFieldIndexIsVector(field->definition_index))
			return ObjectDataFieldGetVector(*field, *header);

		return nullptr;
	}

	//////////////////////////////////////////////////////////////////////////
	// Real
	void ObjectDataGetRealByName(s_object_header_datum *header,
										  const char * data_name, const char * subdata_name,
										  _Inout_ TypeHolder &result) {
		ObjectFieldGetImpl(g_object_real_fields, data_name, *header,
								 result, subdata_name,
								 ObjectDataFieldGetReal);
	}

	void ObjectDataSetRealByName(s_object_header_datum *header, const char * data_name, const char * subdata_name, real data_value) {
		ObjectFieldSetImpl(g_object_real_fields, data_name, *header, data_value, subdata_name, ObjectDataFieldGetReal);
	}

	void InitializeObjectFieldDefinitions() {
		s_object_field_definition::qsort_list(g_object_real_fields);
		s_object_field_definition::qsort_list(g_weapon_tag_real_trigger_fields);
		s_object_field_definition::qsort_list(g_weapon_real_fields);
		s_object_field_definition::qsort_list(g_unit_object_index_fields);
		s_object_field_definition::qsort_list(g_unit_integer_fields);
		s_object_field_definition::qsort_list(g_unit_real_fields);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	void WeaponTagDataTriggerSetRealByName(s_weapon_datum *weapon, long trigger_index, const char * data_name, const char * subdata_name, real data_value) {
		datum_index definition_index = weapon->object.definition_index;

		const auto *definition = blam::tag_get<TagGroups::s_weapon_definition>(definition_index);

		if (trigger_index >= 0 && trigger_index < definition->weapon.triggers.Count) {
			// We're fucking with the tag definition...at runtime :|
			auto &trigger = (const_cast<TagGroups::weapon_trigger_definition &>(definition->weapon.triggers[trigger_index]));

			ObjectFieldSetImpl(g_weapon_tag_real_trigger_fields, data_name, trigger, data_value, subdata_name, WeaponTagDataFieldTriggerSetReal);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Real
	void WeaponDataGetRealByName(s_weapon_datum *weapon, const char * data_name, _Inout_ TypeHolder &result) {
		ObjectFieldGetImpl(g_weapon_real_fields, data_name, weapon->weapon, result, (void *) nullptr, WeaponDataFieldGetReal);
	}

	void WeaponDataSetRealByName(s_weapon_datum *weapon, const char * data_name, real data_value) {
		ObjectFieldSetImpl(g_weapon_real_fields, data_name, weapon->weapon, data_value, (void *) nullptr, WeaponDataFieldGetReal);
	}

	//////////////////////////////////////////////////////////////////////////
	// magazine - Integer
	void WeaponDataMagazineGetIntegerByName(s_weapon_datum *weapon, long magazine_index, const char * data_name, const char * subdata_name, _Inout_ TypeHolder &result) {
		if (magazine_index >= 0 && magazine_index < Enums::k_maximum_number_of_magazines_per_weapon) {
			Objects::s_weapon_data::s_magazine_state &magazine = weapon->weapon.magazines[magazine_index];

			ObjectFieldGetImpl(g_weapon_integer_magazine_fields, data_name, magazine, result, subdata_name, WeaponDataFieldMagazineGetInteger);
		}
	}

	void WeaponDataMagazineSetIntegerByName(s_weapon_datum *weapon, long magazine_index, const char * data_name, const char * subdata_name, long data_value) {
		if (magazine_index >= 0 && magazine_index < Enums::k_maximum_number_of_magazines_per_weapon) {
			Objects::s_weapon_data::s_magazine_state &magazine = weapon->weapon.magazines[magazine_index];

			ObjectFieldSetImpl(g_weapon_integer_magazine_fields, data_name, magazine, data_value, subdata_name, WeaponDataFieldMagazineGetInteger);
		}
	}

	void WeaponTagDataTriggerSetRealByName(s_weapon_datum *weapon, long trigger_index, const char * data_name, const char * subdata_name, real data_value);

	void UnitDataGetObjectIndexByName(s_unit_datum *unit, const char * data_name, _Inout_ TypeHolder &result);

	void UnitDataSetRealByName(s_unit_datum *unit, const char * data_name, real data_value);

	//////////////////////////////////////////////////////////////////////////
	// object_index
	void UnitDataGetObjectIndexByName(s_unit_datum *unit, const char * data_name, _Inout_ TypeHolder &result) {
		ObjectFieldGetImpl(g_unit_object_index_fields, data_name, unit->unit,
								 result, data_name, // getter processes data_name for the subscript
								 UnitDataFieldGetObjectIndex);
	}

	//////////////////////////////////////////////////////////////////////////
	// Integer
	void UnitDataGetIntegerByName(s_unit_datum *unit, const char * data_name, _Inout_ TypeHolder &result) {
		ObjectFieldGetImpl(g_unit_integer_fields, data_name, unit->unit, result, (void *) nullptr, UnitDataFieldGetInteger);
	}

	void UnitDataSetIntegerByName(s_unit_datum *unit, const char * data_name, long data_value) {
		ObjectFieldSetImpl(g_unit_integer_fields, data_name, unit->unit, data_value, (void *) nullptr,
								 UnitDataFieldGetInteger);
	}

	//////////////////////////////////////////////////////////////////////////
	// Real
	void UnitDataGetRealByName(s_unit_datum *unit, const char * data_name, _Inout_ TypeHolder &result) {
		ObjectFieldGetImpl(g_unit_real_fields, data_name, unit->unit, result, (void *) nullptr, UnitDataFieldGetReal);
	}

	void UnitDataSetRealByName(s_unit_datum *unit, const char * data_name, real data_value) {
		ObjectFieldSetImpl(g_unit_real_fields, data_name, unit->unit, data_value, (void *) nullptr, UnitDataFieldGetReal);
	}

};

