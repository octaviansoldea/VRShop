#include "VRCylinder.h"

using namespace VR;
using namespace std;
using namespace osg;

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

string VR::Cylinder::getSQLCommand() const {
	Matrixd cylinderMatrix = getMatrix();
	string strMatrix4X4 = "'";
	int nI, nJ;

	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			strMatrix4X4 += to_string((long double)cylinderMatrix(nI,nJ)) + ";";
		}
	}
	strMatrix4X4 += "'";

	string strColor = "'";
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_CylinderParams.m_arrflRGBA[nI]) + ";";
	}
	strColor += "'";

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderMatrix, CylinderColor, CylinderTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_CylinderParams.m_nRes) + ","
		+ strMatrix4X4 + ","
		+ strColor + ",'"
		+ m_CylinderParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Cylinder'))";

	return(strSQLCommand);
}
