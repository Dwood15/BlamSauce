#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Enums
	{
		// network protocol version id
		enum network_game_protocol_id : long {
			_network_game_protocol_id_100 = 0x94ECF, //  609999
			_network_game_protocol_id_107 = 0x5BC42F,// 6013999
			_network_game_protocol_id_108 = 0x5BCFE7,// 6016999
			_network_game_protocol_id_109 = 0x96A27, //  616999
		};

		enum {
			// MJ.MN.BD.REV#
			k_game_build_string_length = 15,

			k_game_build_string_major_offset = 0,
			k_game_build_string_major_length = 2,

			k_game_build_string_minor_offset = 3,
			k_game_build_string_minor_length = 2,

			k_game_build_string_build_offset = 6,
			k_game_build_string_build_length = 2,

			k_game_build_string_revision_offset = 9,
			k_game_build_string_revision_length = 4,
		};

		enum game_build_number_index : long_enum
		{
			_game_build_number_index_invalid = NONE,

			_game_build_number_index_100 = 0,
			_game_build_number_index_107,
			_game_build_number_index_108,
			_game_build_number_index_109,
			_game_build_number_index_110,

			k_max_game_build_number_index,
		};

		enum network_game_protocol_id : long_enum;
	};

	typedef char game_build_string_t[Enums::k_game_build_string_length+1];

	namespace BuildNumber
	{
		char* GameBuildString()					PTR_IMP_GET2(game_build_version);// [k_game_build_string_length+1]
		char* GamespyGameBuildString()			PTR_IMP_GET2(game_build_version_gamespy);

		static Enums::network_game_protocol_id IndexToNetworkProtocolId(Enums::game_build_number_index index)
		{
			using namespace Enums;

			switch (index)
			{
				case _game_build_number_index_100:	return _network_game_protocol_id_100;
				case _game_build_number_index_107:	return _network_game_protocol_id_107;
				case _game_build_number_index_108:	return _network_game_protocol_id_108;
				case _game_build_number_index_109:
				case _game_build_number_index_110:	return _network_game_protocol_id_109;

					YELO_ASSERT_CASE_UNREACHABLE();
			}
		}

		DOC_TODO_DEBUG("Update these if you change the platform version OS targets")
		// These are the same build strings the stock game checks when verifying a game save
		static cstring k_binary_compatible_build_numbers_stock[] = {
#if PLATFORM_VERSION == 0x1080
			"01.00.08.0616",
#elif PLATFORM_VERSION == 0x1090
			"01.00.09.0620",
#elif PLATFORM_VERSION == 0x10A0
			"01.00.10.0621",
#endif
			"01.00.00.0564",
			"01.00.01.0580",
			"01.00.02.0581",
		};

		static cstring k_build_number_yelo_current = K_OPENSAUCE_VERSION_HCE_BUILD_NUMBER(PLATFORM_VERSION_BUILD);
		static cstring k_binary_compatible_build_numbers_yelo[] = {
			k_build_number_yelo_current
		};
	static bool GameStateHeaderIsValid_BuildNumberImpl(const GameState::s_header_data& header)
		{
			const tag_string& build_number = header.version;
			if(GameState::YeloGameStateEnabled())
			{
				for (auto game_build_number : k_binary_compatible_build_numbers_yelo)
					if ( !strcmp(game_build_number, build_number) )
						return true;
			}
			else
			{
				for (auto game_build_number : k_binary_compatible_build_numbers_stock)
					if ( !strcmp(game_build_number, build_number) )
						return true;
			}

			return false;
		}

		static __declspec(naked) void GameStateHeaderIsValidHook()
		{
			static const uintptr_t RET_ADDRESS = (uintptr_t)(0x53B83B);

			__asm {
			push	ebp
			call	GameStateHeaderIsValid_BuildNumberImpl
			jmp		RET_ADDRESS
			}
		}

		static __declspec(naked) void GameStateTryAndLoadHook()
		{
			static const uintptr_t RET_ADDRESS_TRUE = GET_FUNC_PTR(GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_TRUE);
			static const uintptr_t RET_ADDRESS_FALSE = GET_FUNC_PTR(GAME_STATE_HEADER_TRY_AND_LOAD_HOOK_RET_FALSE);

			__asm {
			//lea		ebx, [esp+0x158-0x14C]
			push	ebx
			call	GameStateHeaderIsValid_BuildNumberImpl
			test	al, al
			jz		is_invalid
			jmp		RET_ADDRESS_TRUE
			is_invalid:
			jmp		RET_ADDRESS_FALSE
			}
		}


		void Initialize()
		{
			Memory::WriteRelativeJmp(&GameStateHeaderIsValidHook, GET_FUNC_VPTR(GAME_STATE_HEADER_IS_VALID_HOOK), true);
			Memory::WriteRelativeJmp(&GameStateTryAndLoadHook, GET_FUNC_VPTR(GAME_STATE_HEADER_TRY_AND_LOAD_HOOK), true);
		}

		void Dispose()
		{
		}

		void InitializeForNewMap()
		{
			if(GameState::YeloGameStateEnabled())
			{
				GameState::s_header_data* header = GameState::GameStateGlobals()->header;
				strcpy_s(header->version, k_build_number_yelo_current);
			}
		}

		void InitializeForYeloGameState(bool enabled)
		{
		}

		std::array<cstring, Enums::k_max_game_build_number_index> k_game_build_numbers = {
			"01.00.00.0609",
			"01.00.07.0613",
			"01.00.08.0616",
			"01.00.09.0620",
			"01.00.10.0621",
		};


		static cstring k_game_build_numbers_yelo[] = {
			k_build_number_yelo_current
		};

		// Returns true if build_number matches one of the numbers in k_game_build_numbers

		bool StringIsValid(cstring build_number)
		{
			for (auto game_build_number : k_game_build_numbers)
				if ( !strcmp(game_build_number, build_number) )
					return true;

			return false;
		}


		static Enums::game_build_number_index StringToBuildNumberIndex(cstring build_number)
		{
			long_enum index = Enums::_game_build_number_index_invalid;

			for (auto game_build_number : k_game_build_numbers)
			{
				++index;
				if ( !strcmp(game_build_number, build_number) )
					return CAST(Enums::game_build_number_index, index);
			}

			return Enums::_game_build_number_index_invalid;
		}

		// Parses a major.minor build version string, eg "1.07", to a Enums::game_build_number_index
		// Returns _game_build_number_index_invalid if given an unidentified version
		Enums::game_build_number_index ShortStringToBuildNumberIndex(cstring maj_minor_str)
		{
			using namespace Enums;
			// we only compare the first part of the string, which we assume is in a MAJ.MIN format
			const size_t k_cmp_length = NUMBEROF("#.##");

			if ( is_null_or_empty(maj_minor_str) ) return _game_build_number_index_invalid;
			else if ( !strncmp(maj_minor_str, "1.00", k_cmp_length) ) return _game_build_number_index_100;
			else if ( !strncmp(maj_minor_str, "1.07", k_cmp_length) ) return _game_build_number_index_107;
			else if ( !strncmp(maj_minor_str, "1.08", k_cmp_length) ) return _game_build_number_index_108;
			else if ( !strncmp(maj_minor_str, "1.09", k_cmp_length) ) return _game_build_number_index_109;
			else if ( !strncmp(maj_minor_str, "1.10", k_cmp_length) ) return _game_build_number_index_110;

			return _game_build_number_index_invalid;
		}

		// Parses a major.minor build version string, eg "1.07", to the full build number
		// Returns NULL if given an unidentified version
		cstring ShortStringToBuildNumberString(cstring maj_minor_str)
		{
			using namespace Enums;

			auto index = ShortStringToBuildNumberIndex(maj_minor_str);

			if (index > _game_build_number_index_invalid && index < k_max_game_build_number_index)
				return k_game_build_numbers[index];

			return nullptr;
		}

		static Enums::game_build_number_index TryAndGetIndexFromVersionString(cstring version_str)
		{
			auto version_index = Enums::_game_build_number_index_invalid;

			// try full version strings first
			version_index = StringToBuildNumberIndex(version_str);

			// test for short, MAJ.MIN, version strings if that failed
			if (version_index == Enums::_game_build_number_index_invalid)
				version_index = ShortStringToBuildNumberIndex(version_str);

			return version_index;
		}

		void ChangeAdvertisedVersionId(Enums::network_game_protocol_id network_protocol_id)
		{
			using namespace Enums;

			if (network_protocol_id == 0)
				return;

			GET_PTR(network_version_id1) = network_protocol_id;
			GET_PTR(network_version_id2) = network_protocol_id;
			GET_PTR(network_version_id3) = network_protocol_id;
		}

		// If [and_game_build] is true, it will also change the GameState::GameBuildStrings
		bool ChangeAdvertisedVersion(cstring version_str, bool and_game_build)
		{
			using namespace Enums;

			auto version_index = TryAndGetIndexFromVersionString(version_str);

			if (version_index != _game_build_number_index_invalid)
			{
				auto network_protocol_id = IndexToNetworkProtocolId(version_index);
				ChangeAdvertisedVersionId(network_protocol_id);

				if (and_game_build)
				{
					cstring build_str = k_game_build_numbers[version_index];

					strcpy(GameBuildString(), build_str);
					strcpy(GamespyGameBuildString(), build_str);
				}
			}

			return version_index != _game_build_number_index_invalid;
		}

		// Returns the games current advertised version
		Enums::network_game_protocol_id GetAdvertisedVersion()
		{
			// assuming all id's match
			return GET_PTR(network_version_id1);
		}
	};
};
