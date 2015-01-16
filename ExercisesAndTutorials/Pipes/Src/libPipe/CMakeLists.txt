PROJECT(libPipe)

SET(SRCS
	PipeMgr.h PipeMgr.cpp
	PipeMgrAutoDeblocking.h PipeMgrAutoDeblocking.cpp
	PipeMgrAutoDeblockingReadInterface.h PipeMgrAutoDeblockingReadInterface.cpp
	PipeMgrAutoDeblockingWriteInterface.h PipeMgrAutoDeblockingWriteInterface.cpp
	PipeMgrCreateConnect.h PipeMgrCreateConnect.cpp
	PipeMgrCreateConnectWriteInterface.h PipeMgrCreateConnectWriteInterface.cpp
	PipeMgrOpen.h PipeMgrOpen.cpp
	PipeMgrOpenReadInterface.h PipeMgrOpenReadInterface.cpp
	PipeMgrOpenReadPeekInterface.h
	PipeMgrPeek.h PipeMgrPeek.cpp
	PipeMgrReadInterface.h PipeMgrReadInterface.cpp
	PipeMgrWriteInterface.h PipeMgrWriteInterface.cpp
	PipeNamesMgr.h PipeNamesMgr.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/../../../Dev/CorePlatform/Src/CoreUtils_CPP/libCommon
	${CMAKE_SOURCE_DIR}/../../../Dev/CorePlatform/Src/CoreUtils_CPP/libTimer
)

ADD_LIBRARY(libPipe ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libPipe/include)
INSTALL(TARGETS libPipe DESTINATION libPipe/lib
		LIBRARY DESTINATION libPipe/lib)




