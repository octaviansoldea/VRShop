CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CoreUtils_OSG)

SET(CMAKE_DEBUG_POSTFIX "D")

SUBDIRS(
	libCamera
	libCommon_OSG
	libPicker
	libCameraPicker
	Test_libCamera
	Test_libPicker
	Test_libCameraPicker
)