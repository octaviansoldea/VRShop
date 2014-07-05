PROJECT(libBuilding)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
)

SET(SRCS
	VRFloor.h VRFloor.cpp
	VRWall.h VRWall.cpp
	VRRoom.h VRRoom.cpp
)

ADD_LIBRARY(libBuilding
	${SRCS}
)

SET_PROPERTY(TARGET libBuilding PROPERTY FOLDER Building)