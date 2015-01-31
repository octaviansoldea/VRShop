PROJECT(libEmbeddedWidgetStatics)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
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


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
  	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
)


#Define sources to be later added into the library
SET(SRCS
	VREmbeddedWidgetStatics.h VREmbeddedWidgetStatics.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libEmbeddedWidgetStatics
  ${SRCS}
)

SET_PROPERTY(TARGET libEmbeddedWidgetStatics PROPERTY FOLDER EmbeddedWidget)