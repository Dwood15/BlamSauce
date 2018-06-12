#pragma once

#include <precompile.h>
#include "../../memory/array_yelo.hpp"
#include "../../game/engines/variants.h"
#include "../game/globals.hpp"

namespace Yelo {
	namespace Networking
	{
		// Password for this machine
		wconst char * ServerPassword() {
			{
				auto sv_password = psv_password;
				(void) ((!!((reinterpret_cast<void *>(0)) != sv_password && (reinterpret_cast<void *>(0x1337BEEF)) != sv_password)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != sv_password && CAST_PTR(void*,PTR_NULL) != sv_password", L"_file_name_", (unsigned) (12)), 0));
			}
			auto sv_password = psv_password;
			return sv_password;
		};
		// Remote console password for this machine
		const char * ServerRconPassword() {
			{
				auto sv_rcon_password = psv_rcon_password;
				(void) ((!!((reinterpret_cast<void *>(0)) != sv_rcon_password && (reinterpret_cast<void *>(0x1337BEEF)) != sv_rcon_password)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != sv_rcon_password && CAST_PTR(void*,PTR_NULL) != sv_rcon_password", L"_file_name_", (unsigned) (14)), 0));
			}
			auto sv_rcon_password = psv_rcon_password;
			return sv_rcon_password;
		};
		// Time limit for this machine
		long ServerTimelimit() {
			{
				auto sv_timelimit = psv_timelimit;
				(void) ((!!((reinterpret_cast<void *>(0)) != sv_timelimit && (reinterpret_cast<void *>(0x1337BEEF)) != sv_timelimit)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != sv_timelimit && CAST_PTR(void*,PTR_NULL) != sv_timelimit", L"_file_name_", (unsigned) (24)), 0));
			}
			auto sv_timelimit = (*psv_timelimit));
			return sv_timelimit;
		};

		// Port used to host a server
		long ConnectionPort() {
			{
				auto halo_argv_port = phalo_argv_port;
				(void) ((!!((reinterpret_cast<void *>(0)) != halo_argv_port && (reinterpret_cast<void *>(0x1337BEEF)) != halo_argv_port)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != halo_argv_port && CAST_PTR(void*,PTR_NULL) != halo_argv_port", L"_file_name_", (unsigned) (35)), 0));
			}
			auto halo_argv_port = (*phalo_argv_port));
			return halo_argv_port;
		};
		// Port used to connect to the server
		long ConnectionClientPort() {
			{
				auto halo_argv_client_port = phalo_argv_client_port;
				(void) ((!!((reinterpret_cast<void *>(0)) != halo_argv_client_port && (reinterpret_cast<void *>(0x1337BEEF)) != halo_argv_client_port)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != halo_argv_client_port && CAST_PTR(void*,PTR_NULL) != halo_argv_client_port", L"_file_name_", (unsigned) (45)), 0));
			}
			auto halo_argv_client_port = (*phalo_argv_client_port));
			return halo_argv_client_port;
		};
	};

	namespace Server
	{
		struct s_banlist_entry
		{
			wchar_t player_name[12+1];	// 0x0
			char cd_hash[32];			// 0x1A
			UNKNOWN_TYPE(bool);			// 0x3A
			unsigned char : 8;
			short ban_count;			// 0x3C
			bool banned_to_infinity;	// 0x3E
			unsigned char : 8;
			__time32_t ban_end_time;	// 0x40

			typedef Memory::DynamicArray<s_banlist_entry> array_t;
		}; static_assert( sizeof(s_banlist_entry) == 0x44 );

		struct s_mapcycle_entry
		{
			const char * map_name;		// Both of these are GlobalAlloc'd
			wconst char * variant_name;
		};

		struct s_network_sv_file_globals
		{
			Memory::DynamicArray<s_banlist_entry> banlist;
			Memory::DynamicArray<s_mapcycle_entry> mapcycles; // defined in 'client' builds, but no code which references it
			unsigned long : 32;

		private:
			char banlist_file[0x108];
		};
		static_assert( sizeof(s_network_sv_file_globals) == 0x124 || sizeof(s_network_sv_file_globals) == 0x25C);


		struct s_network_sv_mapcycle_entry
		{
			s_mapcycle_entry definition;
			unsigned long : 32; // ? if this is anything, it isn't a pointer, that I can be sure of
			GameEngine::s_game_variant variant;
		};

		struct s_network_sv_mapcycle_globals
		{
			Memory::GbxArray<s_network_sv_mapcycle_entry> loaded_mapcycles;
			long current_cycle;

			// dedi only: 4CF2C0. loads the map-cycle definitions
		};


		struct s_network_sv_globals
		{
			bool initialized;
			unsigned char : 8; unsigned short : 16;
			uint last_status_display_time; // game_time
			wchar_t server_password[Enums::k_network_server_password_length+1];
			bool single_flag_force_reset;
			unsigned char : 8;
			char banlist_path[MAX_PATH];

			signed long friendly_fire_type;
			char rcon_password[Enums::k_network_server_password_length+1]; unsigned char : 8; unsigned short : 16;

			unsigned long : 32;

			struct {
				char file_name[256];
				char text[256];
			}motd;
		}; static_assert( sizeof(s_network_sv_globals) == 0x334 || sizeof(s_network_sv_globals) == 0x33C) );

		s_network_sv_file_globals* NetworkSvFileGlobals() {
			{
				auto network_sv_file_globals = pnetwork_sv_file_globals;
				(void) ((!!((reinterpret_cast<void *>(0)) != network_sv_file_globals && (reinterpret_cast<void *>(0x1337BEEF)) != network_sv_file_globals)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != network_sv_file_globals && CAST_PTR(void*,PTR_NULL) != network_sv_file_globals", L"_file_name_", (unsigned) (135)), 0));
			}
			auto network_sv_file_globals = pnetwork_sv_file_globals;
			return network_sv_file_globals;
		}

		s_network_sv_mapcycle_globals* NetworkSvMapcycleGlobals() {
			{
				auto network_sv_mapcycle_globals = pnetwork_sv_mapcycle_globals;
				(void) ((!!((reinterpret_cast<void *>(0)) != network_sv_mapcycle_globals && (reinterpret_cast<void *>(0x1337BEEF)) != network_sv_mapcycle_globals)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != network_sv_mapcycle_globals && CAST_PTR(void*,PTR_NULL) != network_sv_mapcycle_globals", L"_file_name_", (unsigned) (137)), 0));
			}
			auto network_sv_mapcycle_globals = pnetwork_sv_mapcycle_globals;
			return network_sv_mapcycle_globals;
		};

		s_network_sv_globals* NetworkSvGlobals() {
			{
				auto network_sv_globals = pnetwork_sv_globals;
				(void) ((!!((reinterpret_cast<void *>(0)) != network_sv_globals && (reinterpret_cast<void *>(0x1337BEEF)) != network_sv_globals)) ||
						  (_wassert(L"CAST_PTR(void*,PTR_UNKNOWN) != network_sv_globals && CAST_PTR(void*,PTR_NULL) != network_sv_globals", L"_file_name_", (unsigned) (147)), 0));
			}
			auto network_sv_globals = pnetwork_sv_globals;
			return network_sv_globals;
		};


		void Initialize() {}
		void Dispose() {}
	};
};
