PROJECT(libGUIExample)
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

  INCLUDE_DIRECTORIES(
       ${QT_INCLUDE_DIR}
  )
ENDIF(Qt5_FOUND)
#end Qt


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/libGUIExample
	${CMAKE_BINARY_DIR}/libGUIExample
	${CMAKE_SOURCE_DIR}/libCommon_OSG
	${CMAKE_SOURCE_DIR}/libModel
	${CMAKE_SOURCE_DIR}/libPicker
	${CMAKE_SOURCE_DIR}/libCamera
)


#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_UI(UI_SRCS GUI-MainWindow.ui)
  QT5_WRAP_CPP(MOC_SRCS OSGQT_Widget.h OSG_GUI.h)
ELSE(Qt5_FOUND)
  QT4_WRAP_CPP(MOC_SRCS OSGQT_Widget.h OSG_GUI.h)
  QT4_WRAP_UI(UI_SRCS GUI-MainWindow.ui)
ENDIF(Qt5_FOUND)


#Define sources to be later added into the library
SET(SRCS ${MOC_SRCS} ${UI_SRCS}
	OSGQT_Widget.h OSGQT_Widget.cpp
	OSG_GUI.h OSG_GUI.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libGUIExample
  ${SRCS}
)

SET_PROPERTY(TARGET libGUIExample PROPERTY FOLDER Exercise)