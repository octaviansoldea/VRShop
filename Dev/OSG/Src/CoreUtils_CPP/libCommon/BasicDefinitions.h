#ifndef BASIC_DEFINITIONS_H
#define BASIC_DEFINITIONS_H

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifdef __cplusplus
template<class T>
void SWAP(T & aA, T & aB) {T T_TmpVar = (aA); (aA) = (aB); (aB) = T_TmpVar;}
#else
	#define SWAP(a, b, T) {T T_TmpVar = (a); (a) = (b); (b) = T_TmpVar;}
#endif

#define EPS 0.000000001
#define PI 3.1415926535897932384626433832795

inline float degrees2Radians(float aflDegrees)	{return ((float)PI / 180.0) * aflDegrees;}
inline double degrees2Radians(double adbDegrees)	{return ((double)PI / 180.0) * adbDegrees;}

inline float radians2degrees(float aflRadians)	{return aflRadians * 180.0 / (float)PI;}
inline double radians2degrees(double adbRadians)	{return adbRadians * 180.0 / (double)PI;}

#endif //BASIC_DEFINITIONS_H
