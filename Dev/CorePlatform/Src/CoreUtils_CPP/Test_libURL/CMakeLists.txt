PROJECT(Test_libURL)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libURL
)

ADD_EXECUTABLE(Test_libURL
	main.cpp
)

TARGET_LINK_LIBRARIES(Test_libURL
	libCommon
	libURL
	wininet.lib
)

SET_PROPERTY(TARGET Test_libURL PROPERTY FOLDER Basics)