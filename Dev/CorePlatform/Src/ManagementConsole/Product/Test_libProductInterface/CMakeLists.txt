PROJECT(Test_libProductInterface)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
  )
ELSE(Qt5_FOUND)
  #Assume Qt4_FOUND, if we are here
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

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProductInterface
	${CMAKE_BINARY_DIR}/ManagementConsole/Product/libProductInterface
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libCommon_QT
	${CMAKE_SOURCE_DIR}/CoreUtils_OSG/libPicker
	${CMAKE_SOURCE_DIR}/Props/AbstractManagerClient/libAbstractManagerClient
	${CMAKE_SOURCE_DIR}/ManagementConsole/ServerClient/libServerClientCommands
	
)

SET(SRCS
  main.cpp
)

ADD_EXECUTABLE(Test_libProductInterface ${SRCS})

SET(LIBS_COMMON
	${OSG_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	libProductInterface
	libAbstractObject
	libProduct
	libCommon_QT
	libPicker
	libAbstractManagerClient
	libServerClientCommands
	libClient
)

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libProductInterface
	${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libProductInterface
  	${QT_LIBRARIES}
    ${QT_QTSQL_LIBRARY}
	${LIBS_COMMON}
  )
ENDIF(Qt5_FOUND)

SET_PROPERTY(TARGET Test_libProductInterface PROPERTY FOLDER Management)