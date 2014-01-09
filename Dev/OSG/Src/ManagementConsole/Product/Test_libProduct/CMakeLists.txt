project(Test_libInventory)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
)

ADD_EXECUTABLE(Test_libProduct
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libProduct
	libProduct
)

SET_PROPERTY(TARGET Test_libProduct PROPERTY FOLDER Management)