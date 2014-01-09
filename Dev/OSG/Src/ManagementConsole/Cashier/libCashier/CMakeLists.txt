PROJECT(libCashier)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
	${CMAKE_SOURCE_DIR}/ManagementConsole/Users/libUsers
)

#Define sources to be later added into the library
SET(SRCS
	VRCashier.h VRCashier.cpp
	VRPurchase.h VRPurchase.cpp
	VRReceipt.h VRReceipt.cpp
	VRCashierScreen.h VRCashierScreen.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libCashier
  ${SRCS}
)

SET_PROPERTY(TARGET libCashier PROPERTY FOLDER Management)