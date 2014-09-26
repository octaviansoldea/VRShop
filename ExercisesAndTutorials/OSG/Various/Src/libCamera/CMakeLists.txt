PROJECT(libCamera)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
)

#Define sources to be later added into the library
SET(SRCS
	VRKeyboardMouseManipulator.h VRKeyboardMouseManipulator.cpp
	OSGCameraManipulator.h OSGCameraManipulator.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libCamera
  ${SRCS}
)

SET_PROPERTY(TARGET libCamera PROPERTY FOLDER Exercise)