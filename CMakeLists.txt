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

set(TARGET_GAME_VER "HALO_CE_1_10")

#This library has _so much_ information and changes and data that sigscanning isn't really a worthwhile exercise.
#For one, I'm not looking forward to finding all those signatures. Whoever wants to is welcome to try, however... see the queued_sigscanner.h file.

set(STUBBZ runtime/stubbz)
set(HALO_TRIAL runtime/halo1/windows/trial)
set(HALO_FULL runtime/halo1/windows/full)

if (TARGET_GAME_VER MATCHES "^STUBBZ$")
	#Is there more than one stubbz version?
	#Maybe the mac version?
	#	set(LEVELS ${STUBBZ})
	set(GAME ${STUBBZ})
	message(FATAL_ERROR "STUBBZ IS NOT AN IMPLEMENTED TARGET. SORRY.")
endif ()

if (NOT TARGET_GAME_VER MATCHES "^(HALO)_(TRIAL|PC|CE)")
	message(FATAL_ERROR "UNKNOWN VERSION ${TARGET_GAME_VER} SELECTED.")
endif ()

#This is deliberately _not_ an elseif.
if (TARGET_GAME_VER MATCHES "^(HALO)_(TRIAL|PC|CE)")
	set(GAME runtime/halo1)
endif ()

if (TARGET_GAME_VER MATCHES "^HALO_TRIAL$")
	#	set(LEVELS ${HALO_TRIAL})
	set(GAME ${HALO_TRIAL})
	message(FATAL_ERROR "HALO TRIAL IS NOT AN IMPLEMENTED LIBRARY TARGET. SORRY.")
endif ()

if (NOT TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_[0-1][0-9])$")
	message(FATAL_ERROR "UNKNOWN VERSION ${TARGET_GAME_VER} SELECTED.")
endif ()

#This is deliberately _not_ an elseif.
if (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_[0-1][0-9])$")
	#TODO: Find a better way of doing this garbage.
	if (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_0[0-9])$")
		message(FATAL_ERROR "ONLY 1_10 IS AN IMPLEMENTED LIBRARY TARGET. SORRY.")

		if (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_00)$")
			set(MINOR_VER "1_00")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_01)$")
			set(MINOR_VER "1_01")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_02)$")
			set(MINOR_VER "1_02")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_03)$")
			set(MINOR_VER "1_03")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_04)$")
			set(MINOR_VER "1_04")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_05)$")
			set(MINOR_VER "1_05")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_06)$")
			set(MINOR_VER "1_06")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_07)$")
			set(MINOR_VER "1_07")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_08)$")
			set(MINOR_VER "1_08")
		elseif (TARGET_GAME_VER MATCHES "^(HALO)_(PC|CE)_(1_09)$")
			set(MINOR_VER "1_09")
		endif ()
	else ()
		set(MINOR_VER "1_10")
	endif ()

	if (TARGET_GAME_VER MATCHES "^(HALO)_PC_(1_[0-1][0-9])$")
		set(MAJOR_VER ${HALO_FULL}/pc)
		message(FATAL_ERROR "HALO PC IS NOT YET AN IMPLEMENTED LIBRARY TARGET. SORRY.")
	else ()
		set(MAJOR_VER ${HALO_FULL}/ce)
	endif ()

	set(LEVELS ${HALO_FULL})
	set(GAME ${MAJOR_VER}/${MINOR_VER})
endif ()

#I put runtime/versions/versions.h into its own directory b/c I'm not sure if cmake will make <runtime/pc/foobar.h> a valid include
#even though we want only to deal with <foobar.h> for version-specific headers.
include_directories(AFTER ${GAME} ${LEVELS} runtime/versions)

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
	${GAME}/memory_locations.h
	${GAME}/engine_functions.h
	${GAME}/current_engine.h
	${LEVELS}/levels.h
	runtime/versions/versions.h
	runtime/versions/cache_files_win.hpp
	)

set(BITMAP_H
	tags/bitmap_grp.h)

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
	cache/shared/pc_sound_cache.hpp
	cache/shared/texture_cache.hpp
	cache/shared/sound_cache.hpp
	cache/predicted_resources.hpp
	cache/physical_memory_map_structures.hpp
	cache/physical_memory_map.hpp
	cache/shared/pc_texture_cache.hpp
	cache/cache_files.hpp)

set(CAMERA_H
	interface/camera/dead.hpp
	interface/camera/definitions.hpp
	interface/camera/director.hpp
	interface/camera/director_structures.hpp
	interface/camera/first_person.hpp
	interface/camera/following.hpp
	interface/camera/observer.hpp
	)

set(M_ANIMATIONS_H
	models/animations/definitions.hpp
	models/animations/model.hpp
	models/animations/recorded_animation_definitions.hpp
	models/animations/recorded_animation_playback.hpp
	models/animations/recorded_animations_structures.hpp
	models/animations/recorded_animations.hpp
	models/animations/recorded_animation_playback_v1.hpp
	)

set(M_COLLISIONS_H
	models/collision/bsp_definitions.hpp
	models/collision/bsp.hpp
	models/collision/features.hpp
	models/collision/model_definitions.hpp
	models/collision/models.hpp
	)

set(MODELS_H
	${M_ANIMATIONS_H}
	${M_COLLISIONS_H}
	models/collisions.hpp
	models/model_definitions.hpp
	models/models.hpp
	)

set(CRYPTOGRAPHY_H
	cryptography/cryptography.h)

set(DEVICES_H)
set(GAME_H
	game/action_queue.hpp
	game/allegiance.hpp
	game/vehicle_update_queue.hpp
	game/time/time_structures.hpp
	game/time/time.hpp
	memory/position_queue.hpp
	game/player/players.hpp
	game/player/player_structures.hpp
	game/player/player_control.hpp
	game/player/player_action.hpp
	game/multiplayer_sounds.hpp
	game/globals/globals_structures.hpp
	game/globals/globals_definitions.hpp
	game/globals/globals.hpp
	game/game.hpp
	game/engines/engine_stub.hpp
	game/engines/engine_slayer.hpp
	game/engines/engine_race.hpp
	game/engines/engine_oddball.hpp
	game/engines/engine_king.hpp
	game/engines/engine_ctf.hpp
	game/engines/engine.hpp
	game/configuration.hpp
	game/cheats.hpp
	game/state.h game/engines/variants.h)

set(EFFECTS_H
	effects/contrail/contrail_definitions.hpp
	effects/contrail/contrails.hpp
	effects/effects_constants.hpp
	effects/damage/damage_effect_definitions.hpp
	effects/effects.hpp
	effects/particle/weather/weather_particle_systems.hpp
	effects/particle/weather/weather_particle_system_definitions.hpp
	effects/player/player_effects.hpp
	effects/particle/particles.hpp
	effects/particle/particle_systems.hpp
	effects/particle/particle_system_definitions.hpp
	effects/particle/particle_definitions.hpp
	effects/material/material_effect_definitions.hpp
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
	hs/types_traits.hpp
	hs/types_runtime.inl
	)

set(I_HUD_H interface/hud/first_person_weapons.hpp
	interface/hud/first_person_weapons_structures.hpp
	interface/hud/hud.hpp
	interface/hud/weapon_hud_interface_definition.hpp
	interface/hud/unit_hud_interface_definition.hpp
	interface/hud/hud_weapon_structures.hpp
	interface/hud/hud_weapon.hpp
	interface/hud/hud_unit_structures.hpp
	interface/hud/hud_unit.hpp
	interface/hud/hud_nav_points.hpp
	interface/hud/hud_messaging_structures.hpp
	interface/hud/hud_messaging_definitions.hpp
	interface/hud/hud_messaging.hpp
	interface/hud/hud_draw.hpp
	interface/hud/hud_definitions.hpp
	interface/hud/hud_chat.hpp
	interface/hud/weapon_hud_interface_definition.hpp
	)

set(I_WIDGETS_H
	interface/widgets/widgets.hpp
	interface/widgets/ui_event_handler_functions.hpp
	interface/widgets/ui_game_data_input_functions.hpp
	interface/widgets/ui_group.hpp)

set(INTERFACE_H
	${I_HUD_H}
	${I_WIDGETS_H}

	interface/map_list.hpp
	interface/hud/motion_sensor.hpp
	interface/terminal.hpp
	interface/ui_video_screen.hpp
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
	cseries/base.h
	cseries/yelo_base.h
	cseries/errors.h)

set(MATH_H
	math/integer_math.h
	math/real_math.h
	math/color_math.h
	math/matrix_math.h math/periodic_functions.h)

set(INPUT_H
	interface/input/input_abstraction.h
	interface/input/input_windows.h)

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
	memory/simple_circular_queue.hpp
	memory/debug.h
	memory/profiling.h)

set(OBJECTS_H
	objects/damage.hpp
	objects/index_resolution.hpp
	objects/object_definitions.hpp
	objects/object_lights.hpp
	objects/object_structures.hpp
	objects/object_types.hpp
	objects/objects.hpp
	objects/placeholder_definitions.hpp
	objects/scenery_definitions.hpp
	objects/sound_scenery_definitions.hpp
	objects/vehicle_remapper.hpp
	)

set(TAG_HELPERS_H
	tags/group/tag_groups_markup.h
	tags/group/tag_groups_base.h)

set(MAIN_H
	main/main.h
	main/console.hpp
	main/editor.hpp
	main/main_structures.h
	)

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
