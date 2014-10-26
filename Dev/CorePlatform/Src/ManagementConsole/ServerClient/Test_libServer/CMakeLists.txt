project(Test_libServer)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
#    ${Qt5Core_INCLUDE_DIRS}
#    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
#    ${Qt5Network_INCLUDE_DIRS}
#	${Qt5Sql_INCLUDE_DIRS}
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
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServer
#	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/DatabaseNetworkManager/libDatabaseNetworkManager
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabase
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libTimer
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT

	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
#	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent/View
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
	${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatarManagerServer
	${CMAKE_BINARY_DIR}/Props/Avatar/libAvatarManagerServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductManagerServer
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierServer
)

ADD_EXECUTABLE(Test_libServer
	main.cpp
)

SET(LIBS_COMMON
	libAvatar
	libServer
	libClient
	libDatabase
	libDatabaseNetworkManager
	libAgentManager
	libProduct
	libTimer
	libCommon
	libCommon_QT
	Winmm
	libAgent
	libServerClientCommands
	libAvatarManagerServer
	libAgentServer
	libProductManagerServer
	libCashierServer
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libServer
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Network_LIBRARIES}	
    ${Qt5Sql_LIBRARIES}	
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libServer
  	${QT_LIBRARIES}
	${QT_QTNETWORK_INCLUDE_DIR}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET Test_libServer PROPERTY FOLDER ServerClient)