PROJECT(libSceneEditor)

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


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
  ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor
  ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/View
  ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model
  ${CMAKE_BINARY_DIR}/SceneEditor/libSceneEditor
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabaseMgr
  ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
  ${CMAKE_SOURCE_DIR}/Props/Equipment/GeometricShapes/libGeometricShapes
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
)



#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS VRShopBuilder_GUI.ui)
  QT5_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/View/OSGQT_Widget.h 
						${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureModel.h
						VRShopBuilder_GUI.h)
ELSE()
  QT4_WRAP_UI(UI_SRCS VRShopBuilder_GUI.ui)
  QT4_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/View/OSGQT_Widget.h 
						${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureModel.h
						VRShopBuilder_GUI.h)
ENDIF()


#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS} ${UI_SRCS}
	${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/View/OSGQT_Widget.h ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/View/OSGQT_Widget.cpp
	${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureItem.h ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureItem.cpp
	${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureModel.h ${CMAKE_SOURCE_DIR}/SceneEditor/libSceneEditor/Model/VRSceneStructureModel.cpp
	VRShopBuilder.h VRShopBuilder.cpp
	VRShopBuilder_GUI.h VRShopBuilder_GUI.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libSceneEditor ${SRCS}
)

SET_PROPERTY(TARGET libSceneEditor PROPERTY FOLDER SceneEditor)