
set(CRYPTOGRAPHY_H
	${CMAKE_CURRENT_SOURCE_DIR}/cryptography/cryptography.h)

set(ITEMS_H
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_definitions_yelo.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_structures_yelo.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_structures.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/garbage_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_structures.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectile_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectiles.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_definitions.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_structures.h
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapons.h)

add_subdirectory(ai)

add_subdirectory(cache)

add_subdirectory(cseries)

add_subdirectory(effects)

add_subdirectory(game)

add_subdirectory(hs)

add_subdirectory(interface)

add_subdirectory(main)

add_subdirectory(math)

add_subdirectory(memory)

add_subdirectory(models)

add_subdirectory(network)

add_subdirectory(render)

add_subdirectory(scenario)

add_subdirectory(tags)

message(STATUS "TAGS_H: ${TAGS_H}")

set(HEADERS
	${AI_H}
	${CACHE_H}
	${CRYPTOGRAPHY_H}
	${CSERIES_H}
	${EFFECTS_H}
	${GAME_H}
	${INTERFACE_H}
	${ITEMS_H}
	${MAIN_H}
	${MATH_H}
	${MEMORY_H}
	${MODELS_H}
	${NETWORK_H}
	${OBJECTS_H}
	${RENDER_H}
	${RUNTIME_H}
	${SCRIPTING_H}
	${SCENARIO_H}
	${TAGS_H}
	${CMAKE_CURRENT_SOURCE_DIR}/file_io.h
	${CMAKE_CURRENT_SOURCE_DIR}/primary.h
	PARENT_SCOPE)

