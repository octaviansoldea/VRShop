cmake_minimum_required(VERSION 2.6)
PROJECT(libOrientationWidgets)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/ImagePrimitives/libImagePrimitives
)

SET(SRCS 
	AbstractOrientationWidget.h AbstractOrientationWidget.cpp
	CubeWidget.h CubeWidget.cpp
	AxesWidget.h AxesWidget.cpp
    OrientationWidgets.h OrientationWidgets.cpp
)

ADD_LIBRARY(libOrientationWidgets ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libOrientationWidgets/include)
INSTALL(TARGETS libOrientationWidgets DESTINATION libOrientationWidgets/lib
		LIBRARY DESTINATION libOrientationWidgets/lib)

SET_PROPERTY(TARGET libOrientationWidgets PROPERTY FOLDER ImagePrimitives)