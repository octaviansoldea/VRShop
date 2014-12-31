CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(testing)
SET(CMAKE_DEBUG_POSTFIX "D")

FIND_PACKAGE(OpenSceneGraph 
	REQUIRED osg osgDB osgGA osgQt osgUtil osgViewer OpenThreads
)

FIND_PACKAGE(Qt5Core)
IF(Qt5Core_FOUND)
  SET(Qt5_FOUND TRUE)
  FIND_PACKAGE(Qt5Core)
  FIND_PACKAGE(Qt5Gui)
  FIND_PACKAGE(Qt5Widgets)
  FIND_PACKAGE(Qt5OpenGL)
  FIND_PACKAGE(Qt5Sql)
  FIND_PACKAGE(Qt5Network)
ELSE(Qt5Core_FOUND)
  FIND_PACKAGE(Qt4 REQUIRED)
  SET(Qt4_FOUND TRUE)
ENDIF(Qt5Core_FOUND)

	
SUBDIRS(
  libCommon_OSG
  libOSGQTViewer
  libModel
  libReadWriteData
  Test_libModel
)