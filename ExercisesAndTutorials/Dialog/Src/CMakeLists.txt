CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(PriceComparison)

SET(CMAKE_DEBUG_POSTFIX "D")

#Paths to Qt libraries
#SET(CMAKE_PREFIX_PATH 
#	"C:/Programi/Qt/qt-everywhere-opensource-src-4.8.4/include"
	#"C:/Programi/Qt/qt-everywhere-opensource-src-5.0.2_SQLVisual2012_x64/qtbase/lib/cmake"
#)

MESSAGE(STATUS "CMAKE_PREFIX_PATH = " ${CMAKE_PREFIX_PATH})

FIND_PACKAGE(Qt5Core)
IF(Qt5Core_FOUND)
  SET(Qt5_FOUND TRUE)
  MESSAGE("Qt5 found")
  FIND_PACKAGE(Qt5Core)
  FIND_PACKAGE(Qt5Gui)
  FIND_PACKAGE(Qt5Widgets)
ELSE()
	#Search for Qt packages 4 AND 5
	FIND_PACKAGE(Qt4 REQUIRED)
	#IF(QTVERSION MATCHES "4.*")
		SET(Qt4_FOUND TRUE)
		MESSAGE("Qt4 found")
	#ENDIF()
ENDIF()

#Project includes 2 subdirs
SUBDIRS(
    libPlatform
    Test_libPlatform
)