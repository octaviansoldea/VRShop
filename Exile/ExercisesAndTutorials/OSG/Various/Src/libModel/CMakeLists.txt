CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(libModel)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
)

#Define sources to be later added into the library
SET(SRCS ${SRCS}
	BaseModel.h BaseModel.cpp
	Model2D.h Model2D.cpp
	Model3D.h Model3D.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libModel
	${SRCS}
)

SET_PROPERTY(TARGET libModel PROPERTY FOLDER Exercise)