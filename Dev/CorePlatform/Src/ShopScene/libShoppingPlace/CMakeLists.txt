PROJECT(libShoppingPlace)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
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
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
  ${CMAKE_SOURCE_DIR}/Props/Scene/libScene
  ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
  ${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  ${CMAKE_SOURCE_DIR}/Props/Building/libBuilding
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libLighting
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libOSGQTViewer
  ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
  ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatarManagerClient
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
  ${CMAKE_SOURCE_DIR}/ShopScene/libShoppingPlace
  ${CMAKE_BINARY_DIR}/ShopScene/libShoppingPlace
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface/View
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient
  ${CMAKE_BINARY_DIR}/ManagementConsole/Cashier/libCashierClient
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient/View

  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierManagerClient
  ${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands


	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/Props/AbstractManagerClient/libAbstractManagerClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductManagerClient

	${CMAKE_SOURCE_DIR}/ShopScene/libModelViewController
)



#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS	VRShoppingPlace_GUI.ui 
						)
  QT5_WRAP_CPP(MOC_SRCS VRShoppingPlace_GUI.h
						)

ELSE()
  QT4_WRAP_UI(UI_SRCS	VRShoppingPlace_GUI.ui
						)
  QT4_WRAP_CPP(MOC_SRCS VRShoppingPlace_GUI.h
						)
ENDIF()


#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS} ${UI_SRCS}
	VRShoppingPlace.h VRShoppingPlace.cpp
	VRShoppingPlace_GUI.h VRShoppingPlace_GUI.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libShoppingPlace ${SRCS}
)

SET_PROPERTY(TARGET libShoppingPlace PROPERTY FOLDER ShopScene)