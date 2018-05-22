/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/

namespace render_objects_mods
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Queries whether an object should cast a shadow. </summary>
	///
	/// <param name="object_definition">	The object definition. </param>
	///
	/// <returns>	True if the object should cast shadows. </returns>
	static bool __cdecl QueryObjectCastsShadow(const TagGroups::s_object_definition* object_definition)
	{
		bool cast_shadow = false;
		switch(object_definition->object.runtime_object_type)
		{
			case Enums::_object_type_scenery:
			case Enums::_object_type_machine:
			case Enums::_object_type_control:
			case Enums::_object_type_light_fixture:
			case Enums::_object_type_placeholder:
			case Enums::_object_type_sound_scenery:
				cast_shadow = TEST_FLAG(object_definition->object.flags, Flags::_object_definition_cast_shadow_by_default_yelo_bit);
				break;
			default:
				cast_shadow = true;
		}

		return (cast_shadow && !TEST_FLAG(object_definition->object.flags, Flags::_object_definition_does_not_cast_shadow_bit));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Hook for object_new that sets the shadow casting flag. </summary>
	static API_FUNC_NAKED void ObjectNewSetShadowFlag_Hook()
	{
		static uintptr_t RETN_ADDRESS = GET_FUNC_PTR(OBJECT_NEW_SET_SHADOW_FLAG_RETN);

		_asm
		{
			push	eax
			push	edx

			push	edi
			call	QueryObjectCastsShadow
			add		esp, 4

			test	al, al
			jnz		cast_shadows
			or		dword ptr [esi+10h], 40000h

		cast_shadows:
			pop		edx
			pop		eax

			jmp		RETN_ADDRESS
		};
	}

	static void Initialize()
	{
		static datum_index rendered_objects[Enums::k_maximum_rendered_objects_upgrade];

		for(auto ptr : K_MAXIMUM_RENDERED_OBJECTS_REFS_32bit)
			*CAST_PTR(long*,ptr) = Enums::k_maximum_rendered_objects_upgrade;
		for(auto ptr : K_MAXIMUM_RENDERED_OBJECTS_REFS_16bit)
			*CAST_PTR(short*,ptr) = Enums::k_maximum_rendered_objects_upgrade;

		for(auto ptr : K_RENDER_OBJECT_GLOBALS__RENDERED_OBJECTS_REFS)
			*CAST_PTR(datum_index**,ptr) = rendered_objects;

		Memory::WriteRelativeJmp(&ObjectNewSetShadowFlag_Hook, GET_FUNC_VPTR(OBJECT_NEW_SET_SHADOW_FLAG_HOOK), true);

		// Nop-out the instructions that disable shadows for devices, scenery and sound scenery
		for(auto ptr : K_OBJECT_DISABLE_SHADOW_CAST_OVERRIDES)
		{
			static const byte k_nop_opcode[] = 
			{
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop,
				Enums::_x86_opcode_nop
			};

			Memory::WriteMemory(ptr, k_nop_opcode);
		}
	}
};


namespace render_particles_mods
{
	struct s_rendered_particle
	{
		short particle_index;
		short particle_definition_index; // datum's 0x4 field
		short particle_datum_field_2C;
		bool particle_datum_flags_bit5;
				unsigned char : 8;
	}; static_assert( sizeof(s_rendered_particle) == 8 );
	static s_rendered_particle rendered_particles[Enums::k_maximum_number_of_particles_per_map_upgrade];

	//////////////////////////////////////////////////////////////////////////
	// Game client instructions
	NAKED_FUNC_WRITER_ASM_BEGIN(lea_ecx_rendered_particles_mul8)
	lea ecx, rendered_particles[ecx*8]					NAKED_FUNC_WRITER_ASM_END();
	NAKED_FUNC_WRITER_ASM_BEGIN(lea_eax_rendered_particles_mul8)
	lea eax, rendered_particles[eax*8]					NAKED_FUNC_WRITER_ASM_END();
	NAKED_FUNC_WRITER_ASM_BEGIN(lea_ecx_rendered_particles)
	lea ecx, rendered_particles
	nop													NAKED_FUNC_WRITER_ASM_END();
	NAKED_FUNC_WRITER_ASM_BEGIN(lea_eax_rendered_particles_add4)
	lea eax, rendered_particles.particle_datum_field_2C
		nop													NAKED_FUNC_WRITER_ASM_END();
	NAKED_FUNC_WRITER_ASM_BEGIN(lea_eax_rendered_particles)
	lea eax, rendered_particles
	nop													NAKED_FUNC_WRITER_ASM_END();

	static void Initialize()
	{
		Memory::c_naked_func_writer<lea_ecx_rendered_particles_mul8>::
		Write( K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[0] );
		Memory::c_naked_func_writer<lea_eax_rendered_particles_mul8>::
		Write( K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[1] );
		Memory::c_naked_func_writer<lea_ecx_rendered_particles>::
		Write( K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[2] );
		Memory::c_naked_func_writer<lea_eax_rendered_particles_add4>::
		Write( K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[3] );
		Memory::c_naked_func_writer<lea_eax_rendered_particles>::
		Write( K_RENDER_PARTICLES_RENDERED_PARTICLES_ARRAY_ADDRESS_LIST[4] );

		*CAST_PTR(size_t*, GET_FUNC_VPTR(GAME_INITIALIZE_MOD_PER_MAP_UPGRADE_PARTICLES)) =
			Enums::k_maximum_number_of_particles_per_map_upgrade;
	}
};
