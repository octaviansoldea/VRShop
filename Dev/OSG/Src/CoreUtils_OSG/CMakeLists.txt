CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CoreUtils_OSG)

SET(CMAKE_DEBUG_POSTFIX "D")

SUBDIRS(
	libCamera
	libCommon_OSG
	libCommon_QT
	libSearch
	libItemModel
	libLighting
	libMngtController
	libOSGQTViewer
	libPicker
	libController
	Test_libCamera
	Test_libPicker
	Test_libCameraPicker
	Test_libOSGQTViewer
)