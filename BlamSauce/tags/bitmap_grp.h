#pragma once

#include <precompile.h>
#include "../primary.h"
#include "../math/real_math.h"
#include "../math/integer_math.h"
#include "group/markup.h"
#include "../memory/datum_index.h"
#include "group/base.h"
#include "../cseries/base.h"

namespace Yelo {
	namespace Enums {
		enum bitmap_type : short {
			_bitmap_type__2d_texture,
			_bitmap_type__3d_texture,
			_bitmap_type_cube_map,
			_bitmap_type_white,

			_bitmap_type,
		};
		enum bitmap_pixel_format : short {
			_bitmap_pixel_format_a8,
			_bitmap_pixel_format_y8,
			_bitmap_pixel_format_ay8,
			_bitmap_pixel_format_a8y8,
			_bitmap_pixel_format_unused1,
			_bitmap_pixel_format_unused2,
			_bitmap_pixel_format_r5g6b5,
			_bitmap_pixel_format_unused3,
			_bitmap_pixel_format_a1r5g5b5,
			_bitmap_pixel_format_a4r4g4b4,
			_bitmap_pixel_format_x8r8g8b8,
			_bitmap_pixel_format_a8r8g8b8,
			_bitmap_pixel_format_unused4,
			_bitmap_pixel_format_unused5,
			_bitmap_pixel_format_dxt1,
			_bitmap_pixel_format_dxt3,
			_bitmap_pixel_format_dxt5,
			_bitmap_pixel_format_p8_bump,

			_bitmap_pixel_format,
		};
		enum bitmap_group_type : short {
			_bitmap_group_type__2d_textures,
			_bitmap_group_type__3d_textures,
			_bitmap_group_type_cube_maps,
			_bitmap_group_type_sprites,
			_bitmap_group_type_interface_bitmaps,

			k_number_of_bitmap_group_types,
		};
		enum bitmap_group_format : short {
			_bitmap_group_format_compressed_with_color_key_transparency,
			_bitmap_group_format_compressed_with_explicit_alpha,
			_bitmap_group_format_compressed_with_interpolated_alpha,
			_bitmap_group_format__16_bit_color,
			_bitmap_group_format__32_bit_color,
			_bitmap_group_format_monochrome,

			k_number_of_bitmap_group_formats,
		};
		enum bitmap_group_usage : short {
			_bitmap_group_usage_alpha_blend,
			_bitmap_group_usage_default,
			_bitmap_group_usage_height_map,
			_bitmap_group_usage_detail_map,
			_bitmap_group_usage_light_map,
			_bitmap_group_usage_vector_map,

			k_number_of_bitmap_group_usages,

			//_bitmap_group_usage_height_map_blue255,		// Halo2
			//_bitmap_group_usage_embm,						// Halo2. emblem?
			//_bitmap_group_usage_height_map_a8l8,			// Halo2
			//_bitmap_group_usage_height_map_g8b8,			// Halo2
			//_bitmap_group_usage_height_map_g8b8_y_alpha,	// Halo2
		};
		enum sprite_budget : short {
			_sprite_budget__32x32,
			_sprite_budget__64x64,
			_sprite_budget__128x128,
			_sprite_budget__256x256,
			_sprite_budget__512x512,

			_sprite_budget,

			//_sprite_budget__1024x1024,	// Halo2. However, sprite processing fields were hidden from view...
		};
		enum sprite_usage : short {
			_sprite_usage_blend_add_subtract_max,
			_sprite_usage_multiply_min,
			_sprite_usage_double_multiply,

			_sprite_usage,
		};
	};

	namespace Flags {
		enum bitmap_group_flags : unsigned short {
			_bitmap_group_enable_diffusion_dithering_bit,
			_bitmap_group_disable_height_map_compression_bit,
			_bitmap_group_uniform_sprite_sequences_bit,
			_bitmap_group_filthy_sprite_bug_fix_bit,

			k_number_of_bitmap_group_flags,

			_bitmap_group_reserved4_bit =   // Halo2. Use Sharp Bump Filter
			k_number_of_bitmap_group_flags,
			_bitmap_group_unused5_bit,
			_bitmap_group_reserved6_bit,   // Halo2. Use Clamped/Mirrored Bump Filter
			_bitmap_group_reserved7_bit,   // Halo2. Invert Detail Fade
			_bitmap_group_reserved8_bit,   // Halo2. Swap x-y Vector Components
			_bitmap_group_reserved9_bit,   // Halo2. Convert from Signed
			_bitmap_group_reserved10_bit,   // Halo2. Convert to Signed
			_bitmap_group_reserved11_bit,   // Halo2. Import mipmap Chains
			_bitmap_group_reserved12_bit,   // Halo2. Intentionally True Color

			// the bitmap group's data should never be stored in any sort of 'shared' cache file
				_bitmap_group_never_share_resources_yelo_bit,

			k_number_of_bitmap_group_flags_yelo,
		};
	};

	namespace TagGroups {
		struct s_bitmap_group_sprite {
			short bitmap_index;
			unsigned short : 16;
			unsigned long : 32;
			real left;
			real right;
			real top;
			real bottom;
			real_point2d registration_point;
		}; static_assert(sizeof(s_bitmap_group_sprite) == 0x20); // max count: 64

		struct s_bitmap_group_sequence {
			tag_string name;
			short first_bitmap_index;
			short bitmap_count;
			long:8 * sizeof(long) * 4;
			TagBlock <s_bitmap_group_sprite> sprites;
		}; static_assert(sizeof(s_bitmap_group_sequence) == 0x40); // max count: 256

		struct s_bitmap_data {
			struct _flags {
				unsigned short power_of_two_dimensions_bit:1;
				unsigned short compressed_bit:1;
				unsigned short palettized_bit:1;
				unsigned short swizzled_bit:1;
				unsigned short linear_bit:1;
				unsigned short v16u16_bit:1;
				unsigned short orphan_bit:1; // this bitmap and its pixel data are allocated outside of the tag system
				unsigned short cached_bit:1; // _bitmap_cached_bit
				unsigned short in_data_file_bit:1; // data is in the bitmaps data file, not the cache file
			}; static_assert(sizeof(_flags) == sizeof(unsigned short));

			tag signature;
			short width;
			short height;
			short depth;
			short type;
			short format;
			_flags flags;
			point2d registration_point;
			short mipmap_count;
			unsigned short : 16;
			long pixels_offset;

			UNKNOWN_TYPE(long);
			datum_index owner_tag_index;
			datum_index texture_cache_index;
			void        *hardware_format; // IDirect3DBaseTexture9*
			void        *base_address;
		}; static_assert(sizeof(s_bitmap_data) == 0x30); // max count: 2048

		struct s_bitmap_group {
			enum { k_group_tag = 'bitm' };

			////////////////////////////////////////////////////////////////
			// type
			// Type controls bitmap 'geometry'. All dimensions must be a power of two except for SPRITES and INTERFACE BITMAPS:
			//
			// * 2D TEXTURES: Ordinary, 2D textures will be generated.
			// * 3D TEXTURES: Volume textures will be generated from each sequence of 2D texture 'slices'.
			// * CUBE MAPS: Cube maps will be generated from each consecutive set of six 2D textures in each sequence, all faces of a cube map must be square and the same size.
			// * SPRITES: Sprite texture pages will be generated.
			// * INTERFACE BITMAPS: Similar to 2D TEXTURES, but without mipmaps and without the power of two restriction.
			short type;

			////////////////////////////////////////////////////////////////
			// format
			// Format controls how pixels will be stored internally:
			//
			// * COMPRESSED WITH COLOR-KEY TRANSPARENCY: DXT1 compression, uses 4 bits per pixel. 4x4 blocks of pixels are reduced to 2 colors and interpolated, alpha channel uses color-key transparency instead of alpha from the plate (all zero-alpha pixels also have zero-color).
			// * COMPRESSED WITH EXPLICIT ALPHA: DXT2/3 compression, uses 8 bits per pixel. Same as DXT1 without the color key transparency, alpha channel uses alpha from plate quantized down to 4 bits per pixel.
			// * COMPRESSED WITH INTERPOLATED ALPHA: DXT4/5 compression, uses 8 bits per pixel. Same as DXT2/3, except alpha is smoother. Better for smooth alpha gradients, worse for noisy alpha.
			// * 16-BIT COLOR: Uses 16 bits per pixel. Depending on the alpha channel, bitmaps are quantized to either r5g6b5 (no alpha), a1r5g5b5 (1-bit alpha), or a4r4g4b4 (>1-bit alpha).
			// * 32-BIT COLOR: Uses 32 bits per pixel. Very high quality, can have alpha at no added cost. This format takes up the most memory, however. Bitmap formats are x8r8g8b8 and a8r8g8b.
			// * MONOCHROME: Uses either 8 or 16 bits per pixel. Bitmap formats are a8 (alpha), y8 (intensity), ay8 (combined alpha-intensity) and a8y8 (separate alpha-intensity).
			//
			// Note: Height maps (a.k.a. bump maps) should use 32-bit color; this is internally converted to a palettized format which takes less memory.
			short format;

			////////////////////////////////////////////////////////////////
			// usage
			// Usage controls how mipmaps are generated:
			//
			// * ALPHA BLEND: Pixels with zero alpha are ignored in mipmaps, to prevent bleeding the transparent color.
			// * DEFAULT: Downsampling works normally, as in Photoshop.
			// * HEIGHT MAP: The bitmap (normally grayscale) is a height map which gets converted to a bump map. Uses <bump height> below. Alpha is passed through unmodified.
			// * DETAIL MAP: Mipmap color fades to gray, controlled by <detail fade factor> below. Alpha fades to white.
			// * LIGHT MAP: Generates no mipmaps. Do not use!
			// * VECTOR MAP: Used mostly for special effects; pixels are treated as XYZ vectors and normalized after downsampling. Alpha is passed through unmodified.
			short usage;
			unsigned short flags;

			////////////////////////////////////////////////////////////////
			// post-processing
			// These properties control how mipmaps are post-processed.
			real_fraction detail_fade_factor;
			real_fraction sharpen_amount;
			real_fraction bump_height;

			////////////////////////////////////////////////////////////////
			// sprite processing
			// When creating a sprite group, specify the number and size of textures that the group is allowed to occupy. During importing, you'll receive feedback about how well the alloted space was used.
			short sprite_budget_size;
			short sprite_budget_count;

			////////////////////////////////////////////////////////////////
			// color plate
			// The original TIFF file used to import the bitmap group.
			short color_plate_width;
			short color_plate_height;
			tag_data compressed_color_plate_data;

			////////////////////////////////////////////////////////////////
			// processed pixel data
			// Pixel data after being processed by the tool.
			tag_data processed_pixel_data;

			////////////////////////////////////////////////////////////////
			// miscellaneous
			real blur_filter_size;
			real alpha_bias;
			short mipmap_count;

			////////////////////////////////////////////////////////////////
			// ...more sprite processing
			// Sprite usage controls the background color of sprite plates.
			short sprite_usage;
			short sprite_spacing;
			unsigned short : 16;
			TagBlock <s_bitmap_group_sequence> sequences;
			TagBlock <s_bitmap_data>           bitmaps;

			bool ResourcesAreSharable() const {
				return
					!TEST_FLAG(flags, Flags::_bitmap_group_never_share_resources_yelo_bit) &&
					// it makes no sense to ever store lightmaps in a shared cache
					usage != Enums::_bitmap_group_usage_light_map;
			}
		};

		static_assert(sizeof(s_bitmap_group) == 0x6C);
	};
};
