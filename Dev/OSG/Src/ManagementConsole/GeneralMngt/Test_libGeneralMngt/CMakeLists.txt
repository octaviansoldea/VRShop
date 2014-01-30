project(Test_libGeneralMngt)
cmake_minimum_required( VERSION 2.8 )

SET(CMAKE_DEBUG_POSTFIX "D")

SET(src
	main.cpp
)

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/ManagementConsole/GeneralMngt/libGeneralMngt
)

ADD_EXECUTABLE(Test_libGeneralMngt
	main.cpp)

TARGET_LINK_LIBRARIES(Test_libGeneralMngt
	${OSG_LIBRARIES}
	libGeneralMngt
	libProduct
)

SET_PROPERTY(TARGET Test_libGeneralMngt PROPERTY FOLDER Management)