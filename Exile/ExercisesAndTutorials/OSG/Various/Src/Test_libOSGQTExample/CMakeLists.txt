PROJECT(Test_libOSGQTExample)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  MESSAGE("Test_libOSGQTExample Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
  )
  MESSAGE("Test_libOSGQTExample Qt5 used END")
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
	${CMAKE_SOURCE_DIR}/libOSGQTExample
	${CMAKE_BINARY_DIR}/libOSGQTExample
	${CMAKE_SOURCE_DIR}/libModel
	${CMAKE_SOURCE_DIR}/libPicker
	${CMAKE_SOURCE_DIR}/libCamera
)


#Define sources
SET(SRCS
	main.cpp
)


#Define executable
ADD_EXECUTABLE(Test_libOSGQTExample
	${SRCS}
)


#Target link libraries
TARGET_LINK_LIBRARIES(Test_libOSGQTExample
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
	libOSGQTExample
	libModel
	libPicker
	libCamera
)

SET_PROPERTY(TARGET Test_libOSGQTExample PROPERTY FOLDER Exercise)