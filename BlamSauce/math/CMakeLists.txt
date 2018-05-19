#Yeah, I know, I got lazy. But holey moley is it a pain to do so many of these different CMakeLists files.

set(MATH_H
	${CMAKE_CURRENT_SOURCE_DIR}/color_math.h
	${CMAKE_CURRENT_SOURCE_DIR}/integer_math.h
	${CMAKE_CURRENT_SOURCE_DIR}/matrix_math.h
	${CMAKE_CURRENT_SOURCE_DIR}/periodic_functions.h
	${CMAKE_CURRENT_SOURCE_DIR}/real_math.h
	PARENT_SCOPE)
