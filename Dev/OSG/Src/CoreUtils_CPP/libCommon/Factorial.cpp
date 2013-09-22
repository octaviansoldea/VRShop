#include "Array.h"
#include "Factorial.h"

static Array<long long int> arrnFactorials;

int factorial(int anVal) {
	int nSize = arrnFactorials.size;
	if(nSize <= 0) {
		arrnFactorials.setSize(2);
		arrnFactorials[0] = 1;
		arrnFactorials[1] = 1;
		nSize = 2;
	}
	if(anVal >= nSize) {
		Array<long long int> arrnTmp = arrnFactorials;
		arrnFactorials.setSize(anVal + 1);
		int nI;
		for(nI = 0; nI < nSize; nI++) {
			arrnFactorials[nI] = arrnTmp[nI];
		}
		for(nI = nSize; nI < (anVal + 1); nI++) {
			arrnFactorials[nI] = arrnFactorials[nI - 1] * nI;
		}
	}
	long long int nVal = arrnFactorials[anVal];
	return(nVal);
}