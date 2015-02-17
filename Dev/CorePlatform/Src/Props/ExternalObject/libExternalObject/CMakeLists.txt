PROJECT(libExternalObject)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
)

SET(SRCS
  VRExternalObject.h VRExternalObject.cpp
)

ADD_LIBRARY(libExternalObject
  ${SRCS}
)

SET_PROPERTY(TARGET libExternalObject PROPERTY FOLDER Props)