#include "VRObjectTransformation.h"

using namespace VR;
using namespace osg;

ObjectTransformationParams::ObjectTransformationParams() {
	identity();
};

//-----------------------------------------------------------

ObjectTransformation::ObjectTransformation()	{
	const ObjectTransformationParams objectTransformationParams;
	init(objectTransformationParams);
}

//-----------------------------------------------------------

//ObjectTransformation::ObjectTransformation(const ObjectTransformationParams & aObjectTransformationParams)	{
//	init(aObjectTransformationParams);
//}

//-----------------------------------------------------------

void ObjectTransformation::init(const ObjectTransformationParams & aObjectTransformationParams)	{
	m_ObjectTransformationParams = aObjectTransformationParams;
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setTranslationGetMatrix(float aflX, float aflY, float aflZ)	{
	ObjectTransformationParams params;

	params(3,0) = aflX;
	params(3,1) = aflY;
	params(3,2) = aflZ;

	init(params);

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setRotationGetMatrix(float aflAngle, ROTATION_TYPE aENUMRotationm)	{
	ObjectTransformationParams params;

	int nSelection = aENUMRotationm;

	if (nSelection == ROTATION_ON_X)	{
		params(1,1) = cos(aflAngle);
		params(1,2) = -sin(aflAngle);
		params(2,1) = sin(aflAngle);
		params(2,2) = cos(aflAngle);
	}

	else if (nSelection == ROTATION_ON_Y)	{
		params(0,0) = cos(aflAngle);
		params(0,2) = -sin(aflAngle);
		params(2,0) = sin(aflAngle);
		params(2,2) = cos(aflAngle);
	}

	else if (nSelection == ROTATION_ON_Z)	{
		params(0,0) = cos(aflAngle);
		params(0,1) = sin(aflAngle);
		params(1,0) = -sin(aflAngle);
		params(1,1) = cos(aflAngle);
	}

	init(params);

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::setScalingGetMatrix(float aflX, float aflY, float aflZ)	{
	ObjectTransformationParams params;

	params(0,0) = (aflX > 0 ? 1.1 : 0.9);
	params(1,1) = (aflY > 0 ? 1.1 : 0.9);
	params(2,2) = (aflZ > 0 ? 1.1 : 0.9);

	init(params);

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::getMatrix() const	{
	ObjectTransformationParams params = m_ObjectTransformationParams;
	Matrix mtrx(
		params(0,0), params(0,1), params(0,2), params(0,3),
		params(1,0), params(1,1), params(1,2), params(1,3),
		params(2,0), params(2,1), params(2,2), params(2,3),
		params(3,0), params(3,1), params(3,2), params(3,3)
	);

	return mtrx;
}

//-----------------------------------------------------------
