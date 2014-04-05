#include "VRUntransformedPlate3D.h"
#include "VRPlate3D.h"

#include "BasicStringDefinitions.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace osg;
using namespace VR;

string Plate3D::m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Plate3D \
	(Plate3DID INTEGER PRIMARY KEY AUTOINCREMENT,\
	Plate3DMatrix TEXT,\
	Plate3DColor TEXT,\
	Plate3DTexture TEXT,\
	PrimitiveID INTEGER, \
	FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

//-----------------------------------------------------------------------

Plate3DParams::Plate3DParams() : AbstractGeomShapeParams()	{
}

//========================================================================

Plate3D::Plate3D(const Plate3DParams & aPlate3DParams) : AbstractGeomShape(aPlate3DParams)	{
	m_pUntransformedPlate3D = new UntransformedPlate3D();
	addChild(m_pUntransformedPlate3D);

	init(aPlate3DParams);
}

//-----------------------------------------------------------------------

Plate3D::Plate3D(const Plate3D& p3D,const CopyOp& copyop) : AbstractGeomShape(p3D,copyop)	{
	Plate3DParams p3DP;
	p3D.getParams(p3DP);
	setParams(p3DP);
}

//-----------------------------------------------------------------------

const char* Plate3D::className() const	{
	return "Plate3D";
}

//-----------------------------------------------------------------------

Object* Plate3D::cloneType() const	{
	Plate3DParams pPlate3DParams;
	return new Plate3D(pPlate3DParams);
}

//-----------------------------------------------------------------------

Object* Plate3D::clone(const CopyOp& copyop) const	{
	return new Plate3D(*this,copyop);
}

//-----------------------------------------------------------------------

void Plate3D::init(const Plate3DParams & aPlate3DParams)	{
	setParams(aPlate3DParams);

	Matrix & plate3DMatrix = calculateMatrix();
	setMatrix(plate3DMatrix);

	setColor(aPlate3DParams.m_arrflRGBA);
	if ((aPlate3DParams.m_strFileNameTexture != " ") && (aPlate3DParams.m_strFileNameTexture != ""))
		setTexture(aPlate3DParams.m_strFileNameTexture);

	setName("Plate3D");
}

//----------------------------------------------------------------------

void Plate3D::setColor(const std::vector < float > & aarrflColor)	{
	m_pUntransformedPlate3D->setColor(aarrflColor);
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const std::string & astrFileName) {
	m_pUntransformedPlate3D->setTexture(astrFileName);
}

//----------------------------------------------------------

string Plate3D::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

string Plate3D::getSQLCommand() const	{
	Plate3DParams plate3DParams;
	getParams(plate3DParams);

	string strPlate3DParams;
	strPlate3DParams = to_string((long double)plate3DParams.m_flPosX) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flPosY) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flPosZ) + "_";

	strPlate3DParams += to_string((long double)plate3DParams.m_flLenX) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flLenY) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flLenZ) + "_";

	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleYZ) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleXZ) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleXY);


	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)plate3DParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Plate3D (Plate3DMatrix, Plate3DColor, Plate3DTexture, PrimitiveID) VALUES('"
		+ strPlate3DParams + "','"
		+ strColor + "','"
		+ plate3DParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Plate3D'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Plate3D::initFromSQLData(const string & astrSQLData)	{
	Plate3DParams plate3DParams;
	string strSQLData = astrSQLData;

	vector <string> arrstrPlateParams = splitString(strSQLData,";");

	vector <string> arrstrMatrix = splitString(arrstrPlateParams[1],"_");
	vector <string> arrstrColor = splitString(arrstrPlateParams[2],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrMatrix[nI]));
	}

	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			plate3DParams.m_arrflRGBA[nI] = stof(arrstrColor[nI]);
		}
	}

	plate3DParams.m_flPosX = arrflMatrix[0];
	plate3DParams.m_flPosY = arrflMatrix[1];
	plate3DParams.m_flPosZ = arrflMatrix[2];

	plate3DParams.m_flLenX = arrflMatrix[3];
	plate3DParams.m_flLenY = arrflMatrix[4];
	plate3DParams.m_flLenZ = arrflMatrix[5];

	plate3DParams.m_flAngleYZ = arrflMatrix[6];
	plate3DParams.m_flAngleXZ = arrflMatrix[7];
	plate3DParams.m_flAngleXY = arrflMatrix[8];

	plate3DParams.m_strFileNameTexture = arrstrPlateParams[3];

	init(plate3DParams);
}

//----------------------------------------------------------------------

void Plate3D::predefinedObject()	{
	Plate3DParams plate3DParams;
	init(plate3DParams);
	setIsTargetPick(true);
}


//=====================================================================

string Plate3D::getObjectData(const std::string & astrParentName)	{
	Plate3DParams plate3DParams;
	getParams(plate3DParams);

	string strPlate3DParams;
	strPlate3DParams = to_string((long double)plate3DParams.m_flPosX) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flPosY) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flPosZ) + "_";

	strPlate3DParams += to_string((long double)plate3DParams.m_flLenX) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flLenY) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flLenZ) + "_";

	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleYZ) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleXZ) + "_";
	strPlate3DParams += to_string((long double)plate3DParams.m_flAngleXY) + ":";


	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += to_string((long double)plate3DParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += to_string((long double)plate3DParams.m_arrflRGBA[3]) + ":";

	strPlate3DParams += strColor;

	strPlate3DParams += plate3DParams.m_strFileNameTexture + ";";

	strPlate3DParams += astrParentName;

	return strPlate3DParams;
}