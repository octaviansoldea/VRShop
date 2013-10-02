PROJECT(libSplineWidget)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/libMatej
)


SET(SRCS
	SplineWidget.h SplineWidget.cpp
)

ADD_LIBRARY(libSplineWidget ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libSplineWidget/include)
INSTALL(TARGETS libSplineWidget DESTINATION libSplineWidget/lib
		LIBRARY DESTINATION libSplineWidget/lib)
