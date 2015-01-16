PROJECT(Test_libPipePrimitives)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libPipePrimitives
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
)

ADD_EXECUTABLE(Test_libPipePrimitives main.cpp)

TARGET_LINK_LIBRARIES(Test_libPipePrimitives 
	libPipePrimitives
	libAppData
	libCommon
)

SET_PROPERTY(TARGET Test_libPipePrimitives PROPERTY FOLDER Basics)