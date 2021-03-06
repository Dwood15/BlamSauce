// comment the following to just use the parameters as-is
// instead of copying to the stack. I believe there was some 
// concurrency issues originally which caused me to use local 
// buffers instead...
#define ENGINE_FUNCTIONS_USE_LOCAL
enum { k_engine_function_string_buffer_size = 512, };

#define API_FUNC_NAKED_END_NO_STACK_POP()	\
		__asm pop	ebp						\
		__asm retn							\
	}

namespace Yelo
{

	namespace Engine
	{
		namespace Cache
		{
			__declspec(naked) bool FileReadRequest(/*datum_index tag_index,*/
				uint offset_, uint size_, void* buffer, const Yelo::Cache::s_cache_file_request_params& params,
				bool block, Enums::cache_file_request_source source)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(CACHE_FILE_READ_REQUEST);

				API_FUNC_NAKED_START()
					push	esi
					xor		eax, eax

					movzx	eax, source
					push	eax
					movzx	eax, block
					push	eax
					mov		esi, params
					push	buffer
					push	size_
					push	offset_
					call	FUNCTION
					add		esp, 4 * 5

					pop		esi
					API_FUNC_NAKED_END(6); // not including the unused tag_index
			}
		};

		namespace Effects
		{
			void __declspec(naked) NewOnObjectMarker(datum_index effect_definition_index, datum_index object_index, const char * marker_name)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(EFFECT_NEW_ON_OBJECT_MARKER);

				API_FUNC_NAKED_START()
					push	esi
					push	edi
					push	ecx

					mov		ecx, marker_name
					push	ecx
					mov		esi, object_index
					mov		edi, effect_definition_index
					call	FUNCTION
					add		esp, 4 * 1

					pop		ecx
					pop		edi
					pop		esi
				API_FUNC_NAKED_END(3)
			}
		};

		namespace HS
		{
			void ObjectListAdd(datum_index object_list, datum_index object_index)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(OBJECT_LIST_ADD);

				if(object_list.IsNull()) return;

				__asm {
					push	object_index
					mov		eax, object_list
					call	FUNCTION
					add		esp, 4 * 1
				}
			}
		};

		namespace Networking
		{
			#include "Game/EngineFunctions.Networking.inl"
		};

		namespace Objects
		{
			#include "Game/EngineFunctions.Objects.inl"
		};

		namespace Players
		{
			#include "Game/EngineFunctions.Players.inl"
		};

		namespace Scenario
		{
			bool TriggerVolumeTestPoint(long trigger_volume_index, const real_point3d& point)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(SCENARIO_TRIGGER_VOLUME_TEST_POINT);

				__asm {
					mov		ecx, point
					mov		eax, trigger_volume_index
					call	FUNCTION
				}
			}

			bool TriggerVolumeTestObject(long trigger_volume_index, datum_index object)
			{
				if(object.IsNull())
					return false;

				Yelo::Objects::s_object_data* obj = Yelo::Objects::ObjectHeader()[object]->_object;

				return TriggerVolumeTestPoint(trigger_volume_index, obj->center);
			}
		};

		namespace TagGroups
		{
			void PredictResources(TagBlock<Yelo::TagGroups::predicted_resource>& resources_block)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(PHYSICAL_MEMORY_MAP_PREDICT_RESOURCES);

				__asm {
					push	esi

					mov		esi, resources_block
					call	FUNCTION

					pop		esi
				}
			}

			datum_index TagLoaded(tag group_tag, const char * name)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(TAG_LOADED);

#if defined(ENGINE_FUNCTIONS_USE_LOCAL)
				char local[256];
				memset(local, 0, sizeof(local));
				strcpy_s(local, name);
#else
				const char * local = name;
#endif

				__asm {
					push	edi

#if defined(ENGINE_FUNCTIONS_USE_LOCAL)
					lea		eax, local
#else
					mov		eax, local
#endif
					push	eax
					mov		edi, group_tag
					call	FUNCTION
					add		esp, 4 * 1

					pop		edi
				}
			}

			wconst char * UnicodeStringListGetString(datum_index ustr, long index)
			{
				static const uintptr_t FUNCTION = GET_FUNC_PTR(UNICODE_STRING_LIST_GET_STRING);

				__asm {
					mov		edx, index
					mov		ecx, ustr
					call	FUNCTION
				}
			}
		};
	};

	//////////////////////////////////////////////////////////////////////////
	// ai
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// actors.c
		__declspec(naked) void __cdecl actor_delete(datum_index actor_index, bool is_dead)
		{
				static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_DELETE);

				API_FUNC_NAKED_START()
					pushad

					movzx	eax, is_dead
					push	eax
					mov		ebx, actor_index
					call	FUNCTION
					add		esp, 4

					popad
					pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl actor_update(const datum_index actor_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_UPDATE);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx
				push	esi

				mov		esi, actor_index
				call	FUNCTION

				pop		esi
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl actor_customize_unit(const datum_index actor_variant, const datum_index unit_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_CUSTOMIZE_UNIT);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx

				mov		eax, actor_variant
				push	unit_index
				call	FUNCTION
				add		esp, 4
				
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl actor_set_active(const datum_index actor_index, const bool active)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_SET_ACTIVE);

			API_FUNC_NAKED_START()
				push	eax
				push	edi

				xor		eax, eax
				mov		al, active
				mov		edi, actor_index
				call	FUNCTION

				pop		edi
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl actor_set_dormant(const datum_index actor_index, const bool dormant)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_SET_DORMANT);

			API_FUNC_NAKED_START()
				pushad

				xor		ebx, ebx
				mov		bl, dormant
				mov		eax, actor_index
				call	FUNCTION

				popad
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl actor_delete_props(const datum_index actor_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_DELETE_PROPS);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl actor_freeze(const datum_index actor_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_FREEZE);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx

				mov		eax, actor_index
				call	FUNCTION
				
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		void __cdecl actor_braindead(const datum_index actor_index, const bool braindead)
		{
			const auto actor_data = AI::Actors()[actor_index];

			if(braindead)
			{
				actor_data->current_state = Enums::_actor_default_state_none;
				actor_data->state.action = Enums::_actor_action_none;

				actor_delete_props(actor_index);
				actor_freeze(actor_index);
				actor_set_dormant(actor_index, 0);
			}
			else
			{
				if(actor_data->current_state == Enums::_actor_default_state_none)
				{
					actor_data->current_state = Enums::_actor_default_state_alert;
				}
			}
		}

		__declspec(naked) datum_index __cdecl actor_create_for_unit(const bool is_swarm
			, const datum_index unit_index
			, const datum_index actor_variant
			, const datum_index encounter_index
			, const long squad_index
			, const long arg7
			, const long arg6
			, const bool magic_sight_after_timer
			, const Enums::actor_default_state initial_state
			, const Enums::actor_default_state return_state
			, const long command_list_index
			, const long sequence_id)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_CREATE_FOR_UNIT);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl actor_action_change(const datum_index actor_index
			, const Enums::actor_action new_action_type
			, const byte* new_action_data)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(ACTOR_ACTION_CHANGE);

			_asm jmp	FUNCTION;
		}

		//////////////////////////////////////////////////////////////////////////
		// ai_script.c
		__declspec(naked) void __cdecl ai_scripting_attach_free(datum_index unit_index, datum_index actor_variant_definition_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(AI_SCRIPTING_ATTACH_FREE);

			API_FUNC_NAKED_START()
				push	eax
				
				mov		eax, actor_variant_definition_index
				push	unit_index
				call	FUNCTION
				add		esp, 4

				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// bink
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// bink_playback.c
		__declspec(naked) void __cdecl bink_playback_start(const char * bik_path)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(BINK_PLAYBACK_START);

			API_FUNC_NAKED_START()
				push	bik_path
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// cache
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// cache_files_windows.c
		bool __cdecl cache_file_read_request(/*datum_index tag_index,*/
			uint offset, uint size, void* buffer, const Cache::s_cache_file_request_params& params,
			bool block, Enums::cache_file_request_source source)
		{
			return Engine::Cache::FileReadRequest(offset, size, buffer, params, block, source);
		}
		//////////////////////////////////////////////////////////////////////////
		// pc_sound_cache.c
		bool __cdecl sound_cache_sound_request(TagGroups::s_sound_permutation* sound_perm,
			bool block_thread, bool load, bool reference)
		{
			return Engine::SoundCacheRequestSound(sound_perm, block_thread, load, reference);
		}
		//////////////////////////////////////////////////////////////////////////
		// pc_texture_cache.c
		IDirect3DBaseTexture9** __cdecl texture_cache_bitmap_get_hardware_format(TagGroups::s_bitmap_data* bitmap,
			// block
			bool block_thread, bool load)
		{
			return Engine::TextureCacheBitmapGetHardwareFormat(bitmap, block_thread, load);
		}
		//////////////////////////////////////////////////////////////////////////
		// physical_memory_map.c
		void predicted_resources_precache(TagBlock<TagGroups::predicted_resource>& resources)
		{
			return Engine::TagGroups::PredictResources(resources);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// camera
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// director.c
		__declspec(naked) void __cdecl director_save_camera()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(DIRECTOR_SAVE_CAMERA);

			__asm {
				call	FUNCTION
				retn
			}
		}

		__declspec(naked) void __cdecl director_load_camera()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(DIRECTOR_LOAD_CAMERA);

			__asm {
				call	FUNCTION
				retn
			}
		}

		__declspec(naked) short __cdecl director_desired_perspective(const datum_index unit_index, Enums::game_perspective& desired_perspective)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(DIRECTOR_DESIRED_PERSPECTIVE);

			API_FUNC_NAKED_START()
				mov		ecx, unit_index
				mov		edx, [desired_perspective]
				push	edx
				call	FUNCTION
				add		esp, 4
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// game
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// cheats.c
		__declspec(naked) void __cdecl cheat_all_weapons()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_ALL_WEAPONS);

			__asm {
				call	FUNCTION
				retn
			}
		}
		__declspec(naked) void __cdecl cheat_spawn_warthog()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_SPAWN_WARTHOG);

			__asm {
				call	FUNCTION
				retn
			}
		}
		__declspec(naked) void __cdecl cheat_teleport_to_camera()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_TELEPORT_TO_CAMERA);

			__asm {
				call	FUNCTION
				retn
			}
		}
		__declspec(naked) void __cdecl cheat_active_camouflage()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE);

			__asm {
				call	FUNCTION
				retn
			}
		}
		__declspec(naked) void __cdecl cheat_active_camouflage_local_player()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_ACTIVE_CAMOFLAGE_LOCAL_PLAYER);

			__asm {
				call	FUNCTION
				retn
			}
		}
		__declspec(naked) datum_index __cdecl cheat_local_player()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CHEAT_PLAYER_INDEX);

			__asm {
				call	FUNCTION
				retn
			}
		}
		//////////////////////////////////////////////////////////////////////////
		// game_allegiance.c
		bool __cdecl game_team_is_enemy(signed long team, signed long team_to_test)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(GAME_TEAM_IS_ENEMY);

			__asm {
				mov		ecx, team_to_test
				mov		edx, team
				call	FUNCTION
			}
		}
		//////////////////////////////////////////////////////////////////////////
		// game_engine.c
		datum_index __cdecl find_closest_player_index(datum_index player_index)
		{
			return Engine::Players::FindClosestPlayerIndex(player_index);
		}


		__declspec(naked) void __cdecl game_engine_rasterize_message(wconst char * message, real alpha)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(GAME_ENGINE_RASTERIZE_MESSAGE);

			API_FUNC_NAKED_START()
				push	alpha
				push	message
				call	FUNCTION
				add		esp, 4 * 2
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// game_engine_multiplayer_sounds.c
		__declspec(naked) void __cdecl game_engine_play_multiplayer_sound(datum_index player_index, shortmultiplayer_sound_index, bool should_replicate)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(GAME_ENGINE_PLAY_MULTIPLAYER_SOUND);

			API_FUNC_NAKED_START()
				push	esi
				push	edi

				movzx	esi, should_replicate
				push	esi
				movsx	esi, multiplayer_sound_index
				mov		edi, player_index
				call	FUNCTION
				add		esp, 4 * 1

				pop		edi
				pop		esi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// players.c






		//////////////////////////////////////////////////////////////////////////
		// player_control.c
		__declspec(naked) void __cdecl player_control_get_unit_camera_info(const short player_index, Players::s_unit_camera_info& camera_info)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(PLAYER_CONTROL_GET_UNIT_CAMERA_INFO);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx
				push	esi

				mov		ax, player_index
				mov		esi, camera_info
				call	FUNCTION
				
				pop		esi
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// hs
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// hs_library_external.c
		void __cdecl hs_object_orient(datum_index object_index, long cutscene_flag_index, bool teleport, bool set_facing)
		{
			Engine::Objects::ObjectOrient(object_index, cutscene_flag_index, teleport, set_facing);
		}


		void __cdecl hs_effect_new_from_object_marker(datum_index effect_definition_index, datum_index object_index, const char * marker_name)
		{
			Engine::Effects::NewOnObjectMarker(effect_definition_index, object_index, marker_name);
		}
		//////////////////////////////////////////////////////////////////////////
		// object_lists.c
		void __cdecl object_list_add(datum_index object_list_index, datum_index object_index)
		{
			Engine::HS::ObjectListAdd(object_list_index, object_index);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// input
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// input_windows.c
		__declspec(naked) bool __cdecl input_key_is_down(short key_code)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(INPUT_KEY_IS_DOWN);

			API_FUNC_NAKED_START()
				push	ecx

				mov		cx, key_code
				call	FUNCTION

				pop		ecx
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// interface
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// hud.c
		__declspec(naked) wconst char * __cdecl hud_get_item_string(short reference_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(HUD_GET_ITEM_MESSAGE);

			API_FUNC_NAKED_START()
				movsx	edx, reference_index
				call	FUNCTION
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// hud_chat.c
		void __cdecl hud_chat_to_network(long player_number, signed long chat_type, wconst char * text)
		{
			Engine::Networking::EncodeHudChatNetworkData(player_number, chat_type, text);
		}
		__declspec(naked) void __cdecl hud_chat_display_message(wconst char * message)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(KEYSTONE_CHAT_LOG_ADD_STRING);

			API_FUNC_NAKED_START()
				push	message
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// hud_draw.c
		__declspec(naked) void __cdecl hud_draw_meter(short /*local_player_index*/, TagGroups::s_hud_absolute_placement* placement, TagGroups::s_hud_element_meter* element,
			byte arg_C, byte arg_10, unsigned long flags, real arg_18, real arg_1C)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(HUD_DRAW_METER);

			API_FUNC_NAKED_START()
				push	esi

				push	arg_1C
				push	arg_18
				push	flags
				movzx	esi, arg_10
				push	esi
				movzx	esi, arg_C
				push	esi
				mov		esi, element
				push	placement
				call	FUNCTION
				add		esp, 4 * 6

				pop		esi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		__declspec(naked) void __cdecl hud_draw_numbers(short local_player_index, TagGroups::s_hud_absolute_placement* placement, TagGroups::s_hud_element_number* element,
			long number, short arg_10, unsigned long flags, game_ticks_t first_render_time, real arg_1C)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(HUD_DRAW_NUMBERS);

			API_FUNC_NAKED_START()
				push	esi

				push	arg_1C
				push	first_render_time
				push	flags
				movsx	esi, arg_10
				push	esi
				push	number
				push	element
				push	placement
				movsx	esi, local_player_index
				push	esi
				call	FUNCTION
				add		esp, 4 * 8

				pop		esi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		__declspec(naked) void __cdecl hud_draw_static_element(short local_player_index, TagGroups::s_hud_absolute_placement* placement, TagGroups::s_hud_element_static* element,
			unsigned long flags, game_ticks_t first_render_time)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(HUD_DRAW_STATIC_ELEMENT);

			API_FUNC_NAKED_START()
				push	esi

				push	first_render_time
				push	flags
				push	element
				push	placement
				movsx	esi, local_player_index
				push	esi
				call	FUNCTION
				add		esp, 4 * 5

				pop		esi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// hud_messaging.c
		__declspec(naked) void __cdecl hud_print_message(short local_player_index, wconst char * message)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(HUD_PRINT_MESSAGE);

			API_FUNC_NAKED_START()
				push	message
				movsx	eax, local_player_index
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		//////////////////////////////////////////////////////////////////////////
		// ui_video_screen.c
		void __cdecl ui_video_screen_add_resolution(uint width, uint height, uint refresh_rate)
		{
			Engine::RasterizerAddResolution(width, height, refresh_rate);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// items
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// weapons.c
		__declspec(naked) bool __cdecl weapon_prevents_melee_attack(const datum_index weapon_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(WEAPON_PREVENTS_MELEE_ATTACK);

			API_FUNC_NAKED_START()
				push	ecx

				mov		ecx, weapon_index
				call	FUNCTION

				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) bool __cdecl weapon_prevents_grenade_throwing(const datum_index weapon_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(WEAPON_PREVENTS_GRENADE_THROWING);

			API_FUNC_NAKED_START()
				push	ecx

				mov		ecx, weapon_index
				call	FUNCTION

				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl weapon_stop_reload(const datum_index weapon_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(WEAPON_STOP_RELOAD);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl first_person_weapon_message_from_unit(const datum_index unit_index, const long weapon_message_type)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(FIRST_PERSON_WEAPON_MESSAGE_FROM_UNIT);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx

				mov		eax, unit_index
				push	weapon_message_type
				call	FUNCTION
				add		esp, 4
				
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) short __cdecl weapon_get_first_person_animation_time(const datum_index weapon_index
			, const short frame_type
			, Enums::first_person_weapon_animation animation
			, const long arg3)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(WEAPON_GET_FIRST_PERSON_ANIMATION_TIME);

			API_FUNC_NAKED_START()
				push	ecx

				xor		ecx, ecx
				movsx	cx, frame_type
				push	arg3
				push	ecx
				mov		eax, weapon_index
				movsx	cx, animation
				call	FUNCTION
				add		esp, 8
				
				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// main
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// console.c
		__declspec(naked) bool __cdecl console_process_command(unsigned long access_flags, const char * command)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CONSOLE_PROCESS_COMMAND);

			API_FUNC_NAKED_START()
				push	edi

				mov		edi, command
				push	access_flags
				call	FUNCTION
				add		esp, 4 * 1

				pop		edi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		static __declspec(naked) void __cdecl console_printf_impl(bool clear_screen, const char * format)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CONSOLE_PRINTF);

			API_FUNC_NAKED_START()
				push	format
				mov		al, clear_screen
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		void __cdecl console_printf(bool clear_screen, const char * format, ...)
		{
			char local[k_engine_function_string_buffer_size];
			memset(local, 0, k_engine_function_string_buffer_size);

			va_list args;
			va_start(args, format);
			vsprintf_s(local, format, args);
			va_end(args);

			console_printf_impl(clear_screen, local);
		}
		static __declspec(naked) void __cdecl console_response_printf_impl(BOOL clear_screen, const char * format)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CONSOLE_RESPONSE_PRINTF);

			API_FUNC_NAKED_START()
				push	format
				push	clear_screen
				call	FUNCTION
				add		esp, 4 * 2
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		void __cdecl console_response_printf(bool clear_screen, const char * format, ...)
		{
			char local[k_engine_function_string_buffer_size];
			memset(local, 0, k_engine_function_string_buffer_size);

			va_list args;
			va_start(args, format);
			vsprintf_s(local, format, args);
			va_end(args);

			console_response_printf_impl(clear_screen, local);
		}
		static __declspec(naked) void __cdecl console_warning_impl(const char * format)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(CONSOLE_WARNING);

			API_FUNC_NAKED_START()
				push	format
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		void __cdecl console_warning(const char * format, ...)
		{
			char local[k_engine_function_string_buffer_size];
			memset(local, 0, k_engine_function_string_buffer_size);

			va_list args;
			va_start(args, format);
			vsprintf_s(local, format, args);
			va_end(args);

			console_warning_impl(local);
		}
		bool __cdecl console_process_remote_command(const char * command, long machine_index)
		{
			Console::TerminalGlobals()->rcon_machine_index = machine_index;
			bool result = console_process_command(0, command);
			Console::TerminalGlobals()->rcon_machine_index = NONE;

			return result;
		}
		//////////////////////////////////////////////////////////////////////////
		// main.c
		__declspec(naked) bool __cdecl main_connect(const char * address, const char * password)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(MAIN_CONNECT);

			API_FUNC_NAKED_START()
				push	password
				push	address
				call	FUNCTION
				add		esp, 4 * 2
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		void __cdecl main_menu_load()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(MAINMENU_LOAD);

			GameState::MainGlobals()->map.main_menu_scenario_load = true;

			__asm call	FUNCTION
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// math
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// periodic_functions.c
		__declspec(naked) real __cdecl periodic_function_evaluate(Enums::periodic_function function_type, real input)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(PERIODIC_FUNCTION_EVALUATE);
			
			API_FUNC_NAKED_START()
				fld		input
				sub		esp, 4 * 2			// allocate space for the 'input' parameter
				fstp	qword ptr [esp]		// store the input on the stack
				movzx	eax, function_type
				call	FUNCTION
				add		esp, 4 * 2			// deallocate. double type consumes two DWORDs of stack
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		__declspec(naked) real __cdecl transition_function_evaluate(Enums::transition_function function_type, real input)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(TRANSITION_FUNCTION_EVALUATE);

			API_FUNC_NAKED_START()
				push	input
				movzx	ecx, function_type
				call	FUNCTION
				add		esp, 4 * 1
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// memory
	namespace blam
	{
		using namespace Yelo::Memory;

		//////////////////////////////////////////////////////////////////////////
		// data.c
		__declspec(naked) s_data_array* __cdecl data_new(const char * name, long maximum_count, size_t datum_size)
		
		

		__declspec(naked) void __cdecl data_delete_all(s_data_array* data)
		
		
/*		void* __cdecl data_iterator_next(s_data_iterator& iterator)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(DATA_ITERATOR_NEXT);

			API_FUNC_NAKED_START()
				push	edi

				mov		edi, iterator
				call	FUNCTION

				pop		edi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}*/

	};
	//////////////////////////////////////////////////////////////////////////
	// models
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// models.c
		__declspec(naked) short __cdecl model_find_marker(const datum_index render_model_definition_index, const char * marker_name)
		{
			static const uintptr_t CALL_ADDRESS = Engine::GET_FUNC_PTR(MODEL_FIND_MARKER);

			API_FUNC_NAKED_START()
				mov		eax, render_model_definition_index
				push	render_model_definition_index
				push	marker_name
				call	CALL_ADDRESS
				add		esp, 8

				pop		ebp
			API_FUNC_NAKED_END_()
		}

		//////////////////////////////////////////////////////////////////////////
		// model_animations.c
		short __cdecl animation_choose_random_permutation_internal(signed long render_or_affects_game_state, datum_index animation_graph_index, long animation_index)
		{
			return Engine::AnimationPickRandomPermutation(render_or_affects_game_state, animation_graph_index, animation_index);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// objects
	namespace blam
	{
		using namespace Yelo::Objects;

		//////////////////////////////////////////////////////////////////////////
		// damage.c
		bool __cdecl object_restore_body(datum_index object_index)
		{
			return Engine::Objects::RestoreBody(object_index);
		}
		void __cdecl object_deplete_body(datum_index object_index)
		{
			Engine::Objects::DepleteBody(object_index);
		}
		void __cdecl object_deplete_shield(datum_index object_index)
		{
			Engine::Objects::DepleteShield(object_index);
		}
		void __cdecl object_double_charge_shield(datum_index object_index)
		{
			Engine::Objects::DoubleChargeShield(object_index);
		}
		void __cdecl area_of_effect_cause_damage(s_damage_data& data, datum_index )
		{
			// TODO
		}
		void __cdecl object_cause_damage(s_damage_data& data, datum_index damaged_object_index,
			short node_index, short region_index, short damage_materials_element_index,
			real_vector3d* normal)
		{
			Engine::Objects::ObjectCauseDamage(data, damaged_object_index, 
				node_index, region_index, damage_materials_element_index, 
				normal);
		}
		//////////////////////////////////////////////////////////////////////////
		// index_resolution.c
		long __cdecl index_resolution_table_translate(MessageDeltas::s_index_resolution_table& table, datum_index local_index)
		{
			// TODO: get rid of these guards
#ifndef YELO_NO_NETWORK
			return Engine::Networking::TranslateIndex(table, local_index);
#else
			return 0;
#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// objects.c
		void __cdecl object_reset(datum_index object_index)
		{
			Engine::Objects::Reset(object_index);
		}

		void __cdecl object_set_position(datum_index object_index,
			__in_opt real_point3d* new_position, __in_opt real_vector3d* new_forward, __in_opt real_vector3d* new_up)
		{
			Engine::Objects::SetPosition(object_index, new_position, new_forward, new_up);
		}

		void __cdecl object_set_position_network(datum_index object_index,
			real_point3d* new_position)
		{
			Engine::Objects::SetPositionNetwork(object_index, new_position);
		}

		void __cdecl object_translate(datum_index object_index,
			const real_point3d& new_position, __in_opt const s_scenario_location* new_location)
		{
			// TODO
		}

		void __cdecl object_placement_data_new(s_object_placement_data& data, datum_index object_definition_index, datum_index owner_object_index)
		{
			Engine::Objects::PlacementDataNew(data, object_definition_index, owner_object_index);
		}

		datum_index __cdecl object_new(s_object_placement_data& data)
		{
			return Engine::Objects::New(data);
		}

		datum_index __cdecl object_new_with_role(s_object_placement_data& data, Enums::networked_datum role)
		{
			return Engine::Objects::NewWithRole(data, role);
		}

		void __cdecl object_delete_to_network(datum_index object_index)
		{
			Engine::Networking::EncodeObjectDeletionMessage(object_index);
		}

		void __cdecl object_delete(datum_index object_index)
		{
			Engine::Objects::Delete(object_index);
		}

		void __cdecl object_reconnect_to_map(datum_index object_index, __in_opt s_scenario_location* location_reference)
		{
			Engine::Objects::ReconnectToMap(object_index, location_reference);
		}

		void __cdecl object_disconnect_from_map(datum_index object_index)
		{
			Engine::Objects::DisconnectFromMap(object_index);
		}

		__declspec(naked) short __cdecl object_get_marker_by_name(const datum_index object_index
			, const char * marker_name
			, s_object_marker* markers
			, const short maximum_marker_count)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(OBJECT_GET_MARKER_BY_NAME);

			_asm jmp	FUNCTION;
		}

		void __cdecl object_attach_to_marker(datum_index target_object_index, const char * target_marker_name, datum_index object_index, const char * marker_name)
		{
			Engine::Objects::Attach(target_object_index, target_marker_name, object_index, marker_name);
		}



		void __cdecl object_get_orientation(datum_index object_index,
			__out_opt real_vector3d* return_forward, __out_opt real_vector3d* return_up)
		{
			Engine::Objects::GetOrientation(object_index, return_forward, return_up);
		}

		s_scenario_location& __cdecl object_get_location(datum_index object_index, __out s_scenario_location& return_location)
		{
			return Engine::Objects::GetLocation(object_index, return_location);
		}

		void __cdecl object_start_interpolation(datum_index object_index, long interpolation_frame_count)
		{
			Engine::Objects::StartInterpolation(object_index, interpolation_frame_count);
		}

		s_object_data* __cdecl object_iterator_next(s_object_iterator& iter)
		{
			return Engine::Objects::IteratorNext(iter);
		}

		short __cdecl objects_in_sphere(Flags::objects_find_flags find_flags, unsigned long object_type_flags,
			const s_scenario_location& location, const real_point3d& center, real radius, 
			datum_index object_indices[], short maximum_object_indices)
		{
			return Engine::Objects::FindInSphere(find_flags, object_type_flags,
				location, center, radius, object_indices, maximum_object_indices);
		}

		void __cdecl object_definition_predict(datum_index object_index)
		{
			Engine::Objects::DefinitionPredict(object_index);
		}

		bool __cdecl object_header_block_allocate(datum_index object_index, size_t block_reference_offset, size_t size)
		{
			return Engine::Objects::HeaderBlockAllocate(object_index, block_reference_offset, size);
		}

		void __cdecl objects_scripting_set_scale(datum_index object_index, real scale, long ticks)
		{
			Engine::Objects::SetScale(object_index, scale, ticks);
		}

		real __cdecl object_get_level_of_detail_pixels(datum_index object_index)
		{
			return Engine::Objects::GetLevelOfDetailPixels(object_index);
		}

		void __cdecl object_render_state_refresh(datum_index object_render_state_index, datum_index object_index, real level_of_detail_pixels, byte arg4)
		{
			Engine::Objects::ObjectRenderStateRefresh(object_render_state_index, object_index, level_of_detail_pixels, arg4);
		}

		__declspec(naked) void __cdecl objects_update()
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(OBJECTS_UPDATE);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl object_update(datum_index object_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(OBJECT_UPDATE);

			_asm jmp	FUNCTION;
		}
		
		__declspec(naked) void __cdecl object_destroy(const datum_index object_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(OBJECT_DESTROY);

			API_FUNC_NAKED_START()
				push	eax
				push	ecx
				push	edx
				push	edi

				mov		eax, object_index
				call	FUNCTION

				pop		edi
				pop		edx
				pop		ecx
				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// physics
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// collisions.c
		__declspec(naked) bool __cdecl collision_test_vector(unsigned long flags, real_point3d& location, real_vector3d& vector,
			datum_index object_index, Physics::s_collision_result& collision)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(COLLISION_TEST_VECTOR);

			__asm jmp	FUNCTION;
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// rasterizer
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// dx9/rasterizer_dx9.c
		bool __cdecl rasterizer_set_texture_bitmap_data(shortstage, TagGroups::s_bitmap_data* bitmap)
		{
			return Engine::SetTextureSamplerStage(bitmap, stage);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// render
	namespace blam
	{
		void __cdecl render_window(const unsigned short local_player_index
			, void* render_camera
			, void* render_frustum
			, void* rasterizer_camera
			, void* rasterizer_frustum
			, void* rasterizer_target
			, const bool is_mirror)
		{
			CAST_PTR(void (__cdecl*)(const unsigned short, void*, void*, void*, void*, void*, const bool), Engine::GET_FUNC_PTR(RENDER_WINDOW))
				(local_player_index, render_camera, render_frustum, rasterizer_camera, rasterizer_frustum, rasterizer_target, is_mirror);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// scenario
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// scenario.c
		// After calling this function you should call Yelo::GameState::InitializeForNewBSP
		__declspec(naked) bool __cdecl scenario_switch_structure_bsp(short bsp_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(SCENARIO_SWITCH_STRUCTURE_BSP);

			API_FUNC_NAKED_START()
				push	esi

				movsx	esi, bsp_index
				call	FUNCTION

				pop		esi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
		bool __cdecl scenario_trigger_volume_test_point(long trigger_volume_index, const real_point3d& point)
		{
			return Engine::Scenario::TriggerVolumeTestPoint(trigger_volume_index, point);
		}
		bool __cdecl scenario_trigger_volume_test_object(long trigger_volume_index, datum_index object_index)
		{
			return Engine::Scenario::TriggerVolumeTestObject(trigger_volume_index, object_index);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// shell
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// shell_windows.c
		__declspec(naked) bool __cdecl shell_get_command_line_argument(const char * param, _Out_opt_ const char ** value)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(SHELL_GET_COMMAND_LINE_ARGUMENT);

			API_FUNC_NAKED_START()
				push	edi

				mov		edi, value
				push	param
				call	FUNCTION
				add		esp, 4 * 1

				pop		edi
			API_FUNC_NAKED_END_NO_STACK_POP()
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// tag_files
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// tag_groups.c
		datum_index __cdecl tag_loaded(tag group_tag, const char * name)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(TAG_LOADED);

#if defined(ENGINE_FUNCTIONS_USE_LOCAL)
			char local[256];
			memset(local, 0, sizeof(local));
			strcpy_s(local, name);
#else
			const char * local = name;
#endif

			__asm {
				push	edi

#if defined(ENGINE_FUNCTIONS_USE_LOCAL)
				lea		eax, local
#else
				mov		eax, local
#endif
				push	eax
				mov		edi, group_tag
				call	FUNCTION
				add		esp, 4 * 1

				pop		edi
			}
		}
		void __cdecl tag_iterator_new(TagGroups::s_tag_iterator& iter, const tag group_tag_filter)
		{
			memset(&iter, 0, sizeof(iter));
			iter.group_tag_filter = group_tag_filter;
		}
		datum_index __cdecl tag_iterator_next(TagGroups::s_tag_iterator& iter)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(TAG_ITERATOR_NEXT);

			__asm {
				push	esi

				mov		esi, iter
				call	FUNCTION

				pop		esi
			}
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// text
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// text_group.c
		wconst char * unicode_string_list_get_string(datum_index unicode_string_list_definition_index, long reference_index)
		{
			return Engine::TagGroups::UnicodeStringListGetString(unicode_string_list_definition_index, reference_index);
		}
	};
	//////////////////////////////////////////////////////////////////////////
	// units
	namespace blam
	{
		//////////////////////////////////////////////////////////////////////////
		// units.c
		__declspec(naked) void __cdecl unit_update(const datum_index unit_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_UPDATE);

			_asm jmp	FUNCTION;
		}

		void __cdecl unit_set_animation(datum_index unit_index
			, datum_index animation_graph_index
			, long animation_index)
		{
			Engine::Objects::UnitSetAnimation(unit_index, animation_graph_index, animation_index);
		}
		
		__declspec(naked) void __cdecl unit_animation_start_action(const datum_index unit_index, const Enums::unit_replacement_animation_state action_type)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_ANIMATION_START_ACTION);

			_asm jmp	FUNCTION;
		}

		short __cdecl unit_find_nearby_seat(datum_index unit_index
			, datum_index target_unit_index
			, __out short& parent_seat_index)
		{
			return Engine::Objects::UnitFindNearbySeat(unit_index, target_unit_index, parent_seat_index);
		}

		bool __cdecl unit_can_enter_seat(datum_index unit_index
			, datum_index target_unit_index
			, short seat_index
			, __out datum_index* unit_in_seat_index)
		{
			return Engine::Objects::UnitCanEnterSeat(unit_index, target_unit_index, seat_index, unit_in_seat_index);
		}

		bool __cdecl unit_enter_seat(datum_index unit_index
			, datum_index target_unit_index
			, long seat_index)
		{
			return Engine::Objects::UnitEnterSeat(unit_index, target_unit_index, seat_index);
		}

		void __cdecl unit_get_camera_position(datum_index unit_index, __out real_point3d* return_position)
		{
			Engine::Objects::UnitGetCameraPosition(unit_index, return_position);
		}

		void __cdecl unit_kill(const datum_index unit_index)
		{
			auto* unit_datum = blam::object_try_and_get_and_verify_type<s_unit_datum>(unit_index);
			if(unit_datum)
			{
				SET_FLAG(unit_datum->object.damage.flags, Flags::_object_killed_bit, true);
			}
		}

		void __cdecl unit_open(datum_index unit_index)
		{
			Engine::Objects::UnitOpen(unit_index);
		}

		void __cdecl unit_close(datum_index unit_index)
		{
			Engine::Objects::UnitClose(unit_index);
		}

		void __cdecl unit_scripting_exit_vehicle(datum_index unit_index)
		{
			Engine::Objects::UnitExitVehicle(unit_index);
		}

		__declspec(naked) bool __cdecl unit_try_and_exit_seat(const datum_index unit_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_TRY_AND_EXIT_SEAT);

			API_FUNC_NAKED_START()
				push	ecx
				push	edx
				push	edi

				mov		edi, unit_index
				call	FUNCTION
				
				pop		edi
				pop		edx
				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl unit_detach_from_parent(const datum_index unit_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_DETACH_FROM_PARENT);

			API_FUNC_NAKED_START()
				push	edi

				mov		edi, unit_index
				call	FUNCTION

				pop		edi
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		void __cdecl unit_exit_seat_end(datum_index unit_index
			, bool no_network_message
			, bool can_run_on_client_side
			, bool unknown)
		{
			Engine::Objects::UnitExitSeatEnd(unit_index, no_network_message, can_run_on_client_side, unknown);
		}
		
		__declspec(naked) bool __cdecl unit_can_see_point(const datum_index unit_index
			, const real_point3d* point
			, const real view_radians)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_CAN_SEE_POINT);
			
			API_FUNC_NAKED_START()
				push	ecx
				push	edx
				push	edi

				mov		ecx, unit_index
				mov		edi, point
				push	view_radians
				call	FUNCTION
				add		esp, 4

				pop		edi
				pop		edx
				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		short unit_get_custom_animation_time(datum_index unit_index)
		{
			return Engine::Objects::UnitGetCustomAnimationTime(unit_index);
		}
		
		__declspec(naked) bool __cdecl unit_start_user_animation(const datum_index unit_index
			, const datum_index animation_definition_index
			, const char * animation_name
			, const bool interpolate)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_START_USER_ANIMATION);

			API_FUNC_NAKED_START()
				push	ebx
				push	ecx
				push	edx
				push	edi

				mov		eax, animation_name
				mov		edi, animation_definition_index
				xor		ebx, ebx
				mov		bl, interpolate
				push	ebx
				push	unit_index
				call	FUNCTION
				add		esp, 8

				pop		edi
				pop		edx
				pop		ecx
				pop		ebx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl unit_animation_set_state(const datum_index unit_index, const Enums::unit_animation_state state)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_ANIMATION_SET_STATE);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl unit_drop_current_weapon(const datum_index unit_index, const bool force)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_DROP_CURRENT_WEAPON);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) datum_index __cdecl unit_inventory_get_weapon(const datum_index unit_index, const short index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_INVENTORY_GET_WEAPON);
			
			API_FUNC_NAKED_START()
				push	ecx
				push	edx

				mov		eax, unit_index
				xor		ecx, ecx
				mov		cx, index
				call	FUNCTION
				
				pop		edx
				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl unit_ready_desired_weapon(const datum_index unit_index, const bool force)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_READY_DESIRED_WEAPON);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl unit_throw_grenade_release(const datum_index unit_index, const sbyte keyframe)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_THROW_GRENADE_RELEASE);

			_asm jmp	FUNCTION;
		}
		
		__declspec(naked) void __cdecl unit_cause_player_melee_damage(const datum_index unit_index)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_CAUSE_PLAYER_MELEE_DAMAGE);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl unit_damage_aftermath(const datum_index unit_index
			, const Objects::s_damage_data* damage_data
			, const shortdamage_flags
			, const real shield_amount
			, const real body_amount
			, void* arg6
			, const long damage_part)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_DAMAGE_AFTERMATH);

			_asm jmp	FUNCTION;
		}

		__declspec(naked) void __cdecl unit_scripting_set_current_vitality(const datum_index unit_index
			, const real health
			, const real shield)
		{
			static const uintptr_t CALL_ADDRESS = Engine::GET_FUNC_PTR(UNIT_SCRIPTING_SET_CURRENT_VITALITY);

			API_FUNC_NAKED_START()
				push	eax

				mov		eax, unit_index
				push	shield
				push	health
				call	CALL_ADDRESS
				add		esp, 8

				pop		eax
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		__declspec(naked) void __cdecl unit_set_actively_controlled(const datum_index unit_index, const bool controlled)
		{
			static const uintptr_t FUNCTION = Engine::GET_FUNC_PTR(UNIT_SET_ACTIVELY_CONTROLLED);

			API_FUNC_NAKED_START()
				push	ecx

				xor		ecx, ecx
				mov		cl, controlled
				push	unit_index
				call	FUNCTION
				add		esp, 4

				pop		ecx
				pop		ebp
			API_FUNC_NAKED_END_()
		}
	};
};
