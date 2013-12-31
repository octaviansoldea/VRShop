#include "VRObjectTransformation.h"

using namespace VR;
using namespace osg;

ObjectTransformationParams::ObjectTransformationParams() :
m_flMatrix00(1.0), m_flMatrix01(0.0), m_flMatrix02(0.0), m_flMatrix03(0.0),
m_flMatrix10(0.0), m_flMatrix11(1.0), m_flMatrix12(0.0), m_flMatrix13(0.0),
m_flMatrix20(0.0), m_flMatrix21(0.0), m_flMatrix22(1.0), m_flMatrix23(0.0),
m_flMatrix30(0.0), m_flMatrix31(0.0), m_flMatrix32(0.0), m_flMatrix33(1.0)	{
};

//-----------------------------------------------------------

ObjectTransformation::ObjectTransformation()	{
	const ObjectTransformationParams aObjectTransformationParams;
	init(aObjectTransformationParams);
}

//-----------------------------------------------------------

ObjectTransformation::ObjectTransformation(const ObjectTransformationParams & aObjectTransformationParams)	{
	init(aObjectTransformationParams);
}

//-----------------------------------------------------------

void ObjectTransformation::init(const ObjectTransformationParams & aObjectTransformationParams)	{
	m_ObjectTransformationParams = aObjectTransformationParams;
}

//-----------------------------------------------------------

Matrix ObjectTransformation::translation(float aflTranslateX, float aflTranslateY, float aflTranslateZ)	{
	ObjectTransformationParams * pObjectTransformationParams = new ObjectTransformationParams();

	pObjectTransformationParams->m_flMatrix30 = aflTranslateX;
	pObjectTransformationParams->m_flMatrix31 = aflTranslateY;
	pObjectTransformationParams->m_flMatrix32 = aflTranslateZ;

	init(*pObjectTransformationParams);
	delete pObjectTransformationParams;

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::rotation(float aflAngle, ObjectTransformationParams::m_enumRotation aenumRotation)	{
	ObjectTransformationParams * pObjectTransformationParams = new ObjectTransformationParams();

	int nSelection = aenumRotation;

	if (nSelection == ObjectTransformationParams::m_enumRotation::ROTATION_ON_X)	{
		pObjectTransformationParams->m_flMatrix11 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix12 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix21 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix22 = cos(aflAngle);
	}

	else if (nSelection == ObjectTransformationParams::m_enumRotation::ROTATION_ON_Y)	{
		pObjectTransformationParams->m_flMatrix00 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix02 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix20 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix22 = cos(aflAngle);
	}

	else if (nSelection == ObjectTransformationParams::m_enumRotation::ROTATION_ON_Z)	{
		pObjectTransformationParams->m_flMatrix00 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix01 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix10 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix11 = cos(aflAngle);
	}

	else if (nSelection == ObjectTransformationParams::m_enumRotation::DEFAULT)	{
	}

	init(*pObjectTransformationParams);
	delete pObjectTransformationParams;

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::scaling(float aflScaleX, float aflScaleY, float aflScaleZ)	{
	ObjectTransformationParams * pObjectTransformationParams = new ObjectTransformationParams();

	aflScaleX = (1+aflScaleX)>0 ? 1.0 + aflScaleX : 0.001;
	aflScaleY = (1+aflScaleY)>0 ? 1.0 + aflScaleY : 0.001;
	aflScaleZ = (1+aflScaleZ)>0 ? 1.0 + aflScaleZ : 0.001;

	pObjectTransformationParams->m_flMatrix00 = aflScaleX;
	pObjectTransformationParams->m_flMatrix11 = aflScaleY;
	pObjectTransformationParams->m_flMatrix22 = aflScaleZ;

	init(*pObjectTransformationParams);
	delete pObjectTransformationParams;

	return getMatrix();
}

//-----------------------------------------------------------

Matrix ObjectTransformation::getMatrix() const	{
	const ObjectTransformationParams &params = m_ObjectTransformationParams;
	Matrix mtrx(
		params.m_flMatrix00, params.m_flMatrix01, params.m_flMatrix02, params.m_flMatrix03,
		params.m_flMatrix10, params.m_flMatrix11, params.m_flMatrix12, params.m_flMatrix13,
		params.m_flMatrix20, params.m_flMatrix21, params.m_flMatrix22, params.m_flMatrix23,
		params.m_flMatrix30, params.m_flMatrix31, params.m_flMatrix32, params.m_flMatrix33
	);

	return mtrx;
}

//-----------------------------------------------------------
