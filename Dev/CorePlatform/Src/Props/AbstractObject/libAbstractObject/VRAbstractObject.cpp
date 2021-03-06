#include <iostream>
#include <ostream>

#include "BasicDefinitions.h"
#include "BasicStringDefinitions.h"

#include "VRSurfaceOperations.h"

#include "VRAbstractObject.h"

using namespace VR;
using namespace osg;
using namespace std;

unsigned long AbstractObject::s_nAbstractObjectNo = 0;

//------------------------------------------------------------

string AbstractObject::m_strSQLFormat = "";

//==============================================================

AbstractObjectParams::AbstractObjectParams() : 
	m_flPosX(0.0),		m_flPosY(0.0),		m_flPosZ(0.0),
	m_flLenX(1.0),		m_flLenY(1.0),		m_flLenZ(1.0),
	m_flAngleYZ(0.0),	m_flAngleXZ(0.0),	m_flAngleXY(0.0)	{
}

//--------------------------------------------------------------

AbstractObjectParams::~AbstractObjectParams()	{
}

//==============================================================

AbstractObject::AbstractObject(const AbstractObjectParams & aAbstractObjectParams) :
	MatrixTransform(), m_bIsTargetPick(false), m_bIsTargetLocked(false), m_flTransparencyFactor(1.f) {
	setParams(aAbstractObjectParams);

	s_nAbstractObjectNo += 1;
}

//--------------------------------------------------------------

AbstractObject::AbstractObject(const AbstractObject& ao,const CopyOp& copyop) :
MatrixTransform(ao,copyop) {
	AbstractObjectParams aop;
	ao.getParams(aop);
	setParams(aop);
	m_bIsTargetPick = ao.m_bIsTargetPick;

	s_nAbstractObjectNo += 1;
}

//--------------------------------------------------------------

AbstractObject::~AbstractObject() {
}

//=======================================================================

const char * AbstractObject::className() const	{
	return "AbstractObject";
}

//=======================================================================

string AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}

//--------------------------------------------------------------

void AbstractObject::initFromSQLData(vector<string> & avecstrSQLData)	{
}

//--------------------------------------------------------------

void AbstractObject::setRotation(float aflAngleX, float aflAngleY, float aflAngleZ)	{
	//Rotation goes counter-clockwise

	m_flAngleYZ = degrees2Radians(aflAngleX);
	m_flAngleXZ = degrees2Radians(aflAngleY);
	m_flAngleXY = degrees2Radians(aflAngleZ);
}

//--------------------------------------------------------------

void AbstractObject::setPosition(float aflPosX, float aflPosY, float aflPosZ)	{
	m_flPosX = aflPosX;
	m_flPosY = aflPosY;
	m_flPosZ = aflPosZ;
}

//--------------------------------------------------------------

void AbstractObject::setScaling(float aflLenX, float aflLenY, float aflLenZ)	{
	m_flLenX = aflLenX;
	m_flLenY = aflLenY;
	m_flLenZ = aflLenZ;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getPosition() const	{
	Vec3d pos(m_flPosX, m_flPosY, m_flPosZ);

	return pos;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getScaling() const	{
	Vec3d scale(m_flLenX, m_flLenY, m_flLenZ);

	return scale;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getRotation() const	{
	float flAngleX = radians2degrees(m_flAngleYZ);
	float flAngleY = radians2degrees(m_flAngleXZ);
	float flAngleZ = radians2degrees(m_flAngleXY);

	Vec3d rotation(flAngleX, flAngleY, flAngleZ);

	return rotation;
}

//--------------------------------------------------------------------------

string AbstractObject::getTexture() const	{
	return "";
}

//--------------------------------------------------------------------------

Matrix AbstractObject::calculateMatrix() const	{
	Vec3d vec3dPos = getPosition();
	Vec3d vec3dRot = getRotation();
	Vec3d vec3dLen = getScaling();

	Matrix matrix(Matrix::identity());

	Matrix mtrxMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			degrees2Radians(vec3dRot[0]), osg::X_AXIS,
			degrees2Radians(vec3dRot[1]), osg::Y_AXIS,
			degrees2Radians(vec3dRot[2]), osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	return mtrxMatrix;
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

void AbstractObject::setIsTargetLocked(bool abIsTargetLocked)	{
	m_bIsTargetLocked = abIsTargetLocked;
}

//--------------------------------------------------------------------------

bool AbstractObject::getIsTargetLocked() const	{
	return m_bIsTargetLocked;
}

//--------------------------------------------------------------------------

void AbstractObject::setTransparency(float aflTransparenceFactor)	{
	SurfaceOperations::setTransparency(this, aflTransparenceFactor);
	m_flTransparencyFactor = aflTransparenceFactor;
}

//--------------------------------------------------------------------------

float AbstractObject::getTransparency() const	{
	return m_flTransparencyFactor;
}

//--------------------------------------------------------------------------

void AbstractObject::writeObjectHierarchy(vector<string> &avecstrHierarchy)	{
	//Object name
	avecstrHierarchy.push_back(getName());
	
	ref_ptr<AbstractObject> pAO = dynamic_cast<AbstractObject*>(this);

	NodeList::iterator it = pAO->_children.begin();
	for (it; it != pAO->_children.end(); it++)	{
		string strName = it->get()->getName();
		if (strName.empty())	{
			break;
		} else {
			strName = string(2,' ') + strName;
			avecstrHierarchy.push_back(strName);
		}
	}
}

//--------------------------------------------------------------------------

void AbstractObject::print(std::ostream & os) const	{
	os << "========================================Begin AbstractObject" << endl;
	os << "Object name: " << getName() << endl;
	int nI, nJ;
	os << "calculateMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << calculateMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;

	os << "========================================End AbstractObject" << endl;
}

//--------------------------------------------------------------------------

void AbstractObject::preparedObjectData(std::vector<std::string> &avecItems, std::string & astrParent)	{
	ref_ptr<AbstractObject> pAbstractObject = dynamic_cast<AbstractObject*>(this);

	vector<string> * pvecItems = &avecItems;

	int nI=1;

	string strClassName = pAbstractObject->className();
	const string * pstrObjectName = &pAbstractObject->getName();
	string strItem = (string(2*nI,' ') + strClassName + ";" + *pstrObjectName + ";" + pAbstractObject->prepareRowData(astrParent));
	pvecItems->push_back(strItem);

	nI += 1;	//enlarge indent by 1 unit

	NodeList::iterator it;
	for (it = pAbstractObject->_children.begin(); it != pAbstractObject->_children.end(); it++)	{
		ref_ptr<AbstractObject> pChild = dynamic_cast<AbstractObject*>(it->get());

		if(pChild == NULL)	{
			break;
		}

		strClassName = pChild->className();
		pstrObjectName = &pChild->getName();
		strItem = (strClassName + ";" + *pstrObjectName + ";" + pChild->prepareRowData(pAbstractObject->getName()));

		pvecItems->push_back(string(2*nI,' ') + strItem);
	}
}

//--------------------------------------------------------------------------

void AbstractObject::setParams(const AbstractObjectParams & aAbstractObjectParams) {
	m_flPosX = aAbstractObjectParams.m_flPosX;
	m_flPosY = aAbstractObjectParams.m_flPosY;
	m_flPosZ =aAbstractObjectParams.m_flPosZ;

	m_flLenX =aAbstractObjectParams.m_flLenX;
	m_flLenY =aAbstractObjectParams.m_flLenY;
	m_flLenZ =aAbstractObjectParams.m_flLenZ;

	m_flAngleYZ =aAbstractObjectParams.m_flAngleYZ;
	m_flAngleXZ =aAbstractObjectParams.m_flAngleXZ;
	m_flAngleXY =aAbstractObjectParams.m_flAngleXY;
}

//--------------------------------------------------------------------------

void AbstractObject::getParams(AbstractObjectParams & aAbstractObjectParams) const {
	
	aAbstractObjectParams.m_flPosX = m_flPosX;
	aAbstractObjectParams.m_flPosY = m_flPosY;
	aAbstractObjectParams.m_flPosZ = m_flPosZ;
	
	aAbstractObjectParams.m_flLenX = m_flLenX;
	aAbstractObjectParams.m_flLenY = m_flLenY;
	aAbstractObjectParams.m_flLenZ = m_flLenZ;
	
	aAbstractObjectParams.m_flAngleYZ = m_flAngleYZ;
	aAbstractObjectParams.m_flAngleXZ = m_flAngleXZ;
	aAbstractObjectParams.m_flAngleXY = m_flAngleXY;
}

//--------------------------------------------------------------------------

unsigned long AbstractObject::getAbstractObjectNo() const	{
	return s_nAbstractObjectNo;
}
