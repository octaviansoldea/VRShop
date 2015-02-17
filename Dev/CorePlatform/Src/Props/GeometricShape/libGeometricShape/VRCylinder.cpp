#include "BasicStringDefinitions.h"

#include <fstream>

#include "VRCylinder.h"

using namespace VR;
using namespace std;
using namespace osg;

string VR::Cylinder::m_strSQLFormat = 
	"CREATE TABLE IF NOT EXISTS Cylinder "
	"(CylinderID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"CylinderRes INTEGER,"
	"CylinderMatrix TEXT,"
	"CylinderColor TEXT,"
	"CylinderTexture TEXT, "
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

CylinderParams::CylinderParams() : PrismParams() {
	m_nResolution = 20;
}

//-----------------------------------------------------------------------

VR::Cylinder::Cylinder(const CylinderParams & aCylinderParams) : Prism(aCylinderParams)	{
	init(aCylinderParams);
	setName("Cylinder_"+tostr(getAbstractObjectNo()));
}

//----------------------------------------------------------

VR::Cylinder::Cylinder(const VR::Cylinder& cyl,const CopyOp& copyop) : Prism(cyl,copyop)	{
	CylinderParams acp;
	cyl.getParams(acp);
	init(acp);
}

//----------------------------------------------------------

const char* VR::Cylinder::className() const	{
	return "Cylinder";
}

//----------------------------------------------------------

Object* VR::Cylinder::cloneType() const	{
	CylinderParams aCylinderParams;
	return new VR::Cylinder(aCylinderParams);
}

//----------------------------------------------------------

Object* VR::Cylinder::clone(const CopyOp& copyop) const	{
	CylinderParams pCylinderParams;
	this->getParams(pCylinderParams);

	VR::Cylinder * pCylinder = new VR::Cylinder(pCylinderParams);
	
	return pCylinder;
}

//----------------------------------------------------------

void VR::Cylinder::init(const CylinderParams & aCylinderParams)	{
	Prism::init(aCylinderParams);
}

//----------------------------------------------------------

string VR::Cylinder::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------

string VR::Cylinder::getSQLCommand() const {
	CylinderParams cylinderParams;
	getParams(cylinderParams);
	string strCylinderParams;

	strCylinderParams= tostr(cylinderParams.m_flRadius) + "_";
	strCylinderParams+= tostr(cylinderParams.m_flHeight) + "_";

	strCylinderParams+= tostr(cylinderParams.m_flPosX) + "_";
	strCylinderParams+= tostr(cylinderParams.m_flPosY) + "_";
	strCylinderParams+= tostr(cylinderParams.m_flPosZ) + "_";

	strCylinderParams += tostr(cylinderParams.m_flLenX) + "_";
	strCylinderParams += tostr(cylinderParams.m_flLenY) + "_";
	strCylinderParams += tostr(cylinderParams.m_flLenZ) + "_";

	strCylinderParams+= tostr(cylinderParams.m_flAngleXY) + "_";
	strCylinderParams+= tostr(cylinderParams.m_flAngleXZ) + "_";
	strCylinderParams+= tostr(cylinderParams.m_flAngleYZ);	

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += tostr(cylinderParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderMatrix, CylinderColor, CylinderTexture, PrimitiveID) VALUES("
		+ tostr(cylinderParams.m_nResolution) + ",'"
		+ strCylinderParams + "','"
		+ strColor + "','"
		+ cylinderParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Cylinder'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Cylinder::predefinedObject()	{
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------

string VR::Cylinder::prepareRowData(const string & astrParentName)	{
	CylinderParams cylinderParams;
	getParams(cylinderParams);

	string strCylinderParams =
	tostr(cylinderParams.m_nResolution) + "_" +
	tostr(cylinderParams.m_flRadius) + "_" +
	tostr(cylinderParams.m_flHeight) + "_" +

	tostr(cylinderParams.m_flPosX) + "_" +
	tostr(cylinderParams.m_flPosY) + "_" +
	tostr(cylinderParams.m_flPosZ) + "_" +

	tostr(cylinderParams.m_flLenX) + "_" +
	tostr(cylinderParams.m_flLenY) + "_" +
	tostr(cylinderParams.m_flLenZ) + "_" +

	tostr(cylinderParams.m_flAngleXY) + "_" +
	tostr(cylinderParams.m_flAngleXZ) + "_" +
	tostr(cylinderParams.m_flAngleYZ) + ";";	

	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += tostr(cylinderParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += tostr(cylinderParams.m_arrflRGBA[3]) + ";";

	strCylinderParams += strColor + cylinderParams.m_strFileNameTexture + ";" + astrParentName + ";";

	return strCylinderParams;
}