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

#Cmake doesn't recognize 'C++latest', and since msvc compiler's c++17 implementation is somewhat incomplete,
#we must manually set it, below.
#set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Tempera)
project(${PROJECT_NAME} CXX C)

#This library has _so much_ information and changes and data that sigscanning isn't really a worthwhile exercise.
#For one, I'm not looking forward to finding all those signatures. Whoever wants to is welcome to try, however... see the queued_sigscanner.h file.
set(TARGET_GAME_VER "HALO_CE_1_10")

# Define Release by default.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "Build type not specified: Using Release by default.")
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "MSVC VERSION --- ${MSVC_VERSION}")
message(STATUS "BINARY OUT DIR --- ${PROJECT_BINARY_DIR}")

find_package(Git REQUIRED)

#https://github.com/nlohmann/json#serialization--deserialization
#TODO: JSON SERIALIZATION/DESERIALIZATION

message(STATUS "DX PATH: ${DX_PATH}")

add_subdirectory(runtime)

find_path(DX_PATH FindDirectX.cmake PATHS ${PROJECT_SOURCE_DIR}/cmake REQUIRED)

set(CMAKE_MODULE_PATH ${DX_PATH} ${HCE_PATH})

find_package(DirectX REQUIRED)
find_package(HaloCE REQUIRED)

include_directories(BEFORE ${DirectX_INCLUDE_DIRS})

include_directories(AFTER ${GAME_LIB_DIRS})

add_subdirectory(BlamSauce)

add_definitions(-D_WINDOWS)

#include_directories(runtime/versions/ ${PROJECT_SOURCE_DIR}/${GAME}/ ${PROJECT_SOURCE_DIR}/${LEVELS}/)

#include_directories(AFTER ${GAME} ${LEVELS} ./versions)

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

#Crappy hack to stop "CMake doesn't know what language this is!" errors. Could probably do something like use .hpp files instead. /shrug
add_library(${PROJECT_NAME} STATIC ${HEADERS} primary.cpp)

add_library(${PROJECT_NAME}_iface INTERFACE)
#target_compile_definitions(${PROJECT_NAME}_iface INTERFACE)

install(TARGETS ${PROJECT_NAME} EXPORT library_targets LIBRARY DESTINATION lib ARCHIVE DESTINATION ar)

message(STATUS "Outputting lib to: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
