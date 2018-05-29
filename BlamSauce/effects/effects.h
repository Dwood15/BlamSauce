#pragma once

#include <precompile.h>
#include "../math/matrix_math.h"
#include "../scenario/structures.h"
#include "particle/particle_systems.hpp"
#include "particle/particles.hpp"
#include "contrail/contrails.hpp"
#include "effect_definitions.hpp"

namespace Yelo::Effects {
		//////////////////////////////////////////////////////////////////////////
		// game-state: effects
		struct s_effect_datum : Memory::s_datum_base {
			// BIT(0) - ?
			// BIT(1) - loops
			// BIT(2) - loop stopped with event
			// BIT(3) - loop stopped without event
			// BIT(4) - ?
			// BIT(5) - ?
			// BIT(6) - nonviolent
			unsigned short flags;
			datum_index    definition_index;
			struct { // Enums::object_function_reference - 1
				short primary_scale;   // a
				short secondary_scale;   // b
				short change_color;
			}              object_function_indexes;
			unsigned short : 16;
			Yelo::Scenario::s_scenario_location location;
			real_rgb_color                      color;            // defaults to white
			real_vector3d                       transitional_velocity;
			//////////////////////////////////////////////////////////////////////////
			// no code which creates effects seems to actually set this struct up
			PAD(0, 12);
			// 0x30 UNKNOWN_TYPE(long)
			// 0x34 void (__cdecl* )(__out real_vector3d&, __out real_point3d&, ?) // last arg is the value at 0x30
			// 0x38 ?
			//////////////////////////////////////////////////////////////////////////
			datum_index                         object_index;         // object this effect was created on
			datum_index                         attached_object_index;   // object attached to this effect
			real                                scale_a, scale_b;
			short                               local_player_index;
			short                               event_index;
			UNKNOWN_TYPE(real);
			real                                event_delay_time;
			UNKNOWN_TYPE(real);
			datum_index                         location_datum_indices[Enums::k_maximum_effect_locations_count];
			byte                                particles_counts[Enums::k_maximum_effect_particles_per_event_count];
		}; static_assert(sizeof(s_effect_datum) == 0xFC);
		typedef Memory::DataArray<s_effect_datum, Enums::k_maximum_number_of_effects_per_map, Enums::k_maximum_number_of_effects_per_map_upgrade> effect_data_t;

		//////////////////////////////////////////////////////////////////////////
		// game-state: effect locations
		struct s_effect_location_datum : Memory::s_datum_base {
			// if != NONE and the sign bit is set, it's a first person weapon node
			short          node_index;
			datum_index    next_location_index;
			real_matrix4x3 node_matrix;
		}; static_assert(sizeof(s_effect_location_datum) == 0x3C);
		typedef Memory::DataArray<s_effect_location_datum, Enums::k_maximum_number_of_effect_locations_per_map, Enums::k_maximum_number_of_effect_locations_per_map_upgrade> effect_location_data_t;
	};

namespace Yelo::Effects
{
	contrail_data_t&					Contrails();
	contrail_point_data_t&				ContrailPoints();
	particle_data_t&					Particles();
	effect_data_t&						Effects();
	effect_location_data_t&				EffectLocations();
	particle_systems_data_t&			ParticleSystems();
	particle_system_particles_data_t&	ParticleSystemParticles();


	//////////////////////////////////////////////////////////////////////////
	// game-state: structure detail-objects
	struct s_structure_detail_objects_data : TStructImpl(42032)
	{
	};
	s_structure_detail_objects_data*		StructureDetailObjects();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// game-state: structure decals
	struct s_structure_decals_data : TStructImpl(4)
	{
	};
	s_structure_decals_data*				StructureDecals();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// game-state: breakable-surface globals
	struct s_breakable_surface_globals_data : TStructImpl(16900)
	{
	};
	s_breakable_surface_globals_data*		BreakableSurfaceGlobals();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// game-state: decals
	struct s_decals_datum : TStructImpl(56)
	{
	};
	typedef Memory::DataArray<s_decals_datum, 2048> decals_data_t;
	decals_data_t*						Decals();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// game-state: decal globals
	struct s_decal_globals_data : TStructImpl(10252)
	{
	};
	s_decal_globals_data*					DecalGlobals();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// game-state: decal vertex cache
	struct s_decal_vertex_cache_data
	{
		Memory::s_lruv_cache cache;
		Memory::s_data_array header;

		Memory::s_lruv_cache_block datums[2048];
	};
	s_decal_vertex_cache_data*			DecalVertexCache();
	//////////////////////////////////////////////////////////////////////////

	namespace Effects
	{
		contrail_data_t& Contrails()									DPTR_IMP_GET_BYREF(contrails);
		contrail_point_data_t& ContrailPoints()							DPTR_IMP_GET_BYREF(contrail_points);
		particle_data_t& Particles()									DPTR_IMP_GET_BYREF(particles);
		effect_data_t& Effects()										DPTR_IMP_GET_BYREF(effects);
		effect_location_data_t& EffectLocations()						DPTR_IMP_GET_BYREF(effect_locations);
		particle_systems_data_t& ParticleSystems()						DPTR_IMP_GET_BYREF(particle_systems);
		particle_system_particles_data_t& ParticleSystemParticles()		DPTR_IMP_GET_BYREF(particle_system_particles);

		s_structure_detail_objects_data* StructureDetailObjects()		DPTR_IMP_GET(structure_detail_objects);
		s_structure_decals_data* StructureDecals()						DPTR_IMP_GET(structure_decals);
		s_breakable_surface_globals_data* BreakableSurfaceGlobals()		DPTR_IMP_GET(breakable_surface_globals);
		decals_data_t* Decals()											DPTR_IMP_GET(decals);
		s_decal_globals_data* DecalGlobals()							DPTR_IMP_GET(decal_globals);
		s_decal_vertex_cache_data* DecalVertexCache()					DPTR_IMP_GET(decal_vertex_cache);


		static void InitializePerMapUpgrades()
		{
			render_particles_mods::Initialize();

			// For now, we're leaving these upgrades off
			*(reinterpret_cast<size_t *>(((reinterpret_cast<void *>(PTR_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECTS))))) =
				Enums::k_maximum_number_of_effects_per_map_upgrade;
			*(reinterpret_cast<size_t *>(((reinterpret_cast<void *>(PTR_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_EFFECT_LOCATIONS))))) =
				Enums::k_maximum_number_of_effect_locations_per_map_upgrade;

			*(reinterpret_cast<size_t *>(((reinterpret_cast<void *>(PTR_GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLE_SYSTEM_PARTICLES))))) =
				Enums::k_maximum_number_of_particle_system_particles_per_map_upgrade;
		}
		static void Initialize()
		{
			if(!CMDLINE_GET_PARAM(no_os_gfx).ParameterSet())
				InitializePerMapUpgrades();

			Memory::CreateHookRelativeCall(&Effects::Update, GET_FUNC_VPTR(EFFECTS_UPDATE_HOOK), Enums::_x86_opcode_retn);
		}

		static void Dispose()
		{
		}

		void __cdecl Update()
		{
		}
	};
};
