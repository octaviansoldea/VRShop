PROJECT(libReadWritePPM)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	ReadWritePPM.h ReadWritePPM.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libColor
)

ADD_LIBRARY(libReadWritePPM ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libReadWritePPM/include)
INSTALL(TARGETS libReadWritePPM DESTINATION libReadWritePPM/lib
		LIBRARY DESTINATION libReadWritePPM/lib)

SET_PROPERTY(TARGET libReadWritePPM PROPERTY FOLDER Basics)