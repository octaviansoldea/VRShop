PROJECT(CentralControl)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
  )
ELSE(Qt5_FOUND)
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS		)
  QT5_WRAP_CPP(MOC_SRCS 	VRCentralControl.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		VRCentralControl.h)  
  QT4_WRAP_UI(UI_SRCS		)
ENDIF(Qt5_FOUND)


INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/DatabaseNetworkManager/libDatabaseNetworkManager
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar

	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libTimer
)

SET(SRCS
  VRCentralControl.h VRCentralControl.cpp
  main.cpp
)

ADD_EXECUTABLE(CentralControl ${SRCS} ${UI_SRCS} ${MOC_SRCS})

SET(LIBS_COMMON
	${OSG_LIBRARIES}
	${OSGANIMATION_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	libServer
	libClient
	libDatabaseNetworkManager
	libDatabase
	libCommon
	libCommon_QT
	libAgentManager
	libAgent
	libAvatar
	libProduct
	libTimer
	Winmm
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(CentralControl
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
	${Qt5Network_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(CentralControl
  	${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET CentralControl PROPERTY FOLDER CentralControl)