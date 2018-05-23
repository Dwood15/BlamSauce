#pragma once

#include <precompile.h>
#include "../material/material_effect_definitions.hpp"
#include "../../game/objects/object_definitions.hpp"
#include "../../math/periodic_functions.h"

namespace Yelo {
	namespace Enums {
		enum shader_type {
			_shader_type_screen,// sscr
			_shader_type_effect,
			_shader_type_decal,   // sdec

			_shader_type_environment,
			_shader_type_model,
			_shader_type_transparent_generic,
			_shader_type_transparent_chicago,
			_shader_type_transparent_chicago_extended,
			_shader_type_transparent_water,
			_shader_type_transparent_glass,
			_shader_type_transparent_meter,
			_shader_type_transparent_plasma,

			k_number_of_shader_types,
		};
		enum environment_shader_type : short {
			_environment_shader_type_normal,
			_environment_shader_type_blended,
			_environment_shader_type_blended_base_specular,

			_environment_shader_type,
		};
		enum detail_map_function : short {
			_detail_map_function_double_biased_multiply,
			_detail_map_function_multiply,
			_detail_map_function_double_biased_add,

			_detail_map_function,
		};
		enum reflection_type : short {
			_reflection_type_bumped_cube_map,
			_reflection_type_flat_cube_map,
			_reflection_type_bumped_radiosity,

			_reflection_type,
		};
		enum detail_mask : short {
			_detail_mask_none,
			_detail_mask_reflection_mask_inverse,
			_detail_mask_reflection_mask,
			_detail_mask_self_illumination_mask_inverse,
			_detail_mask_self_illumination_mask,
			_detail_mask_change_color_mask_inverse,
			_detail_mask_change_color_mask,
			_detail_mask_multipurpose_map_alpha_inverse,
			_detail_mask_multipurpose_map_alpha,

			_detail_mask,
		};
		enum first_map_type : short {
			_first_map_type__2d_map,
			_first_map_type_first_map_is_reflection_cube_map,
			_first_map_type_first_map_is_object_centered_cube_map,
			_first_map_type_first_map_is_viewer_centered_cube_map,

			_first_map_type,
		};
		enum shader_framebuffer_blend_function : short {
			_shader_framebuffer_blend_function_alpha_blend,
			_shader_framebuffer_blend_function_multiply,
			_shader_framebuffer_blend_function_double_multiply,
			_shader_framebuffer_blend_function_add,
			_shader_framebuffer_blend_function_subtract,
			_shader_framebuffer_blend_function_component_min,
			_shader_framebuffer_blend_function_component_max,
			_shader_framebuffer_blend_function_alpha_multiply_add,

			_shader_framebuffer_blend_function,
		};
		enum shader_framebuffer_fade_mode : short {
			_shader_framebuffer_fade_mode_none,
			_shader_framebuffer_fade_mode_fade_when_perpendicular,
			_shader_framebuffer_fade_mode_fade_when_parallel,

			_shader_framebuffer_fade_mode,
		};
		enum color_function : short {
			_color_function_current,
			_color_function_next_map,
			_color_function_multiply,
			_color_function_double_multiply,
			_color_function_add,
			_color_function_add_signed_current,
			_color_function_add_signed_next_map,
			_color_function_subtract_current,
			_color_function_subtract_next_map,
			_color_function_blend_current_alpha,
			_color_function_blend_current_alpha_inverse,
			_color_function_blend_next_map_alpha,
			_color_function_blend_next_map_alpha_inverse,

			_color_function,
		};
		enum color_input : short {
			_color_input_zero,
			_color_input_one,
			_color_input_one_half,
			_color_input_negative_one,
			_color_input_negative_one_half,
			_color_input_map_color_0,
			_color_input_map_color_1,
			_color_input_map_color_2,
			_color_input_map_color_3,
			_color_input_vertex_color_0__diffuse_light,
			_color_input_vertex_color_1__fade_perpendicular,
			_color_input_scratch_color_0,
			_color_input_scratch_color_1,
			_color_input_constant_color_0,
			_color_input_constant_color_1,
			_color_input_map_alpha_0,
			_color_input_map_alpha_1,
			_color_input_map_alpha_2,
			_color_input_map_alpha_3,
			_color_input_vertex_alpha_0__fade_none,
			_color_input_vertex_alpha_1__fade_perpendicular,
			_color_input_scratch_alpha_0,
			_color_input_scratch_alpha_1,
			_color_input_constant_alpha_0,
			_color_input_constant_alpha_1,

			_color_input,
		};
		enum color_input_mapping : short {
			_color_input_mapping_clamp_x,
			_color_input_mapping__1__clamp_x,
			_color_input_mapping__2,
			_color_input_mapping__1__2,
			_color_input_mapping_clamp_x__1_2,
			_color_input_mapping__1_2__clamp_x,
			_color_input_mapping_x,
			_color_input_mapping_x_1,

			_color_input_mapping,
		};
		enum color_output : short {
			_color_output_discard,
			_color_output_scratch_color_0__final_color,
			_color_output_scratch_color_1,
			_color_output_vertex_color_0,
			_color_output_vertex_color_1,
			_color_output_map_color_0,
			_color_output_map_color_1,
			_color_output_map_color_2,
			_color_output_map_color_3,

			_color_output,
		};
		enum color_output_function : short {
			_color_output_function_multiply,
			_color_output_function_dot_product,

			_color_output_function,
		};
		enum output_mapping : short {
			_output_mapping_identity,
			_output_mapping_scale_by_1_2,
			_output_mapping_scale_by_2,
			_output_mapping_scale_by_4,
			_output_mapping_bias_by_1_2,
			_output_mapping_expand_normal,

			_output_mapping,
		};
		enum alpha_input : short {
			_alpha_input_zero,
			_alpha_input_one,
			_alpha_input_one_half,
			_alpha_input_negative_one,
			_alpha_input_negative_one_half,
			_alpha_input_map_alpha_0,
			_alpha_input_map_alpha_1,
			_alpha_input_map_alpha_2,
			_alpha_input_map_alpha_3,
			_alpha_input_vertex_alpha_0__fade_none,
			_alpha_input_vertex_alpha_1__fade_perpendicular,
			_alpha_input_scratch_alpha_0,
			_alpha_input_scratch_alpha_1,
			_alpha_input_constant_alpha_0,
			_alpha_input_constant_alpha_1,
			_alpha_input_map_blue_0,
			_alpha_input_map_blue_1,
			_alpha_input_map_blue_2,
			_alpha_input_map_blue_3,
			_alpha_input_vertex_blue_0__blue_light,
			_alpha_input_vertex_blue_1__fade_parallel,
			_alpha_input_scratch_blue_0,
			_alpha_input_scratch_blue_1,
			_alpha_input_constant_blue_0,
			_alpha_input_constant_blue_1,

			_alpha_input,
		};
		enum alpha_output : short {
			_alpha_output_discard,
			_alpha_output_scratch_alpha_0__final_alpha,
			_alpha_output_scratch_alpha_1,
			_alpha_output_vertex_alpha_0__fog,
			_alpha_output_vertex_alpha_1,
			_alpha_output_map_alpha_0,
			_alpha_output_map_alpha_1,
			_alpha_output_map_alpha_2,
			_alpha_output_map_alpha_3,

			_alpha_output,
		};

		enum shader_effect_secondary_map_anchor : short {
			_shader_effect_secondary_map_anchor_with_primary,
			_shader_effect_secondary_map_anchor_with_screen_space,
			_shader_effect_secondary_map_anchor_zsprite,

			_shader_effect_secondary_map_anchor,
		};
	};

	namespace Flags {
		enum shader_extension_usage : unsigned short {
			_shader_extension_usage_none                       = 0,
			_shader_extension_usage_normal_map                 = 1 << 0,
			_shader_extension_usage_detail_normal              = 1 << 1,
			_shader_extension_usage_specular_map               = 1 << 2,
			_shader_extension_usage_specular_lighting          = 1 << 3,
			_shader_extension_usage_directional_lightmaps_diff = 1 << 4,
			_shader_extension_usage_directional_lightmaps_spec = 1 << 5,
			_shader_extension_usage_depth_fade                 = 1 << 6,

			_shader_extension_usage,
		};

		enum shader_extension_usage_bit : unsigned short {
			_shader_extension_usage_bit_normal_map,
			_shader_extension_usage_bit_detail_normal,
			_shader_extension_usage_bit_specular_map,
			_shader_extension_usage_bit_specular_lighting,
			_shader_extension_usage_bit_directional_lightmaps_diff,
			_shader_extension_usage_bit_directional_lightmaps_spec,
			_shader_extension_usage_bit_depth_fade,

			_shader_extension_usage_bit,
		};
	};

	namespace TagGroups {
		struct s_shader_animation_function {
			Enums::object_function_reference u_animation_source;
			Enums::periodic_function         u_animation_function;
			real                             animation_period;
			real                             animation_phase;
			real                             animation_scale;
		}; static_assert(sizeof(s_shader_animation_function) == 16);
		struct s_shader_animation {
			s_shader_animation_function anim_u, anim_v, anim_rot;
			real_point2d                rotation_animation_center;
		}; static_assert(sizeof(s_shader_animation) == 56);
		struct s_shader_texture_animation_function {
			////////////////////////////////////////////////////////////////
			// texture scrolling animation
			// Scrolls all 2D maps simultaneously.
			Enums::periodic_function animation_function;
			unsigned short : 16;
			real animation_period;
			real animation_scale;
		}; static_assert(sizeof(s_shader_texture_animation_function) == 12);
		struct s_shader_scaled_map {
			real          scale;
			tag_reference map;
		}; static_assert(sizeof(s_shader_scaled_map) == 20);
		struct s_shader_color_function {
			real_rgb_color           on_color;
			real_rgb_color           off_color;
			Enums::periodic_function animation_function;
			unsigned short : 16;
			real animation_period;
			real animation_phase;
			long:8 * sizeof(long) * 6;
		}; static_assert(sizeof(s_shader_color_function) == 60);
		struct s_shader_shader_framebuffer_function {
			Enums::shader_framebuffer_blend_function shader_framebuffer_blend_function;
			Enums::shader_framebuffer_fade_mode      shader_framebuffer_fade_mode;
			Enums::object_function_reference         shader_framebuffer_fade_source;
			unsigned short : 16;
		}; static_assert(sizeof(s_shader_shader_framebuffer_function) == 8);
		struct s_shader_radiosity_properties {
			struct __flags {
				Yelo::byte_flags alpha_tested_bit:1;
				Yelo::byte_flags decal_bit:1;
				Yelo::byte_flags two_sided_bit:1;
				Yelo::byte_flags first_map_is_in_screenspace_bit:1;
				Yelo::byte_flags draw_before_water_bit:1;
				Yelo::byte_flags ignore_effect_bit:1;
				Yelo::byte_flags scale_first_map_with_distance_bit:1;
				Yelo::byte_flags numeric_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(byte_flags));

			byte                                 numeric_counter_limit;
			__flags                              flags;
			Enums::first_map_type                first_map_type;
			s_shader_shader_framebuffer_function shader_framebuffer_function;
		}; static_assert(sizeof(s_shader_radiosity_properties) == 12);
		//////////////////////////////////////////////////////////////////////////
		struct _shader_definition {
			struct __flags {
				unsigned short simple_parameterization_bit:1;
				unsigned short ignore_normals_bit:1;
				unsigned short transparent_lit_bit:1;
			};

			struct __flags_1 {
				unsigned short unused_bit:1;
			}; static_assert(sizeof(__flags_1) == sizeof(unsigned short));

			struct {
				////////////////////////////////////////////////////////////////
				// radiosity properties
				__flags             flags;
				Yelo::Enums::detail_level detail_level;
				real                power;
				real_rgb_color      color_of_emitted_light;
				real_rgb_color      tint_color;
			} radiosity;

			////////////////////////////////////////////////////////////////
			// physics properties
			__flags_1            flags_1;
			Enums::material_type material_type;

			Enums::shader_type shader_type;
			short              extension_usage;
		}; static_assert(sizeof(_shader_definition) == 0x28);

		struct s_shader_definition {
			enum { k_group_tag = 'shdr' };

			_shader_definition shader;
		}; static_assert(sizeof(_shader_definition) == 0x28);
		//////////////////////////////////////////////////////////////////////////
		struct s_shader_effect_extension {
			byte:8 * sizeof(byte) * 4;

			// Depth fade
			real depth_fade_distance;
			real camera_fade_distance;

			tag_block:8 * sizeof(tag_block) * 3;
		};
		struct _shader_effect_definition {
			struct _flags {
				unsigned short sort_bias_bit:1;
				unsigned short nonlinear_tint_bit:1;
				unsigned short dont_overdraw_fp_weapon_bit:1;
			}; static_assert(sizeof(_flags) == sizeof(unsigned short));
			struct _map_flags {
				unsigned short unfiltered_bit:1;
			}; static_assert(sizeof(_map_flags) == sizeof(unsigned short));

			_flags                                          flags;
			Enums::shader_framebuffer_blend_function        blend_function;
			Enums::shader_framebuffer_fade_mode             fade_mode;
			_map_flags                                      map_flags;
			Yelo::TagBlock<const s_shader_effect_extension> shader_extension;
			PAD128;

			struct {
				tag_reference                             bitmap;
				Enums::shader_effect_secondary_map_anchor anchor;
				_map_flags                                flags;
				s_shader_animation                        animation;
			}                                               secondary_map;
			unsigned long : 32;
			real z_sprite_radius_scale;
			PAD128;
			unsigned long : 32;
		}; static_assert(sizeof(_shader_effect_definition) == 0x8C);

		// the following tags/blocks have inline instances of this:
		// contrail, lightning_shader_block, particle, particle_system_type_particle_states_block
		// not all of those field sets expose all the available tag fields...
		struct s_shader_effect : s_shader_definition {
			enum { k_group_tag = 'seff' };

			_shader_effect_definition effect;
		}; static_assert(sizeof(s_shader_effect) == 0xB4);

		//////////////////////////////////////////////////////////////////////////
		struct s_shader_environment_extension {
			struct _flags {
				unsigned short do_not_use_dlms_bit:1;
			}; static_assert(sizeof(_flags) == sizeof(unsigned short));

			struct __specular_color_flags {
				unsigned short alpha_as_exponent_mask_bit:1;
			}; static_assert(sizeof(__specular_color_flags) == sizeof(unsigned short));

			_flags flags;
			byte : 16;
			real bump_amount;

			tag_reference          specular_color_map;
			real                   specular_color_coefficient;
			real                   specular_color_exponent;
			__specular_color_flags specular_color_flags;
			byte		:8 * sizeof(byte) * 2;

			real_fraction  perpendicular_brightness;
			real_rgb_color perpendicular_tint_color;
			real_fraction  parallel_brightness;
			real_rgb_color parallel_tint_color;

			real specular_lighting_exponent;
			real specular_lighting_coefficient;

			tag_block:8 * sizeof(tag_block) * 2;
		};
		struct _shader_environment_definition {
			struct _flags {
				unsigned short alpha_tested_bit:1;
				unsigned short bump_map_is_specular_mask_bit:1;
				unsigned short true_atmospheric_fog_bit:1;
			}; static_assert(sizeof(_flags) == sizeof(unsigned short));

			////////////////////////////////////////////////////////////////
			// environment shader
			// Setting <true atmospheric fog> enables per-pixel atmospheric fog (for models) but disables point/spot lights, planar fog, and the ability to control the atmospheric fog density for this shader.
			_flags flags;

			////////////////////////////////////////////////////////////////
			// environment shader type
			// Controls how diffuse maps are combined:
			// 
			// NORMAL:
			// Secondary detail map alpha controls blend between primary and secondary detail map. Specular mask is alpha of blended primary and secondary detail map alpha multiplied by alpha of micro detail map.
			// 
			// BLENDED:
			// Base map alpha controls blend between primary and secondary detail map. Specular mask is alpha of blended primary and secondary detail map alpha multiplied by alpha of micro detail map.
			// 
			// BLENDED BASE SPECULAR:
			// Same as BLENDED, except specular mask is alpha is base map times alpha of micro detail map.
			Enums::environment_shader_type type;

			////////////////////////////////////////////////////////////////
			// lens flares
			struct {
				real          spacing;
				tag_reference reference;
			}                              lens_flare;

			Yelo::TagBlock<const s_shader_environment_extension> shader_extension;
			byte:8 * sizeof(byte) * 44 - sizeof(tag_block);

			////////////////////////////////////////////////////////////////
			// diffuse properties
			struct {
				struct _flags {
					unsigned short rescale_detail_maps_bit:1;
					unsigned short rescale_bump_map_bit:1;
				}; static_assert(sizeof(_flags) == sizeof(unsigned short));

				_flags flags;
				unsigned short             : 16;
				long:8 * sizeof(long) * 6;
				tag_reference              base_map;
				long:8 * sizeof(long) * 6;
				Enums::detail_map_function detail_map_function;
				unsigned short : 16;
				s_shader_scaled_map        primary_detail_map;
				s_shader_scaled_map        secondary_detail_map;
				long:8 * sizeof(long) * 6;
				Enums::detail_map_function micro_detail_map_function;
				unsigned short : 16;
				s_shader_scaled_map micro_detail_map;
				real_rgb_color      material_color;
				long:8 * sizeof(long) * 3;
			}                                                    diffuse;

			////////////////////////////////////////////////////////////////
			// bump properties
			// Perforated (alpha-tested) shaders use alpha in bump map.
			struct {
				s_shader_scaled_map bump_map;
				real                pad_; // postprocessed
				real                pad_; // postprocessed
				long:8 * sizeof(long) * 4;
			}                                                    bump;

			////////////////////////////////////////////////////////////////
			// texture scrolling animation
			// Scrolls all 2D maps simultaneously.
			s_shader_texture_animation_function texture_scrolling[2];
			long:8 * sizeof(long) * 6;

			////////////////////////////////////////////////////////////////
			// self-illumination properties
			// There are three self-illumination effects which are added together. Each effect has an <on color>, used when the shader is active, and an <off color>, used when the shader is not active. The self-illumination map is used as follows:
			// * RED: primary mask
			// * GREEN: secondary mask
			// * BLUE: plasma mask
			// * ALPHA: plasma animation reference
			// 
			// Each effect also has an animation <function>, <period> and <phase>, used when the shader is active. The primary and secondary effects simply modulate the <on color> by the animation value to produce an animation color, and then blend between the animation color and the <off color> based on the shader's activation level, and finally modulate by the mask.
			// 
			// The plasma shader compares the animation value with the alpha channel of the map (the plasma animation reference) and produces a high value when they are similar and a dark value when they are different. This value modulates the <plasma on color> to produce a plasma animation color, and the rest proceeds just like the primary and secondary effects.
			struct {
				struct _flags {
					unsigned short unfiltered_bit:1;
				}; static_assert(sizeof(_flags) == sizeof(unsigned short));

				_flags flags;
				unsigned short          : 16;
				long:8 * sizeof(long) * 6;
				s_shader_color_function color_functions[3];
				s_shader_scaled_map     map;
				long:8 * sizeof(long) * 6;
			}                                   self_illumination;

			////////////////////////////////////////////////////////////////
			// specular properties
			// Controls dynamic specular highlights. The highlight is modulated by <brightness> as well as a blend between <perpendicular color> and <parallel color>.
			// 
			// Set <brightness> to zero to disable.
			struct {
				struct _flags {
					unsigned short overbright_bit:1;
					unsigned short extra_shiny_bit:1;
					unsigned short lightmap_is_specular_bit:1;
				}; static_assert(sizeof(_flags) == sizeof(unsigned short));

				_flags flags;
				unsigned short : 16;
				long:8 * sizeof(long) * 4;
				real_fraction  brightness;
				long:8 * sizeof(long) * 5;
				real_rgb_color perpendicular_color;
				real_rgb_color parallel_color;
				long:8 * sizeof(long) * 4;
			}                                   specular;

			////////////////////////////////////////////////////////////////
			// reflection properties
			// Controls environment cube map reflections. The color of the cube map is "tinted" by a blend between <perpendicular color> and <parallel color> from the SPECULAR PROPERTIES above, and then modulated by a blend between <perpendicular brightness> and <parallel brightness>.
			// 
			// BUMPED CUBE MAP:
			// This type of reflection uses the shader's bump map (if it exists) to affect the reflection, as well as the perpendicular and parallel brightness (i.e. the "fresnel" effect).
			// 
			// FLAT CUBE MAP:
			// This is the fastest type of reflection. The bump map is used to attenuate the fresnel effect, but the reflection image itself is not bumped.
			// 
			// Clear <reflection cube map> or set both <perpendicular brightness> and <parallel brightness> to zero to disable.
			struct {
				struct _flags {
					unsigned short dynamic_mirror_bit:1;
				}; static_assert(sizeof(_flags) == sizeof(unsigned short));

				_flags                 flags;
				Enums::reflection_type type;
				real_fraction          lightmap_brightness_scale;
				long:8 * sizeof(long) * 7;
				real_fraction          perpendicular_brightness;
				real_fraction          parallel_brightness;
				long:8 * sizeof(long) * 4;
				long:8 * sizeof(long) * 2;
				long:8 * sizeof(long) * 4;
				tag_reference          cube_map;
				long:8 * sizeof(long) * 4;
			}                                   reflection;
		}; static_assert(sizeof(_shader_environment_definition) == 0x31C);

		struct s_shader_environment_definition : s_shader_definition {
			enum { k_group_tag = 'senv' };

			_shader_environment_definition environment;
		}; static_assert(sizeof(s_shader_environment_definition) == 0x344); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct s_shader_model_extension {
			struct __specular_color_flags {
				unsigned short alpha_as_exponent_mask_bit:1;
			}; static_assert(sizeof(__specular_color_flags) == sizeof(unsigned short));

			struct __diffuse_lighting_flags {
				unsigned short do_not_use_dlms_bsp_bit:1;
			}; static_assert(sizeof(__diffuse_lighting_flags) == sizeof(unsigned short));

			struct s_map {
				tag_reference map;
				union {
					byte:8 * sizeof(byte) * 16;
					struct {
						real coefficient; //used by all
						union {
							struct {
								unsigned long : 32;
								real                   exponent;  //only used by specular color
								__specular_color_flags flags;
							};
							struct {
								real scale;  //only used by detail normals
								real v_scale;  //only used by detail normals
							};
						};
					};
				}             modifiers;
			};

			s_map specular_color;   //32
			s_map base_normal;   //32
			s_map detail_normals[2];  //64

			real_fraction  perpendicular_brightness;
			real_rgb_color perpendicular_tint_color;
			real_fraction  parallel_brightness;
			real_rgb_color parallel_tint_color;

			__diffuse_lighting_flags diffuse_lighting_flags;
			unsigned short : 16;
			unsigned long  : 32;

			real specular_lighting_exponent;
			real specular_lighting_coefficient;

			byte:8 * sizeof(byte) * 16;
		};
		struct _shader_model_definition {
			struct __flags {
				unsigned short detail_after_reflection_bit:1;
				unsigned short two_sided_bit:1;
				unsigned short not_alpha_tested_bit:1;
				unsigned short alpha_blended_decal_bit:1;
				unsigned short true_atmospheric_fog_bit:1;
				unsigned short disable_two_sided_culling_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			struct __flags_1 {
				unsigned short no_random_phase_bit:1;
			}; static_assert(sizeof(__flags_1) == sizeof(unsigned short));

			////////////////////////////////////////////////////////////////
			// model shader
			// Setting <true atmospheric fog> enables per-pixel atmospheric fog but disables point/spot lights, planar fog, and the ability to control the atmospheric fog density for this shader.
			__flags flags;
			unsigned short : 16;
			long:8 * sizeof(long) * 3;
			real_fraction  translucency;
			long:8 * sizeof(long) * 4;

			////////////////////////////////////////////////////////////////
			// change color
			// Change color is used to recolor the diffuse map, it affects pixels based on the BLUE channel of the multipurpose map.
			Enums::object_change_color_reference change_color_source;
			unsigned short : 16;
			long:8 * sizeof(long) * 7;

			struct {
				////////////////////////////////////////////////////////////////
				// self-illumination
				// Self-illumination adds diffuse light to pixels based on the GREEN channel of the multipurpose map. The external self-illumination color referenced by <color source> is modulated by the self-illumination animation.
				__flags_1 flags_1;
				unsigned short : 16;
				Enums::object_change_color_reference color_source;
				Enums::periodic_function             animation_function;
				real                                 animation_period;
				real_rgb_color                       animation_color_lower_bound;
				real_rgb_color                       animation_color_upper_bound;
				long:8 * sizeof(long) * 3;
			}              self_illumination;

			struct { // 0x9C
				////////////////////////////////////////////////////////////////
				// maps
				// Base map alpha is used for alpha-testing.
				// 
				// Multipurpose map is used for the following:
				// * RED: specular reflection mask (modulates reflections)
				// * GREEN: self-illumination mask (adds to diffuse light)
				// * BLUE: primary change color mask (recolors diffuse map)
				// * ALPHA: auxiliary mask
				// 
				// Note that when DXT1 compressed color-key textures are used for the multipurpose map (as they should be normally), the alpha channel is 1-bit and any non-zero alpha pixels must have zero-color, therefore the secondary change color mask cannot affect pixels already affected by any of the other channels.
				// 
				// Detail map affects diffuse map, and optionally affects reflection if <detail after reflection> flag is set.
				real                                           map_u_scale;
				real                                           map_v_scale;
				tag_reference                                  base_map;
				long:8 * sizeof(long) * 2;
				tag_reference                                  multipurpose_map;
				long:8 * sizeof(long) * 2;
				Yelo::Enums::detail_function                         detail_function;
				Enums::detail_mask                             detail_mask;
				s_shader_scaled_map                            detail_map;
				real                                           detail_map_v_scale;
				Yelo::TagBlock<const s_shader_model_extension> shader_extension;
				s_shader_animation                             animation;
				long:8 * sizeof(long) * 2;
			}              maps;

			struct {
				////////////////////////////////////////////////////////////////
				// reflection properties
				real           reflection_falloff_distance;
				real           reflection_cutoff_distance;
				real_fraction  perpendicular_brightness;
				real_rgb_color perpendicular_tint_color;
				real_fraction  parallel_brightness;
				real_rgb_color parallel_tint_color;
				tag_reference  reflection_cube_map;
			}              reflection_properties;

			long:8 * sizeof(long) * 4;
			unsigned long : 32;
			long:8 * sizeof(long) * 4;
			long:8 * sizeof(long) * 8;
		}; static_assert(sizeof(_shader_model_definition) == 0x190);

		struct s_shader_model_definition : s_shader_definition {
			enum { k_group_tag = 'soso' };

			_shader_model_definition model;
		}; static_assert(sizeof(s_shader_model_definition) == 0x1B8); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct s_shader_transparent_layer {
			tag_reference shader;
		}; static_assert(sizeof(s_shader_transparent_layer) == 0x10); // max count: 4
		struct s_shader_transparent_chicago_map {
			struct __flags {
				unsigned short unfiltered_bit:1;
				unsigned short alpha_replicate_bit:1;
				unsigned short u_clamped_bit:1;
				unsigned short v_clamped_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			__flags flags;
			unsigned short        : 16;
			long:8 * sizeof(long) * 10;
			Enums::color_function color_function;
			Enums::color_function alpha_function;
			long:8 * sizeof(long) * 9;
			real                  map_u_scale;
			real                  map_v_scale;
			real                  map_u_offset;
			real                  map_v_offset;
			real                  map_rotation;
			real_fraction         mipmap_bias;
			tag_reference         map;
			long:8 * sizeof(long) * 10;

			////////////////////////////////////////////////////////////////
			// 2D texture animation
			s_shader_animation map_animation;
		}; static_assert(sizeof(s_shader_transparent_chicago_map) == 0xDC); // max count: 4
		struct s_shader_transparent_chicago_base {
			struct __extra_flags {
				unsigned long don_t_fade_active_camouflage_bit:1;
				unsigned long numeric_countdown_timer_bit:1;
			}; static_assert(sizeof(__extra_flags) == sizeof(unsigned long));

			////////////////////////////////////////////////////////////////
			// chicago shader
			s_shader_radiosity_properties radiosity_properties;

			////////////////////////////////////////////////////////////////
			// lens flares
			real          lens_flare_spacing;
			tag_reference lens_flare;
		};
		//////////////////////////////////////////////////////////////////////////
		struct _shader_transparent_chicago_definition : s_shader_transparent_chicago_base {
			Yelo::TagBlock<const s_shader_transparent_layer>       extra_layers;
			Yelo::TagBlock<const s_shader_transparent_chicago_map> maps;
			__extra_flags                                          extra_flags;
			long:8 * sizeof(long) * 2;
		};

		struct s_shader_transparent_chicago_definition : s_shader_definition {
			enum { k_group_tag = 'schi' };

			_shader_transparent_chicago_definition transparent_chicago;
		}; static_assert(sizeof(s_shader_transparent_chicago_definition) == 0x6C); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct _shader_transparent_chicago_extended_definition : s_shader_transparent_chicago_base {
			Yelo::TagBlock<const s_shader_transparent_layer>       extra_layers;
			Yelo::TagBlock<const s_shader_transparent_chicago_map> _4_stage_maps;
			Yelo::TagBlock<const s_shader_transparent_chicago_map> _2_stage_maps;
			__extra_flags                                          extra_flags;
			long:8 * sizeof(long) * 2;
		};

		struct s_shader_transparent_chicago_extended_definition : s_shader_definition {
			enum { k_group_tag = 'scex' };

			_shader_transparent_chicago_extended_definition transparent_chicago_extended;
		}; static_assert(sizeof(s_shader_transparent_chicago_extended_definition) == 0x78); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct s_shader_transparent_generic_map {
			struct __flags {
				unsigned short unfiltered_bit:1;
				unsigned short u_clamped_bit:1;
				unsigned short v_clamped_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			__flags flags;
			unsigned short : 16;
			real          map_u_scale;
			real          map_v_scale;
			real          map_u_offset;
			real          map_v_offset;
			real          map_rotation;
			real_fraction mipmap_bias;
			tag_reference map;

			////////////////////////////////////////////////////////////////
			// 2D texture animation
			s_shader_animation map_animation;
		}; static_assert(sizeof(s_shader_transparent_generic_map) == 0x64); // max count: 4
		struct s_shader_transparent_generic_stage {
			struct __flags {
				unsigned short color_mux_bit:1;
				unsigned short alpha_mux_bit:1;
				unsigned short a_out_controls_color0_animation_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			__flags flags;
			unsigned short : 16;

			////////////////////////////////////////////////////////////////
			// constants and animation
			// Constant color 0 is animated in exactly the same way as the self-illumination color of the model shader, except that it has an alpha component in addition to the RGB components. Constant color 1 is just a constant.
			Enums::object_change_color_reference color0_source;
			Enums::periodic_function             color0_animation_function;
			real                                 color0_animation_period;
			real_argb_color                      color0_animation_lower_bound;
			real_argb_color                      color0_animation_upper_bound;
			real_argb_color                      color1;

			////////////////////////////////////////////////////////////////
			// color inputs
			struct {
				Enums::color_input         input;
				Enums::color_input_mapping input_mapping;
			}                                    color_inputs[4];

			////////////////////////////////////////////////////////////////
			// color outputs
			struct {
				Enums::color_output          output;
				Enums::color_output_function output_function;
			}                                    color_outputs[2];
			Enums::color_output                  output_ab_cd_mux_sum;
			Enums::output_mapping                output_mapping;

			////////////////////////////////////////////////////////////////
			// alpha inputs
			struct {
				Enums::alpha_input         input_;
				Enums::color_input_mapping input_mapping;
			}                                    alpha_inputs[4];

			////////////////////////////////////////////////////////////////
			// alpha outputs
			struct {
				Enums::alpha_output output;
			}                                    alpha_outputs[2];
			Enums::alpha_output                  output_ab_cd_mux_sum_1;
			Enums::output_mapping                output_mapping_1;
		}; static_assert(sizeof(s_shader_transparent_generic_stage) == 0x70); // max count: 7
		struct _shader_transparent_generic_definition {
			////////////////////////////////////////////////////////////////
			// generic transparent shader
			s_shader_radiosity_properties radiosity_properties;

			////////////////////////////////////////////////////////////////
			// lens flares
			real                                                     lens_flare_spacing;
			tag_reference                                            lens_flare;
			Yelo::TagBlock<const s_shader_transparent_layer>         extra_layers;
			Yelo::TagBlock<const s_shader_transparent_generic_map>   maps;
			Yelo::TagBlock<const s_shader_transparent_generic_stage> stages;
		};

		struct s_shader_transparent_generic_definition : s_shader_definition {
			enum { k_group_tag = 'sotr' };

			_shader_transparent_generic_definition transparent_generic;
		}; static_assert(sizeof(s_shader_transparent_generic_definition) == 0x6C); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct _shader_transparent_glass_definition {
			struct __flags {
				unsigned short alpha_tested_bit:1;
				unsigned short decal_bit:1;
				unsigned short two_sided_bit:1;
				unsigned short bump_map_is_specular_mask_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			////////////////////////////////////////////////////////////////
			// glass shader
			__flags flags;
			unsigned short      : 16;

			////////////////////////////////////////////////////////////////
			// background tint properties
			// Background pixels are multiplied by the tint map and constant tint color.
			long:8 * sizeof(long) * 10;
			real_rgb_color      background_tint_color;
			s_shader_scaled_map background_tint_map;
			long:8 * sizeof(long) * 5;

			////////////////////////////////////////////////////////////////
			// reflection properties
			// Reflection maps are multiplied by fresnel terms (glancing angles cause reflections to disappear) and then added to the background. The primary reflection map is textured normally, while the secondary reflection map is magnified.
			unsigned short : 16;
			Enums::reflection_type reflection_type;
			real_fraction          perpendicular_brightness;
			real_rgb_color         perpendicular_tint_color;
			real_fraction          parallel_brightness;
			real_rgb_color         parallel_tint_color;
			tag_reference          reflection_map;
			s_shader_scaled_map    bump_map;
			long:8 * sizeof(long) * 32;

			////////////////////////////////////////////////////////////////
			// diffuse properties
			// Diffuse lights are accumulated in monochrome and then alpha-blended with diffuse map and diffuse detail map. The color is determined by double-multiplying both maps and multiplying with the accumulated light, the result being alpha-blended into the framebuffer. The opacity is determined by multiplying both map's alpha channels. Since this effect is alpha-blended, it covers up tinting and reflection on pixels with high opacity.
			unsigned long : 32;
			s_shader_scaled_map diffuse_map;
			s_shader_scaled_map diffuse_detail_map;
			long:8 * sizeof(long) * 7;

			////////////////////////////////////////////////////////////////
			// specular properties
			// Specular lights are accumulated in monochrome and then alpha-blended with diffuse map and diffuse detail map. The color is determined by double-multiplying both maps and multiplying with the accumulated light, the result being alpha-blended into the framebuffer. The opacity is determined by multiplying both map's alpha channels. Since this effect is alpha-blended, it covers up tinting, reflection and diffuse texture on pixels with high opacity.
			unsigned long : 32;
			s_shader_scaled_map specular_map;
			s_shader_scaled_map specular_detail_map;
			long:8 * sizeof(long) * 7;
		};

		struct s_shader_transparent_glass_definition : s_shader_definition {
			enum { k_group_tag = 'sgla' };

			_shader_transparent_glass_definition transparent_glass;
		}; static_assert(sizeof(s_shader_transparent_glass_definition) == 0x1E0); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct _shader_transparent_meter_definition {
			struct __flags {
				unsigned short decal_bit:1;
				unsigned short two_sided_bit:1;
				unsigned short flash_color_is_negative_bit:1;
				unsigned short tint_mode_2_bit:1;
				unsigned short unfiltered_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			////////////////////////////////////////////////////////////////
			// meter shader
			__flags flags;
			unsigned short : 16;
			long:8 * sizeof(long) * 8;
			tag_reference  map;
			long:8 * sizeof(long) * 8;

			////////////////////////////////////////////////////////////////
			// colors
			real_rgb_color gradient_min_color;
			real_rgb_color gradient_max_color;
			real_rgb_color background_color;
			real_rgb_color flash_color;
			real_rgb_color tint_color;
			real_fraction  meter_transparency;
			real_fraction  background_transparency;
			long:8 * sizeof(long) * 6;

			////////////////////////////////////////////////////////////////
			// external function sources
			Enums::object_function_reference meter_brightness_source;
			Enums::object_function_reference flash_brightness_source;
			Enums::object_function_reference value_source;
			Enums::object_function_reference gradient_source;
			Enums::object_function_reference flash_extension_source;
			unsigned short : 16;
			long:8 * sizeof(long) * 8;
		};

		struct s_shader_transparent_meter_definition : s_shader_definition {
			enum { k_group_tag = 'smet' };

			_shader_transparent_meter_definition transparent_meter;
		}; static_assert(sizeof(s_shader_transparent_meter_definition) == 0x104); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct _shader_transparent_plasma_definition {
			////////////////////////////////////////////////////////////////
			// plasma shader
			unsigned short : 16;
			unsigned short : 16;

			////////////////////////////////////////////////////////////////
			// intensity
			// Controls how bright the plasma is.
			Enums::object_function_reference intensity_source;
			unsigned short : 16;
			real intensity_exponent;

			////////////////////////////////////////////////////////////////
			// offset
			// Controls how far the plasma energy extends from the model geometry.
			Enums::object_function_reference offset_source;
			unsigned short : 16;
			real offset_amount;
			real offset_exponent;
			long:8 * sizeof(long) * 8;

			////////////////////////////////////////////////////////////////
			// color
			// Controls the tint color and Fresnel brightness effects.
			real_fraction                        perpendicular_brightness;
			real_rgb_color                       perpendicular_tint_color;
			real_fraction                        parallel_brightness;
			real_rgb_color                       parallel_tint_color;
			Enums::object_change_color_reference tint_color_source;
			unsigned short : 16;
			long:8 * sizeof(long) * 8;
			unsigned short : 16;
			unsigned short : 16;
			long:8 * sizeof(long) * 4;

			////////////////////////////////////////////////////////////////
			// primary noise map
			unsigned long : 32;
			unsigned long : 32;
			real                primary_animation_period;
			real_vector3d       primary_animation_direction;
			s_shader_scaled_map primary_noise_map;
			long:8 * sizeof(long) * 8;

			////////////////////////////////////////////////////////////////
			// secondary noise map
			unsigned long : 32;
			real                secondary_animation_period;
			real_vector3d       secondary_animation_direction;
			s_shader_scaled_map secondary_noise_map;
			long:8 * sizeof(long) * 8;
		};

		struct s_shader_transparent_plasma_definition : s_shader_definition {
			enum { k_group_tag = 'spla' };

			_shader_transparent_plasma_definition transparent_plasma;
		}; static_assert(sizeof(s_shader_transparent_plasma_definition) == 0x14C); // max count: 1
		//////////////////////////////////////////////////////////////////////////
		struct s_shader_transparent_water_ripple {
			unsigned short : 16;
			unsigned short : 16;
			real_fraction contribution_factor;
			long:8 * sizeof(long) * 8;
			angle         animation_angle;
			real          animation_velocity;
			real_vector2d map_offset;
			short         map_repeats;
			short         map_index;
			long:8 * sizeof(long) * 4;
		}; static_assert(sizeof(s_shader_transparent_water_ripple) == 0x4C); // max count: 4
		struct _shader_transparent_water_definition {
			struct __flags {
				unsigned short base_map_alpha_modulates_reflection_bit:1;
				unsigned short base_map_color_modulates_background_bit:1;
				unsigned short atmospheric_fog_bit:1;
				unsigned short draw_before_fog_bit:1;
			}; static_assert(sizeof(__flags) == sizeof(unsigned short));

			////////////////////////////////////////////////////////////////
			// water shader
			// Base map color modulates the background, while base map alpha modulates reflection brightness. Both of these effects can be independently enables and disabled. Note that if the <base map alpha modulates reflection> flag is not set, then the perpendicular/parallel brightness has no effect (but the perpendicular/parallel tint color DOES has an effect).
			__flags flags;
			unsigned short : 16;
			long:8 * sizeof(long) * 8;
			tag_reference  base_map;
			long:8 * sizeof(long) * 4;
			real_fraction  view_perpendicular_brightness;
			real_rgb_color view_perpendicular_tint_color;
			real_fraction  view_parallel_brightness;
			real_rgb_color view_parallel_tint_color;
			long:8 * sizeof(long) * 4;
			tag_reference  reflection_map;
			long:8 * sizeof(long) * 4;
			angle          ripple_animation_angle;
			real           ripple_animation_velocity;
			real           ripple_scale;
			tag_reference  ripple_maps;
			short          ripple_mipmap_levels;
			unsigned short : 16;
			real_fraction                                           ripple_mipmap_fade_factor;
			real                                                    ripple_mipmap_detail_bias;
			long:8 * sizeof(long) * 16;
			Yelo::TagBlock<const s_shader_transparent_water_ripple> ripples;
			long:8 * sizeof(long) * 4;
		};

		struct s_shader_transparent_water_definition : s_shader_definition {
			enum { k_group_tag = 'swat' };

			_shader_transparent_water_definition transparent_water;
		}; static_assert(sizeof(s_shader_transparent_water_definition) == 0x140); // max count: 1
		//////////////////////////////////////////////////////////////////////////
	};
};
