PROJECT(Test_libDatabaseMgr)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

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


INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabaseMgr
  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
)

SET(SRCS
  main.cpp
)

ADD_EXECUTABLE(Test_libDatabaseMgr ${SRCS})


SET(LIBS_COMMON 
	libDatabaseMgr
	libCommon
	libFurniture
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libDatabaseMgr
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libDatabaseMgr
  	${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF()

SET_PROPERTY(TARGET Test_libDatabaseMgr PROPERTY FOLDER Database)