PROJECT(libShopEditor)

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
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCameraPicker
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
  ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor
  ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/View
  ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model
  ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs
  ${CMAKE_BINARY_DIR}/ShopScene/libShopEditor
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabaseMgr
  ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
  ${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
)



#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS	VRShopBuilder_GUI.ui 
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.ui
						)
  QT5_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/View/OSGQT_Widget.h 
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureModel.h
						VRShopBuilder_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.h
						)

ELSE()
  QT4_WRAP_UI(UI_SRCS	VRShopBuilder_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.ui
						)
  QT4_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/View/OSGQT_Widget.h 
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureModel.h
						VRShopBuilder_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.h
						)
ENDIF()


#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS} ${UI_SRCS}
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/View/OSGQT_Widget.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/View/OSGQT_Widget.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureItem.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureItem.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureModel.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneStructureModel.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneHierarchy.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/Model/VRSceneHierarchy.cpp
	VRShopBuilder.h VRShopBuilder.cpp
	VRShopBuilder_GUI.h VRShopBuilder_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRInsertNewItem_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRDuplicateItem_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRProductSettings_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveProduct_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRRemoveSelection_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRNewProject_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.h ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs/VRSaveAs_GUI.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libShopEditor ${SRCS}
)

SET_PROPERTY(TARGET libShopEditor PROPERTY FOLDER ShopScene)