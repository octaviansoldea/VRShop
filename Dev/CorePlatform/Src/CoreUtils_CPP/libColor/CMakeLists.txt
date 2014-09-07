PROJECT(libColor)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	Color.h
	ColorGenerator.h ColorGenerator.cpp
)

ADD_LIBRARY(libColor ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libColor/include)
INSTALL(TARGETS libColor DESTINATION libcolor/lib
		LIBRARY DESTINATION libcolor/lib)

SET_PROPERTY(TARGET libColor PROPERTY FOLDER Basics)