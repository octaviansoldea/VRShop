CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CoreUtils_CPP)

SET(CMAKE_DEBUG_POSTFIX "D")

SUBDIRS(
	libColor
	libCommon
	libReadWritePPM
	libTimer
	libAppData
	Test_libColor
	Test_libCommon
	Test_libReadWritePPM
	Test_libTimer
	Test_libAppData
)