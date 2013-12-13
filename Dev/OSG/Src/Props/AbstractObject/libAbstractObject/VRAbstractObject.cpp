#include "BasicDefinitions.h"

#include "VRAbstractObject.h"

using namespace VR;
using namespace std;

string AbstractObject::m_strSQLFormat = "";

//==============================================================

AbstractObjectParams::AbstractObjectParams() : 
	m_flPosX(0.0),		m_flPosY(0.0),		m_flPosZ(0.0),
	m_flScaleX(1.0),	m_flScaleY(1.0),	m_flScaleZ(1.0),
	m_flAngleXY(0.0),	m_flAngleXZ(0.0),	m_flAngleYZ(0.0)	{
}

//==============================================================

AbstractObject::AbstractObject() : m_bIsTargetPick(false)	{
}

//--------------------------------------------------------------

AbstractObject::AbstractObject(const AbstractObjectParams & aAbstractObjectParams)	{
	m_AbstractObjectParams = aAbstractObjectParams;
}

//--------------------------------------------------------------

string AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}

//--------------------------------------------------------------

void AbstractObject::setRotation(const AbstractObjectParams & aAbstractObjectParams)	{
	//Rotation goes counter-clockwise
	m_AbstractObjectParams = aAbstractObjectParams;

	m_AbstractObjectParams.m_flAngleXY = degrees2Radians(m_AbstractObjectParams.m_flAngleXY);
	m_AbstractObjectParams.m_flAngleXZ = degrees2Radians(m_AbstractObjectParams.m_flAngleXZ);
	m_AbstractObjectParams.m_flAngleYZ = degrees2Radians(m_AbstractObjectParams.m_flAngleYZ);
}

//--------------------------------------------------------------

void AbstractObject::setPosition(const AbstractObjectParams & aAbstractObjectParams)	{
	m_AbstractObjectParams.m_flPosX = aAbstractObjectParams.m_flPosX;
	m_AbstractObjectParams.m_flPosY = aAbstractObjectParams.m_flPosY;
	m_AbstractObjectParams.m_flPosZ = aAbstractObjectParams.m_flPosZ;
}

//--------------------------------------------------------------

void AbstractObject::setScaling(const AbstractObjectParams & aAbstractObjectParams)	{
	m_AbstractObjectParams.m_flScaleX = aAbstractObjectParams.m_flScaleX;
	m_AbstractObjectParams.m_flScaleY = aAbstractObjectParams.m_flScaleY;
	m_AbstractObjectParams.m_flScaleZ = aAbstractObjectParams.m_flScaleZ;
}

//--------------------------------------------------------------------------

void AbstractObject::setIsTargetPick(bool abIsTargetPick)	{
	m_bIsTargetPick = abIsTargetPick;
}

//--------------------------------------------------------------------------

bool AbstractObject::getIsTargetPick() const	{
	return m_bIsTargetPick;
}

//--------------------------------------------------------------------------

void AbstractObject::setParentName(std::string astrParentName)	{
	m_strParentName = astrParentName;
}

//--------------------------------------------------------------------------

string AbstractObject::getParentName() const	{
	return m_strParentName;
}
