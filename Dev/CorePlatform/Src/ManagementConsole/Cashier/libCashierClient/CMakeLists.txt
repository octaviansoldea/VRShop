PROJECT(libCashierClient)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
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
	   ${QT_QTSQL_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
    ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands

	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient
	${CMAKE_BINARY_DIR}/ManagementConsole/Cashier/libCashierClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierClient/View
	${CMAKE_SOURCE_DIR}/Props/AbstractManagerClient/libAbstractManagerClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgentManager
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashierManagerClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
)

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS	${CMAKE_CURRENT_SOURCE_DIR}/View/VRCashier_GUI.ui)
  QT5_WRAP_CPP(MOC_SRCS )#VRCashierClient.h)

ELSE()
  QT4_WRAP_UI(UI_SRCS	${CMAKE_CURRENT_SOURCE_DIR}/View/VRCashier_GUI.ui)
  QT4_WRAP_CPP(MOC_SRCS )#VRCashierClient.h)
ENDIF()


#Define sources to be later added into the library
SET(SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/View/VRCashier_GUI.h ${CMAKE_CURRENT_SOURCE_DIR}/View/VRCashier_GUI.cpp
	VRReceipt.h VRReceipt.cpp
	VRCashierClient.h VRCashierClient.cpp
	VRTransaction.h VRTransaction.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libCashierClient
  ${SRCS} ${UI_SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libCashierClient PROPERTY FOLDER Management)