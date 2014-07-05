#include "VRUntransformedSphere.h"
#include "VRSphere.h"

#include "BasicStringDefinitions.h"

#include <string>
#include <iostream>
#include <fstream>

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

VR::Sphere::Sphere(const SphereParams & aSphereParams) : AbstractGeomShape(aSphereParams)	{
	m_pUntransformedSphere = new UntransformedSphere();
	addChild(m_pUntransformedSphere);

	setName("Sphere_"+tostr(getAbstractObjectNo()));

	init(aSphereParams);
}

//-----------------------------------------------------------------------

VR::Sphere::Sphere(const VR::Sphere& sp,const osg::CopyOp& copyop) :
AbstractGeomShape(sp,copyop)	{
	SphereParams spP;
	sp.getParams(spP);

	setName("Sphere_"+tostr(getAbstractObjectNo()));
	init(spP);
}

//-----------------------------------------------------------------------

const char* VR::Sphere::className() const	{
	return "Sphere";
}

//-----------------------------------------------------------------------

Object* VR::Sphere::cloneType() const	{
	SphereParams aSphereParams;
	return new Sphere(aSphereParams);
}

//-----------------------------------------------------------------------

Object* VR::Sphere::clone(const CopyOp& copyop) const	{
	return new Sphere(*this,copyop);
}

//-----------------------------------------------------------------------

void VR::Sphere::init(const SphereParams & aSphereParams)	{
	setParams(aSphereParams);

	setResolution(aSphereParams.m_nResPhi);
	
	Matrix matrix;
	matrix.set(aSphereParams.m_flRadius,	0,							0,							0,
			   0,							aSphereParams.m_flRadius,	0,							0,
			   0,							0,							aSphereParams.m_flRadius,	0,
			   0,							0,							0,							1);

	Matrix SphereMatrix =
		matrix.scale(aSphereParams.m_flLenX, aSphereParams.m_flLenY, aSphereParams.m_flLenZ)
		*
		matrix.rotate(
			aSphereParams.m_flAngleYZ, osg::X_AXIS,
			aSphereParams.m_flAngleXZ, osg::Y_AXIS,
			aSphereParams.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(aSphereParams.m_flPosX, aSphereParams.m_flPosY, aSphereParams.m_flPosZ)
	;
	
	setMatrix(SphereMatrix);

	setColor(aSphereParams.m_arrflRGBA);
	if ((aSphereParams.m_strFileNameTexture != " ") && (aSphereParams.m_strFileNameTexture != ""))
		setTexture(aSphereParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void VR::Sphere::setColor(const std::vector < float > & aarrflColor)	{
	m_pUntransformedSphere->setColor(aarrflColor);
}

//----------------------------------------------------------------------

void VR::Sphere::setTexture(const std::string & astrFileName) {
	m_pUntransformedSphere->setTexture(astrFileName);
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
	SphereParams sphereParams;
	getParams(sphereParams);

	string strSphereParams;
	strSphereParams = to_string((long double)sphereParams.m_flRadius) + "_";

	strSphereParams += to_string((long double)sphereParams.m_flPosX) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flPosY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flPosZ) + "_";
											
	strSphereParams += to_string((long double)sphereParams.m_flLenX) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flLenY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flLenZ) + "_";
										
	strSphereParams += to_string((long double)sphereParams.m_flAngleXY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flAngleXZ) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flAngleYZ);

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)sphereParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Sphere (SphereRes, SphereMatrix, SphereColor, SphereTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)sphereParams.m_nResPhi) + ",'"
		+ strSphereParams + "','"
		+ strColor + "','"
		+ sphereParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Sphere'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Sphere::initFromSQLData(const string & astrSQLData)	{
	SphereParams sphereParams;
	string strSQLData = astrSQLData;

	vector <string> arrstrSphereParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrSphereParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrSphereParams[3],"_");

	sphereParams.m_nResPhi = sphereParams.m_nResTheta = stof(arrstrSphereParams[1]);
	sphereParams.m_flRadius = stof(arrstrMatrix[0]);

	sphereParams.m_flPosX = stof(arrstrMatrix[1]);
	sphereParams.m_flPosY = stof(arrstrMatrix[2]);
	sphereParams.m_flPosZ = stof(arrstrMatrix[3]);

	sphereParams.m_flLenX = stof(arrstrMatrix[4]);
	sphereParams.m_flLenY = stof(arrstrMatrix[5]);
	sphereParams.m_flLenZ = stof(arrstrMatrix[6]);

	sphereParams.m_flAngleXY = stof(arrstrMatrix[7]);
	sphereParams.m_flAngleXZ = stof(arrstrMatrix[8]);
	sphereParams.m_flAngleYZ = stof(arrstrMatrix[9]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			sphereParams.m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	sphereParams.m_strFileNameTexture = arrstrSphereParams[4];

	init(sphereParams);
}

//----------------------------------------------------------------------

void VR::Sphere::predefinedObject()	{
	SphereParams sphereParams;
	getParams(sphereParams);
	init(sphereParams);
	setIsTargetPick(true);
}

//----------------------------------------------------------------------

string VR::Sphere::prepareRowData(const string & astrParentName)	{
	SphereParams sphereParams;
	getParams(sphereParams);

	string strSphereParams;
	strSphereParams = to_string((long double)sphereParams.m_flRadius) + "_";

	strSphereParams += to_string((long double)sphereParams.m_flPosX) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flPosY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flPosZ) + "_";
											
	strSphereParams += to_string((long double)sphereParams.m_flLenX) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flLenY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flLenZ) + "_";
										
	strSphereParams += to_string((long double)sphereParams.m_flAngleXY) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flAngleXZ) + "_";
	strSphereParams += to_string((long double)sphereParams.m_flAngleYZ) + ";";

	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += to_string((long double)sphereParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += to_string((long double)sphereParams.m_arrflRGBA[3]) + ";";

	strSphereParams += strColor;

	strSphereParams += sphereParams.m_strFileNameTexture + ";";

	strSphereParams += astrParentName + ";";
	return strSphereParams;
}