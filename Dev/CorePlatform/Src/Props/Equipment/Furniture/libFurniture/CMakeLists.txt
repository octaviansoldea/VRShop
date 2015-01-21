    PROJECT(libFurniture)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
    
    SET(CMAKE_DEBUG_POSTFIX "D")
    
    INCLUDE_DIRECTORIES(
    	${OPENSCENEGRAPH_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libCommon
  	${CMAKE_SOURCE_DIR}/CoreUtils_CPP/libAppData
    	${CMAKE_SOURCE_DIR}/Props/AbstractObject/libAbstractObject
    	${CMAKE_SOURCE_DIR}/Props/GeometricShape/libGeometricShape
    )
    
    SET(SRCS
      VRFurniture.h VRFurniture.cpp
      VRCustomFurniture.h VRCustomFurniture.cpp
      VRCupboard.h VRCupboard.cpp
      VRContainer.h VRContainer.cpp
    )
    
    ADD_LIBRARY(libFurniture
      ${SRCS}
    )
    
    SET_PROPERTY(TARGET libFurniture PROPERTY FOLDER Props)
