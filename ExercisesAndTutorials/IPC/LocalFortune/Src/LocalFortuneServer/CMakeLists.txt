CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LocalFortuneServer)

IF(Qt5_FOUND)
  MESSAGE("LocalFortuneServer Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
  )
  MESSAGE("LocalFortuneServer Qt5 used END")

ELSE()
  #Assume Qt4_FOUND, if we are here
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

  # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
    ${QT_INCLUDE_DIR}
	${QT_QTNETWORK_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
ENDIF()

#MOC according to the Qt version
IF(Qt5_FOUND)
  QT5_WRAP_CPP(MOC_SRCS server.h)
ELSE()
  QT4_WRAP_CPP(MOC_SRCS server.h)
ENDIF()


#Define sources to be later added into the library
SET(SRCS ${SRCS} ${MOC_SRCS}
	server.h server.cpp
    main.cpp
)


# Set executables
ADD_EXECUTABLE(LocalFortuneServer MACOSX_BUNDLE ${SRCS})


IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(LocalFortuneServer
	${Qt5Core_LIBRARIES}
	${Qt5Gui_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
    ${Qt5Network_LIBRARIES}	
  )
ELSE()
TARGET_LINK_LIBRARIES( LocalFortuneServer
	${QT_LIBRARIES}
	${QT_QTNETWORK_LIBRARY}
)
ENDIF()