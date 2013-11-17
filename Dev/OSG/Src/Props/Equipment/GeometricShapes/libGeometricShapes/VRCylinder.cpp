#include "VRCylinder.h"

using namespace VR;
using namespace std;

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
	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderRadius, CylinderHeight, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_CylinderParams.m_nRes) + ","
		+ to_string((long double)m_CylinderParams.m_flRadius) + ","
		+ to_string((long double)m_CylinderParams.m_flHeight) + ","
		+ to_string((_Longlong)1) + ")";
	return(strSQLCommand);
}
