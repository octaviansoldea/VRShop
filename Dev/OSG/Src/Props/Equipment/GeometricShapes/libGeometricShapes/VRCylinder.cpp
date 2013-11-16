#include "VRCylinder.h"

using namespace VR;
using namespace std;

CylinderParams::CylinderParams() {
	m_flRadius = 1.0; m_flHeight = 1.0; m_nRes = 20;
	m_flPosX = 0.0; m_flPosY = 0.0; m_flPosZ = 0.0;

	m_pchFileName = "";

	m_arrflRGBA[0] = 1.0;
	m_arrflRGBA[1] = 0.0;
	m_arrflRGBA[2] = 0.0;
	m_arrflRGBA[3] = 1.0;
}

//-----------------------------------------------------------------------

VR::Cylinder::Cylinder()	{
}

//----------------------------------------------------------

VR::Cylinder::Cylinder(const CylinderParams & aCylinderParams) : Prism(aCylinderParams)	{
}

//----------------------------------------------------------

string VR::Cylinder::getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const {
	const CylinderParams & aCylinderParams = static_cast<const CylinderParams&>(aAbstractGeomShapeParams);

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderRadius, CylinderHeight, PrimitiveID) VALUES("
		+ to_string((_Longlong)aCylinderParams.m_nRes) + ","
		+ to_string((long double)aCylinderParams.m_flRadius) + ","
		+ to_string((long double)aCylinderParams.m_flHeight) + ","
		+ to_string((_Longlong)1) + ")";
	return(strSQLCommand);
}
