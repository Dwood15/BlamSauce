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
project(${PROJECT_NAME} CXX C)

set(CMAKE_CXX_STANDARD 17)

#TODO: JSON SERIALIZATION/DESERIALIZATION
#https://github.com/nlohmann/json#serialization--deserialization

message(STATUS "MSVC VERSION --- ${MSVC_VERSION}")
message(STATUS "BINARY OUT DIR --- ${PROJECT_BINARY_DIR}")

find_path(DX_PATH FindDirectX.cmake PATHS ${PROJECT_SOURCE_DIR}/cmake REQUIRED)
find_path(HCE_PATH FindHaloCE.cmake PATHS ${PROJECT_SOURCE_DIR}/cmake REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${DX_PATH} ${HCE_PATH})

find_package(HaloCE REQUIRED)
find_package(DirectX REQUIRED)

#TODO: JSON SERIALIZATION/DESERIALIZATION
#https://github.com/nlohmann/json#serialization--deserialization
include_directories(BEFORE ${DirectX_INCLUDE_DIRS})
message(STATUS "DX include Dirs: ${DirectX_INCLUDE_DIRS}")

#EXAMPLE DX INCLUDE PATH: D:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include

# Defines Release by default.
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "Build type not specified: Using Release by default.")
endif(NOT CMAKE_BUILD_TYPE)


add_definitions(-D_WINDOWS)
if(MINGW)
	if($ENV{CLION_IDE})
		#convenience function for CLion.
		return()
	endif()

	message(STATUS "Mingw detected.")
	set(COMPILER_REL_FLDR mingw)
	set(CMAKE_CXX_FLAGS "-std=c++17\ -fpermissive")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}\ -g\ -m32\ -masm=intel")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -g -m32 -masm=intel")
elseif(MSVC)
	#vc++ 2017 build toolset. Available from microsoft _without_ the abomination that is visual studio, here: http://landinghub.visualstudio.com/visual-cpp-build-tools
	if(NOT CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION OR NOT "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" STREQUAL "10.0.16299.0")
		#message(WARNING "CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION is empty! Could not find applicable windows 10 sdk.")
		set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0.16299.0)
		#TODO: CHECK FOR AVAILABLE SDK VERSIONS IF NONE SET
	endif()

	set(COMPILER_REL_FLDR msvc)
	set(CMAKE_C_FLAGS '')
	set(CMAKE_CXX_FLAGS /std:c++latest\ /MTd\ )
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd\ /Gy- /W3 /Od /Zi /MP /EHsc /fp:fast\ /std:c++latest\ /arch:SSE2 /D\ \"WIN32\" /D \"_WINDOWS\" /D \"_USRDLL\" /D \"_WINDLL\"\ /D_CRT_SECURE_NO_WARNINGS")
else()
	message(FATAL_ERROR "Unrecognized compiler/suite: ${CMAKE_CXX_COMPILER_ID}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	#DO DEBUG STUFF HERE
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./bin/${COMPILER_REL_FLDR}-debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	if($ENV{CLION_IDE})
		message(STATUS "convenience hack for making CLion less annoying.")
		return()
	endif()
	set(OUTPUT_DIR ./bin/${COMPILER_REL_FLDR}-Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/ar")

if(MSVC)
	set(LINKER_FLAGS "/MANIFEST\ /NXCOMPAT\ /DEBUG\ /MACHINE:X86\ /SAFESEH:NO\ /INCREMENTAL:NO\ /SUBSYSTEM:WINDOWS\ /MANIFESTUAC:NO\ /OPT:NOICF\ /NOLOGO\ /ASSEMBLYDEBUG\ ") #rip alignment on win32
	set(CMAKE_SHARED_LINKER_FLAGS ${LINKER_FLAGS})

elseif(NOT MSVC)
	set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} $ENV{LDFLAGS} "-lws2_32 -static-libgcc -static-libstdc++ -static -luserenv -static -static -ladvapi32")
endif()

set(CSERIES_H cseries/MacrosCpp.h cseries/cseries.h cseries/cseries_base.h)
set(MATH_H math/integer_math.h math/real_math.h math/color_math.h math/matrix_math.h)
set(INPUT_H input/input_abstraction.h input/input_windows.h)
set(MEMORY_H memory/datum_index.h)
set(TAG_HELPERS_H tag_helpers/tag_groups_markup.h main/main.h)
set(MAIN_H main/main.h)

set(HEADERS ${MAIN_H} ${CSERIES_H} ${MATH_H} ${INPUT_H} ${TAG_HELPERS_H} ${MEMORY_H})

set(CSERIES_CPP  cseries/cseries_windows.cpp)
set(MATH_CPP math/real_math.cpp)
set(INPUT_CPP )
set(MEMORY_CPP )
set(TAG_HELPERS_CPP )
set(MAIN_CPP )

set(CPPFILES ${MAIN_CPP} ${MATH_CPP} ${INPUT_CPP} ${CSERIES_CPP} ${MEMORY_CPP} ${TAG_HELPERS_CPP})

add_library(${PROJECT_NAME} STATIC ${CPPFILES})

message(STATUS "Outputting lib to: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
