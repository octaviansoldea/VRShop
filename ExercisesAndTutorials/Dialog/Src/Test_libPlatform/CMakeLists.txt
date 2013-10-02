PROJECT(Test_libPlatform)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(Qt5_FOUND)
  MESSAGE("Test_libPlatform Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
  )
  MESSAGE("Test_libPlatform Qt5 used END")
ELSE()
  IF(QT_USE_FILE)
    INCLUDE(${QT_USE_FILE})
  ELSE(QT_USE_FILE)
    SET(QT_LIBRARIES   ${QT_QT_LIBRARY})
  ENDIF(QT_USE_FILE)

 # Use the include path and library for Qt that is used by VTK.
  INCLUDE_DIRECTORIES(
    ${QT_INCLUDE_DIR}
    ${QT_QTSQL_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF()


INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/libPlatform
)

SET(SRCS
  Test_libPlatform.cpp
)

ADD_EXECUTABLE(Test_libPlatform ${SRCS})

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libPlatform
	libPlatform
	${Qt5Core_LIBRARIES}
	${Qt5Gui_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libPlatform
	libPlatform
	${QT_LIBRARIES}
  )
ENDIF()