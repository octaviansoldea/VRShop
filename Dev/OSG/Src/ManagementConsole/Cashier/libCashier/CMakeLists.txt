PROJECT(libCashier)
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
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
	   ${QT_QTSQL_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabaseMgr
	${CMAKE_SOURCE_DIR}/ManagementConsole/Users/libUsers
)

#Define sources to be later added into the library
SET(SRCS
	VRCashier.h VRCashier.cpp
	VRReceipt.h VRReceipt.cpp
	VRCashierScreen.h VRCashierScreen.cpp
	VRTransaction.h VRTransaction.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libCashier
  ${SRCS}
)

SET_PROPERTY(TARGET libCashier PROPERTY FOLDER Management)