#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the OSGQtBrowser project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

  
file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
	[^.]*.htm*
    )

include_directories(${PLUGIN_INCLUDE_DIRS})


FIND_PACKAGE(OpenSceneGraph 
	REQUIRED osg osgAnimation osgDB osgGA osgQt osgUtil osgViewer OpenThreads
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

IF(Qt5_FOUND)
  MESSAGE("Database Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
  )
  MESSAGE("Database Qt5 used END")

ELSE()
  #Assume Qt4_FOUND, if we are here
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
	   ${QT_QTSQL_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF()

include_directories	(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
)


# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

	
SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )


# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

LINK_DIRECTORIES( ${Boost_LIBRARY_DIRS} 
)

SET(LIBS_COMMON
	${OSG_LIBRARIES}
	${OSGANIMATION_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGUTIL_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(${PLUGIN_NAME}
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(${PLUGIN_NAME}
	${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF()



#this will build a Chrome package
#add_chrome_package(${PLUGIN_NAME}
#	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#	"${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
#	"${CMAKE_CURRENT_SOURCE_DIR}/sign/package_key.pem"
#	${PROJECT_NAME})

#this will build a XPI package using XPISigner (see http://code.google.com/p/xpisigner/ )
# add_signed_xpi_installer(${PLUGIN_NAME}
# 	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#   "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
# 	$ENV{XPI_PATH} 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx" 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
# 	${PROJECT_NAME})

