PROJECT(libCommon_QT)
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

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_CPP(MOC_SRCS VRQFrame.h VRQLabel.h)
ELSE()
  QT4_WRAP_CPP(MOC_SRCS VRQFrame.h VRQLabel.h)
ENDIF()


SET(SRCS
	VRBasicQtOperations.h VRBasicQtOperations.cpp
	VRQFrame.h VRQFrame.cpp
	VRQLabel.h VRQLabel.cpp
)

ADD_LIBRARY(libCommon_QT
  ${SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libCommon_QT PROPERTY FOLDER Utils)