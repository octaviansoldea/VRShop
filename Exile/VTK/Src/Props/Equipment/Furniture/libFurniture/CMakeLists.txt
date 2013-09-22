PROJECT(libFurniture)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

#includes
INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/Props/Equipment/GeometricShapes/libGeometricShapes
)

#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS}
  Shelf.h Shelf.cpp
  Cupboard.h Cupboard.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libFurniture
  ${SRCS}
)

SET_PROPERTY(TARGET libFurniture PROPERTY FOLDER Props)