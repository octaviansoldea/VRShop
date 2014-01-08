project(Test_libCamera)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

FIND_PACKAGE(OpenSceneGraph REQUIRED osg osgDB osgGA osgViewer OpenThreads)

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCameraPicker

	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/Props/GeometricShapes/libGeometricShapes
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG

)

ADD_EXECUTABLE(Test_libCamera
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libCamera
	${OSG_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGUTIL_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	libCamera
	libPicker
	libCameraPicker
	libAbstractObject
	libGeometricShapes
	libCommon_OSG
)

SET_PROPERTY(TARGET Test_libCamera PROPERTY FOLDER Utils)