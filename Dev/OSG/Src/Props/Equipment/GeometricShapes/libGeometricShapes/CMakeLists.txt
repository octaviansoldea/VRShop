PROJECT(libGeometricShapes)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
)

SET(SRCS
	VRAbstractGeomShape.h VRAbstractGeomShape.cpp
	VRCylinder.h VRCylinder.cpp
	VRPrism.h VRPrism.cpp
	VRPlate3D.h VRPlate3D.cpp
	VRUntransformedPlate2D.h VRUntransformedPlate2D.cpp
	VRUntransformedPlate3D.h VRUntransformedPlate3D.cpp
	VRUntransformedPolygon2D.h VRUntransformedPolygon2D.cpp
	VRUntransformedPolygon3D.h VRUntransformedPolygon3D.cpp
	VRUntransformedSphere.h VRUntransformedSphere.cpp
)

ADD_LIBRARY(libGeometricShapes
	${SRCS}
)

SET_PROPERTY(TARGET libGeometricShapes PROPERTY FOLDER Props)