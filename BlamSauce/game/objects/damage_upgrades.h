namespace Yelo::Objects {
	static void ObjectDamageAftermath_CalculateAcceleration(const TagGroups::s_object_definition *object_definition,
																			  const TagGroups::s_damage_effect_definition *damage_definition,
																			  const real_vector3d &distance_from_object,
																			  real_vector3d &vector) {

		if (damage_definition->damage.UseInstantaneousAcceleration3D()) {
			vector = damage_definition->damage.instantaneous_acceleration3d;
		} else {
			real scalar = damage_definition->damage.instantaneous_acceleration;
			vector.Set(scalar, scalar, scalar);
		}

		vector *= object_definition->object.acceleration_scale;

		vector *= K_SECONDS_PER_TICK;

		vector.i *= distance_from_object.i;
		vector.j *= distance_from_object.j;
		vector.k *= distance_from_object.k;
	}

	__declspec(naked) static void __cdecl ObjectDamageAftermath_CalculateAccelerationHook() {
		using namespace Enums;

		__asm {
		fstp   st // undo the object_definition->object.acceleration_scale load

		push   ecx // object type
		push   PLATFORM_ENGINE_VALUE(ebp, ebx) // object datum

		lea      ecx,[esp+0x30+8+ (-0x18)] // acceleration
		lea      eax,[esp+0x30+8+ (-0x0C)] // distance_from_object
		push   ecx
		push   eax
		push   PLATFORM_ENGINE_VALUE(ebx, edx) // damage def
		push   esi // object def
		call   ObjectDamageAftermath_CalculateAcceleration

		pop      PLATFORM_ENGINE_VALUE(ebp, ebx)
		pop      ecx

		movsx   eax, cx
		cmp      eax, _object_type_projectile
		jmp      OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK_RETURN
		}
	}

	static bool ObjectDamageAftermath_InstantaneousAccelerationIsInvalidForUnit(const TagGroups::s_damage_effect_definition *damage_definition) {
		auto lte_eps     = damage_definition->damage.instantaneous_acceleration <= K_REAL_EPSILON;
		auto gte_eps_neg = damage_definition->damage.instantaneous_acceleration >= -K_REAL_EPSILON;

		return (lte_eps && gte_eps_neg);
	}

	__declspec(naked) static void __cdecl ObjectDamageAftermath_UnitValidateInstantaneousAccelerationHook() {
		__asm {
		push   ecx // object type

		push   PLATFORM_ENGINE_VALUE(ebx, edx)
		call   ObjectDamageAftermath_InstantaneousAccelerationIsInvalidForUnit

		pop      ecx

		test   al, al
		jnz      invalid_inst_accel
		jmp      OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN

		invalid_inst_accel:
		jmp      OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN_INVALID
		}
	}

	static void ObjectDamageAftermath_UpgradesInitialize() {
		Memory::WriteRelativeJmp(ObjectDamageAftermath_CalculateAccelerationHook, CAST_PTR(void * , OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK), true);

		Memory::WriteRelativeJmp(ObjectDamageAftermath_UnitValidateInstantaneousAccelerationHook, CAST_PTR(void * , OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK), true);
	}
};

