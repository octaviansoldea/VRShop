PROJECT(Test_libReadWritePPM)
 
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libColor
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libReadWritePPM/
)

ADD_EXECUTABLE(Test_libReadWritePPM comandsRead.cpp)
TARGET_LINK_LIBRARIES(Test_libReadWritePPM libReadWritePPM) 

SET_PROPERTY(TARGET Test_libReadWritePPM PROPERTY FOLDER Basics)