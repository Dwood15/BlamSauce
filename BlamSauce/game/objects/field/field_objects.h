#pragma once

#include <precompile.h>

namespace Yelo::Objects {
	s_object_type_definition **ObjectTypeDefinitions();

	s_widget_type_definition *WidgetTypeDefinitions();

	Render::cached_object_render_states_data_t *CachedObjectRenderStates();

	s_unit_globals_data *UnitGlobals();

	typedef Memory::DataArray<s_device_groups_datum, 1024> device_groups_data_t;

	device_groups_data_t &DeviceGroups();

	/////////////////////////////////////////////////////////////////////////
	// pad?
	struct collideable_object_data : TStructImpl(2048) {};

	collideable_object_data *CollideableObject();

	struct cluster_collideable_object_reference_datum : TStructImpl(12) {};
	typedef Memory::DataArray<cluster_collideable_object_reference_datum, 2048> cluster_collideable_object_reference_data_t;

	cluster_collideable_object_reference_data_t &ClusterCollideableObjectReference();

	struct collideable_object_cluster_reference_datum : TStructImpl(12) {};
	typedef Memory::DataArray<collideable_object_cluster_reference_datum, 2048> collideable_object_cluster_reference_data_t;

	collideable_object_cluster_reference_data_t &CollideableObjectClusterReference();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//
	// pad?
	struct noncollideable_object_data : TStructImpl(2048) {};

	noncollideable_object_data *NoncollideableObject();

	struct cluster_noncollideable_object_reference_datum : TStructImpl(12) {};
	typedef Memory::DataArray<cluster_noncollideable_object_reference_datum, 2048> cluster_noncollideable_object_reference_data_t;

	cluster_noncollideable_object_reference_data_t &ClusterNoncollideableObjectReference();

	struct noncollideable_object_cluster_reference_datum : TStructImpl(12) {};
	typedef Memory::DataArray<noncollideable_object_cluster_reference_datum, 2048> noncollideable_object_cluster_reference_data_t;

	noncollideable_object_cluster_reference_data_t &NoncollideableObjectClusterReference();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Object widgets
	typedef Memory::DataArray<s_widget_datum, 64> widget_data_t;

	widget_data_t &Widgets();

	struct s_flag_datum : TStructImpl(5820) {};
	typedef Memory::DataArray<s_flag_datum, 2> flag_data_t;

	flag_data_t &Flags();

	struct s_antenna_datum : TStructImpl(700) {};
	typedef Memory::DataArray<s_antenna_datum, 12> antenna_data_t;

	antenna_data_t &Antennas();

	struct s_glow_datum : TStructImpl(604) {};
	typedef Memory::DataArray<s_glow_datum, 8> glow_data_t;

	glow_data_t &Glow();

	struct s_glow_particles_datum : TStructImpl(100) {};
	typedef Memory::DataArray<s_glow_particles_datum, 512> glow_particles_data_t;

	glow_particles_data_t &GlowParticles();

	struct s_light_volumes_datum : Memory::s_datum_base_aligned {
		datum_index definition_index; // msg2
	}; static_assert(sizeof(s_light_volumes_datum) == 0x8);
	typedef Memory::DataArray<s_light_volumes_datum, 256> light_volumes_data_t;

	light_volumes_data_t &LightVolumes();

	struct s_lightnings_datum : Memory::s_datum_base_aligned {
		datum_index definition_index; // elec
	}; static_assert(sizeof(s_lightnings_datum) == 0x8);
	typedef Memory::DataArray<s_lightnings_datum, 256> lightnings_data_t;

	lightnings_data_t &Lightnings();
	//////////////////////////////////////////////////////////////////////////

	// Turn the engine's vehicle remapper on or off
	void VehicleRemapperEnable(bool enabled) {
		// jnz eip+2+10
		static const byte k_enable_code[]  = {Enums::_x86_opcode_jnz_short, 0x0A};
		// nop, nop
		static const byte k_disable_code[] = {Enums::_x86_opcode_nop, Enums::_x86_opcode_nop};

		Memory::WriteMemory(GET_FUNC_VPTR(OBJECT_TYPES_PLACE_ALL_MOD_VEHI_REMAP), (enabled ? k_enable_code : k_disable_code), sizeof(k_enable_code));
	}

	//////////////////////////////////////////////////////////////////////////
#include <YeloLib/Halo1/render/render_objects_upgrades.inl>

	s_object_type_definition** ObjectTypeDefinitions()							PTR_IMP_GET(object_type_definitions);
	s_widget_type_definition*  WidgetTypeDefinitions()							PTR_IMP_GET(widget_type_definitions);

	widget_data_t& Widgets()													DPTR_IMP_GET_BYREF(widgets);
	flag_data_t& Flags()														DPTR_IMP_GET_BYREF(flags);
	antenna_data_t& Antennas()													DPTR_IMP_GET_BYREF(antennas);
	glow_data_t& Glow()															DPTR_IMP_GET_BYREF(glow);
	glow_particles_data_t& GlowParticles()										DPTR_IMP_GET_BYREF(glow_particles);
	light_volumes_data_t& LightVolumes()										DPTR_IMP_GET_BYREF(light_volumes);
	lightnings_data_t& Lightnings()												DPTR_IMP_GET_BYREF(lightnings);


	Render::cached_object_render_states_data_t* CachedObjectRenderStates()		DPTR_IMP_GET(cached_object_render_states);
	s_unit_globals_data* UnitGlobals()											DPTR_IMP_GET(unit_globals);
	device_groups_data_t& DeviceGroups()										DPTR_IMP_GET_BYREF(device_groups);
	object_header_data_t& ObjectHeader()										DPTR_IMP_GET_BYREF(object_header);
	s_objects_pool_data* ObjectsPool()											DPTR_IMP_GET(objects_pool);
	s_object_globals_data* ObjectGlobals()										DPTR_IMP_GET(object_globals);
	s_object_name_list_data* ObjectNameList()									DPTR_IMP_GET(object_name_list);


	collideable_object_data* CollideableObject()								DPTR_IMP_GET(collideable_object);
	cluster_collideable_object_reference_data_t& ClusterCollideableObjectReference()		DPTR_IMP_GET_BYREF(cluster_collideable_object_reference);
	collideable_object_cluster_reference_data_t& CollideableObjectClusterReference()		DPTR_IMP_GET_BYREF(collideable_object_cluster_reference);

	noncollideable_object_data* NoncollideableObject()							DPTR_IMP_GET(noncollideable_object);
	cluster_noncollideable_object_reference_data_t& ClusterNoncollideableObjectReference()	DPTR_IMP_GET_BYREF(cluster_noncollideable_object_reference);
	noncollideable_object_cluster_reference_data_t& NoncollideableObjectClusterReference()	DPTR_IMP_GET_BYREF(noncollideable_object_cluster_reference);

#include "Objects/Objects.WeaponSettings.inl"
#include "Objects/Objects.VehicleSettings.inl"
	///////////////////////////////////////////////////////////////////////////


	class c_settings_container : public Yelo::Configuration::c_configuration_container {
	public:
		Configuration::c_configuration_value<bool> m_vehicle_remapper_enabled;

		c_settings_container() : Configuration::c_configuration_container("Objects"), m_vehicle_remapper_enabled("VehicleRemapperEnabled", true) {}

	protected:
		const std::vector<i_configuration_value *const> GetMembers() final override {
			return std::vector<i_configuration_value *const>{&m_vehicle_remapper_enabled};
		}
	};

	class c_settings_objects : public Settings::c_settings_singleton<c_settings_container, c_settings_objects> {
	public:
		void PostLoad() final override {
			VehicleRemapperEnable(Get().m_vehicle_remapper_enabled);
		}
	};

	static void InitializeScripting()
	{
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_objects_distance_to_object, scripting_objects_distance_to_object_evaluate);

		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_object_data_get_real, scripting_object_data_get_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_object_data_set_real, scripting_object_data_set_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_object_data_set_vector, scripting_object_data_set_vector_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_object_data_save_vector, scripting_object_data_save_vector_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_weapon_data_get_real, scripting_weapon_data_get_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_weapon_data_set_real, scripting_weapon_data_set_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_weapon_data_magazine_get_integer, scripting_weapon_data_magazine_get_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_weapon_data_magazine_set_integer, scripting_weapon_data_magazine_set_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_weapon_data_trigger_set_real, scripting_weapon_data_trigger_set_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_unit_data_get_object, scripting_unit_data_get_object_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_unit_data_get_integer, scripting_unit_data_get_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_unit_data_set_integer, scripting_unit_data_set_integer_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_unit_data_get_real, scripting_unit_data_get_real_evaluate);
		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_unit_data_set_real, scripting_unit_data_set_real_evaluate);

		Scripting::InitializeScriptFunctionWithParams(Enums::_hs_function_vehicle_remapper_enabled, scripting_vehicle_remapper_enabled_evaluate);
	}

	bool __cdecl ShouldKillChildObject(const s_object_datum* object_datum)
	{
		if(object_datum->object.VerifyType(s_unit_datum::k_object_types_mask))
		{
			auto& unit_datum = *CAST_PTR(const s_unit_datum*, object_datum);
			if(unit_datum.unit.vehicle_seat_index != NONE)
			{
				auto* seat_extension_definition = GetSeatExtensionDefinition(unit_datum.object.parent_object_index, unit_datum.unit.vehicle_seat_index);
				if(seat_extension_definition)
				{
					return !TEST_FLAG(seat_extension_definition->flags, Flags::_unit_seat_extensions_flags_prevent_death_when_unit_dies);
				}
			}
		}

		return true;
	}

	__declspec(naked) static void ObjectDepleteBodyKillChildHook() {
		static const uintptr_t RETN_ADDRESS = GET_FUNC_PTR(OBJECT_DEPLETE_BODY_KILL_CHILD_RETN);

		_asm
			{
				push	eax
			push	ecx
			push	edx

			push	eax
			call	ShouldKillChildObject
			add		esp, 4
			cmp		al, 0

			pop		edx
			pop		ecx
			pop		eax

			jz		skip_kill
			or		[eax + 106h], cx

			skip_kill:
			jmp		RETN_ADDRESS
			};
	}

	void __cdecl ObjectsUpdate()
	{
		AI::ObjectsUpdate();
		Units::ObjectsUpdate();

		blam::objects_update();
	}

	void Initialize()
	{
		c_settings_objects::Register(Settings::Manager());

		Memory::WriteRelativeJmp(&Objects::Update, GET_FUNC_VPTR(OBJECTS_UPDATE_HOOK), false);

		if(!CMDLINE_GET_PARAM(no_os_gfx).ParameterSet())
			render_objects_mods::Initialize();

		Weapon::Initialize();
		Equipment::Initialize();
		Units::Initialize();

		InitializeScripting();
		InitializeObjectFieldDefinitions();
		ObjectDamageAftermath_UpgradesInitialize();

		Memory::WriteRelativeCall(&ObjectsUpdate, GET_FUNC_VPTR(OBJECTS_UPDATE_CALL), true);
		Memory::WriteRelativeJmp(&ObjectDepleteBodyKillChildHook, GET_FUNC_VPTR(OBJECT_DEPLETE_BODY_KILL_CHILD_HOOK), true);
	}

	void Dispose()
	{
		Units::Dispose();

		Weapon::Dispose();

		c_settings_objects::Unregister(Settings::Manager());
	}

	static void UseBipedJumpPenalty(bool use_fix) {
		using namespace TagGroups;

		const size_t k_game_globals_player_stun_offset                 = FIELD_OFFSET(s_game_globals_player_information, stun);
		const size_t k_game_globals_player_stun_turning_penalty_offset = k_game_globals_player_stun_offset + FIELD_OFFSET(s_game_globals_player_information::_stun, turning_penalty);
		const size_t k_game_globals_player_stun_jumping_penalty_offset = k_game_globals_player_stun_offset + FIELD_OFFSET(s_game_globals_player_information::_stun, jumping_penalty);

		static_assert(k_game_globals_player_stun_turning_penalty_offset == 0x84);
		static_assert(k_game_globals_player_stun_jumping_penalty_offset == 0x88);
		// stock code uses turning penalty for whatever reason
		*CAST_PTR(size_t*, GET_FUNC_VPTR(BIPED_JUMP_MOD_STUN_PENALTY_FIELD_REF)) = use_fix ? k_game_globals_player_stun_jumping_penalty_offset : k_game_globals_player_stun_turning_penalty_offset;
	}

	static void ObjectsUpdateIgnorePlayerPvs(bool use_fix)
	{
		typedef Memory::s_memory_change_data<GET_FUNC_VPTR(OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP1), 1+1+sizeof(uintptr_t)> nop1_t;
		typedef Memory::s_memory_change_data<GET_FUNC_VPTR(OBJECTS_UPDATE__OBJECT_IN_PLAYER_PVS_NOP2), 2> nop2_t;

		if(use_fix) {
			nop1_t::MemoryApplyNopCodes();
			nop2_t::MemoryApplyNopCodes();
		}
		else {
			nop1_t::MemoryApplyUndo();
			nop2_t::MemoryApplyUndo();
		}
	}

	void InitializeForNewMap() {
		bool objects_update_ignore_player_pvs = blam::global_scenario_get()->type == Enums::_scenario_type_main_menu &&
															 TEST_FLAG(Scenario::GetYelo()->flags, Flags::_project_yellow_game_updates_ignore_player_pvs_hack_bit);
		ObjectsUpdateIgnorePlayerPvs(objects_update_ignore_player_pvs);

		bool use_jump_penalty_fix = TEST_FLAG(Scenario::GetYeloGlobals()->flags, Flags::_project_yellow_globals_force_game_to_use_stun_jumping_penalty_bit);
		UseBipedJumpPenalty(use_jump_penalty_fix);

		Units::InitializeForNewMap();
	}

	void DisposeFromOldMap() {
		Units::DisposeFromOldMap();
	}

	void __cdecl Update() {
		static const uintptr_t OBJECTS_GARBAGE_COLLECTION = GET_FUNC_PTR(OBJECTS_GARBAGE_COLLECTION);
		_asm{
			call   OBJECTS_GARBAGE_COLLECTION
		}

		// Do custom code here:
	}

	void InitializeForYeloGameState(bool enabled) {
		size_t *omp_allocation_size = GET_PTR2(object_memory_pool_allocation_size);
		//			*omp_allocation_size = Enums::k_object_memory_pool_allocation_size;
		//			if(enabled) *omp_allocation_size += Enums::k_game_state_allocation_size_object_memory_pool_upgrade;

		Units::InitializeForYeloGameState(enabled);
	}

	// Get the current state of the engine's vehicle remapper
	bool VehicleRemapperEnabled() {
		return c_settings_objects::Instance()->m_vehicle_remapper_enabled;
	}
};
namespace Yelo::blam
{
	s_object_data* object_get(datum_index object_index)
	{
		return Objects::ObjectHeader()[object_index]->_object;
	}
};
#include "Objects/Objects.WeaponSettings.hpp"
