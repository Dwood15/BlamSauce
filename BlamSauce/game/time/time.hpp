/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../configuration.h"
#include "../../cseries/base.h"

namespace Yelo {
	namespace GameState {
		struct s_game_time_globals;

		s_game_time_globals *GameTimeGlobals();
	};

	namespace blam {
		real game_time_get_seconds_per_tick() {
			return K_SECONDS_PER_TICK;
		}

		real game_ticks_to_seconds(long ticks) {
			return CAST(real, ticks) * K_SECONDS_PER_TICK;
		}

		long game_seconds_to_ticks(long seconds) {
			return seconds * K_TICKS_PER_SECOND;
		}

		real game_seconds_to_ticks(real seconds) {
			return seconds * CAST(real, K_TICKS_PER_SECOND);
		}

		long game_seconds_to_ticks_round(real seconds) {
			return CAST(long, game_seconds_to_ticks(seconds));
		}

		game_ticks_t game_time_get() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals && game_time_globals->initialized);

			return game_time_globals->game_time;
		}

		game_time_t game_time_get_elapsed() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals && game_time_globals->initialized);

			return game_time_globals->elapsed_time;
		}

		game_ticks_t local_time_get() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals && game_time_globals->initialized);

			return game_time_globals->game_time;
		}

		game_time_t local_time_get_elapsed() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals && game_time_globals->initialized);

			return game_time_globals->elapsed_time;
		}

		bool game_in_progress() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals);

			if (game_time_globals->initialized) {
				return game_time_globals->active || game_time_globals->paused;
			}

			return false;
		}

		bool game_time_get_paused() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals);

			return game_time_globals->paused;
		}

		void game_time_set_paused(bool paused) {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals);

			if (game_time_globals->initialized) {
				game_time_globals->active = !paused;
			}

			game_time_globals->paused = paused;
		}

		float game_time_get_speed() {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals);

			return game_time_globals->game_speed;
		}

		void game_time_set_speed(float speed) {
			auto game_time_globals = GameState::GameTimeGlobals();
			assert(game_time_globals);

			game_time_globals->game_speed = speed;
		}
	};
};
