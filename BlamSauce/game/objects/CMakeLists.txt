#I can't help but feel like this whole bit right here is needlessly verbose....
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bipeds)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/units)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vehicles)

set(OBJECTS_H
	${CMAKE_CURRENT_SOURCE_DIR}/damage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/index_resolution.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_lights.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_types.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/objects.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/placeholder_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scenario_object_definitions_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scenery_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound_scenery_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/vehicle_remapper.hpp
	${UNITS_H}
	${BIPEDS_H}
	${VEHICLES_H}
	)
