#include "VRUntransformedSphere.h"
#include "VRSphere.h"

#include "StringManipulation.h"

#include <string>
#include <iostream>

using namespace std;
using namespace osg;
using namespace VR;

string VR::Sphere::m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Sphere "
	"(SphereID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"SphereRes TEXT,"
	"SphereMatrix TEXT,"
	"SphereColor TEXT,"
	"SphereTexture TEXT, "
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

//-----------------------------------------------------------------------

VR::SphereParams::SphereParams()	{
}

//-----------------------------------------------------------------------

VR::Sphere::Sphere()	{
	m_pUntransformedSphere = new UntransformedSphere(m_SphereParams);
	addChild(m_pUntransformedSphere);
}

//----------------------------------------------------------

VR::Sphere::Sphere(const SphereParams & aSphereParams)	{
	m_SphereParams = aSphereParams;
	m_pUntransformedSphere = new UntransformedSphere();
	init(m_SphereParams);
	addChild(m_pUntransformedSphere);
}

//-----------------------------------------------------------------------

void VR::Sphere::init(const AbstractGeomShapeParams & aAbstractGeomShapeParams)	{
	m_SphereParams = static_cast<const SphereParams&>(aAbstractGeomShapeParams);

	setResolution(m_SphereParams.m_nResPhi);
	
	Matrix matrix;
	matrix.set(m_SphereParams.m_flRadius,	0,							0,							0,
			   0,							m_SphereParams.m_flRadius,	0,							0,
			   0,							0,							m_SphereParams.m_flRadius,	0,
			   0,							0,							0,							1);

	Matrix SphereMatrix =
		matrix.scale(m_SphereParams.m_flLenX, m_SphereParams.m_flLenY, m_SphereParams.m_flLenZ)
		*
		matrix.rotate(
			m_SphereParams.m_flAngleYZ, osg::X_AXIS,
			m_SphereParams.m_flAngleXZ, osg::Y_AXIS,
			m_SphereParams.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(m_SphereParams.m_flPosX, m_SphereParams.m_flPosY, m_SphereParams.m_flPosZ)
	;
	
	setMatrix(SphereMatrix);

	setColor(m_SphereParams.m_arrflRGBA);
	if ((m_SphereParams.m_strFileNameTexture != " ") && (m_SphereParams.m_strFileNameTexture != ""))
		setTexture(m_SphereParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void VR::Sphere::setColor(const std::vector < float > & aarrflColor)	{
	m_SphereParams.m_arrflRGBA = aarrflColor;
	m_pUntransformedSphere->setColor(m_SphereParams.m_arrflRGBA);
}

//----------------------------------------------------------------------

void VR::Sphere::setTexture(const std::string & astrFileName) {
	m_SphereParams.m_strFileNameTexture = astrFileName;
	m_pUntransformedSphere->setTexture(m_SphereParams.m_strFileNameTexture);
}

//----------------------------------------------------------

void VR::Sphere::setResolution(int anRes) {
	m_pUntransformedSphere->setResolution(anRes,anRes);
}

//----------------------------------------------------------

string VR::Sphere::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

string VR::Sphere::getSQLCommand() const	{
	string strSphereParams;
	strSphereParams = to_string((long double)m_SphereParams.m_flRadius) + "_";

	strSphereParams += to_string((long double)m_SphereParams.m_flPosX) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flPosY) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flPosZ) + "_";
							   					 
	strSphereParams += to_string((long double)m_SphereParams.m_flLenX) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flLenY) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flLenZ) + "_";
												 
	strSphereParams += to_string((long double)m_SphereParams.m_flAngleXY) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flAngleXZ) + "_";
	strSphereParams += to_string((long double)m_SphereParams.m_flAngleYZ);

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_SphereParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Sphere (SphereRes, SphereMatrix, SphereColor, SphereTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_SphereParams.m_nResPhi) + ",'"
		+ strSphereParams + "','"
		+ strColor + "','"
		+ m_SphereParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Sphere'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Sphere::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;

	vector <string> arrstrSphereParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrSphereParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrSphereParams[3],"_");

	m_SphereParams.m_nResPhi = m_SphereParams.m_nResTheta = stof(arrstrSphereParams[1]);
	m_SphereParams.m_flRadius = stof(arrstrMatrix[0]);
	
	m_SphereParams.m_flPosX = stof(arrstrMatrix[1]);
	m_SphereParams.m_flPosY = stof(arrstrMatrix[2]);
	m_SphereParams.m_flPosZ = stof(arrstrMatrix[3]);

	m_SphereParams.m_flLenX = stof(arrstrMatrix[4]);
	m_SphereParams.m_flLenY = stof(arrstrMatrix[5]);
	m_SphereParams.m_flLenZ = stof(arrstrMatrix[6]);

	m_SphereParams.m_flAngleXY = stof(arrstrMatrix[7]);
	m_SphereParams.m_flAngleXZ = stof(arrstrMatrix[8]);
	m_SphereParams.m_flAngleYZ = stof(arrstrMatrix[9]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			m_SphereParams.m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	m_SphereParams.m_strFileNameTexture = arrstrSphereParams[4];

	init(m_SphereParams);
}

//----------------------------------------------------------------------

void VR::Sphere::predefinedObject()	{
	init(m_SphereParams);
	setIsTargetPick(true);
}
