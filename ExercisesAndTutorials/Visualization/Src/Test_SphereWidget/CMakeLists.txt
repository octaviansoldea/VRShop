PROJECT(Test_SphereWidget)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/libSphereWidget
)


SET(SRCS
	Test_SphereWidget.cpp
)


ADD_EXECUTABLE(Test_SphereWidget ${SRCS})


TARGET_LINK_LIBRARIES(Test_SphereWidget
	libSphereWidget
	vtkHybrid
	vtkGraphics
	vtkIO
	vtkCommon
	vtkRendering
	vtkVolumeRendering
	vtkWidgets
	vtkexoIIc
	vtkexpat
	vtkfreetype
	vtkftgl
)
