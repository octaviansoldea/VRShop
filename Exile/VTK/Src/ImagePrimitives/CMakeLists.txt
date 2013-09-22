CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ImagePrimitives)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SUBDIRS(
	libRenWin
	libImagePrimitives
	libOrientationWidgets
	Test_libOrientationWidgets
)




