PROJECT(Test_HandleWidget)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/libHandleWidget
)


SET(SRCS
	Test_HandleWidget.cpp
)


ADD_EXECUTABLE(Test_HandleWidget ${SRCS})


TARGET_LINK_LIBRARIES(Test_HandleWidget
	libHandleWidget
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
