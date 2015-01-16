PROJECT(Test_libPipe)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/libPipeClientServer
)

ADD_EXECUTABLE(Test_libPipe main.cpp)

TARGET_LINK_LIBRARIES(Test_libPipe
	libPipeClientServer
)

SET_PROPERTY(TARGET Test_libPipe PROPERTY FOLDER Basics)