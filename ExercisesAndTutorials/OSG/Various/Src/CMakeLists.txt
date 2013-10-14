CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET(CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64")

FIND_PACKAGE(OpenSceneGraph 
	REQUIRED osg osgDB osgGA osgQt osgUtil osgViewer OpenThreads
)

FIND_PACKAGE(Qt5Core)
IF(Qt5Core_FOUND)
  SET(Qt5_FOUND TRUE)
  MESSAGE("Qt5 found")
  FIND_PACKAGE(Qt5Core)
  FIND_PACKAGE(Qt5Gui)
  FIND_PACKAGE(Qt5Widgets)
  FIND_PACKAGE(Qt5OpenGL)
ELSE()
  #Search for Qt packages 4 AND 5
  FIND_PACKAGE(Qt4 REQUIRED)
  SET(Qt4_FOUND TRUE)
  MESSAGE("Qt4 found")
ENDIF(Qt5Core_FOUND)

SUBDIRS(
  libModel
  libOSGQTExample
  libCamera
  libCommon_OSG
  libPicker
  Test_libCommon_OSG
  Test_libPicker
  Test_libCamera
  Test_libOSGQTExample  
)
