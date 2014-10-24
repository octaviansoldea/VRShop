PROJECT(Test_libEmbeddedWidget)
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

  # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
#       ${CMAKE_CURRENT_BINARY_DIR}
#       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)
#end Qt


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/EmbeddedWidget/libEmbeddedWidget
	${CMAKE_BINARY_DIR}/EmbeddedWidget/libEmbeddedWidget

  ${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
  ${CMAKE_SOURCE_DIR}/Props/Scene/libScene
  ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
  ${CMAKE_SOURCE_DIR}/Props/Equipment/GeometricShape/libGeometricShape
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  ${CMAKE_SOURCE_DIR}/Props/Building/libBuilding
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libLighting
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libOSGQTViewer
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
  ${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
  ${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
  ${CMAKE_SOURCE_DIR}/ShopScene/libShoppingPlace
  ${CMAKE_BINARY_DIR}/ShopScene/libShoppingPlace
  ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs/ProductItem
  ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
  ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatarManager
  ${CMAKE_SOURCE_DIR}/Props/Avatar/libAnimationEditor
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient/View


  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libItemModel
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libSearch
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libMngtController
  ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor
  ${CMAKE_BINARY_DIR}/ShopScene/libShopEditor
  ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
  ${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierManagerClient
  ${CMAKE_SOURCE_DIR}/Props/AbstractManagerClient/libAbstractManagerClient
  ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductManagerClient
  ${CMAKE_SOURCE_DIR}/ShopScene/libModelViewController
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
	libAgent
	libAgentManager
	libAbstractObject
	libGeometricShape
	libPopUpGUIs
	libShopEditor
	libShoppingPlace
	libCommon
	libCommon_OSG
	libCommon_QT
	libCamera
	libPicker
	libFurniture
	libBuilding
	libScene
	libLighting
	libOSGQTViewer
	libProduct
	libProductInterface
	libController
	libServer
	libClient
	libAvatar
	libAvatarManager
	libAnimationEditor
	libDatabase
	libCashierClient
	libEmbeddedWidget

  libItemModel
  libSearch
  libController
  libMngtController
  
  libShopEditor
  libPopUpGUIs
  libProduct
  libServerClientCommands
  libCashierManagerClient
  libAbstractManagerClient
  libProductManagerClient
  libModelViewController
)


#Define sources
SET(SRCS
	main.cpp
)


#Define executable
ADD_EXECUTABLE(Test_libEmbeddedWidget
	${SRCS}
)


IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libEmbeddedWidget
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
    ${Qt5Network_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libEmbeddedWidget
    ${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF()

SET_PROPERTY(TARGET Test_libEmbeddedWidget PROPERTY FOLDER EmbeddedWidget)