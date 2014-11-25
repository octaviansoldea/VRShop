CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(testing)
SET(CMAKE_DEBUG_POSTFIX "D")
	
SUBDIRS(
  libCommon_OSG
  libOSGQTViewer
  libModel
  libReadWriteData
  Test_libModel
)