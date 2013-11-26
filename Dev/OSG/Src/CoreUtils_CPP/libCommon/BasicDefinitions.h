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

inline float degrees2Radians(float & aflDegrees)	{return (PI / 180) * aflDegrees;}

//#define MAX_STR_LEN 256

#endif //BASIC_DEFINITIONS_H
