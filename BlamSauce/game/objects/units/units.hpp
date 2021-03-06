#pragma once

#include <precompile.h>

namespace Yelo {
	namespace Objects {
		struct s_damage_data;

		struct s_unit_globals_data {
			short:8 * sizeof(short);
			short:8 * sizeof(short);
			bool :8 * sizeof(bool);
			unsigned char : 8;
			unsigned short : 16;
		};
	};

	namespace blam {
		void __cdecl unit_update(const datum_index unit_index);

		void __cdecl unit_set_animation(datum_index unit_index, datum_index animation_graph_index, long animation_index);

		short __cdecl unit_find_nearby_seat(datum_index unit_index, datum_index target_unit_index, __out short &parent_seat_index);

		bool __cdecl unit_can_enter_seat(datum_index unit_index, datum_index target_unit_index, short seat_index, __out datum_index *unit_in_seat_index);

		bool __cdecl unit_enter_seat(datum_index unit_index, datum_index target_unit_index, long seat_index);

		// Calculates the viewing position based on the unit's 'head' marker if it has one. 
		// If not, it will estimate the position based on the object's origin.
		void __cdecl unit_get_camera_position(datum_index unit_index, __out real_point3d *return_position);

		void __cdecl unit_kill(const datum_index unit_index);

		void __cdecl unit_open(datum_index unit_index);

		void __cdecl unit_close(datum_index unit_index);

		void __cdecl unit_scripting_exit_vehicle(datum_index unit_index);

		bool __cdecl unit_try_and_exit_seat(const datum_index unit_index, bool can_run_on_client_side);

		void __cdecl unit_detach_from_parent(const datum_index unit_index);

		void __cdecl unit_exit_seat_end(datum_index unit_index, bool no_network_message, bool can_run_on_client_side, bool);

		bool __cdecl unit_can_see_point(const datum_index unit_index, const real_point3d *point, const real view_radians);

		// Returns the number of frames remaining in an unit's custom animation
		short unit_get_custom_animation_time(datum_index unit_index);

		bool __cdecl unit_start_user_animation(const datum_index unit_index, const datum_index animation_definition_index, const char * animation_name, const bool interpolate);

		void __cdecl unit_animation_start_action(const datum_index unit_index, const Enums::unit_replacement_animation_state action_type);

		void __cdecl unit_animation_set_state(const datum_index unit_index, const Enums::unit_animation_state state);

		void __cdecl unit_drop_current_weapon(const datum_index unit_index, const bool force);

		datum_index __cdecl unit_inventory_get_weapon(const datum_index unit_index, const short index);

		void __cdecl unit_ready_desired_weapon(const datum_index unit_index, const bool force);

		void __cdecl unit_throw_grenade_release(const datum_index unit_index, const sbyte keyframe);

		void __cdecl unit_cause_player_melee_damage(const datum_index unit_index);

		void
		__cdecl unit_damage_aftermath(const datum_index unit_index, const Objects::s_damage_data *damage_data, const short damage_flags, const real shield_amount, const real body_amount, void *arg6,
												const long damage_part);

		void __cdecl unit_set_actively_controlled(const datum_index unit_index, const bool controlled);
	};
};
