PROJECT(libDatabaseNetworkManager)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
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

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatarManagerServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductManagerServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierServer
)


#Define sources to be later added into the library
SET(SRCS
	VRDatabaseNetworkManager.h VRDatabaseNetworkManager.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libDatabaseNetworkManager
  ${SRCS}
)

SET_PROPERTY(TARGET libDatabaseNetworkManager PROPERTY FOLDER DatabaseNetworkManager)