PROJECT(Test_SplineWidget)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/libSplineWidget
	${CMAKE_SOURCE_DIR}/libMatej
)


SET(SRCS
	Test_SplineWidget.cpp
)


ADD_EXECUTABLE(Test_SplineWidget ${SRCS})


TARGET_LINK_LIBRARIES(Test_SplineWidget
	libSplineWidget
	libMatej
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
