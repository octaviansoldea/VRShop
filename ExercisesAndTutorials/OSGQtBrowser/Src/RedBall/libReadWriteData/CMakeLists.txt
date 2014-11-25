PROJECT(libReadWriteData)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	ReadWrite.h ReadWrite.cpp
)

ADD_LIBRARY(libReadWriteData
  ${SRCS}
)

SET_PROPERTY(TARGET libReadWriteData PROPERTY FOLDER Utils)