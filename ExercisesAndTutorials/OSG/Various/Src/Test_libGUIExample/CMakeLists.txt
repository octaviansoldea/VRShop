PROJECT(Test_libOSGQTExample)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
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

  # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
#       ${CMAKE_CURRENT_BINARY_DIR}
#       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF(Qt5_FOUND)
#end Qt


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/libGUIExample
	${CMAKE_BINARY_DIR}/libGUIExample
	${CMAKE_SOURCE_DIR}/libModel
	${CMAKE_SOURCE_DIR}/libCommon_OSG
	${CMAKE_SOURCE_DIR}/libPicker
	${CMAKE_SOURCE_DIR}/libCamera
)


#Define sources
SET(SRCS
	main.cpp
)


#Define executable
ADD_EXECUTABLE(Test_libGUIExample
	${SRCS}
)


#Target link libraries
TARGET_LINK_LIBRARIES(Test_libGUIExample
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5OpenGL_LIBRARIES}
	${OSG_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGUTIL_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	libGUIExample
	libCommon_OSG
	libModel
	libPicker
	libCamera
)

SET_PROPERTY(TARGET Test_libGUIExample PROPERTY FOLDER Exercise)