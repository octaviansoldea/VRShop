PROJECT(libPicker)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/libModel
)

#Define sources to be later added into the library
SET(SRCS
	OSGPicker.h OSGPicker.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libPicker
  ${SRCS}
)

SET_PROPERTY(TARGET libPicker PROPERTY FOLDER Exercise)