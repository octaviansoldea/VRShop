PROJECT(libItemModel)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#start Qt
IF(Qt5_FOUND)
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
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
  QT5_WRAP_UI(UI_SRCS
  )
  QT5_WRAP_CPP(MOC_SRCS 
#	VRDataStructureModel.h
  )
ELSE()
  QT4_WRAP_UI(UI_SRCS
  )
  QT4_WRAP_CPP(MOC_SRCS
#	VRDataStructureModel.h
)
ENDIF()


#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
)

#Define sources to be later added into the library
SET(SRCS
	VRDataStructureItem.h VRDataStructureItem.cpp
	VRDataStructureModel.h VRDataStructureModel.cpp
)

ADD_LIBRARY(libItemModel
  ${SRCS} ${MOC_SRCS}
)

SET_PROPERTY(TARGET libItemModel PROPERTY FOLDER Utils)