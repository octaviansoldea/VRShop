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
	m_pUntransformedPolyhedron = new UntransformedPolyhedron();

	init(aCylinderParams);
	setName("Cylinder");

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
	return new VR::Cylinder(*this,copyop);
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

	strCylinderParams= to_string((long double)cylinderParams.m_flRadius) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flHeight) + "_";

	strCylinderParams+= to_string((long double)cylinderParams.m_flPosX) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flPosY) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flPosZ) + "_";

	strCylinderParams += to_string((long double)cylinderParams.m_flLenX) + "_";
	strCylinderParams += to_string((long double)cylinderParams.m_flLenY) + "_";
	strCylinderParams += to_string((long double)cylinderParams.m_flLenZ) + "_";

	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleXY) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleXZ) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleYZ);	

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)cylinderParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Cylinder (CylinderRes, CylinderMatrix, CylinderColor, CylinderTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)cylinderParams.m_nResolution) + ",'"
		+ strCylinderParams + "','"
		+ strColor + "','"
		+ cylinderParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Cylinder'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void VR::Cylinder::predefinedObject()	{
	CylinderParams cylinderParams;
	init(cylinderParams);
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------

string VR::Cylinder::SQLFieldValues(const string & astrParentName)	{
	CylinderParams cylinderParams;
	getParams(cylinderParams);
	string strCylinderParams;

	strCylinderParams= to_string((long double)cylinderParams.m_flRadius) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flHeight) + "_";

	strCylinderParams+= to_string((long double)cylinderParams.m_flPosX) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flPosY) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flPosZ) + "_";

	strCylinderParams += to_string((long double)cylinderParams.m_flLenX) + "_";
	strCylinderParams += to_string((long double)cylinderParams.m_flLenY) + "_";
	strCylinderParams += to_string((long double)cylinderParams.m_flLenZ) + "_";

	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleXY) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleXZ) + "_";
	strCylinderParams+= to_string((long double)cylinderParams.m_flAngleYZ) + ";";	

	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += to_string((long double)cylinderParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += to_string((long double)cylinderParams.m_arrflRGBA[3]) + ";";

	strCylinderParams += strColor;

	strCylinderParams += cylinderParams.m_strFileNameTexture + ";";

	strCylinderParams += astrParentName + ";";

	return strCylinderParams;
}