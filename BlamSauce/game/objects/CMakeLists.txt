#I can't help but feel like this whole bit right here is needlessly verbose....
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bipeds)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/units)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vehicles)

set(OBJECTS_H
	${CMAKE_CURRENT_SOURCE_DIR}/damage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/index_resolution.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_lights.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object_structures.h
	${CMAKE_CURRENT_SOURCE_DIR}/object_types.h
	${CMAKE_CURRENT_SOURCE_DIR}/objects.h
	${CMAKE_CURRENT_SOURCE_DIR}/objects_yelo.h
	${CMAKE_CURRENT_SOURCE_DIR}/placeholder_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scenario_object_definitions_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/scenery_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sound_scenery_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/vehicle_remapper.hpp
	${O_UNITS_H}
	${O_BIPEDS_H}
	${O_VEHICLES_H}
	PARENT_SCOPE)
