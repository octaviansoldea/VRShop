PROJECT(libHandleWidget)

INCLUDE_DIRECTORIES(
)


SET(SRCS
	HandleWidget.h HandleWidget.cpp
)

ADD_LIBRARY(libHandleWidget ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libHandleWidget/include)
INSTALL(TARGETS libHandleWidget DESTINATION libHandleWidget/lib
		LIBRARY DESTINATION libHandleWidget/lib)
