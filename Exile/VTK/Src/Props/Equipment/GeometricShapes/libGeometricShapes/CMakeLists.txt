PROJECT(libGeometricShapes)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS}
  GenericPlate.h GenericPlate.cpp
  PlatePipe.h PlatePipe.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libGeometricShapes
  ${SRCS}
)

SET_PROPERTY(TARGET libGeometricShapes PROPERTY FOLDER Props)