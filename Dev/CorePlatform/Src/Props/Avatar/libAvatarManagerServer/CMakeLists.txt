PROJECT(libAvatarManagerServer)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
	${Qt5Sql_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
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

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
#	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
	${CMAKE_BINARY_DIR}/Props/Avatar/libAvatarManagerServer
)

SET(SRCS
  VRAvatarManagerServer.h VRAvatarManagerServer.cpp
)

ADD_LIBRARY(libAvatarManagerServer
  ${SRCS}
)

SET_PROPERTY(TARGET libAvatarManagerServer PROPERTY FOLDER AvatarManagerServer)