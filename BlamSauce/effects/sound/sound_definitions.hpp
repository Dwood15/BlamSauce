/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Flags
	{
		enum sound_definition_flags : long_flags
		{
			_sound_definition_fit_to_adpcm_blocksize_bit,
			_sound_definition_split_long_sound_into_permutations_bit,

			k_number_of_sound_definition_flags,

			_sound_definition_reserved2_bit =	// Halo2. always spatialize#always play as 3d sound, even in first person
				k_number_of_sound_definition_flags,
			_sound_definition_reserved3_bit,	// Halo2. never obstruct#disable occlusion/obstruction for this sound
			_sound_definition_reserved4_bit,	// Halo2. internal don't touch
			_sound_definition_reserved5_bit,	// Halo2. use huge sound transmission
			_sound_definition_reserved6_bit,	// Halo2. link count to owner unit
			_sound_definition_reserved7_bit,	// Halo2. pitch range is language
			_sound_definition_reserved8_bit,	// Halo2. don't use sound class speaker flag
			_sound_definition_reserved9_bit,	// Halo2. don't use lipsync data

			// the sound definition's data should never be stored in any sort of 'shared' cache file
			_sound_definition_never_share_resources_yelo_bit,

			k_number_of_sound_definition_flags_yelo,
		};
	};

	namespace TagGroups
	{
		struct s_sound_permutation
		{
			tag_string name;
			real skip_fraction;
			real gain;
			short compression;
			short next_permutation_index;

			datum_index cache_block_index;		// 0x2C
			void* cache_base_address;			// 0x30
			datum_index cache_tag_index;		// 0x34
			//long unused0;						// 0x38, used on the pc. size of the decompressed xbox adpcm samples buffer (cache_base_address)
			//long unused1;						// 0x3C, used on the pc. owner sound tag index
			long decompressed_buffer_size;
			datum_index owner_tag_index;

			// samples' tag_data flags
			enum { _samples_in_data_file_bit = 0 }; // data is in the sounds data file, not the cache file
			tag_data samples;

			tag_data mouth_data;
			tag_data subtitle_data;
		}; static_assert( sizeof(s_sound_permutation) == 0x7C );

		struct s_sound_pitch_range
		{
			tag_string name;
			real natural_pitch;
			real_bounds bend_bounds;
			short actual_permutation_count;
			unsigned short : 16;
			tag_block:8 * sizeof(tag_block) * 1;
			Yelo::TagBlock<s_sound_permutation> permutations;
		}; static_assert( sizeof(s_sound_pitch_range) == 0x48 );

		struct s_sound_definition_playback_parameters
		{
			real_bounds audible_distance;
			real skip_fraction;
			real_bounds random_pitch_bounds;
			angle_bounds cone_angles; // inner, outer
			real outer_cone_gain;
			real gain_modifier;
			real max_bend_per_second;
		};
		struct s_sound_definition_scale_modifiers
		{
			real skip_fraction_modifier;
			real gain_modifier;
			real pitch_modifier;
		};
		struct s_sound_promotion_parameters
		{
			tag_reference sound;
			short count;
			unsigned short : 16;
		};
		struct sound_definition
		{
			enum { k_group_tag = 'snd!' };

			unsigned long flags;
			short sound_class;
			short sample_rate;

			s_sound_definition_playback_parameters playback_parameters;
			// unused, when-scale-is-ZERO, unused, when-scale-is-ONE, unused
			s_sound_definition_scale_modifiers scale_modifiers[5];

			short encoding;
			short compression;

			s_sound_promotion_parameters promotion_parameters;

			tag_data:8 * sizeof(tag_data) * 1;
			Yelo::TagBlock<const s_sound_pitch_range> pitch_ranges;

			bool ResourcesAreSharable() const
			{
				return !TEST_FLAG(flags, Flags::_sound_definition_never_share_resources_yelo_bit);
			}
		}; static_assert( sizeof(sound_definition) == 0xA4 );


		struct looping_sound_definition
		{
			enum { k_group_tag = 'lsnd' };

			unsigned long flags;
			struct s_scale_function
			{
				real detail_sound_period;
				UNKNOWN_TYPE(real); // postprocessed field
				UNKNOWN_TYPE(real); // postprocessed field
			}	scale_zero,
				scale_one;

			datum_index runtime_scripting_sound_index;
			real runtime_maximum_audible_distance;
			unsigned long : 32;
			unsigned long : 32;

			tag_reference continuous_damage_effect;
			tag_block tracks;
			tag_block detail_sounds;
		}; static_assert( sizeof(looping_sound_definition) == 0x54 );
	};
};
