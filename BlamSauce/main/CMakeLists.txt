#Yeah, I know, I got lazy. But holey moley is it a pain to do so many of these different CMakeLists files.

set(M_CONFIGURATION_H
	${CMAKE_CURRENT_SOURCE_DIR}/configuration/c_settings_manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/configuration/c_settings_singleton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/configuration/yelo_settings_definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/configuration/yelo_shared_settings.hpp
	)

set(MAIN_H
	${M_CONFIGURATION_H}
	${CMAKE_CURRENT_SOURCE_DIR}/main.h
	${CMAKE_CURRENT_SOURCE_DIR}/campaign.h
	${CMAKE_CURRENT_SOURCE_DIR}/console.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/editor.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main_structures.h
	PARENT_SCOPE)
