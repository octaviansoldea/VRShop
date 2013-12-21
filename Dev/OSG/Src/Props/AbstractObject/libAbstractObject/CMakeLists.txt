PROJECT(libAbstractObject)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/GeometricShapes/libGeometricShapes
	${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
)

SET(SRCS
    VRAbstractObject.h VRAbstractObject.cpp
)

ADD_LIBRARY(libAbstractObject ${SRCS})



FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libAbstractObject/include)
INSTALL(TARGETS libAbstractObject DESTINATION libAbstractObject/lib
		LIBRARY DESTINATION libAbstractObject/lib)

SET_PROPERTY(TARGET libAbstractObject PROPERTY FOLDER Props)