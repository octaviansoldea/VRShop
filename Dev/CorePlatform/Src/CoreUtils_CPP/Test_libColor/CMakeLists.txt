PROJECT(Test_libColor)

SET(CMAKE_DEBUG_POSTFIX "D")
 
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libColor
)

ADD_EXECUTABLE(Test_libColor Test_libColor.cpp)
TARGET_LINK_LIBRARIES(Test_libColor libColor) 

SET_PROPERTY(TARGET Test_libColor PROPERTY FOLDER Basics)