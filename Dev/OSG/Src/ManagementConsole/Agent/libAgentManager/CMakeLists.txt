PROJECT(libAgentManager)
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

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS		)
  QT5_WRAP_CPP(MOC_SRCS 	)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS		)  
  QT4_WRAP_UI(UI_SRCS		)
ENDIF(Qt5_FOUND)


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
    ${CMAKE_SOURCE_DIR}/Props/Avatar/libAvatar

	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
)

#Define sources to be later added into the library
SET(SRCS
	VRAgentManager.h VRAgentManager.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libAgentManager
  ${SRCS} ${MOC_SRCS} ${UI_SRCS}
)

SET_PROPERTY(TARGET libAgentManager PROPERTY FOLDER Agent)