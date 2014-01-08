PROJECT(libCamera)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCameraPicker
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
)

SET(SRCS
	VRKeyboardMouseManipulator.h VRKeyboardMouseManipulator.cpp
)

ADD_LIBRARY(libCamera
  ${SRCS}
)

SET_PROPERTY(TARGET libCamera PROPERTY FOLDER Utils)