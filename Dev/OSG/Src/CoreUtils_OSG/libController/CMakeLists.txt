PROJECT(libController)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")


#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
  )
ELSE(Qt5_FOUND)
  #Assume Qt4_FOUND, if we are here
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
	   ${QT_QTSQL_INCLUDE_DIR}
  )
ENDIF(Qt5_FOUND)
#end Qt

#MOC according to the Qt version
IF(Qt5_FOUND)
   QT5_WRAP_CPP(MOC_SRCS
   VRCameraController.h
   VRPickAndDragController.h
   VRDatabaseController.h
   VRSearchListController.h
   VRSceneHierarchyController.h
   )
ELSE()
  QT4_WRAP_CPP(MOC_SRCS
  VRCameraController.h
  VRPickAndDragController.h
  VRDatabaseController.h
  VRSearchListController.h
  VRSceneHierarchyController.h
  )
ENDIF()

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
	${CMAKE_SOURCE_DIR}/Props/Scene/libScene
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
)

SET(SRCS
	VRCameraController.h VRCameraController.cpp
	VRPickAndDragController.h VRPickAndDragController.cpp
	VRDatabaseController.h VRDatabaseController.cpp
	VRSearchListController.h VRSearchListController.cpp
	VRSceneHierarchyController.h VRSceneHierarchyController.cpp
)

ADD_LIBRARY(libController
  ${SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libController PROPERTY FOLDER Utils)