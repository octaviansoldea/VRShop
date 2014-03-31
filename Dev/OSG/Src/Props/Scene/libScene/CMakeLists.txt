PROJECT(libScene)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
)

SET(SRCS
    VRScene.h VRScene.cpp
)

ADD_LIBRARY(libScene ${SRCS})



FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libScene/include)
INSTALL(TARGETS libScene DESTINATION libScene/lib
		LIBRARY DESTINATION libScene/lib)

SET_PROPERTY(TARGET libScene PROPERTY FOLDER Props)