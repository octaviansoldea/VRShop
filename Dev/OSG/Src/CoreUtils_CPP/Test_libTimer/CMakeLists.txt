PROJECT(Test_libTimer)
 
 SET(CMAKE_DEBUG_POSTFIX "D")
 
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../libTimer
)

ADD_EXECUTABLE(Test_libTimer Test_libTimer.cpp)
TARGET_LINK_LIBRARIES(Test_libTimer
	Winmm
	libTimer
)

SET_PROPERTY(TARGET Test_libTimer PROPERTY FOLDER Basics)