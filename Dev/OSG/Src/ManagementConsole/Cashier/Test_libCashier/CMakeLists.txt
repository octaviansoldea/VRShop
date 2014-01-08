project(Test_libCashier)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashier
)

ADD_EXECUTABLE(Test_libCashier
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libCashier
	libCashier
)

SET_PROPERTY(TARGET Test_libCashier PROPERTY FOLDER Management)