PROJECT(libAvatarManager)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
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

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS		)
  QT5_WRAP_CPP(MOC_SRCS 	VRAvatarManagerClient.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		VRAvatarManagerClient.h)
  QT4_WRAP_UI(UI_SRCS		)
ENDIF(Qt5_FOUND)


INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_OSG
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCamera
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAnimationEditor
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
)

SET(SRCS
  VRAvatarManagerClient.h VRAvatarManagerClient.cpp
  VRAvatarManagerServer.h VRAvatarManagerServer.cpp
)

ADD_LIBRARY(libAvatarManager
  ${SRCS} ${MOC_SRCS} ${UI_SRCS}
)

SET_PROPERTY(TARGET libAvatarManager PROPERTY FOLDER AvatarManager)