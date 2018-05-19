#TODO: Add any ${CMAKE_CURRENT_SOURCE_DIR}/experimental/<filename>.cpp CPP files here 
#set(EXPERIMENTAL_CPP )

#TODO: ADD ${EXPERIMENTAL_CPP}
set(TEMPERA_CPP ./main.cpp)

add_library(dinput8 SHARED ${})

target_link_libraries(dinput8 ${DETOURS_GLOB} ${MARIADB_LIBRARY} ${CAPSTONE_STATIC_GLOB} ${DirectX_LIBRARIES})

#TODO: set output to a global ROOT dir variable from the top-level cmakelists file.
# This should be based on the target version discovery in ../runtime/CMakelists.txt

#set(CMAKE_PDB_OUTPUT_DIRECTORY "${HaloCE_ROOT_DIR}")
#set(LIBRARY_OUTPUT_PATH "${HaloCE_ROOT_DIR}")

set_target_properties(dinput8 PROPERTIES OUTPUT_NAME "dinput8")