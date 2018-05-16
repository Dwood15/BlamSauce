set(R_SHADERS_H
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/effect_postprocess_collection_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/effect_postprocess_generic_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_postprocess_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_postprocess_generic_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_postprocess_globals_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_postprocess_runtime.inl
	)

set(RASTERIZER_H
	${R_SHADERS_H}
	${CMAKE_CURRENT_SOURCE_DIR}/dx9.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/geometry.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/rasterizer.hpp

	PARENT_SCOPE)
