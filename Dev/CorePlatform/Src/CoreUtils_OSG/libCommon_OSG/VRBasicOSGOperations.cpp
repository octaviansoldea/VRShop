#include <osg/Matrix>
#include "BasicStringDefinitions.h"

#include "VRBasicOSGOperations.h"

using namespace std;
using namespace osg;

Matrixd vecstr2Matrix(std::vector<std::string> & avecstrMatrixData)	{
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

//------------------------------------------------------------------------------

std::string matrix2String(osg::Matrixd & amtrxMatrixData, char achDelimiter)	{
	if (!amtrxMatrixData.valid())	{
		return 0;
	}

	string strMatrixData="";
	int nI,nJ;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			strMatrixData += (tostr(amtrxMatrixData(nI,nJ)) + achDelimiter);
		}
	}
	strMatrixData.pop_back();

	return strMatrixData;
}

//------------------------------------------------------------------------------

double distanceL2Matrixd(const osg::Matrixd & amtrxA, const osg::Matrixd & amtrxB) {
	double dbRes = 0.0;
	int nI,nJ;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			double dbDistEl = amtrxA(nI,nJ) - amtrxB(nI,nJ);
			dbRes += dbDistEl * dbDistEl;
		}
	}
	return(sqrt(dbRes));
}