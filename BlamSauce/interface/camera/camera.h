/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#if PLATFORM_IS_USER
#include <blamlib/Halo1/camera/director.hpp>
#include <YeloLib/configuration/c_configuration_value.hpp>
#include <YeloLib/configuration/c_configuration_container.hpp>
#include <YeloLib/open_sauce/settings/c_settings_singleton.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum settings_adjustment_result : long_enum;

		enum camera_script_mode : _enum
		{
			_camera_script_mode_none = _enum(NONE),
			_camera_script_mode_unk = 0,
			_camera_script_mode_controlled,
			_camera_script_mode_first_person,
			_camera_script_mode_dead,
		};
	};

	namespace Flags
	{
		enum observer_globals_data_flags : byte_flags
		{
			_observer_update_flag =			FLAG(0),
			_observer_unk1_flag =			FLAG(1),
			_observer_unk2_flag =			FLAG(2),
			_observer_unk3_flag =			FLAG(3),
			_observer_unk4_flag =			FLAG(4),
			_observer_dont_pass_time_flag =	FLAG(5),
		};
	};

	namespace Camera
	{
		struct s_camera_command
		{
			Flags::observer_globals_data_flags flags;
			unsigned char : 8; unsigned short : 16;

			real_point3d position;
			real_point3d offset;
			real depth;
			real fov;
			real_vector3d forward;
			real_vector3d up;
			real_vector3d vector;
			real time; // 0 when ever not in transition into 3rdperson

			byte_flags command_flags[Enums::k_number_of_director_game_modes]; // 3 in fp, 0 default
			unsigned char : 8; unsigned short : 16;
			real commands[Enums::k_number_of_director_game_modes]; // all the same during transitions, 0.0f = command finished
		}; static_assert( sizeof(s_camera_command) == 0x68 );

		struct s_observer
		{ 
			tag header_signature;				// 0x0
			s_camera_command* command_update;	// 0x4
			s_camera_command command;			// 0x8
			bool updated_for_frame;
			UNKNOWN_TYPE(bool);
			unsigned short : 16;

			// calculated / camera
			struct s_calculated_result
			{
				real_point3d position;			// 0x74
				s_scenario_location location;	// 0x80
				real_vector3d velocity;			// 0x88
				real_vector3d forward;			// 0x94
				real_euler_angles3d up;			// 0xA0
				real fov;						// 0xAC
			}result;	static_assert( sizeof(s_calculated_result) == 0x3C );

			// focus. this structure isn't a real structure in the game's code (these fields are part of s_observer)
			struct s_calculated_origin
			{
				real_point3d position;	// 0xB0
				real_point3d offset;	// 0xBC
				real depth;				// 0xC8 distance
				real fov;				// 0xCC
				real_vector3d forward;	// 0xD0
				real_vector3d up;		// 0xDC
			}origin;	static_assert( sizeof(s_calculated_origin) == 0x38 );

			byte __pad[432]; // 0xE8

			// I'm thinking these are actually real_matrix3x3
			// k_count = 11
			// 0x0E8 real velocities[k_count]

			// 0x114, 0x118, 0x11C

			// 0x120 real ?[k_count]

			// 0x14C, 0x150, 0x154

			// 0x158 real ?[k_count]
			// 0x184 real ?[k_count]
			// 0x1B0 real ?[k_count]
			// 0x1DC real ?[k_count]
			// 0x208 real ?[k_count]
			// 0x234 real ?[k_count]
			// 0x260 real ?[k_count]

			// 0x28C, 0x290, 0x294

			tag trailer_signature; // 0x298

			void GetRightVector(real_vector3d& right) const					{ right = this->origin.forward ^ this->origin.up; }
		}; static_assert( sizeof(s_observer) == 0x29C );
		s_observer*		Observer();

		struct s_camera_script_globals_data
		{
			bool initialized; // set this and [enabled] to true to enable scripted camera
			bool enabled;
			Enums::camera_script_mode mode;
			struct {
				short next; // next camera point index
				unsigned short : 16;
				real time; // multiply by 30 to then ftol to get camera_time
				real_point3d position;
				real_vector3d forward;
				real_euler_angles3d up;
				real fov;
			}camera_point;
			datum_index owner_unit;

			struct {
				datum_index tag_index; // [model_animation]
				short animation_index; // index in the animations block
			}animation;
		};
		s_camera_script_globals_data*	CameraScriptGlobals();


		struct s_director_scripting_data
		{
			bool initialized;
			unsigned char : 8; unsigned short : 16;
		};
		s_director_scripting_data*	DirectorScripting();

		struct s_cinematic_globals_data
		{
			real unknown1;
			uint time;
			bool show_letterbox;
			bool in_progress;
			bool can_be_skipped;
			bool suppress_bsp_object_creation;
			struct {
				short title_index;
				short title_delay;
			}chapter_titles[4];
		};
		s_cinematic_globals_data*		CinematicGlobals();


		void Initialize();
		void Dispose();
		void Update();

		// Dump the current view state for use in screen-shot point plotting
		void DumpViewState(cstring name = NULL);
		void* DumpViewStateEvaluate(void** arguments);
	};




	namespace Fov
	{
		class c_settings_container
			: public Configuration::c_configuration_container
		{
		public:
			Configuration::c_configuration_value<real> m_field_of_view;
			Configuration::c_configuration_value<bool> m_ignore_fov_change_in_cinematics;
			Configuration::c_configuration_value<bool> m_ignore_fov_change_in_main_menu;

			c_settings_container();
			
		protected:
			const std::vector<i_configuration_value* const> GetMembers() final override;
		};

		class c_settings_fov
			: public Settings::c_settings_singleton<c_settings_container, c_settings_fov>
		{
		public:
			void PostLoad() final override;

			void PreSave() final override;
		};

		void Initialize();
		void Dispose();

		real GetFieldOfView();
		void SetFieldOfView(const real fov);
		void ResetFieldOfView();
	};
};
//Lazy merge :)
namespace Yelo::Camera
	{
		s_observer* Observer()									PTR_IMP_GET2(observers);
		s_camera_script_globals_data* CameraScriptGlobals()		PTR_IMP_GET2(camera_script_globals);
		s_director_scripting_data* DirectorScripting()			DPTR_IMP_GET(director_scripting);
		s_cinematic_globals_data* CinematicGlobals()			DPTR_IMP_GET(cinematic_globals);
		s_director_data* GlobalDirector()						PTR_IMP_GET2(global_director);

		short __cdecl DirectorDesiredPerspective(const datum_index unit_index, Enums::game_perspective& perspective)
		{
			if(!unit_index.IsNull())
			{
				auto& unit_datum = *blam::object_get_and_verify_type<Objects::s_unit_datum>(unit_index);

				if(unit_datum.unit.animation.state == Enums::_unit_animation_state_yelo_unit_mounted)
				{
					auto* unit_extension_definition = Objects::GetUnitExtensionDefinition(unit_index);
					if(unit_extension_definition && (unit_extension_definition->mounted_state.Count == 1))
					{
						auto& mounted_state_definition = unit_extension_definition->mounted_state[0];

						if(TEST_FLAG(mounted_state_definition.flags, Flags::_unit_mounted_state_flags_third_person_camera))
						{
							perspective = Enums::_game_perspective_following_camera;
							return Enums::_game_perspective_following_camera;
						}
					}
				}
			}

			return blam::director_desired_perspective(unit_index, perspective);
		}

		API_FUNC_NAKED short __cdecl DirectorChooseGamePerspectiveHook(Enums::game_perspective& perspective)
		{
			API_FUNC_NAKED_START()
				push	perspective
				push	ecx
				call	DirectorDesiredPerspective
				add		esp, 8
				pop		ebp
			API_FUNC_NAKED_END_()
		}

		void Initialize()
		{
			#pragma region old third person shit
			static byte asm_change_short1[] = {0x01, 0x00};
			static byte asm_change_short0[] = {0x00, 0x00};
			static byte asm_change_long0[] = {0x00, 0x00, 0x00, 0x00};

			Memory::CreateHookRelativeCall(&Camera::UpdateFor3rd, GET_FUNC_VPTR(OBSERVER_UPDATE_COMMAND_HOOK), Enums::_x86_opcode_retn);
			Memory::WriteMemory(GET_FUNC_VPTR(DIRECTOR_GET_PERSPECTIVE_DEFAULT_SET), asm_change_short1, 2);
			Memory::WriteMemory(GET_FUNC_VPTR(HUD_INITIALIZE_FOR_NEW_MAP_DEFAULT_SET_SHOW_HUD), asm_change_short0, 2);
			Memory::WriteMemory(GET_FUNC_VPTR(HUD_ADD_ITEM_MESSAGE_DEFAULT_SET_SHOW_MSG), asm_change_long0, 4);
			#pragma endregion

			Memory::WriteRelativeCall(&DirectorChooseGamePerspectiveHook, GET_FUNC_VPTR(DIRECTOR_CHOOSE_GAME_PERSPECTIVE_HOOK), true);

			Fov::Initialize();
		}

		void Dispose()
		{
			Fov::Dispose();
		}

		void Update()
		{
		}

		#pragma region old third person shit
		void __cdecl UpdateFor3rd()
		{
			if (*((byte *)0x400001EE)!=0x5C && *((short *)0x64741C)==0 && *((short *)0x64741E)==1)
			//if(GameState::GameGlobals()->data[0x1A] != 0x5C &&
			//	Camera::Observer()->timer._unknown4 == 0 &&
			//	Camera::Observer()->timer._unknown4_pad[1] == 1)
			{
				Camera::ObserverGlobals()->command.offset.y = 0.4f;
				Camera::ObserverGlobals()->command.offset.z = 0.2f;
				Camera::ObserverGlobals()->command.depth = 2.0f;
			}
		}
		#pragma endregion

		void DumpViewState(cstring name)
		{
			if(!name) name = "view_state.bin";

			FILE* f = Settings::CreateReport(name, false, false);

			if(f != nullptr)
			{
				fwrite(&Render::RenderGlobals()->camera, sizeof(Render::s_render_camera), 1, f);
				fwrite(&Render::RenderGlobals()->frustum, sizeof(Render::s_render_frustum), 1, f);
				fclose(f);
			}
		}

		void* DumpViewStateEvaluate(void** arguments)
		{
 			DumpViewState();

			return nullptr;
		}
	};

namespace Yelo::Fov
	{
		static real g_fov_scale = 1.0f;

#pragma region Settings
		c_settings_container::c_settings_container()
			: Configuration::c_configuration_container("Camera")
			, m_field_of_view("FieldOfView", 70.0f)
			, m_ignore_fov_change_in_cinematics("IgnoreFOVChangeInCinematics", true)
			, m_ignore_fov_change_in_main_menu("IgnoreFOVChangeInMainMenu", true)
		{ }

		const std::vector<Configuration::i_configuration_value* const> c_settings_container::GetMembers()
		{
			return std::vector<i_configuration_value* const> { &m_field_of_view, &m_ignore_fov_change_in_cinematics, &m_ignore_fov_change_in_main_menu };
		}

		void c_settings_fov::PostLoad()
		{
			real base_fov = __min(Get().m_field_of_view, 160.0f);
			base_fov =		__max(base_fov, 40.0f);

			g_fov_scale = base_fov / 70.0f;
		}

		void c_settings_fov::PreSave()
		{
			Get().m_field_of_view = 70.0f * g_fov_scale;
		}
#pragma endregion

		static void __cdecl observer_update_command_hook()
		{
			if (Players::PlayerControlGlobals()->local_players[0].zoom_level > -1)
			{
				return;
			}

			bool in_main_menu = Yelo::Cache::CacheFileGlobals()->cache_header.cache_type == Enums::_shared_cache_type_main_menu;
			if(in_main_menu && c_settings_fov::Instance()->m_ignore_fov_change_in_main_menu)
			{
				return;
			}

			if(!in_main_menu
				&& Camera::DirectorScripting()->initialized
				&& c_settings_fov::Instance()->m_ignore_fov_change_in_cinematics)
			{
				return;
			}

			real player_fov = Camera::Observer()->command_update->fov;
			if(player_fov != 0.0f)
			{
				Camera::Observer()->command.fov = player_fov * g_fov_scale;
			}
		}

		void Initialize()
		{
			// Overwrite the 'retn' at the observer_update_command with a jmp to our hook code
			Memory::WriteRelativeJmp(observer_update_command_hook, GET_FUNC_VPTR(OBSERVER_UPDATE_COMMAND_HOOK), true);

			// Disabled the max fov check
			GET_PTR(MAX_FOV_CHECK_JMP) = Enums::_x86_opcode_jmp_short;

			c_settings_fov::Register(Settings::Manager());
		}

		void Dispose()
		{
			c_settings_fov::Unregister(Settings::Manager());
		}

		real GetFieldOfView()
		{
			 return 70.0f * g_fov_scale;
		}

		void SetFieldOfView(const real fov)
		{
			g_fov_scale = fov / 70.0f;
		}

		void ResetFieldOfView()
		{
			g_fov_scale = 1.0f;
		}
	};
#endif
