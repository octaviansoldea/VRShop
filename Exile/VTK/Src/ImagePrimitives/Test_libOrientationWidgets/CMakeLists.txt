PROJECT(Test_libOrientationWidgets)

SET(CMAKE_DEBUG_POSTFIX "D")

# Find VTK.
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/ImagePrimitives/libImagePrimitives
	${CMAKE_SOURCE_DIR}/ImagePrimitives/libOrientationWidgets
)

ADD_EXECUTABLE(Test_libOrientationWidgets Test_libOrientationWidgets.cpp)
TARGET_LINK_LIBRARIES(Test_libOrientationWidgets
	vtkCommon
    vtkDICOMParser
    vtkRendering
    vtkexoIIc
    vtkexpat
    vtkFiltering
    vtkfreetype
    vtkftgl
    vtkGenericFiltering
    vtkGraphics
    vtkHybrid
    vtkImaging 
    vtkIO
    vtkNetCDF
    vtkRendering
    vtksys
    vtkVolumeRendering
    vtkWidgets
	libOrientationWidgets
)

SET_PROPERTY(TARGET Test_libOrientationWidgets PROPERTY FOLDER ImagePrimitives)