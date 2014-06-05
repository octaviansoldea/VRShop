CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Animation)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_DEBUG_POSTFIX "D")

FIND_PACKAGE(OpenSceneGraph 
	REQUIRED osg osgDB osgGA osgQt osgUtil osgViewer OpenThreads osgSim osgAnimation osgWidget osgFX
)

INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS})

SUBDIRS(
	osganimate
	osganimationeasemotion
	osganimationhardware
	osganimationmakepath
	osganimationmorph
	osganimationnode
	osganimationskinning
	osganimationsolid
	osganimationtimeline
	osganimationviewer	
	
	libAvatar
	Test_libAvatar
)
