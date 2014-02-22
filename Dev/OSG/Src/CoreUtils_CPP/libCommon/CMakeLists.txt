PROJECT(libCommon)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	Array.h Array.cpp
	BasicDefinitions.h
    BasicStringDefinitions.h BasicStringDefinitions.cpp
	FileOperations.h FileOperations.cpp
    Log.h Log.cpp
    Singleton.h
    Trace.h Trace.cpp
)

ADD_LIBRARY(libCommon ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libCommon/include)
INSTALL(TARGETS libCommon DESTINATION libCommon/lib
		LIBRARY DESTINATION libCommon/lib)

SET_PROPERTY(TARGET libCommon PROPERTY FOLDER Basics)