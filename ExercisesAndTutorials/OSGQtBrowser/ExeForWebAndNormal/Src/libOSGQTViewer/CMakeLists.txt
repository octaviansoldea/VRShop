PROJECT(libOSGQTViewer)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")


#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
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

#MOC according to the Qt version
IF(Qt5_FOUND)
   QT5_WRAP_CPP(MOC_SRCS	VROSGQT_Widget.h)
ELSE()
  QT4_WRAP_CPP(MOC_SRCS		VROSGQT_Widget.h)
ENDIF()

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
)

SET(SRCS
	VROSGQT_Widget.h VROSGQT_Widget.cpp
)

ADD_LIBRARY(libOSGQTViewer
  ${SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libOSGQTViewer PROPERTY FOLDER Utils)