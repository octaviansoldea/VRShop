PROJECT(libDatabaseMgr)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  MESSAGE("Database Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
  )
  MESSAGE("Database Qt5 used END")

ELSE()
  #Assume Qt4_FOUND, if we are here
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
	   ${QT_QTSQL_INCLUDE_DIR}
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF()

#MOC according to the Qt version
#IF(Qt5_FOUND)
#  QT5_WRAP_CPP(MOC_SRCS DatabaseMgr.h)
#ELSE()
#  QT4_WRAP_CPP(MOC_SRCS DatabaseMgr.h)
#ENDIF()


INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  ${CMAKE_SOURCE_DIR}/Props/Equipment/GeometricShapes/libGeometricShapes
)

#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS}
  DatabaseMgr.h DatabaseMgr.cpp
  DatabaseMgrSQLite.h DatabaseMgrSQLite.cpp
  DatabaseMgrODBC.h DatabaseMgrODBC.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libDatabaseMgr
  ${SRCS}
)

SET_PROPERTY(TARGET libDatabaseMgr PROPERTY FOLDER Database)