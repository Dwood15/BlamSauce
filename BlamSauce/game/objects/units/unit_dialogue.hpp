#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Enums
	{
		enum unit_speech_priority : short
		{
			_unit_speech_none,
			_unit_speech_idle,
			_unit_speech_pain,
			_unit_speech_talk,
			_unit_speech_communicate,
			_unit_speech_shout,
			_unit_speech_script,
			_unit_speech_involuntary,
			_unit_speech_exclaim,
			_unit_speech_scream,
			_unit_speech_death,

			k_number_of_unit_speech_priorities, // NUMBER_OF_UNIT_SPEECH_PRIORITIES
		};

		enum unit_scream_type : short
		{
			_unit_scream_type_fear,
			_unit_scream_type_enemy_grenade, // _dialogue_vocalization_hurt_enemy_grenade
			_unit_scream_type_pain,
			_unit_scream_type_maimed_limb,
			_unit_scream_type_mained_head,
			_unit_scream_type_resurrection,

			k_number_of_unit_scream_types, // NUMBER_OF_UNIT_SCREAM_TYPES
		};
	};

	namespace Objects
	{
		struct s_unit_speech
		{
			Enums::unit_speech_priority priority;
			Enums::unit_scream_type scream;
			datum_index sound_definition_index;
			short time_rel_pad0; // time related
			unsigned short pad_unknown;
			long pad_unverified; // haven't verified what is here yet
			byte ai_information[0x20];
		}; static_assert( sizeof(s_unit_speech) == 0x30 );
	};
};
