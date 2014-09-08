project(Test_libPicker)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

FIND_PACKAGE(OpenSceneGraph REQUIRED osg osgDB osgGA osgUtil osgViewer OpenThreads)

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/libPicker
	${CMAKE_SOURCE_DIR}/libCamera
	${CMAKE_SOURCE_DIR}/libModel
	${CMAKE_SOURCE_DIR}/libCommon_OSG
)

ADD_EXECUTABLE(Test_libPicker
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libPicker
	${OSG_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGUTIL_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	libCommon_OSG
	libPicker
	libCamera
	libModel
)

SET_PROPERTY(TARGET Test_libPicker PROPERTY FOLDER Exercise)