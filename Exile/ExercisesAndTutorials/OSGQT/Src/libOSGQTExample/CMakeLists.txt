PROJECT(libOSGQTExample)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  MESSAGE("libOSGQTExample Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
  )
  MESSAGE("libOSGQTExample Qt5 used END")
ELSE(Qt5_FOUND)
  #Assume Qt4_FOUND, if we are here
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
  )
ENDIF(Qt5_FOUND)
#end Qt


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/libOSGQTExample
	${CMAKE_BINARY_DIR}/libOSGQTExample
	${CMAKE_SOURCE_DIR}/libModel
)


#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS OSGQT.ui)
  QT5_WRAP_CPP(MOC_SRCS OSGQT_Widget.h OSGQT_GUI.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS OSGQT_Widget.h OSGQT_GUI.h)
  QT4_WRAP_UI(UI_SRCS OSGQT.ui)
ENDIF(Qt5_FOUND)


#Define sources to be later added into the library
SET(SRCS ${MOC_SRCS} ${UI_SRCS}
	OSGQT_Widget.h OSGQT_Widget.cpp
	OSGQT_GUI.h OSGQT_GUI.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libOSGQTExample
  ${SRCS}
)

SET_PROPERTY(TARGET libOSGQTExample PROPERTY FOLDER Exercise)