PROJECT(libPipePrimitives)

SET(SRCS
	VRPipeServer.h VRPipeServer.cpp
	VRPipeClient.h VRPipeClient.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
)

ADD_LIBRARY(libPipePrimitives ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libPipePrimitives/include)
INSTALL(TARGETS libPipePrimitives DESTINATION libPipePrimitives/lib
		LIBRARY DESTINATION libPipePrimitives/lib)

SET_PROPERTY(TARGET libPipePrimitives PROPERTY FOLDER Basics)


