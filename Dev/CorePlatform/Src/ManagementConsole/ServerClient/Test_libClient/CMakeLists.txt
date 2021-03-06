project(Test_libClient)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
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


SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
)

ADD_EXECUTABLE(Test_libClient
	main.cpp)

SET(LIBS_COMMON
	libAppData
	libClient
	libCommon_QT
	libServerClientCommands
	libCommon
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libClient
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
    ${Qt5Network_LIBRARIES}	
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libClient
  	${QT_LIBRARIES}
	${QT_QTNETWORK_LIBRARY}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET Test_libClient PROPERTY FOLDER ServerClient)