CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET(CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64")

FIND_PACKAGE(OpenSceneGraph 
	REQUIRED osg osgDB osgGA osgUtil osgViewer OpenThreads
)

SUBDIRS(
  libCamera
  libPicker
  Test_libPicker
  Test_libCamera
)