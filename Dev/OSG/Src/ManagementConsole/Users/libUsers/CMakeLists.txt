PROJECT(libUsers)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_DEBUG_POSTFIX "D")

#General includes, irrespective of the Qt version
INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/ManagementConsole/Product/libProduct
)

#Define sources to be later added into the library
SET(SRCS
	VRBasket.h VRBasket.cpp
	VRUsersBase.h VRUsersBase.cpp
	VRCustomer.h VRCustomer.cpp
	VRUserAccount.h VRUserAccount.cpp
)

#Library to be later used in the main
ADD_LIBRARY(libUsers
  ${SRCS}
)

SET_PROPERTY(TARGET libUsers PROPERTY FOLDER Users)