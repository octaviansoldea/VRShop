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

CylinderParams::CylinderParams() {
	m_nRes = 20;
}

//-----------------------------------------------------------------------

VR::Cylinder::Cylinder()	{
}

//----------------------------------------------------------

VR::Cylinder::Cylinder(const CylinderParams & aCylinderParams) : Prism(aCylinderParams)	{
	m_CylinderParams = aCylinderParams;
}

//----------------------------------------------------------

string VR::Cylinder::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------

string VR::Cylinder::getSQLCommand() const {
	string strCylinderParams;

	strCylinderParams= to_string((long double)m_CylinderParams.m_flRadius) + "_";
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flHeight) + "_";

	strCylinderParams+= to_string((long double)m_CylinderParams.m_flPosX) + "_";
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flPosY) + "_";
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flPosZ) + "_";

	strCylinderParams += to_string((long double)m_CylinderParams.m_flLenX) + "_";
	strCylinderParams += to_string((long double)m_CylinderParams.m_flLenY) + "_";
	strCylinderParams += to_string((long double)m_CylinderParams.m_flLenZ) + "_";
												 
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flAngleXY) + "_";
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flAngleXZ) + "_";
	strCylinderParams+= to_string((long double)m_CylinderParams.m_flAngleYZ);	

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_CylinderParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderMatrix, CylinderColor, CylinderTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_CylinderParams.m_nRes) + ",'"
		+ strCylinderParams + "','"
		+ strColor + "','"
		+ m_CylinderParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Cylinder'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Cylinder::predefinedObject()	{
	init(m_CylinderParams);
	setIsTargetPick(true);
}
