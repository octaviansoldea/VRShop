PROJECT(libCommon)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	BasicDefinitions.h
    Array.h Array.cpp
    BasicStringDefinitions.h BasicStringDefinitions.cpp
    BitFlip.h
    Factorial.h Factorial.cpp
    FileOperations.h FileOperations.cpp
    IniReader.h IniReader.cpp
    IniWriter.h IniWriter.cpp
    Log.h Log.cpp
    Singleton.h
    Trace.h Trace.cpp
	StringManipulation.h StringManipulation.cpp
)

ADD_LIBRARY(libCommon ${SRCS})

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libCommon/include)
INSTALL(TARGETS libCommon DESTINATION libCommon/lib
		LIBRARY DESTINATION libCommon/lib)

SET_PROPERTY(TARGET libCommon PROPERTY FOLDER Basics)