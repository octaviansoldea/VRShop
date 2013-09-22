cmake_minimum_required(VERSION 2.6)
PROJECT(libImagePrimitives)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
)


SET(SRCS 
    BasicVTKDefinitions.h BasicVTKDefinitions.cpp
)

ADD_LIBRARY(libImagePrimitives ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libImagePrimitives/include)
INSTALL(TARGETS libImagePrimitives DESTINATION libImagePrimitives/lib
		LIBRARY DESTINATION libImagePrimitives/lib)

SET_PROPERTY(TARGET libImagePrimitives PROPERTY FOLDER ImagePrimitives)