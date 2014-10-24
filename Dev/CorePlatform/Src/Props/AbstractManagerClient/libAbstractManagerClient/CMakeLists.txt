PROJECT(libAbstractManagerClient)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
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
  QT5_WRAP_CPP(MOC_SRCS 	VRAbstractManagerClient.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		VRAbstractManagerClient.h)
  QT4_WRAP_UI(UI_SRCS		)
ENDIF(Qt5_FOUND)


INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
)

SET(SRCS
    VRAbstractManagerClient.h VRAbstractManagerClient.cpp
)

ADD_LIBRARY(libAbstractManagerClient ${SRCS} ${MOC_SRCS})


SET_PROPERTY(TARGET libAbstractManagerClient PROPERTY FOLDER AbstractManagerClient)