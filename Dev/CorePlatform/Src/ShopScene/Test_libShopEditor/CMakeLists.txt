    PROJECT(Test_libSceneEditor)
    
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
    
    SET(CMAKE_DEBUG_POSTFIX "D")
    
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
    
    
    INCLUDE_DIRECTORIES(
      ${OPENSCENEGRAPH_INCLUDE_DIRS}
      ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libItemModel
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libSearch
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libController
      ${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
      ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libOSGQTViewer
      ${CMAKE_SOURCE_DIR}/ShopScene/libShopEditor
      ${CMAKE_BINARY_DIR}/ShopScene/libShopEditor
      ${CMAKE_SOURCE_DIR}/ShopScene/libPopUpGUIs
      ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
      ${CMAKE_SOURCE_DIR}/Props/Scene/libScene
      ${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
      ${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
      ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
      ${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	  ${CMAKE_SOURCE_DIR}/EmbeddedWidget/libEmbeddedWidgetStatics
    )
    
    SET(LIBS_COMMON 
    	${OSG_LIBRARIES}
    	${OSGDB_LIBRARIES}
    	${OSGGA_LIBRARIES}
    	${OSGQT_LIBRARIES}
    	${OSGUTIL_LIBRARIES}
    	${OSGVIEWER_LIBRARIES}
    	${OPENTHREADS_LIBRARIES}
    	libDatabase
    	libAbstractObject
    	libGeometricShape
		libExternalObject
    	libPopUpGUIs
    	libShopEditor
    	libCommon
    	libCommon_OSG
    	libCommon_QT
  		libAppData
    	libItemModel
    	libSearch
    	libCamera
    	libPicker
    	libController
    	libServerClientCommands
    	libFurniture
    	libScene
    	libProduct
    	libOSGQTViewer
		libEmbeddedWidgetStatics
    )
    
    SET(SRCS
      main.cpp
    )
    
    ADD_EXECUTABLE(Test_libShopEditor ${SRCS})
    
    IF(Qt5_FOUND)
      TARGET_LINK_LIBRARIES(Test_libShopEditor
        ${Qt5Core_LIBRARIES}
        ${Qt5Gui_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Sql_LIBRARIES}
    	${LIBS_COMMON}
      )
    ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
      TARGET_LINK_LIBRARIES(Test_libShopEditor
        ${QT_LIBRARIES}
        ${QT_QTSQL_LIBRARY}
    	${LIBS_COMMON}
      )
    ENDIF()
    
    SET_PROPERTY(TARGET Test_libShopEditor PROPERTY FOLDER ShopScene)
