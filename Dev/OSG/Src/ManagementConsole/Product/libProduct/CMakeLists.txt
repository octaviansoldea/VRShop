PROJECT(libProduct)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
)

#Define sources to be later added into the library
SET(SRCS
	VRProduct.h VRProduct.cpp
	VRBasket.h VRBasket.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libProduct
  ${SRCS}
)

SET_PROPERTY(TARGET libProduct PROPERTY FOLDER Management)