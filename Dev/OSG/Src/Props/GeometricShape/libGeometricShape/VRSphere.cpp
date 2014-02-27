#include "VRUntransformedSphere.h"
#include "VRSphere.h"

#include "BasicStringDefinitions.h"

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

VR::SphereParams::SphereParams() : AbstractGeomShapeParams()	{
}

//-----------------------------------------------------------------------

VR::Sphere::Sphere() : AbstractGeomShape(new SphereParams())	{
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);
	m_pUntransformedSphere = new UntransformedSphere(*pSphereParams);
	addChild(m_pUntransformedSphere);
}

//----------------------------------------------------------

VR::Sphere::Sphere(SphereParams * apSphereParams) : AbstractGeomShape(apSphereParams)	{
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);
	m_pUntransformedSphere = new UntransformedSphere();
	init(*pSphereParams);
	addChild(m_pUntransformedSphere);
}

//-----------------------------------------------------------------------

void VR::Sphere::init(const AbstractGeomShapeParams & aAbstractGeomShapeParams)	{
	const SphereParams * pSphereParams = dynamic_cast<const SphereParams*>(&aAbstractGeomShapeParams);

	setResolution(pSphereParams->m_nResPhi);
	
	Matrix matrix;
	matrix.set(pSphereParams->m_flRadius,	0,							0,							0,
			   0,							pSphereParams->m_flRadius,	0,							0,
			   0,							0,							pSphereParams->m_flRadius,	0,
			   0,							0,							0,							1);

	Matrix SphereMatrix =
		matrix.scale(pSphereParams->m_flLenX, pSphereParams->m_flLenY, pSphereParams->m_flLenZ)
		*
		matrix.rotate(
			pSphereParams->m_flAngleYZ, osg::X_AXIS,
			pSphereParams->m_flAngleXZ, osg::Y_AXIS,
			pSphereParams->m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(pSphereParams->m_flPosX, pSphereParams->m_flPosY, pSphereParams->m_flPosZ)
	;
	
	setMatrix(SphereMatrix);

	setColor(pSphereParams->m_arrflRGBA);
	if ((pSphereParams->m_strFileNameTexture != " ") && (pSphereParams->m_strFileNameTexture != ""))
		setTexture(pSphereParams->m_strFileNameTexture);
}

//----------------------------------------------------------------------

void VR::Sphere::setColor(const std::vector < float > & aarrflColor)	{
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);

	pSphereParams->m_arrflRGBA = aarrflColor;
	m_pUntransformedSphere->setColor(pSphereParams->m_arrflRGBA);
}

//----------------------------------------------------------------------

void VR::Sphere::setTexture(const std::string & astrFileName) {
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);
	pSphereParams->m_strFileNameTexture = astrFileName;
	m_pUntransformedSphere->setTexture(pSphereParams->m_strFileNameTexture);
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
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);

	string strSphereParams;
	strSphereParams = to_string((long double)pSphereParams->m_flRadius) + "_";

	strSphereParams += to_string((long double)pSphereParams->m_flPosX) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flPosY) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flPosZ) + "_";

	strSphereParams += to_string((long double)pSphereParams->m_flLenX) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flLenY) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flLenZ) + "_";

	strSphereParams += to_string((long double)pSphereParams->m_flAngleXY) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flAngleXZ) + "_";
	strSphereParams += to_string((long double)pSphereParams->m_flAngleYZ);

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)pSphereParams->m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Sphere (SphereRes, SphereMatrix, SphereColor, SphereTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)pSphereParams->m_nResPhi) + ",'"
		+ strSphereParams + "','"
		+ strColor + "','"
		+ pSphereParams->m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Sphere'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Sphere::initFromSQLData(const string & astrSQLData)	{
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);
	string strSQLData = astrSQLData;

	vector <string> arrstrSphereParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrSphereParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrSphereParams[3],"_");

	pSphereParams->m_nResPhi = pSphereParams->m_nResTheta = stof(arrstrSphereParams[1]);
	pSphereParams->m_flRadius = stof(arrstrMatrix[0]);

	pSphereParams->m_flPosX = stof(arrstrMatrix[1]);
	pSphereParams->m_flPosY = stof(arrstrMatrix[2]);
	pSphereParams->m_flPosZ = stof(arrstrMatrix[3]);

	pSphereParams->m_flLenX = stof(arrstrMatrix[4]);
	pSphereParams->m_flLenY = stof(arrstrMatrix[5]);
	pSphereParams->m_flLenZ = stof(arrstrMatrix[6]);

	pSphereParams->m_flAngleXY = stof(arrstrMatrix[7]);
	pSphereParams->m_flAngleXZ = stof(arrstrMatrix[8]);
	pSphereParams->m_flAngleYZ = stof(arrstrMatrix[9]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			pSphereParams->m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	pSphereParams->m_strFileNameTexture = arrstrSphereParams[4];

	init(*pSphereParams);
}

//----------------------------------------------------------------------

void VR::Sphere::predefinedObject()	{
	SphereParams * pSphereParams = dynamic_cast<SphereParams*>(m_pAbstractObjectParams);
	init(*pSphereParams);
	setIsTargetPick(true);
}
