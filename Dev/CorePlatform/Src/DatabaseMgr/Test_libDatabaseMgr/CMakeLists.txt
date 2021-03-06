PROJECT(Test_libDatabaseMgr)
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

INCLUDE_DIRECTORIES(
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
	${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  ${CMAKE_SOURCE_DIR}/DatabaseMgr/libDatabaseMgr
)

SET(SRCS
  main.cpp
)

ADD_EXECUTABLE(Test_libDatabaseMgr ${SRCS})

SET(LIBS_COMMON 
	${OSG_LIBRARIES}
	${OSGDB_LIBRARIES}
	libFurniture
	libGeometricShape
	libAbstractObject
	libDatabaseMgr
	libCommon
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
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET Test_libDatabaseMgr PROPERTY FOLDER Database)