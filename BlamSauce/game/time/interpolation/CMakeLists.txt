#I can't help but feel like this whole bit right here is pointless...
set(INTERP_H
	${CMAKE_CURRENT_SOURCE_DIR}/c_interp_base.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/c_interp_function.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/c_interp_linear.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/i_interpolator.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/interpolation.hpp
	PARENT_SCOPE)
