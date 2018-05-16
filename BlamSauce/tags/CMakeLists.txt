add_subdirectory(files)
add_subdirectory(group)
add_subdirectory(string_ids)

set(TAGS_H
	${FILES_H}
	${GROUP_H}
	${STRING_ID_H}
	${CMAKE_CURRENT_SOURCE_DIR}/bitmap_grp.h
	${CMAKE_CURRENT_SOURCE_DIR}/tag_database_definitions.hpp
	PARENT_SCOPE
	)
