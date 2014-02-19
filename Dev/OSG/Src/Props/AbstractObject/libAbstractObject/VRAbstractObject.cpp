#include "BasicDefinitions.h"

#include "VRContainer.h"
#include "VRCupboard.h"

#include "VRCylinder.h"
#include "VRPlate3D.h"
#include "VRPrism.h"
#include "VRSphere.h"

#include "VRAbstractObject.h"

using namespace VR;
using namespace osg;
using namespace std;

string AbstractObject::m_strSQLFormat = "";

//==============================================================

AbstractObjectParams::AbstractObjectParams() : 
	m_flPosX(0.0),		m_flPosY(0.0),		m_flPosZ(0.0),
	m_flLenX(1.0),		m_flLenY(1.0),		m_flLenZ(1.0),
	m_flAngleXY(0.0),	m_flAngleXZ(0.0),	m_flAngleYZ(0.0)	{
}

//==============================================================

AbstractObject::AbstractObject() : m_bIsTargetPick(false)	{
	const AbstractObjectParams aAbstractObjectParams;
	m_AbstractObjectParams = aAbstractObjectParams;
}

//--------------------------------------------------------------

AbstractObject::~AbstractObject()	{
}

//=======================================================================

ref_ptr<AbstractObject> AbstractObject::createInstance(const string & astrClassName)	{
	if (astrClassName == "Cupboard")
		return (new Cupboard);
	if (astrClassName == "Container")
		return (new Container);
	if (astrClassName == "Plate3D")
		return (new Plate3D);
	if (astrClassName == "Cylinder")
		return (new Cylinder);
	if (astrClassName == "Prism")
		return (new Prism);
	if (astrClassName == "Sphere")
		return (new VR::Sphere);
}

//=======================================================================

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
	m_AbstractObjectParams.m_flLenX = aAbstractObjectParams.m_flLenX;
	m_AbstractObjectParams.m_flLenY = aAbstractObjectParams.m_flLenY;
	m_AbstractObjectParams.m_flLenZ = aAbstractObjectParams.m_flLenZ;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getPosition() const	{
	Vec3d pos;
	pos.set(m_AbstractObjectParams.m_flPosX, m_AbstractObjectParams.m_flPosY, m_AbstractObjectParams.m_flPosZ);

	return pos;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getScaling() const	{
	Vec3d scale;
	scale.set(m_AbstractObjectParams.m_flLenX, m_AbstractObjectParams.m_flLenY, m_AbstractObjectParams.m_flLenZ);

	return scale;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getRotation() const	{
	Vec3d rotation;
	rotation.set(m_AbstractObjectParams.m_flAngleXY, m_AbstractObjectParams.m_flAngleXZ, m_AbstractObjectParams.m_flAngleYZ);

	return rotation;
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

