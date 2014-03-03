PROJECT(libPicker)
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
  QT5_WRAP_UI(UI_SRCS
  )
  QT5_WRAP_CPP(MOC_SRCS 
	VRPickAndDragHandlerShopEditor.h
  )
ELSE()
  QT4_WRAP_UI(UI_SRCS
  )
  QT4_WRAP_CPP(MOC_SRCS
	VRPickAndDragHandlerShopEditor.h
)
ENDIF()


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/Props/Scene/libScene
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor/PopUpGUIs
	${CMAKE_BINARY_DIR}/ShopScene/libShopEditor
)

#Define sources to be later added into the library
SET(SRCS
	VRPickAndDragHandler.h VRPickAndDragHandler.cpp
	VRPickAndDragHandlerShopEditor.h VRPickAndDragHandlerShopEditor.cpp
)

ADD_LIBRARY(libPicker
  ${SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libPicker PROPERTY FOLDER Utils)