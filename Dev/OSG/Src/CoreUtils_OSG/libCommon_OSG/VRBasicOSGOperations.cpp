#include <osg/Matrix>

#include "VRBasicOSGOperations.h"

using namespace VR;
using namespace std;
using namespace osg;

Matrixd BasicOSGOperations::vecstr2Matrix(std::vector<std::string> & avecstrMatrixData)	{
	if (avecstrMatrixData.size() != 16)
		return Matrixd::identity();

	Matrixd mtrxResult;

	int nI,nJ;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			mtrxResult(nI,nJ) = stof(avecstrMatrixData[4*nI+nJ]);
		}
	}
	return mtrxResult;	
}