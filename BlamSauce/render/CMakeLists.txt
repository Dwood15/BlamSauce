add_subdirectory(rasterizer)

set(RENDER_H
	${RASTERIZER_H}
	${CMAKE_CURRENT_SOURCE_DIR}/cameras.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/constants.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/objects.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/render.hpp)
