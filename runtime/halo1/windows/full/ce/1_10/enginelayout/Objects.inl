#pragma once

#include <cstdint>
#include "../../../../../../../BlamSauce/memory/upgrades/blam_memory_upgrades.hpp"

#ifdef ENGINE_DPTR
#undef ENGINE_DPTR
#endif

#ifdef ENGINE_PTR
#undef ENGINE_PTR
#endif

#ifdef FUNC_PTR
#undef FUNC_PTR
#endif

#define ENGINE_PTR(type, name, ...) static auto* const name = reinterpret_cast<type*>(__VA_ARGS__);
#define DUO_PTR(...) __VA_ARGS__
#define FUNC_PTR(name, value, ...) static auto const name  =  value
#define CAST_PTR(type, ptr)      reinterpret_cast<type>(ptr)

//////////////////////////////////////////////////////////////////////////
// Objects.cpp
static auto *const object_type_definitions = reinterpret_cast<s_object_type_definition ***>(K_OBJECT_TYPE_DEFINITIONS);;
static auto *const widget_type_definitions = reinterpret_cast<s_widget_type_definition **>(K_WIDGET_TYPE_DEFINITIONS);;

static auto **const widgets = reinterpret_cast<widget_data_t **>(K_WIDGETS);;
static auto **const flags = reinterpret_cast<flag_data_t **>(K_FLAGS);;
static auto **const antennas = reinterpret_cast<antenna_data_t **>(K_ANTENNAS);;
static auto **const glow = reinterpret_cast<glow_data_t **>(K_GLOW);;
static auto **const glow_particles = reinterpret_cast<glow_particles_data_t **>(K_GLOW_PARTICLES);;
static auto **const light_volumes = reinterpret_cast<light_volumes_data_t **>(K_LIGHT_VOLUMES);;
static auto **const lightnings = reinterpret_cast<lightnings_data_t **>(K_LIGHTNINGS);;

static auto **const cached_object_render_states = reinterpret_cast<Render::cached_object_render_states_data_t **>(K_CACHED_OBJECT_RENDER_STATES);;
static auto **const unit_globals = reinterpret_cast<s_unit_globals_data **>(K_UNIT_GLOBALS);;
static auto **const device_groups = reinterpret_cast<device_groups_data_t **>(K_DEVICE_GROUPS);;
static auto **const object_header = reinterpret_cast<object_header_data_t **>(K_OBJECT_HEADER);;
static auto **const objects_pool = reinterpret_cast<s_objects_pool_data **>(K_OBJECTS_POOL);;
static auto **const object_globals = reinterpret_cast<s_object_globals_data **>(K_OBJECT_GLOBALS);;
static auto **const object_name_list = reinterpret_cast<s_object_name_list_data **>(K_OBJECT_NAME_LIST);;

static auto **const collideable_object = reinterpret_cast<collideable_object_data **>(K_COLLIDEABLE_OBJECT);;
static auto **const cluster_collideable_object_reference = reinterpret_cast<cluster_collideable_object_reference_data_t **>(K_CLUSTER_COLLIDEABLE_OBJECT_REFERENCE);;
static auto **const collideable_object_cluster_reference = reinterpret_cast<collideable_object_cluster_reference_data_t **>(K_COLLIDEABLE_OBJECT_CLUSTER_REFERENCE);;
static auto **const noncollideable_object = reinterpret_cast<noncollideable_object_data **>(K_NONCOLLIDEABLE_OBJECT);;
static auto **const cluster_noncollideable_object_reference = reinterpret_cast<cluster_noncollideable_object_reference_data_t **>(K_CLUSTER_NONCOLLIDEABLE_OBJECT_REFERENCE);;
static auto **const noncollideable_object_cluster_reference = reinterpret_cast<noncollideable_object_cluster_reference_data_t **>(K_NONCOLLIDEABLE_OBJECT_CLUSTER_REFERENCE);;

static auto *const object_memory_pool_allocation_size = reinterpret_cast<size_t *>(K_OBJECT_MEMORY_POOL_ALLOCATION_SIZE);;

static auto const OBJECT_TYPES_PLACE_ALL_MOD_VEHI_REMAP = K_OBJECT_TYPES_PLACE_ALL_MOD_VEHI_REMAP;
static auto const OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP1 = K_OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP1;
static auto const OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP2 = K_OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP2;
static auto const OBJECTS_UPDATE_CALL = K_OBJECTS_UPDATE_CALL;
static auto const OBJECTS_UPDATE_HOOK = K_OBJECTS_UPDATE_HOOK;
static auto const OBJECTS_GARBAGE_COLLECTION = K_OBJECTS_GARBAGE_COLLECTION;
static auto const OBJECT_DAMAGE_OBJECT_BODY_HOOK = K_OBJECT_DAMAGE_OBJECT_BODY_HOOK;
static auto const BIPED_UPDATE_MOVING_HOOK = K_BIPED_UPDATE_MOVING_HOOK;
static auto const BIPED_JUMP_MOD_STUN_PENALTY_FIELD_REF = K_BIPED_JUMP_MOD_STUN_PENALTY_FIELD_REF;
static auto const OBJECT_DEPLETE_BODY_KILL_CHILD_HOOK = K_OBJECT_DEPLETE_BODY_KILL_CHILD_HOOK;
static auto const OBJECT_DEPLETE_BODY_KILL_CHILD_RETN = K_OBJECT_DEPLETE_BODY_KILL_CHILD_RETN;

	static const uintptr_t OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK =			K_OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK;
	static const uintptr_t OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK_RETURN =	K_OBJECT_DAMAGE_AFTERMATH__CALC_ACCEL_HOOK_RETURN;

	static const uintptr_t OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK =					K_OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK;
	static const uintptr_t OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN =			K_OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN;
	static const uintptr_t OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN_INVALID =	K_OBJECT_DAMAGE_AFTERMATH__UNIT_VALIDATE_INST_ACCEL_HOOK_RETURN_INVALID;

	namespace render_objects_mods
	{
		static uintptr_t K_MAXIMUM_RENDERED_OBJECTS_REFS_32bit[] = {
			K_MAXIMUM_RENDERED_OBJECTS_REF_32BIT_0,
			K_MAXIMUM_RENDERED_OBJECTS_REF_32BIT_1,
		};
		static uintptr_t K_MAXIMUM_RENDERED_OBJECTS_REFS_16bit[] = {
			K_MAXIMUM_RENDERED_OBJECTS_REF_16BIT_0,
		};
		static uintptr_t K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REFS[] = {
			K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REF_0,
			K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REF_1,
			K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REF_2,
			K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REF_3,
		};

		static auto const OBJECT_NEW_SET_SHADOW_FLAG_HOOK = K_OBJECT_NEW_SET_SHADOW_FLAG_HOOK;
		static auto const OBJECT_NEW_SET_SHADOW_FLAG_RETN = K_OBJECT_NEW_SET_SHADOW_FLAG_RETN;
		static void* K_OBJECT_DISABLE_SHADOW_CAST_OVERRIDES[] = {
			reinterpret_cast<void *>(K_OBJECT_DISABLE_SHADOW_CAST_OVERRIDE_0),
			reinterpret_cast<void *>(K_OBJECT_DISABLE_SHADOW_CAST_OVERRIDE_1),
			reinterpret_cast<void *>(K_OBJECT_DISABLE_SHADOW_CAST_OVERRIDE_2),
		};
	};

	namespace Weapon
	{
		static auto const FIRST_PERSON_WEAPON_RENDER_UPDATE = K_FIRST_PERSON_WEAPON_RENDER_UPDATE;
		static auto const RENDER_WINDOW_CALL_HOOK_FIRST_PERSON_WEAPON_RENDER_UPDATE = K_RENDER_WINDOW_CALL_HOOK_FIRST_PERSON_WEAPON_RENDER_UPDATE;
	};


//////////////////////////////////////////////////////////////////////////
// Equipment.cpp


//////////////////////////////////////////////////////////////////////////
// Units.cpp
	static uint K_UNIT_ZOOM_LEVEL_OFFSET_REFS[] = {
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_0,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_1,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_2,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_3,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_4,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_5,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_6,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_7,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_8,
		K_UNIT_ZOOM_LEVEL_OFFSET_REF_9,
	};
	static uint K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REFS[] = {
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_0,
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_1,
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_2,
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_3,
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_4,
		K_UNIT_DESIRED_ZOOM_LEVEL_OFFSET_REF_5,
	};

	static uint K_NUMBER_OF_UNIT_GRENADE_TYPES_REFS[] = {
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_0,
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_1,
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_2,
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_3,
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_4,
		K_NUMBER_OF_UNIT_GRENADE_TYPES_REF_5,
	};
	static uint K_MAXIMUM_UNIT_GRENADE_INDEX_REFS[] = {
		K_MAXIMUM_UNIT_GRENADE_INDEX_REF_0,
		K_MAXIMUM_UNIT_GRENADE_INDEX_REF_1,
		K_MAXIMUM_UNIT_GRENADE_INDEX_REF_2,
	};

static auto const ACTOR_DIED_UNIT_GRENADE_COUNT_MOD = K_ACTOR_DIED_UNIT_GRENADE_COUNT_MOD;
static auto const PLAYER_ADD_EQUIPMENT_UNIT_GRENADE_COUNT_MOD = K_PLAYER_ADD_EQUIPMENT_UNIT_GRENADE_COUNT_MOD;
static auto const BIPED_NEW_FROM_NETWORK_UNIT_GRENADE_COUNT_MOD = K_BIPED_NEW_FROM_NETWORK_UNIT_GRENADE_COUNT_MOD;
static auto const BIPED_UPDATE_BASELINE_UNIT_GRENADE_COUNT_MOD1 = K_BIPED_UPDATE_BASELINE_UNIT_GRENADE_COUNT_MOD1;
static auto const BIPED_UPDATE_BASELINE_UNIT_GRENADE_COUNT_MOD2 = K_BIPED_UPDATE_BASELINE_UNIT_GRENADE_COUNT_MOD2;
static auto const BIPED_BUILD_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD1 = K_BIPED_BUILD_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD1;
static auto const BIPED_BUILD_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD2 = K_BIPED_BUILD_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD2;
static auto const BIPED_PROCESS_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD = K_BIPED_PROCESS_UPDATE_DELTA_UNIT_GRENADE_COUNT_MOD;
static auto const BIPED_UPDATE_CHECK_PARENT_UNIT_TYPE = K_BIPED_UPDATE_CHECK_PARENT_UNIT_TYPE;
static auto const UNIT_DAMAGE_AFTERMATH_CALL = K_UNIT_DAMAGE_AFTERMATH_CALL;

	//////////////////////////////////////////////////////////////////////////
	// Units.SeatBoarding
	static auto const UNIT_CAN_ENTER_SEAT_HOOK = K_UNIT_CAN_ENTER_SEAT_HOOK;

	//////////////////////////////////////////////////////////////////////////
	// Units.SeatDamage
	static auto const BIPED_SEATED_MELEE_HOOK = K_BIPED_SEATED_MELEE_HOOK;
static auto const BIPED_SEATED_MELEE_RETN = K_BIPED_SEATED_MELEE_RETN;
static auto const UNIT_THROW_GRENADE_RELEASE_HOOK = K_UNIT_THROW_GRENADE_RELEASE_HOOK;
static auto const WEAPON_PREVENTS_GRENADE_THROWING_HOOK = K_WEAPON_PREVENTS_GRENADE_THROWING_HOOK;
static auto const WEAPON_PREVENTS_GRENADE_THROWING_RETN = K_WEAPON_PREVENTS_GRENADE_THROWING_RETN;

	//////////////////////////////////////////////////////////////////////////
	// Units.Animations
	static auto const ANIMATION_STATE_DEFINED_KEYFRAME_HOOK = K_ANIMATION_STATE_DEFINED_KEYFRAME_HOOK;
static auto const ANIMATION_STATE_DEFINED_KEYFRAME_STOCK_RETN = K_ANIMATION_STATE_DEFINED_KEYFRAME_STOCK_RETN;
static auto const ANIMATION_STATE_DEFINED_KEYFRAME_SKIP_RETN = K_ANIMATION_STATE_DEFINED_KEYFRAME_SKIP_RETN;

static auto const ANIMATION_STATE_FINAL_KEYFRAME_HOOK = K_ANIMATION_STATE_FINAL_KEYFRAME_HOOK;
static auto const ANIMATION_STATE_FINAL_KEYFRAME_STOCK_RETN = K_ANIMATION_STATE_FINAL_KEYFRAME_STOCK_RETN;
static auto const ANIMATION_STATE_FINAL_KEYFRAME_SKIP_RETN = K_ANIMATION_STATE_FINAL_KEYFRAME_SKIP_RETN;

	static void** K_UNIT_ANIMATION_STATE_INTERRUPTABLE_CALLS[] = {
		reinterpret_cast<void **>(K_UNIT_ANIMATION_STATE_INTERRUPTABLE_CALL_0),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_STATE_INTERRUPTABLE_CALL_1),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_STATE_INTERRUPTABLE_CALL_2),
	};
	static void** K_UNIT_ANIMATION_BUSY_CALLS[] = {
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_0),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_1),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_2),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_3),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_4),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_5),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_6),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_7),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_8),
		reinterpret_cast<void **>(K_UNIT_ANIMATION_BUSY_CALL_9),
	};
static auto const UNIT_ANIMATION_STATE_LOOPS_CALL = K_UNIT_ANIMATION_STATE_LOOPS_CALL;
static auto const UNIT_ANIMATION_WEAPON_IK_CALL = K_UNIT_ANIMATION_WEAPON_IK_CALL;
static auto const UNIT_ANIMATION_VEHICLE_IK_CALL = K_UNIT_ANIMATION_VEHICLE_IK_CALL;
