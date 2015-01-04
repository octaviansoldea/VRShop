PROJECT(Test_libAppData)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
)

ADD_EXECUTABLE(Test_libAppData Test_libAppData.cpp)
TARGET_LINK_LIBRARIES(Test_libAppData libAppData) 

SET_PROPERTY(TARGET Test_libAppData PROPERTY FOLDER Basics)