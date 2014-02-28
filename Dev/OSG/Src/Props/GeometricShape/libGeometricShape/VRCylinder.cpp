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
	m_nRes = 20;
}

//-----------------------------------------------------------------------

VR::Cylinder::Cylinder() : Prism(new CylinderParams())	{
	CylinderParams * pCylinderParams = dynamic_cast<CylinderParams*>(m_pAbstractObjectParams);

	m_pUntransformedPolygon3D = new UntransformedPolygon3D(*pCylinderParams);
	addChild(m_pUntransformedPolygon3D);
}

//----------------------------------------------------------

VR::Cylinder::Cylinder(CylinderParams * apCylinderParams) : Prism(apCylinderParams)	{
	m_pUntransformedPolygon3D = new UntransformedPolygon3D();

	CylinderParams * pCylinderParams = dynamic_cast<CylinderParams*>(m_pAbstractObjectParams);
	init(*pCylinderParams);
}

//----------------------------------------------------------

string VR::Cylinder::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------

string VR::Cylinder::getSQLCommand() const {
	CylinderParams * pCylinderParams = dynamic_cast<CylinderParams*>(m_pAbstractObjectParams);
	string strCylinderParams;

	strCylinderParams= to_string((long double)pCylinderParams->m_flRadius) + "_";
	strCylinderParams+= to_string((long double)pCylinderParams->m_flHeight) + "_";

	strCylinderParams+= to_string((long double)pCylinderParams->m_flPosX) + "_";
	strCylinderParams+= to_string((long double)pCylinderParams->m_flPosY) + "_";
	strCylinderParams+= to_string((long double)pCylinderParams->m_flPosZ) + "_";

	strCylinderParams += to_string((long double)pCylinderParams->m_flLenX) + "_";
	strCylinderParams += to_string((long double)pCylinderParams->m_flLenY) + "_";
	strCylinderParams += to_string((long double)pCylinderParams->m_flLenZ) + "_";

	strCylinderParams+= to_string((long double)pCylinderParams->m_flAngleXY) + "_";
	strCylinderParams+= to_string((long double)pCylinderParams->m_flAngleXZ) + "_";
	strCylinderParams+= to_string((long double)pCylinderParams->m_flAngleYZ);	

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)pCylinderParams->m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderMatrix, CylinderColor, CylinderTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)pCylinderParams->m_nRes) + ",'"
		+ strCylinderParams + "','"
		+ strColor + "','"
		+ pCylinderParams->m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Cylinder'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Cylinder::predefinedObject()	{
	CylinderParams * pCylinderParams = dynamic_cast<CylinderParams*>(m_pAbstractObjectParams);
	init(*pCylinderParams);
	setIsTargetPick(true);
}
