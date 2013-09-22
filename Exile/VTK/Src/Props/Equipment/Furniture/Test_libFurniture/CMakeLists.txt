PROJECT(Test_libFurniture)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_DEBUG_POSTFIX "D")

IF(Qt5_FOUND)
  MESSAGE("Test_libFurniture Qt5 used START")
  INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
  )
  MESSAGE("Test_libFurniture Qt5 used END")

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
       ${CMAKE_CURRENT_BINARY_DIR}
       ${CMAKE_CURRENT_SOURCE_DIR}
  )
ENDIF()

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/Props/Equipment/Furniture/libFurniture
  ${CMAKE_SOURCE_DIR}/Props/Equipment/GeometricShapes/libGeometricShapes
  ${CMAKE_SOURCE_DIR}/ImagePrimitives/libRenWin
  #${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
  #${CMAKE_SOURCE_DIR}/ImagePrimitives/libImagePrimitives
  ${CMAKE_SOURCE_DIR}/ImagePrimitives/libOrientationWidgets
)

SET(LIBS_COMMON 
	libGeometricShapes
	libFurniture
	libRenWin
	libOrientationWidgets
)

SET(SRCS
  main.cpp
)

ADD_EXECUTABLE(Test_libFurniture ${SRCS})

IF(Qt5_FOUND)
  TARGET_LINK_LIBRARIES(Test_libFurniture
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
	QVTK
	${LIBS_COMMON}
  )
ELSEIF(NOT Qt5_FOUND AND Qt4_FOUND)
  TARGET_LINK_LIBRARIES(Test_libFurniture
    ${QT_LIBRARIES}
	QVTK #This line is not tested yet
	vtkRendering
	#vtkGraphics
	#vtkIO
	#vtkCommon
	#vtkVolumeRendering
	#vtkwidgets
	${LIBS_COMMON}
  )
ENDIF()

SET_PROPERTY(TARGET Test_libFurniture PROPERTY FOLDER Props)