PROJECT(libCameraPicker)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
)

SET(SRCS
    VRKeyboardMousePicker.h VRKeyboardMousePicker.cpp
)

ADD_LIBRARY(libCameraPicker ${SRCS})



FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libCameraPicker/include)
INSTALL(TARGETS libCameraPicker DESTINATION libCameraPicker/lib
		LIBRARY DESTINATION libCameraPicker/lib)

SET_PROPERTY(TARGET libCameraPicker PROPERTY FOLDER Utils)