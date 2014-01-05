#include "VRObjectTransformation.h"

using namespace VR;
using namespace osg;

ObjectTransformation::ObjectTransformation()	{
	makeIdentity();
}

//-----------------------------------------------------------

ObjectTransformation::ObjectTransformation(const ObjectTransformation & aObjectTransformation)	{
	set(aObjectTransformation);
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setTranslationGetMatrix(float aflX, float aflY, float aflZ)	{
	return Matrix::translate(aflX,aflY,aflZ);
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setRotationGetMatrix(float aflAngle, ROTATION_AXIS aAxis)	{
	ObjectTransformation oT;

	int nSelection = aAxis;

	if (nSelection == X_AXIS)	{
		oT(1,1) = cos(aflAngle);
		oT(1,2) = -sin(aflAngle);
		oT(2,1) = sin(aflAngle);
		oT(2,2) = cos(aflAngle);
	}
	else if (nSelection == Y_AXIS)	{
		oT(0,0) = cos(aflAngle);
		oT(0,2) = -sin(aflAngle);
		oT(2,0) = sin(aflAngle);
		oT(2,2) = cos(aflAngle);
	}

	else if (nSelection == Z_AXIS)	{
		oT(0,0) = cos(aflAngle);
		oT(0,1) = sin(aflAngle);
		oT(1,0) = -sin(aflAngle);
		oT(1,1) = cos(aflAngle);
	}

	return ObjectTransformation::ObjectTransformation(oT);
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setScalingGetMatrix(float aflX, float aflY, float aflZ)	{

	//aflX = (1+aflX)>0 ? 1.0 + aflX : 0.001;
	//aflY = (1+aflY)>0 ? 1.0 + aflY : 0.001;
	//aflZ = (1+aflZ)>0 ? 1.0 + aflZ : 0.001;

	aflX = (aflX > 0 ? 1.1 : 0.9);
	aflY = (aflY > 0 ? 1.1 : 0.9);
	aflZ = (aflZ > 0 ? 1.1 : 0.9);

	return Matrix::scale(aflX,aflY,aflZ);
}

//-----------------------------------------------------------
