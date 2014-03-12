#include "BasicDefinitions.h"

#include "VRCustomFurniture.h"
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
	m_flAngleYZ(0.0),	m_flAngleXZ(0.0),	m_flAngleXY(0.0)	{
}

//--------------------------------------------------------------

AbstractObjectParams::~AbstractObjectParams()	{
}

//==============================================================

AbstractObject::AbstractObject() : MatrixTransform()	{
}

//--------------------------------------------------------------

AbstractObject::AbstractObject(AbstractObjectParams * apAbstractObjectParams) : m_bIsTargetPick(false),MatrixTransform()	{
	if(apAbstractObjectParams == 0)
		m_pAbstractObjectParams = new AbstractObjectParams;
	else
		m_pAbstractObjectParams = apAbstractObjectParams;
}

//--------------------------------------------------------------

AbstractObject::AbstractObject(const AbstractObject& ao,const CopyOp& copyop) :
MatrixTransform(ao,copyop)	{
	m_pAbstractObjectParams = ao.m_pAbstractObjectParams;
	m_bIsTargetPick = ao.m_bIsTargetPick;
}

//--------------------------------------------------------------

AbstractObject::~AbstractObject()	{
	delete m_pAbstractObjectParams;
}

//=======================================================================

const char * AbstractObject::className() const	{
	return "AbstractObject";
}

//-----------------------------------------------------------------------

ref_ptr<AbstractObject> AbstractObject::createInstance(const string & astrClassName)	{
	if (astrClassName == "Cupboard")
		return (new Cupboard);
	if (astrClassName == "Container")
		return (new Container);
	if (astrClassName == "CustomFurniture")
		return (new CustomFurniture);
	if (astrClassName == "Plate3D")
		return (new Plate3D);
	if (astrClassName == "Cylinder")
		return (new VR::Cylinder);
	if (astrClassName == "Prism")
		return (new Prism);
	if (astrClassName == "Sphere")
		return (new VR::Sphere);
}

//=======================================================================

string AbstractObject::getSQLFormat() const {
	return(m_strSQLFormat);
}

//--------------------------------------------------------------

void AbstractObject::setRotation(float aflAngleX, float aflAngleY, float aflAngleZ)	{
	//Rotation goes counter-clockwise

	m_pAbstractObjectParams->m_flAngleYZ = degrees2Radians(aflAngleX);
	m_pAbstractObjectParams->m_flAngleXZ = degrees2Radians(aflAngleY);
	m_pAbstractObjectParams->m_flAngleXY = degrees2Radians(aflAngleZ);
}

//--------------------------------------------------------------

void AbstractObject::setPosition(float aflPosX, float aflPosY, float aflPosZ)	{
	m_pAbstractObjectParams->m_flPosX = aflPosX;
	m_pAbstractObjectParams->m_flPosY = aflPosY;
	m_pAbstractObjectParams->m_flPosZ = aflPosZ;
}

//--------------------------------------------------------------

void AbstractObject::setScaling(float aflLenX, float aflLenY, float aflLenZ)	{
	m_pAbstractObjectParams->m_flLenX = aflLenX;
	m_pAbstractObjectParams->m_flLenY = aflLenY;
	m_pAbstractObjectParams->m_flLenZ = aflLenZ;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getPosition() const	{
	Vec3d pos;
	pos.set(m_pAbstractObjectParams->m_flPosX, m_pAbstractObjectParams->m_flPosY, m_pAbstractObjectParams->m_flPosZ);

	return pos;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getScaling() const	{
	Vec3d scale;
	scale.set(m_pAbstractObjectParams->m_flLenX, m_pAbstractObjectParams->m_flLenY, m_pAbstractObjectParams->m_flLenZ);

	return scale;
}

//--------------------------------------------------------------------------

Vec3d AbstractObject::getRotation() const	{
	float flAngleX = radians2degrees(m_pAbstractObjectParams->m_flAngleYZ);
	float flAngleY = radians2degrees(m_pAbstractObjectParams->m_flAngleXZ);
	float flAngleZ = radians2degrees(m_pAbstractObjectParams->m_flAngleXY);

	Vec3d rotation(flAngleX, flAngleY, flAngleZ);

	return rotation;
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

void AbstractObject::writeObjectHierarchy(std::vector<std::string> &avecstrHierarchy)	{
	avecstrHierarchy.push_back(getName());
	
	AbstractObject * pAO = dynamic_cast<AbstractObject*>(this);

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
	os << "Object name: " << getName() << endl;
	int nI, nJ;
	os << "GetMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << getMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;
	os << "calculateMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << calculateMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;

	os << "Child index: " << getChildIndex(this) << endl;

	os << "========================================" << endl;
}