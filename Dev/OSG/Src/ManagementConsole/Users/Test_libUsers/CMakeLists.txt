project(Test_libUsers)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/ManagementConsole/Users/libUsers
)

ADD_EXECUTABLE(Test_libUsers
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libUsers
	libUsers
)

SET_PROPERTY(TARGET Test_libUsers PROPERTY FOLDER Users)