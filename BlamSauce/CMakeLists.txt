
set(CRYPTOGRAPHY_H cryptography/cryptography.h)

set(HS_H
	${CMAKE_CURRENT_SOURCE_DIR}/hs/compile.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/constants.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/hs.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/library_external.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/library_internal.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/library_internal_compile.inl
	${CMAKE_CURRENT_SOURCE_DIR}/hs/library_internal_runtime.inl
	${CMAKE_CURRENT_SOURCE_DIR}/hs/object_lists.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/object_lists_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/runtime.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/runtime_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/scenario.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/threads.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/types.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/types_compile.inl
	${CMAKE_CURRENT_SOURCE_DIR}/hs/types_traits.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/types_runtime.inl
	)

set(ITEMS_H
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/garbage_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectile_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectiles.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapons.hpp)

set(CSERIES_H
	cseries/MacrosCpp.h
	cseries/cseries.h
	cseries/base.h
	cseries/yelo_base.h
	cseries/errors.h)


add_subdirectory(ai)

add_subdirectory(cache)

add_subdirectory(game)

add_subdirectory(effects)

add_subdirectory(interface)

add_subdirectory(main)

add_subdirectory(math)

add_subdirectory(memory)

add_subdirectory(network)

add_subdirectory(render)

add_subdirectory(scenario)

add_subdirectory(tags)

set(HEADERS
	${MAIN_H}
	${CSERIES_H}
	${MATH_H}
	${TAGS_H}
	${MEMORY_H}
	${RENDER_H}
	${AI_H}
	${SCENARIO_H}
	${RUNTIME_H}
	${NETWORK_H}
	${ITEMS_H}
	${INTERFACE_H}
	${HS_H}
	${EFFECTS_H}
	${CRYPTOGRAPHY_H}
	${CACHE_H}
	${MODELS_H}
	${GAME_H}
	${OBJECTS_H}
	primary.h
	)

#Crappy hack to stop "CMake doesn't know what language this is!" errors. Could probably do something like use .hpp files instead. /shrug
add_library(${PROJECT_NAME} STATIC primary.cpp ${HEADERS})

add_library(${PROJECT_NAME}_iface INTERFACE)
#target_compile_definitions(${PROJECT_NAME}_iface INTERFACE)

install(TARGETS ${PROJECT_NAME} EXPORT library_targets LIBRARY DESTINATION lib ARCHIVE DESTINATION ar)

message(STATUS "Outputting lib to: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
