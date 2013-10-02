PROJECT(libSphereWidget)

INCLUDE_DIRECTORIES(
)


SET(SRCS
	SphereWidget.h SphereWidget.cpp
)

ADD_LIBRARY(libSphereWidget ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libSphereWidget/include)
INSTALL(TARGETS libSphereWidget DESTINATION libSphereWidget/lib
		LIBRARY DESTINATION libSphereWidget/lib)
