/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <d3dx9.h>

#include "../../../tags/group/markup.h"
#include "../../../main/main.h"
#include "../../../math/integer_math.h"
#include "../../../math/real_math.h"
#include "../../../tags/group/base.h"
#include "../../../cache/predicted_resources.hpp"
#include "shader_postprocess_generic_definitions.hpp"
#include "../../../cache/shared/texture_cache.hpp"

namespace Yelo {
	namespace Enums {
		enum postprocess_render_stage : short {
			_postprocess_render_stage_pre_blur,
			_postprocess_render_stage_pre_alpha_blended,
			_postprocess_render_stage_pre_hud,
			_postprocess_render_stage_pre_ui,
			_postprocess_render_stage_post_ui,
			_postprocess_render_stage_blur,

			_postprocess_render_stage
		};

		enum shader_variable_base_type : short {
			_shader_variable_base_type_boolean,
			_shader_variable_base_type_integer,
			_shader_variable_base_type_float,

			_shader_variable_base_type_argb_color,
			_shader_variable_base_type_matrix,
			_shader_variable_base_type_texture,

			_shader_variable_base_type
		};

		enum effect_activation_state : short {
			_effect_activation_state_initially_active,
			_effect_activation_state_is_in_cutscene,
			_effect_activation_state_player_is_zoomed,
			_effect_activation_state_player_using_a_vehicle,

			_effect_activation_control_state
		};
	};

	namespace TagGroups {
		struct shader_variable_type {
			short type;      // Enums::shader_variable_base_type
			short count;   // # of [shader_variable_base_type]s
		};

		template <Enums::shader_variable_base_type TType, size_t TCount = 1>
		struct s_shader_postprocess_shader_variable {
			struct {
				D3DXHANDLE dx_handle;
			} runtime;

			bool IsUsed() { return runtime.dx_handle != NULL; }

			void ClearHandles() { runtime.dx_handle = NULL; }

			void Initialize(LPD3DXEFFECT effect, const char *id, bool semantic = false);

			template <typename TValueType>
			void GetValues(TValueType *values_out, const TValueType *values1, const TValueType *values2, const size_t count, const real *interp_values);

			void GetValues(BOOL *values_out, const bool *values1, const bool *values2, const size_t count, const real *interp_values);

			void GetValues(D3DXCOLOR *values_out, const FLOAT *values1, const FLOAT *values2, const size_t count, const real *interp_values);

			void SetVariableInterp(LPD3DXEFFECT effect, const void *data1, const void *data2, const real *interp_values);

			// [fixup_argb_color_hack] - internal use only, use default when calling externally
			void SetVariable(LPD3DXEFFECT effect, void *data, const bool fixup_argb_color_hack = true);
		};

		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type>            t_shader_variable_base;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_boolean>    t_shader_variable_bool;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_integer>    t_shader_variable_int;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_float>      t_shader_variable_real;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_float, 2>   t_shader_variable_real2d;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_float, 3>   t_shader_variable_real3d;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_float, 4>   t_shader_variable_real4d;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_argb_color> t_shader_variable_color;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_matrix>     t_shader_variable_matrix;
		typedef s_shader_postprocess_shader_variable<Enums::_shader_variable_base_type_texture>    t_shader_variable_texture;

		//////////////////////////////////////////////////////////////////////////
		// shader_postprocess base
		struct s_pass_definition {
			TAG_FIELD(tag_string, name);

			struct _flags {
				TAG_FLAG16(clear_target);
				TAG_FLAG16(copy_scene_to_target);
				TAG_FLAG16(clear_buffer_texture);
			} flags;   static_assert(sizeof(_flags) == sizeof(unsigned short));
			TAG_FIELD(short, render_chain);

			TAG_PAD(ss_pass_def0, long, 3);
		}; static_assert(sizeof(s_pass_definition) == 0x30);

		struct s_technique_definition {
			TAG_FIELD(tag_string, name);

			struct _flags {
				TAG_FLAG16(sm_1_0);
				TAG_FLAG16(sm_2_0);
				TAG_FLAG16(sm_3_0);
			} shader_model;   static_assert(sizeof(_flags) == sizeof(unsigned short));

			unsigned short : 16;

			TAG_PAD(ss_tech_def0, long, 4);

			TAG_TBLOCK_(passes, s_pass_definition);
		}; static_assert(sizeof(s_technique_definition) == 0x40);

		struct s_shader_postprocess_definition {
			enum { k_group_tag = 'shpp' };
			unsigned short : 16;
			struct _flags {
				TAG_FLAG16(shader_is_binary);
			} flags;

			TAG_FIELD(tag_data, shader_code_text);
			TAG_FIELD(tag_data, shader_code_binary);

			t_shader_variable_matrix  ortho_wvp_matrix;   // Orthographic projection matrix handle
			t_shader_variable_real2d  scene_size;         // Handle to the scene size float2 value
			t_shader_variable_real2d  screen_fov;         // Handle to the screen fov float2 value
			t_shader_variable_real2d  hud_scale;         // Handle to the hud scale float2 value
			t_shader_variable_real2d  pixel_size;         // Handle to the pixel size float2 value
			t_shader_variable_real    near_clip_dist;      // Handle to the near clip float value
			t_shader_variable_real    far_clip_dist;      // Handle to the far clip float value
			t_shader_variable_real    frame_time;         // Handle to the frame time float value
			t_shader_variable_texture tex_source;         // Handle to the post-process source texture
			t_shader_variable_texture tex_scene;         // Handle to the saved scene texture
			t_shader_variable_texture tex_buffer;         // Handle to the secondary buffer

			TAG_PAD(ss_pp_def0, long, 5);

			TAG_TBLOCK_(techniques, s_technique_definition);
			TAG_TBLOCK_(predicted_resources, predicted_resource);

			struct _runtime {
				struct _postprocess_flags {
					TAG_FLAG16(valid_shader);
					TAG_FLAG16(uses_gbuffer);
				} flags;
				unsigned short : 16;   static_assert(sizeof(_postprocess_flags) == sizeof(unsigned short));

				TAG_FIELD(LPD3DXEFFECT, dx_effect);
				TAG_FIELD(D3DXHANDLE, postprocess_handle);
				TAG_FIELD(s_technique_definition*, active_technique);
				TAG_PAD(ss_pp_padaasdf, long, 4);
			}                         runtime;

			s_shader_postprocess_definition() {}
		};

		static_assert(sizeof(s_shader_postprocess_definition) == 0xA4);


		//////////////////////////////////////////////////////////////////////////
		// effect_postprocess base
		struct s_effect_postprocess_custom_vertex_data {
			TAG_FIELD(real_bounds, x_data);
			TAG_FIELD(real_bounds, y_data);
			TAG_FIELD(real_bounds, z_data);
			TAG_FIELD(real_bounds, w_data);
		}; static_assert(sizeof(s_effect_postprocess_custom_vertex_data) == 0x20);

		struct s_effect_postprocess_quad_definition {
			TAG_FIELD(point2d, tessellation);
			TAG_FIELD(real_bounds, x_bounds);
			TAG_FIELD(real_bounds, y_bounds);
			TAG_TBLOCK_(custom_vertex_data, s_effect_postprocess_custom_vertex_data); // not implemented
		};

		struct s_effect_postprocess_definition {
			enum { k_group_tag = 'shpe' };
			TAG_PAD(ss_pp_def_e0, byte, 12);

			TAG_FIELD(s_effect_postprocess_quad_definition, quad_definition);

			struct _runtime {
				struct _postprocess_flags {
					TAG_FLAG16(valid_effect);
					TAG_FLAG16(is_active);
					TAG_FLAG16(uses_gbuffer);
				} flags;
				unsigned short : 16;

				TAG_PAD(ss_pp_def_e1, byte, 12);
			} runtime;

		}; static_assert(sizeof(s_effect_postprocess_definition) == 0x3C);
	};
};

namespace Yelo::TagGroups {
	/////////////////////////////////////////////////////////////////////
	// s_shader_postprocess_parameter
	void s_shader_postprocess_parameter::GetBoundingValues(void *&lower_ref, void *&upper_ref) {
		switch (value_type.type) {
			case Enums::_shader_variable_base_type_boolean:
				value.boolean.inverse = !value.boolean.enabled;

				lower_ref = &value.boolean.enabled;
				upper_ref = &value.boolean.inverse;
				break;

			case Enums::_shader_variable_base_type_integer:
				lower_ref = &value.integer32.lower_bound;
				upper_ref = &value.integer32.upper_bound;
				break;

			case Enums::_shader_variable_base_type_float:
				switch (value_type.count) {
					case 1:
						lower_ref = &value.real32.lower_bound;
						upper_ref = &value.real32.upper_bound;
						break;
					case 2:
						lower_ref = &value.vector2d.lower_bound;
						upper_ref = &value.vector2d.upper_bound;
						break;
					case 3:
						lower_ref = &value.vector3d.lower_bound;
						upper_ref = &value.vector3d.upper_bound;
						break;
					case 4:
						lower_ref = &value.vector4d.lower_bound;
						upper_ref = &value.vector4d.upper_bound;
						break;
				}
				break;

			case Enums::_shader_variable_base_type_argb_color:
				lower_ref = &value.color4d.lower_bound;
				upper_ref = &value.color4d.upper_bound;
				break;
		}
	}

	void s_shader_postprocess_parameter::SetVariableInterp(LPD3DXEFFECT effect, const void *lower_data, const void *upper_data, const real *interp_values) {
		switch (value_type.type) {
			case Enums::_shader_variable_base_type_boolean:
				value.boolean.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
				break;

			case Enums::_shader_variable_base_type_integer:
				value.integer32.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
				break;

			case Enums::_shader_variable_base_type_float:
				switch (value_type.count) {
					case 1:
						value.real32.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
						break;
					case 2:
						value.vector2d.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
						break;
					case 3:
						value.vector3d.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
						break;
					case 4:
						value.vector4d.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
						break;
				}
				break;

			case Enums::_shader_variable_base_type_argb_color:
				value.color4d.handle.SetVariableInterp(effect, lower_data, upper_data, interp_values);
				break;
		}
	}

	void s_shader_postprocess_parameter::SetVariable(LPD3DXEFFECT effect, void *data, const bool fixup_argb_color_hack) {
		switch (value_type.type) {
			case Enums::_shader_variable_base_type_boolean:
				value.boolean.handle.SetVariable(effect, data, fixup_argb_color_hack);
				break;

			case Enums::_shader_variable_base_type_integer:
				value.integer32.handle.SetVariable(effect, data, fixup_argb_color_hack);
				break;

			case Enums::_shader_variable_base_type_float:
				switch (value_type.count) {
					case 1:
						value.real32.handle.SetVariable(effect, data, fixup_argb_color_hack);
						break;
					case 2:
						value.vector2d.handle.SetVariable(effect, data, fixup_argb_color_hack);
						break;
					case 3:
						value.vector3d.handle.SetVariable(effect, data, fixup_argb_color_hack);
						break;
					case 4:
						value.vector4d.handle.SetVariable(effect, data, fixup_argb_color_hack);
						break;
				}
				break;

			case Enums::_shader_variable_base_type_argb_color:
				value.color4d.handle.SetVariable(effect, data, fixup_argb_color_hack);
				break;
		}
	}

	HRESULT s_shader_postprocess_parameter::LoadBitmap(IDirect3DDevice9 *pDevice) {
		HRESULT hr = E_FAIL;
		if (value_type.type != Enums::_shader_variable_base_type_texture)
			return hr;

		if (!bitmap_value.flags.is_external_bit) {
			if (bitmap_value.runtime._internal.bitmap != nullptr) {
				// Load the bitmap into the pc texture cache, and block until the he direct3d texture is created
				blam::texture_cache_bitmap_get_hardware_format(bitmap_value.runtime._internal.bitmap, true, true);

				hr = (bitmap_value.runtime._internal.bitmap->hardware_format == nullptr ? E_FAIL : S_OK);
			}
		} else {
			if (bitmap_value.runtime.external.source != nullptr)
				hr = D3DXCreateTextureFromFile(pDevice, bitmap_value.runtime.external.source, &bitmap_value.runtime.external.texture_2d);
		}
		bitmap_value.flags.is_loaded_bit = SUCCEEDED(hr);
		return hr;
	}

	void s_shader_postprocess_parameter::ReleaseBitmap() {
		if (value_type.type != Enums::_shader_variable_base_type_texture)
			return;

		// No need to release the bitmap if it is internal, Halo handles that itself
		if (bitmap_value.flags.is_external_bit)
			Yelo::safe_release(bitmap_value.runtime.external.texture_2d);
	}

	IDirect3DTexture9 *s_shader_postprocess_parameter::GetTexture() {
		if (value_type.type != Enums::_shader_variable_base_type_texture)
			return nullptr;

		if (!bitmap_value.flags.is_loaded_bit)
			return nullptr;
		return bitmap_value.flags.is_external_bit ? bitmap_value.runtime.external.texture_2d : CAST_PTR(IDirect3DTexture9*, bitmap_value.runtime._internal.bitmap->hardware_format);
	}

	void s_shader_postprocess_parameter::SetParameter(const s_shader_postprocess_value_base *value_source) {
		std::memcpy(value_name, value_source->value_name, sizeof(tag_string));
		std::memcpy(&value_type, &value_source->value_type, sizeof(value_type));
		std::memcpy(&value, &value_source->value, sizeof(value));
		std::memcpy(&runtime_value, &value_source->runtime_value, sizeof(runtime_value));
		std::memcpy(&animation_function, &value_source->animation_function, sizeof(animation_function));
	}

	void s_shader_postprocess_parameter::SetParameter(const s_shader_postprocess_bitmap *value_source) {
		SetParameter(CAST_PTR(const s_shader_postprocess_value_base*, value_source));

		bitmap_value.bitmap.tag_index = value_source->bitmap.tag_index;

		blam::tag_reference_set(bitmap_value.bitmap, value_source->bitmap.group_tag, value_source->bitmap.name);
	}
};

#include "./shader_postprocess_runtime.inl"

