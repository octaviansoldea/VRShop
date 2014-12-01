PROJECT(libProductManagerServer)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Sql_INCLUDE_DIRS}
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
	   ${QT_QTNETWORK_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
)

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS		)
  QT5_WRAP_CPP(MOC_SRCS 	)#VRProductManagerServer.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		)#VRProductManagerServer.h)
  QT4_WRAP_UI(UI_SRCS		)
ENDIF(Qt5_FOUND)


#Define sources to be later added into the library
SET(SRCS ${MOC_SRCS}
	VRProductManagerServer.h VRProductManagerServer.cpp
	VRBasketServer.h VRBasketServer.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libProductManagerServer
  ${SRCS}
)

SET_PROPERTY(TARGET libProductManagerServer PROPERTY FOLDER Management)