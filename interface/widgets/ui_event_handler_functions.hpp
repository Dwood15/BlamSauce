/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum ui_widget_event_handler_function : short
		{
			_ui_widget_event_handler_function_null,
			_ui_widget_event_handler_function_list_goto_next_item,
			_ui_widget_event_handler_function_list_goto_previous_item,
			_ui_widget_event_handler_function_unused,
			_ui_widget_event_handler_function_unused_1,
			_ui_widget_event_handler_function_initialize_sp_level_list_solo,
			_ui_widget_event_handler_function_initialize_sp_level_list_coop,
			_ui_widget_event_handler_function_dispose_sp_level_list,
			_ui_widget_event_handler_function_solo_level_set_map,
			_ui_widget_event_handler_function_set_difficulty,
			_ui_widget_event_handler_function_start_new_game,
			_ui_widget_event_handler_function_pause_game_restart_at_checkpoint,
			_ui_widget_event_handler_function_pause_game_restart_level,
			_ui_widget_event_handler_function_pause_game_return_to_main_menu,
			_ui_widget_event_handler_function_clear_multiplayer_player_joins,
			_ui_widget_event_handler_function_join_controller_to_mp_game,
			_ui_widget_event_handler_function_initialize_net_game_server_list,
			_ui_widget_event_handler_function_start_network_game_server,
			_ui_widget_event_handler_function_dispose_net_game_server_list,
			_ui_widget_event_handler_function_shutdown_network_game,
			_ui_widget_event_handler_function_net_game_join_from_server_list,
			_ui_widget_event_handler_function_split_screen_game_initialize,
			_ui_widget_event_handler_function_coop_game_initialize,
			_ui_widget_event_handler_function_main_menu_intialize,
			_ui_widget_event_handler_function_mp_type_menu_initialize,
			_ui_widget_event_handler_function_pick_play_stage_for_quick_start,
			_ui_widget_event_handler_function_mp_level_list_initialize,
			_ui_widget_event_handler_function_mp_level_list_dispose,
			_ui_widget_event_handler_function_mp_level_select,
			_ui_widget_event_handler_function_mp_profiles_list_initialize,
			_ui_widget_event_handler_function_mp_profiles_list_dispose,
			_ui_widget_event_handler_function_mp_profile_set_for_game,
			_ui_widget_event_handler_function_swap_player_team,
			_ui_widget_event_handler_function_net_game_join_player,
			_ui_widget_event_handler_function_player_profile_list_initialize,
			_ui_widget_event_handler_function_player_profile_list_dispose,
			_ui_widget_event_handler_function__3wide_plyr_prof_set_for_game,
			_ui_widget_event_handler_function__1wide_plyr_prof_set_for_game,
			_ui_widget_event_handler_function_mp_profile_begin_editing,
			_ui_widget_event_handler_function_mp_profile_end_editing,
			_ui_widget_event_handler_function_mp_profile_set_game_engine,
			_ui_widget_event_handler_function_mp_profile_change_name,
			_ui_widget_event_handler_function_mp_profile_set_ctf_rules,
			_ui_widget_event_handler_function_mp_profile_set_koth_rules,
			_ui_widget_event_handler_function_mp_profile_set_slayer_rules,
			_ui_widget_event_handler_function_mp_profile_set_oddball_rules,
			_ui_widget_event_handler_function_mp_profile_set_racing_rules,
			_ui_widget_event_handler_function_mp_profile_set_player_options,
			_ui_widget_event_handler_function_mp_profile_set_item_options,
			_ui_widget_event_handler_function_mp_profile_set_indicator_opts,
			_ui_widget_event_handler_function_mp_profile_init_game_engine,
			_ui_widget_event_handler_function_mp_profile_init_name,
			_ui_widget_event_handler_function_mp_profile_init_ctf_rules,
			_ui_widget_event_handler_function_mp_profile_init_koth_rules,
			_ui_widget_event_handler_function_mp_profile_init_slayer_rules,
			_ui_widget_event_handler_function_mp_profile_init_oddball_rules,
			_ui_widget_event_handler_function_mp_profile_init_racing_rules,
			_ui_widget_event_handler_function_mp_profile_init_player_opts,
			_ui_widget_event_handler_function_mp_profile_init_item_options,
			_ui_widget_event_handler_function_mp_profile_init_indicator_opts,
			_ui_widget_event_handler_function_mp_profile_save_changes,
			_ui_widget_event_handler_function_color_picker_menu_initialize,
			_ui_widget_event_handler_function_color_picker_menu_dispose,
			_ui_widget_event_handler_function_color_picker_select_color,
			_ui_widget_event_handler_function_player_profile_begin_editing,
			_ui_widget_event_handler_function_player_profile_end_editing,
			_ui_widget_event_handler_function_player_profile_change_name,
			_ui_widget_event_handler_function_player_profile_save_changes,
			_ui_widget_event_handler_function_plyr_prf_init_cntl_settings,
			_ui_widget_event_handler_function_plyr_prf_init_adv_cntl_set,
			_ui_widget_event_handler_function_plyr_prf_save_cntl_settings,
			_ui_widget_event_handler_function_plyr_prf_save_adv_cntl_set,
			_ui_widget_event_handler_function_mp_game_player_quit,
			_ui_widget_event_handler_function_main_menu_switch_to_solo_game,
			_ui_widget_event_handler_function_request_del_player_profile,
			_ui_widget_event_handler_function_request_del_playlist_profile,
			_ui_widget_event_handler_function_final_del_player_profile,
			_ui_widget_event_handler_function_final_del_playlist_profile,
			_ui_widget_event_handler_function_cancel_profile_delete,
			_ui_widget_event_handler_function_create_edit_playlist_profile,
			_ui_widget_event_handler_function_create_edit_player_profile,
			_ui_widget_event_handler_function_net_game_speed_start,
			_ui_widget_event_handler_function_net_game_delay_start,
			_ui_widget_event_handler_function_net_server_accept_conx,
			_ui_widget_event_handler_function_net_server_defer_start,
			_ui_widget_event_handler_function_net_server_allow_start,
			_ui_widget_event_handler_function_disable_if_no_xdemos,
			_ui_widget_event_handler_function_run_xdemos,
			_ui_widget_event_handler_function_sp_reset_controller_choices,
			_ui_widget_event_handler_function_sp_set_p1_controller_choice,
			_ui_widget_event_handler_function_sp_set_p2_controller_choice,
			_ui_widget_event_handler_function_error_if_no_network_connection,
			_ui_widget_event_handler_function_start_server_if_none_advertised,
			_ui_widget_event_handler_function_net_game_unjoin_player,
			_ui_widget_event_handler_function_close_if_not_editing_profile,
			_ui_widget_event_handler_function_exit_to_xbox_dashboard,
			_ui_widget_event_handler_function_new_campaign_chosen,
			_ui_widget_event_handler_function_new_campaign_decision,
			_ui_widget_event_handler_function_pop_history_stack_once,
			_ui_widget_event_handler_function_difficulty_menu_init,
			_ui_widget_event_handler_function_begin_music_fade_out,
			_ui_widget_event_handler_function_new_game_if_no_plyr_profiles,
			_ui_widget_event_handler_function_exit_gracefully_to_xbox_dashboard,
			_ui_widget_event_handler_function_pause_game_invert_pitch,
			_ui_widget_event_handler_function_start_new_coop_game,
			_ui_widget_event_handler_function_pause_game_invert_spinner_get,
			_ui_widget_event_handler_function_pause_game_invert_spinner_set,
			_ui_widget_event_handler_function_main_menu_quit_game,
			_ui_widget_event_handler_function_mouse__emit_accept_event,
			_ui_widget_event_handler_function_mouse__emit_back_event,
			_ui_widget_event_handler_function_mouse__emit_dpad_left_event,
			_ui_widget_event_handler_function_mouse__emit_dpad_right_event,
			_ui_widget_event_handler_function_mouse_spinner_3wide_click,
			_ui_widget_event_handler_function_controls_screen_init,
			_ui_widget_event_handler_function_video_screen_init,
			_ui_widget_event_handler_function_controls_begin_binding,
			_ui_widget_event_handler_function_gamespy_screen_init,
			_ui_widget_event_handler_function_gamespy_screen_dispose,
			_ui_widget_event_handler_function_gamespy_select_header,
			_ui_widget_event_handler_function_gamespy_select_item,
			_ui_widget_event_handler_function_gamespy_select_button,
			_ui_widget_event_handler_function_plr_prof_init_mouse_set,
			_ui_widget_event_handler_function_plr_prof_change_mouse_set,
			_ui_widget_event_handler_function_plr_prof_init_audio_set,
			_ui_widget_event_handler_function_plr_prof_change_audio_set,
			_ui_widget_event_handler_function_plr_prof_change_video_set,
			_ui_widget_event_handler_function_controls_screen_dispose,
			_ui_widget_event_handler_function_controls_screen_change_set,
			_ui_widget_event_handler_function_mouse__emit_x_event,
			_ui_widget_event_handler_function_gamepad_screen_init,
			_ui_widget_event_handler_function_gamepad_screen_dispose,
			_ui_widget_event_handler_function_gamepad_screen_change_gamepads,
			_ui_widget_event_handler_function_gamepad_screen_select_item,
			_ui_widget_event_handler_function_mouse_screen_defaults,
			_ui_widget_event_handler_function_audio_screen_defaults,
			_ui_widget_event_handler_function_video_screen_defaults,
			_ui_widget_event_handler_function_controls_screen_defaults,
			_ui_widget_event_handler_function_profile_set_edit_begin,
			_ui_widget_event_handler_function_profile_manager_delete,
			_ui_widget_event_handler_function_profile_manager_select,
			_ui_widget_event_handler_function_gamespy_dismiss_error,
			_ui_widget_event_handler_function_server_settings_init,
			_ui_widget_event_handler_function_ss_edit_server_name,
			_ui_widget_event_handler_function_ss_edit_server_password,
			_ui_widget_event_handler_function_ss_start_game,
			_ui_widget_event_handler_function_video_test_dialog_init,
			_ui_widget_event_handler_function_video_test_dialog_dispose,
			_ui_widget_event_handler_function_video_test_dialog_accept,
			_ui_widget_event_handler_function_gamespy_dismiss_filters,
			_ui_widget_event_handler_function_gamespy_update_filter_settings,
			_ui_widget_event_handler_function_gamespy_back_handler,
			_ui_widget_event_handler_function_mouse_spinner_1wide_click,
			_ui_widget_event_handler_function_controls_back_handler,
			_ui_widget_event_handler_function_controls_advanced_launch,
			_ui_widget_event_handler_function_controls_advanced_ok,
			_ui_widget_event_handler_function_mp_pause_menu_open,
			_ui_widget_event_handler_function_mp_game_options_open,
			_ui_widget_event_handler_function_mp_choose_team,
			_ui_widget_event_handler_function_mp_prof_init_vehicle_options,
			_ui_widget_event_handler_function_mp_prof_save_vehicle_options,
			_ui_widget_event_handler_function_single_prev_cl_item_activated,
			_ui_widget_event_handler_function_mp_prof_init_teamplay_options,
			_ui_widget_event_handler_function_mp_prof_save_teamplay_options,
			_ui_widget_event_handler_function_mp_game_options_choose,
			_ui_widget_event_handler_function_emit_custom_activation_event,
			_ui_widget_event_handler_function_plr_prof_cancel_audio_set,
			_ui_widget_event_handler_function_plr_prof_init_network_options,
			_ui_widget_event_handler_function_plr_prof_save_network_options,
			_ui_widget_event_handler_function_credits_post_render,
			_ui_widget_event_handler_function_difficulty_item_select,
			_ui_widget_event_handler_function_credits_initialize,
			_ui_widget_event_handler_function_credits_dispose,
			_ui_widget_event_handler_function_gamespy_get_patch,
			_ui_widget_event_handler_function_video_screen_dispose,
			_ui_widget_event_handler_function_campaign_menu_init,
			_ui_widget_event_handler_function_campaign_menu_continue,
			_ui_widget_event_handler_function_load_game_menu_init,
			_ui_widget_event_handler_function_load_game_menu_dispose,
			_ui_widget_event_handler_function_load_game_menu_activated,
			_ui_widget_event_handler_function_solo_menu_save_checkpoint,
			_ui_widget_event_handler_function_mp_type_set_mode,
			_ui_widget_event_handler_function_checking_for_updates_ok,
			_ui_widget_event_handler_function_checking_for_updates_dismiss,
			_ui_widget_event_handler_function_direct_ip_connect_init,
			_ui_widget_event_handler_function_direct_ip_connect_go,
			_ui_widget_event_handler_function_direct_ip_edit_field,
			_ui_widget_event_handler_function_network_settings_edit_a_port,
			_ui_widget_event_handler_function_network_settings_defaults,
			_ui_widget_event_handler_function_load_game_menu_delete_request,
			_ui_widget_event_handler_function_load_game_menu_delete_finish,

			k_number_of_ui_widget_event_handler_functions,
		};

		enum ui_widget_event : short
		{
			_ui_widget_event_a_button,
			_ui_widget_event_b_button,
			_ui_widget_event_x_button,
			_ui_widget_event_y_button,
			_ui_widget_event_black_button,
			_ui_widget_event_white_button,
			_ui_widget_event_left_trigger,
			_ui_widget_event_right_trigger,
			_ui_widget_event_dpad_up,
			_ui_widget_event_dpad_down,
			_ui_widget_event_dpad_left,
			_ui_widget_event_dpad_right,
			_ui_widget_event_start_button,
			_ui_widget_event_back_button,
			_ui_widget_event_left_thumb,
			_ui_widget_event_right_thumb,
			_ui_widget_event_left_analog_stick_up,
			_ui_widget_event_left_analog_stick_down,
			_ui_widget_event_left_analog_stick_left,
			_ui_widget_event_left_analog_stick_right,
			_ui_widget_event_right_analog_stick_up,
			_ui_widget_event_right_analog_stick_down,
			_ui_widget_event_right_analog_stick_left,
			_ui_widget_event_right_analog_stick_right,
			_ui_widget_event_created,
			_ui_widget_event_deleted,
			_ui_widget_event_get_focus,
			_ui_widget_event_lose_focus,
			_ui_widget_event_left_mouse,
			_ui_widget_event_middle_mouse,
			_ui_widget_event_right_mouse,
			_ui_widget_event_double_click,
			_ui_widget_event_custom_activation,
			_ui_widget_event_post_render,

			k_number_of_ui_widget_events,
		};
	};

	namespace TagGroups
	{
		struct ui_widget_event_handler_reference
		{
			struct __flags
			{
				TAG_FLAG(close_current_widget);
				TAG_FLAG(close_other_widget);
				TAG_FLAG(close_all_widgets);
				TAG_FLAG(open_widget);
				TAG_FLAG(reload_self);
				TAG_FLAG(reload_other_widget);
				TAG_FLAG(give_focus_to_widget);
				TAG_FLAG(run_function);
				TAG_FLAG(replace_self_w_widget);
				TAG_FLAG(go_back_to_previous_widget);
				TAG_FLAG(run_scenario_script);
				TAG_FLAG(try_to_branch_on_failure);
			}; static_assert( sizeof(__flags) == sizeof(long_flags) );

			TAG_FIELD(__flags, flags);
			TAG_ENUM(event_type, Enums::ui_widget_event);
			TAG_ENUM(function, Enums::ui_widget_event_handler_function);
			TAG_FIELD(tag_reference, widget_tag, 'DeLa');
			TAG_FIELD(tag_reference, sound_effect, 'snd!');
			TAG_FIELD(tag_string, script);
		}; static_assert( sizeof(ui_widget_event_handler_reference) == 0x48 ); // max count: 32
	};
};
