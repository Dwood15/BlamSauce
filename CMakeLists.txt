cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
unset(CMAKE_SHARED_LIBRARY_PREFIX)
unset(CMAKE_CL_64)

#capstone variables for debugging...
set(CAPSTONE_ARM_SUPPORT 0)
set(CAPSTONE_ARM64_SUPPORT 0)
set(CAPSTONE_MIPS_SUPPORT 0)
set(CAPSTONE_PPC_SUPPORT 0)
set(CAPSTONE_SPARC_SUPPORT 0)
set(CAPSTONE_SYSZ_SUPPORT 0)
set(CAPSTONE_XCORE_SUPPORT 0)
set(CAPSTONE_X86_SUPPORT 1)
#fuck att syntax.
set(CAPSTONE_X86_ATT_DISABLE ON)
#end capstone

set(PROJECT_NAME BlamSauce)

project(${PROJECT_NAME} CXX)

set(GAME_VER "CE_110")

set(CE_RUN runtime/custom_edition)
set(PC_RUN runtime/pc)

set(STUBBZ_RUN runtime/stubbz)
set(TRIAL_RUN runtime/trial)

#Is there even more than one stubbz runtime?
set(RUNTIME_STUBBZ ${STUBBZ_RUN})
set(RUNTIME_TRIAL ${TRIAL_RUN})

##CE RUNTIMES
set(RUNTIME_CE110 "./${CE_RUN}/1_10")
set(RUNTIME_CE109 "./${CE_RUN}/1_09")

##PC RUNTIMES
set(RUNTIME_PC110 "./${PC_RUN}/1_10")
set(RUNTIME_PC109 "./${PC_RUN}/1_09")

#This library has _so much_ information and changes and data that sigscanning isn't really a worthwhile exercise.
#For one, I'm not looking forward to finding all those signatures. Whoever wants to is welcome to try, however... see the queued_sigscanner.h file.
if (GAME_VER STREQUAL "CE_110")
	set(RUNTIME_DIR ${RUNTIME_CE110})
elseif (GAME_VER STREQUAL "CE_109")
	set(RUNTIME_DIR ${RUNTIME_CE109})
elseif (GAME_VER STREQUAL "PC_110")
	set(RUNTIME_DIR ${RUNTIME_PC110})
endif ()

include_directories(AFTER ${RUNTIME_DIR})
#Don't set this - it overrides the 17, and the msvc compiler's implementation of C++17 is, by default, somewhat incomplete.
#set(CMAKE_CXX_STANDARD 17)

#TODO: JSON SERIALIZATION/DESERIALIZATION
#https://github.com/nlohmann/json#serialization--deserialization

message(STATUS "MSVC VERSION --- ${MSVC_VERSION}")
message(STATUS "BINARY OUT DIR --- ${PROJECT_BINARY_DIR}")

find_path(DX_PATH FindDirectX.cmake PATHS ${PROJECT_SOURCE_DIR}/cmake REQUIRED)
find_path(HCE_PATH FindHaloCE.cmake PATHS ${PROJECT_SOURCE_DIR}/cmake REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${DX_PATH} ${HCE_PATH})

find_package(HaloCE REQUIRED)
find_package(DirectX REQUIRED)

#Required for getting the JSON library from nlohmann's github.
find_package(Git REQUIRED)

#TODO: JSON SERIALIZATION/DESERIALIZATION
#https://github.com/nlohmann/json#serialization--deserialization
include_directories(BEFORE ${DirectX_INCLUDE_DIRS})
message(STATUS "DX include Dirs: ${DirectX_INCLUDE_DIRS}")

#EXAMPLE DX INCLUDE PATH: D:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include

# Defines Release by default.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "Build type not specified: Using Release by default.")
endif (NOT CMAKE_BUILD_TYPE)

add_definitions(-D_WINDOWS)
if (MINGW)
	if ($ENV{CLION_IDE})
		#convenience function for CLion.
		return()
	endif ()

	message(STATUS "Mingw detected.")
	set(COMPILER_REL_FLDR mingw)
	set(CMAKE_CXX_FLAGS "-std=c++latest\ -fpermissive")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}\ -g\ -m32\ -masm=intel")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -g -m32 -masm=intel")
elseif (MSVC)
	#vc++ 2017 build toolset. Available from microsoft _without_ the abomination that is visual studio, here: http://landinghub.visualstudio.com/visual-cpp-build-tools
	if (NOT CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION OR NOT "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" STREQUAL "10.0.16299.0")
		#message(WARNING "CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION is empty! Could not find applicable windows 10 sdk.")
		set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0.16299.0)
		#TODO: CHECK FOR AVAILABLE SDK VERSIONS IF NONE SET
	endif ()

	set(COMPILER_REL_FLDR msvc)
	set(CMAKE_C_FLAGS '')
	set(CMAKE_CXX_FLAGS /std:c++latest\ /MTd\ )
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd\ /Gy- /W3 /Od /Zi /MP /EHsc /fp:fast\ /std:c++latest\ /arch:SSE2 /D\ \"WIN32\" /D \"_WINDOWS\" /D \"_USRDLL\" /D \"_WINDLL\"\ /D_CRT_SECURE_NO_WARNINGS")
else ()
	message(FATAL_ERROR "Unrecognized compiler/suite: ${CMAKE_CXX_COMPILER_ID}")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	#DO DEBUG STUFF HERE
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./bin/${COMPILER_REL_FLDR}-debug")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	if ($ENV{CLION_IDE})
		message(STATUS "convenience hack for making CLion less annoying.")
		return()
	endif ()
	set(OUTPUT_DIR ./bin/${COMPILER_REL_FLDR}-Release)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/ar")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")

if (MSVC)
	set(LINKER_FLAGS "/MANIFEST\ /NXCOMPAT\ /DEBUG\ /MACHINE:X86\ /SAFESEH:NO\ /INCREMENTAL:NO\ /SUBSYSTEM:WINDOWS\ /MANIFESTUAC:NO\ /OPT:NOICF\ /NOLOGO\ /ASSEMBLYDEBUG\ ") #rip alignment on win32
	set(CMAKE_SHARED_LINKER_FLAGS ${LINKER_FLAGS})
elseif (NOT MSVC)
	set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} $ENV{LDFLAGS} "-lws2_32 -static-libgcc -static-libstdc++ -static -luserenv -static -static -ladvapi32")
endif ()

set(RUNTIME_H
	${RUNTIME_DIR}/EngineFunctionADDRs.h)

set(BITMAP_H
	bitmaps/bitmap_grp.h)

set(NETWORK_H
	network/message_header.h
	network/transport/endpoint_set_winsock.h
	network/transport/address.h
	network/transport/endpoint_winsock.h)

set(CACHE_H
	cache/builder.hpp
	cache/cache_base.hpp
	cache/cache_files_globals.hpp
	cache/cache_files_structures.hpp
	cache/constants.hpp
	cache/data_file.hpp
	cache/data_file_structures.hpp
	cache/pc_sound_cache.hpp
	cache/texture_cache.hpp
	cache/sound_cache.hpp
	cache/predicted_resources.hpp
	cache/physical_memory_map_structures.hpp
	cache/physical_memory_map.hpp
	cache/pc_texture_cache.hpp
	cache/cache_files.hpp)

set(CAMERA_H
	camera/dead.hpp
	camera/definitions.hpp
	camera/director.hpp
	camera/director_structures.hpp
	camera/first_person.hpp
	camera/following.hpp
	camera/observer.hpp
	)

set(CUTSCENE_H
	cutscene/recorded_animation_definitions.hpp
	cutscene/recorded_animation_playback.hpp
	cutscene/recorded_animations_structures.hpp
	cutscene/recorded_animations.hpp
	cutscene/recorded_animation_playback_v1.hpp
	)


set(CRYPTOGRAPHY_H
	cryptography/cryptography.h)

set(DEVICES_H)
set(GAME_H
	game/action_queue.hpp
	game/allegiance.hpp
	game/vehicle_update_queue.hpp
	game/time_structures.hpp
	game/time.hpp
	game/position_queue.hpp
	game/players.hpp
	game/player_structures.hpp
	game/player_control.hpp
	game/player_action.hpp
	game/multiplayer_sounds.hpp
	game/globals_structures.hpp
	game/globals_definitions.hpp
	game/globals.hpp
	game/game.hpp
	game/engine_stub.hpp
	game/engine_slayer.hpp
	game/engine_race.hpp
	game/engine_oddball.hpp
	game/engine_king.hpp
	game/engine_ctf.hpp
	game/engine.hpp
	game/configuration.hpp
	game/cheats.hpp
	game/allegiance_structures.hpp
	)

set(EFFECTS_H
	effects/contrail_definitions.hpp
	effects/contrails.hpp
	effects/effects_constants.hpp
	effects/damage_effect_definitions.hpp
	effects/effects.hpp
	effects/weather_particle_systems.hpp
	effects/weather_particle_system_definitions.hpp
	effects/player_effects.hpp
	effects/particles.hpp
	effects/particle_systems.hpp
	effects/particle_system_definitions.hpp
	effects/particle_definitions.hpp
	effects/material_effect_definitions.hpp
	effects/effect_definitions.hpp
	)

set(HS_H
	hs/compile.hpp
	hs/constants.hpp
	hs/hs.hpp
	hs/library_external.hpp
	hs/library_internal.hpp
	hs/library_internal_compile.inl
	hs/library_internal_runtime.inl
	hs/object_lists.hpp
	hs/object_lists_structures.hpp
	hs/runtime.hpp
	hs/runtime_structures.hpp
	hs/scenario_definitions.hpp
	hs/structures.hpp
	hs/threads.hpp
	hs/types.hpp
	hs/types_compile.inl
	hs/types_definitions.inl
	hs/types_traits.hpp
	hs/types_runtime.inl
	)

set(INTERFACE_H
	interface/first_person_weapons.hpp
	interface/first_person_weapons_structures.hpp
	interface/hud.hpp
	interface/weapon_hud_interface_definition.hpp
	interface/unit_hud_interface_definition.hpp
	interface/hud_weapon_structures.hpp
	interface/hud_weapon.hpp
	interface/hud_unit_structures.hpp
	interface/hud_unit.hpp
	interface/hud_nav_points.hpp
	interface/hud_messaging_structures.hpp
	interface/hud_messaging_definitions.hpp
	interface/hud_messaging.hpp
	interface/hud_draw.hpp
	interface/hud_definitions.hpp
	interface/hud_chat.hpp
	interface/map_list.hpp
	interface/motion_sensor.hpp
	interface/terminal.hpp
	interface/ui_video_screen.hpp
	interface/ui_widget.hpp
	interface/ui_widget_event_handler_functions.hpp
	interface/ui_widget_game_data_input_functions.hpp
	interface/ui_widget_group.hpp
	interface/unit_hud_interface_definition.hpp
	interface/weapon_hud_interface_definition.hpp
	)

set(ITEMS_H
	items/equipment_definitions.hpp
	items/equipment_structures.hpp
	items/garbage_definitions.hpp
	items/item_definitions.hpp
	items/item_structures.hpp
	items/projectile_definitions.hpp
	items/projectiles.hpp
	items/weapon_definitions.hpp
	items/weapon_structures.hpp
	items/weapons.hpp)

set(SCENARIO_H
	scenario/scenario.h
	scenario/scenario_definitions.h
	scenario/structures.h)

set(ACTIONS_H
	ai/actions/action_alert.hpp
	ai/actions/action_avoid.hpp
	ai/actions/action_charge.hpp
	ai/actions/action_wait.hpp
	ai/actions/action_vehicle.hpp
	ai/actions/action_uncover.hpp
	ai/actions/action_sleep.hpp
	ai/actions/action_search.hpp
	ai/actions/action_obey.hpp
	ai/actions/action_guard.hpp
	ai/actions/action_flee.hpp
	ai/actions/action_fight.hpp
	ai/actions/action_converse.hpp)

set(AI_H
	ai/ai.h
	ai/ai_communication.h
	ai/ai_scenario_definitions.h
	ai/ai_script.h
	ai/ai_structures.h
	ai/encounters.h
	ai/path.h
	ai/prop_structures.h
	ai/props.h
	ai/actor_types/actor_types.h)

set(ACTORS_H
	ai/actors/actor_combat.hpp
	ai/actors/actor_definitions.hpp
	ai/actors/actors.hpp
	ai/actors/actor_types.hpp
	ai/actors/actor_structures.hpp
	ai/actors/actor_stimulus.hpp
	ai/actors/actor_perception.hpp
	ai/actors/actor_moving.hpp
	ai/actors/actor_looking.hpp
	ai/actors/actor_combat.hpp)

set(CSERIES_H
	cseries/MacrosCpp.h
	cseries/cseries.h
	cseries/cseries_base.h)

set(MATH_H
	math/integer_math.h
	math/real_math.h
	math/color_math.h
	math/matrix_math.h)

set(INPUT_H
	input/input_abstraction.h
	input/input_windows.h)

set(MEMORY_H
	memory/datum_index.h
	memory/queued_sigscanner.h
	memory/array.h
	memory/bitstream.h
	memory/byte_swapping_base.h
	memory/byte_swapping.h
	memory/circular_queue.h
	memory/data.h
	memory/data_base.h
	memory/lruv_cache.h
	memory/memory_pool.h
	memory/simple_circular_queue.hpp)

set(TAG_HELPERS_H
	tag_helpers/tag_groups_markup.h
	tag_helpers/tag_groups_base.h)

set(MAIN_H
	main/main.h
	main/console.hpp
	main/editor.hpp
	main/main_structures.h
	main/levels.h)

set(HEADERS
	${MAIN_H}
	${CSERIES_H}
	${MATH_H}
	${INPUT_H}
	${TAG_HELPERS_H}
	${MEMORY_H}
	${AI_H}
	${ACTORS_H}
	${ACTIONS_H}
	${SCENARIO_H}
	${RUNTIME_H}
	${BITMAP_H}
	${NETWORK_H}
	${ITEMS_H}
	${INTERFACE_H}
	${HS_H}
	${EFFECTS_H}
	${DEVICES_H}
	${CRYPTOGRAPHY_H}
	${CAMERA_H}
	${CACHE_H}
	${CUTSCENE_H}
	${GAME_H}
	primary.h)

#Crappy hack to stop "CMake doesn't know what language this is!" errors. Could probably do something like use .hpp files instead. /shrug
add_library(${PROJECT_NAME} STATIC primary.cpp ${HEADERS})

add_library(${PROJECT_NAME}_iface INTERFACE)
#target_compile_definitions(${PROJECT_NAME}_iface INTERFACE)

install(TARGETS ${PROJECT_NAME} EXPORT library_targets LIBRARY DESTINATION lib ARCHIVE DESTINATION ar)

message(STATUS "Outputting lib to: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
