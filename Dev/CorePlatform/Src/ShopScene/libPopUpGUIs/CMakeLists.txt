PROJECT(libPopUpGUIs)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
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
  #${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libOSGQTViewer
  #${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libItemModel
  #${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
  ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
  ${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
  #${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  #${CMAKE_SOURCE_DIR}/Props/Scene/libScene
  #${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libSearch
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
  #${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
  #${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
  ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs
  ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem
  ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem
  ${CMAKE_BINARY_DIR}/ShopScene/libPopUpGUIs
)

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.ui
						)
  QT5_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUIBase.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.h
						)

ELSE()
  QT4_WRAP_UI(UI_SRCS	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.ui
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.ui
						)
  QT4_WRAP_CPP(MOC_SRCS ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUIBase.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.h
#						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.h
						${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.h
						)
ENDIF()


#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS} ${UI_SRCS}
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRInsertNewItem_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRDuplicateItem_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUIBase.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUIBase.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItem_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemPrism_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/EditItem/VREditItemFurniture_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRRemoveProduct_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRRemoveSelection_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRNewProject_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.h 
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/VRSaveAs_GUI.cpp
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.h
	${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem/VRAddProduct_GUI.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libPopUpGUIs ${SRCS})

SET_PROPERTY(TARGET libPopUpGUIs PROPERTY FOLDER ShopScene)