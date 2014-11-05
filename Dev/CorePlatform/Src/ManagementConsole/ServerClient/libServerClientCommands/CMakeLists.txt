PROJECT(libServerClientCommands)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")


#Define sources to be later added into the library
SET(SRCS
	VRServerClientCommands.h VRServerClientCommands.cpp
	VRShopBuilderCommands.h VRShopBuilderCommands.cpp
)


#Library to be later used in the main
ADD_LIBRARY(libServerClientCommands
  ${SRCS}
)

SET_PROPERTY(TARGET libServerClientCommands PROPERTY FOLDER ServerClient)