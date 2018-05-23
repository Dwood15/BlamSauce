#pragma once

#include <precompile.h>
#include "../../../../../../../BlamSauce/math/matrix_math.h"

#ifdef ENGINE_DPTR
#undef ENGINE_DPTR
#endif

#ifdef ENGINE_PTR
#undef ENGINE_PTR
#endif

#ifdef FUNC_PTR
#undef FUNC_PTR
#endif

#define ENGINE_DPTR(type, name, ...) static auto** const name = reinterpret_cast<type**>(__VA_ARGS__);
#define ENGINE_PTR(type, name, ...) static auto* const name = reinterpret_cast<type*>(__VA_ARGS__);
#define DUO_PTR(...) __VA_ARGS__
#define FUNC_PTR(name, value, ...) static auto const name  =  value
#define CAST_PTR(type, ptr)      reinterpret_cast<type>(ptr)

//////////////////////////////////////////////////////////////////////////
// Rasterizer.cpp
	namespace Rasterizer
	{
		static real_matrix3x4** K_VSH_CONSTANTS__NODEMATRICES_REFERENCES[] = {
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_0),
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_1),
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_2),
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_3),
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_4),
			reinterpret_cast<real_matrix3x4 **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCE_5),
		};
		static void** K_VSH_CONSTANTS__NODEMATRICES_REFERENCES_PLUS_8[] = {
			reinterpret_cast<void **>(K_VSH_CONSTANTS__NODEMATRICES_REFERENCES_PLUS_8_0),
		};

		static auto *const rasterizer_config = reinterpret_cast<s_rasterizer_config *>(K_RASTERIZER_CONFIG, PTR_NULL);;
		static auto *const rasterizer_globals = reinterpret_cast<s_rasterizer_globals *>(K_RASTERIZER_GLOBALS, PTR_NULL);;
		static auto *const rasterizer_debug_data = reinterpret_cast<s_rasterizer_debug_options *>(K_RASTERIZER_DEBUG_DATA, PTR_NULL);;
		static auto *const rasterizer_frame_params = reinterpret_cast<s_rasterizer_frame_parameters *>(K_RASTERIZER_FRAME_PARAMS, PTR_NULL);;

		static auto const RASTERIZER_DISPOSE = K_RASTERIZER_DISPOSE;
		static auto const RASTERIZER_DISPOSE_CALL_FROM_RASTERIZER = K_RASTERIZER_DISPOSE_CALL_FROM_RASTERIZER;
		static auto const RASTERIZER_DISPOSE_CALL_FROM_SHELL = K_RASTERIZER_DISPOSE_CALL_FROM_SHELL;
		

		static void** K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_LIST[] = {
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_0),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_1),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_2),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_3),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_4),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_5),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_6),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_7),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_8),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_9),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_10),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_11),
			reinterpret_cast<void **>(K_RENDERED_TRIANGLE_ARRAY_UPGRADE_ADDRESS_12),
		};
		static unsigned short* K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_LIST[] = {
			reinterpret_cast<unsigned short *>(K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_0),
			reinterpret_cast<unsigned short *>(K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_1),
			reinterpret_cast<unsigned short *>(K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_2),
			reinterpret_cast<unsigned short *>(K_MAXIMUM_RENDERED_TRIANGLES_UPGRADE_ADDRESS_3),
		};

		static auto *const RASTERIZER_DYNAMIC_GEOMETRY_INITIALIZE__CreateIndexBuffer_Length_ARG = reinterpret_cast<DWORD *>(K_RASTERIZER_DYNAMIC_GEOMETRY_INITIALIZE__CREATEINDEXBUFFER_LENGTH_ARG, PTR_NULL);;

		static auto *const RASTERIZER_DEVICE_ADAPTER_INDEX = reinterpret_cast<DWORD *>(K_RASTERIZER_DEVICE_ADAPTER_INDEX, PTR_NULL);;

		static char** K_SCREENSHOT_FOLDER_REFERENCES[] = {
			reinterpret_cast<char **>(K_SCREENSHOT_FOLDER_REFERENCE_0),
			reinterpret_cast<char **>(K_SCREENSHOT_FOLDER_REFERENCE_1),
		};
	};
	namespace Render
	{
		static auto *const render_window = reinterpret_cast<s_render_window *>(K_RENDER_WINDOW, PTR_NULL);;
		static auto *const render_globals = reinterpret_cast<s_render_globals *>(K_RENDER_GLOBALS, PTR_NULL);;
		static auto *const global_render_targets = reinterpret_cast<s_render_target *>(K_GLOBAL_RENDER_TARGETS, PTR_NULL);;
		static auto *const structure_render_globals = reinterpret_cast<s_structure_render_globals *>(K_STRUCTURE_RENDER_GLOBALS, PTR_NULL);;

		static auto const RENDER_WINDOW_REFLECTION_CALL = K_RENDER_WINDOW_REFLECTION_CALL;
		static auto const RENDER_WINDOW_REFLECTION_CALL_RETN = K_RENDER_WINDOW_REFLECTION_CALL_RETN;

		static auto const RENDER_WINDOW_END_HOOK = K_RENDER_WINDOW_END_HOOK;
	};

	namespace Render { namespace Lightmaps
	{
			static auto const BSP_LIGHTMAP_INDEX_HOOK = K_BSP_LIGHTMAP_INDEX_HOOK;
			static auto const BSP_LIGHTMAP_INDEX_RETN = K_BSP_LIGHTMAP_INDEX_RETN;
			static auto const SET_LIGHTMAP_SAMPLER_CALL = K_SET_LIGHTMAP_SAMPLER_CALL;
			static auto const OBJECT_RENDER_CACHE_LIGHTMAP_TAG_INDEX_HOOK = K_OBJECT_RENDER_CACHE_LIGHTMAP_TAG_INDEX_HOOK;
			static auto const OBJECT_RENDER_CACHE_LIGHTMAP_TAG_INDEX_RETN = K_OBJECT_RENDER_CACHE_LIGHTMAP_TAG_INDEX_RETN;
	};};

	namespace Render { namespace Sky
	{
			static auto const FOG_ATMOSPHERIC_SKY_TAG_INDEX_HOOK = K_FOG_ATMOSPHERIC_SKY_TAG_INDEX_HOOK;
			static auto const FOG_ATMOSPHERIC_SKY_TAG_INDEX_RETN = K_FOG_ATMOSPHERIC_SKY_TAG_INDEX_RETN;
			static auto const FOG_PLANAR_SKY_TAG_INDEX_HOOK = K_FOG_PLANAR_SKY_TAG_INDEX_HOOK;
			static auto const FOG_PLANAR_SKY_TAG_INDEX_RETN = K_FOG_PLANAR_SKY_TAG_INDEX_RETN;
			static auto const RENDER_SKY_SKY_TAG_INDEX_HOOK = K_RENDER_SKY_SKY_TAG_INDEX_HOOK;
			static auto const RENDER_SKY_SKY_TAG_INDEX_RETN = K_RENDER_SKY_SKY_TAG_INDEX_RETN;
			static auto const VISIBLE_SKY_ENABLE_SKY_TAG_INDEX_HOOK = K_VISIBLE_SKY_ENABLE_SKY_TAG_INDEX_HOOK;
			static auto const VISIBLE_SKY_ENABLE_SKY_TAG_INDEX_RETN = K_VISIBLE_SKY_ENABLE_SKY_TAG_INDEX_RETN;
	};};
