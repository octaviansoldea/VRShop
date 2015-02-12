PROJECT(libCommon_OSG)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
)

SET(SRCS
	VRAxes.h VRAxes.cpp
	VRBoundingBox.h VRBoundingBox.cpp
	VRGrid.h VRGrid.cpp
	VRObjectTransformation.h VRObjectTransformation.cpp
	VRBasicOSGOperations.h VRBasicOSGOperations.cpp
	VRReadAndSaveFileCallback.h VRReadAndSaveFileCallback.cpp
	VRSurfaceOperations.h VRSurfaceOperations.cpp
)

ADD_LIBRARY(libCommon_OSG
  ${SRCS}
)

SET_PROPERTY(TARGET libCommon_OSG PROPERTY FOLDER Utils)