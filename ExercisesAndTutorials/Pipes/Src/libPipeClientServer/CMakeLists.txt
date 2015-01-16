PROJECT(libPipeClientServer)

SET(CMAKE_DEBUG_POSTFIX "D")

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(SRCS
	VRPipeClient.h VRPipeClient.cpp
	VRPipeServer.h VRPipeServer.cpp
)

ADD_LIBRARY(libPipeClientServer ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libPipeClientServer/include)
INSTALL(TARGETS libPipeClientServer DESTINATION libPipeClientServer/lib
		LIBRARY DESTINATION libPipeClientServer/lib)

SET_PROPERTY(TARGET libPipeClientServer PROPERTY FOLDER Basics)


