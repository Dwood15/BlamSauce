
set(CRYPTOGRAPHY_H
	${CMAKE_CURRENT_SOURCE_DIR}/cryptography/cryptography.h)

set(HS_H
	${CMAKE_CURRENT_SOURCE_DIR}/hs/compile.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/hs.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hs/hs_yelo.hpp
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
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_definitions_yelo.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_structures_yelo.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/equipment_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/garbage_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/item_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectile_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/projectiles.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapon_structures.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/items/weapons.hpp)

add_subdirectory(ai)

add_subdirectory(cache)

add_subdirectory(cseries)

add_subdirectory(game)

add_subdirectory(effects)

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
	${HS_H}
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
	${SCENARIO_H}
	${TAGS_H}
	${CMAKE_CURRENT_SOURCE_DIR}/primary.h
	PARENT_SCOPE)

