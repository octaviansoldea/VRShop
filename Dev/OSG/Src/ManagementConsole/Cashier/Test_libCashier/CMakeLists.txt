project(Test_libCashier)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
	${CMAKE_SOURCE_DIR}/ManagementConsole/Cashier/libCashier
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/ManagementConsole/Agent/libAgent
)

ADD_EXECUTABLE(Test_libCashier
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libCashier
	${OSG_LIBRARIES}
	libAbstractObject
	libCashier
	libProduct
	libAgent
)

SET_PROPERTY(TARGET Test_libCashier PROPERTY FOLDER Management)