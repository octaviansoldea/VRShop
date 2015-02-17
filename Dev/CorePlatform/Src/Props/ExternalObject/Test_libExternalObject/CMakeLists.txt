PROJECT(Test_libExternalObject)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

INCLUDE_DIRECTORIES(
	${OPENSCENEGRAPH_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
)

SET(SRCS
  main.cpp
)

ADD_EXECUTABLE(Test_libExternalObject ${SRCS})

TARGET_LINK_LIBRARIES(Test_libExternalObject
	${OPENTHREADS_LIBRARIES}
	libCommon
	libAppData
	libAbstractObject
	libExternalObject
)

SET_PROPERTY(TARGET Test_libExternalObject PROPERTY FOLDER Props)