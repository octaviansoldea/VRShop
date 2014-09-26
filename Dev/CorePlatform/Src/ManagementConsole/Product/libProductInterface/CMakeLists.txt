PROJECT(libProductInterface)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
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
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface
	${CMAKE_BINARY_DIR}/ManagementConsole/Product/libProductInterface
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View
)

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS		${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.ui)
  QT5_WRAP_CPP(MOC_SRCS 	VRProductInterface.h VRProductBasketInterface.h
							${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.h
							)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		VRProductInterface.h VRProductBasketInterface.h
							${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.h)
  QT4_WRAP_UI(UI_SRCS		${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.ui)
ENDIF(Qt5_FOUND)


#Define sources to be later added into the library
SET(SRCS ${MOC_SRCS} ${UI_SRCS}
	VRProductInterface.h VRProductInterface.cpp
	VRProductBasketInterface.h VRProductBasketInterface.cpp
	VRProductBasketInterfaceController.h VRProductBasketInterfaceController.cpp
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.h
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View/VRProductBasketInterfaceItem_GUI.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libProductInterface
  ${SRCS}
)

SET_PROPERTY(TARGET libProductInterface PROPERTY FOLDER Management)