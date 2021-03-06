project(Test_libCashierClient)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")


IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
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


SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient
	${CMAKE_BINARY_DIR}/ManagementConsole/Cashier/libCashierClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient/View
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
	${CMAKE_SOURCE_DIR}/Props/AbstractManagerClient/libAbstractManagerClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierManagerClient
)

ADD_EXECUTABLE(Test_libCashierClient
	main.cpp)

SET(LIBS_COMMON
	${OSG_LIBRARIES}
	libCommon
	libAbstractObject
	libCashierClient
	libProduct
	libAgent
	libAbstractManagerClient
	libAgentManager
	libCashierManagerClient
	libClient
	libServerClientCommands
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libCashierClient
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libCashierClient
  	${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET Test_libCashierClient PROPERTY FOLDER Management)