PROJECT(libDatabase)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(Qt5_FOUND)
  MESSAGE("Database Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
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

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
  ${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
)

#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS}
  VRDatabaseInterface.h VRDatabaseInterface.cpp
  VRDatabaseInterfaceShopEditor.h VRDatabaseInterfaceShopEditor.cpp
  VRDatabaseInterfaceShopClient.h VRDatabaseInterfaceShopClient.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libDatabase
  ${SRCS}
)

SET_PROPERTY(TARGET libDatabase PROPERTY FOLDER Database)