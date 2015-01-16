CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CoreUtils_CPP)

SET(CMAKE_DEBUG_POSTFIX "D")
    
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
   # Windows specific code
   SET(ProjectsWindows libPipePrimitives Test_libPipePrimitives)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	
    SUBDIRS(
    	libColor
    	libCommon
    	libReadWritePPM
    	libTimer
		libAppData
		libURL
		${ProjectsWindows}
    	Test_libColor
    	Test_libCommon
    	Test_libReadWritePPM
    	Test_libTimer
		Test_libAppData
		Test_libURL
    )
