PROJECT(libTimer)

SET(CMAKE_DEBUG_POSTFIX "D")

SET(SRCS
	Chronometer.h Chronometer.cpp
    Chronometer_CPUTime.h Chronometer_CPUTime.cpp
    Chronometer_RealTime.h Chronometer_RealTime.cpp
    Chronometer_QueryPerformance.h Chronometer_QueryPerformance.cpp
    Timer.h Timer.cpp
    Timer_CPUTime.h Timer_CPUTime.cpp
    Timer_RealTime.h Timer_RealTime.cpp
    Timer_QueryPerformance.h Timer_QueryPerformance.cpp
    TimerBase.h TimerBase.cpp
)



ADD_LIBRARY(libTimer ${SRCS})

#FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
#INSTALL(FILES ${files} DESTINATION include/Called)


FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION libTimer/include)
INSTALL(TARGETS libTimer DESTINATION libTimer/lib
		LIBRARY DESTINATION libTimer/lib)

SET_PROPERTY(TARGET libTimer PROPERTY FOLDER Basics)