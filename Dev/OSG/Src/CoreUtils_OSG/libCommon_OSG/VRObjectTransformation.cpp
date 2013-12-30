#include <vector>
#include <iostream>

#include "VRObjectTransformation.h"

using namespace VR;

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

osg::Matrix ObjectTransformation::translation(float aflTranslateX, float aflTranslateY, float aflTranslateZ)	{
	ObjectTransformationParams * pObjectTransformationParams = new ObjectTransformationParams();

	pObjectTransformationParams->m_flMatrix30 = aflTranslateX;
	pObjectTransformationParams->m_flMatrix31 = aflTranslateY;
	pObjectTransformationParams->m_flMatrix32 = aflTranslateZ;

	init(*pObjectTransformationParams);
	delete pObjectTransformationParams;

	return getMatrix();
}

//-----------------------------------------------------------

osg::Matrix ObjectTransformation::rotation(float aflAngle, ObjectTransformationParams::enumRotation aenumRotation)	{
	ObjectTransformationParams * pObjectTransformationParams = new ObjectTransformationParams();

	int nSelection = aenumRotation;

	if (nSelection == ObjectTransformationParams::enumRotation::RotationOnX)	{
		pObjectTransformationParams->m_flMatrix11 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix12 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix21 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix22 = cos(aflAngle);
	}

	if (nSelection == ObjectTransformationParams::enumRotation::RotationOnY)	{
		pObjectTransformationParams->m_flMatrix00 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix02 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix20 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix22 = cos(aflAngle);
	}

	if (nSelection == ObjectTransformationParams::enumRotation::RotationOnZ)	{
		pObjectTransformationParams->m_flMatrix00 = cos(aflAngle);
		pObjectTransformationParams->m_flMatrix01 = sin(aflAngle);
		pObjectTransformationParams->m_flMatrix10 = -sin(aflAngle);
		pObjectTransformationParams->m_flMatrix11 = cos(aflAngle);
	}

	if (nSelection == ObjectTransformationParams::enumRotation::Default)	{
	}

	init(*pObjectTransformationParams);
	delete pObjectTransformationParams;

	return getMatrix();
}

//-----------------------------------------------------------

osg::Matrix ObjectTransformation::scaling(float aflScaleX, float aflScaleY, float aflScaleZ)	{
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

osg::Matrix ObjectTransformation::getMatrix() const	{
	osg::Matrix mtrx(
		m_ObjectTransformationParams.m_flMatrix00, m_ObjectTransformationParams.m_flMatrix01,m_ObjectTransformationParams.m_flMatrix02,m_ObjectTransformationParams.m_flMatrix03,
		m_ObjectTransformationParams.m_flMatrix10, m_ObjectTransformationParams.m_flMatrix11,m_ObjectTransformationParams.m_flMatrix12,m_ObjectTransformationParams.m_flMatrix13,
		m_ObjectTransformationParams.m_flMatrix20, m_ObjectTransformationParams.m_flMatrix21,m_ObjectTransformationParams.m_flMatrix22,m_ObjectTransformationParams.m_flMatrix23,
		m_ObjectTransformationParams.m_flMatrix30, m_ObjectTransformationParams.m_flMatrix31,m_ObjectTransformationParams.m_flMatrix32,m_ObjectTransformationParams.m_flMatrix33
	);

	return mtrx;
}
