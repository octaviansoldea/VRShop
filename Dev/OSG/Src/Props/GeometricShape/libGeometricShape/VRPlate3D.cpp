#include "VRUntransformedPlate3D.h"
#include "VRPlate3D.h"

#include "StringManipulation.h"

#include <string>
#include <iostream>

using namespace std;
using namespace osg;
using namespace VR;

string Plate3D::m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Plate3D "
	"(Plate3DID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"Plate3DMatrix TEXT,"
	"Plate3DColor TEXT,"
	"Plate3DTexture TEXT,"
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

//-----------------------------------------------------------------------

Plate3DParams::Plate3DParams() : 
m_strFileNameTexture(" ")	{
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
}

//-----------------------------------------------------------------------

Plate3D::Plate3D()	{
	m_pUntransformedPlate3D = new UntransformedPlate3D();
	addChild(m_pUntransformedPlate3D);
}

//-----------------------------------------------------------------------

void Plate3D::init(const AbstractGeomShapeParams & aAbstractGeomShapeParams)	{
	m_Plate3DParams = static_cast<const Plate3DParams&>(aAbstractGeomShapeParams);

	Matrix matrix;
	matrix.set(m_Plate3DParams.m_flLenX,	0,							0,						  0,
			   0,							m_Plate3DParams.m_flLenY,	0,						  0,
			   0,							0,							m_Plate3DParams.m_flLenZ, 0,
			   m_Plate3DParams.m_flPosX,	m_Plate3DParams.m_flPosY,	m_Plate3DParams.m_flPosZ, 1);

	setMatrix(matrix);

	setColor(m_Plate3DParams.m_arrflRGBA);
	if ((m_Plate3DParams.m_strFileNameTexture != " ") && (m_Plate3DParams.m_strFileNameTexture != ""))
		setTexture(m_Plate3DParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void Plate3D::setColor(const std::vector < float > & aarrflColor)	{
	m_Plate3DParams.m_arrflRGBA = aarrflColor;
	m_pUntransformedPlate3D->setColor(m_Plate3DParams.m_arrflRGBA);
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const std::string & astrFileName) {
	m_Plate3DParams.m_strFileNameTexture = astrFileName;
	m_pUntransformedPlate3D->setTexture(m_Plate3DParams.m_strFileNameTexture);
}

//----------------------------------------------------------

string Plate3D::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

std::string Plate3D::getSQLCommand() const	{
	string strPlate3DParams;
	strPlate3DParams = to_string((long double)m_Plate3DParams.m_flPosX) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flPosY) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flPosZ) + "_";
							   					 
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flLenX) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flLenY) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flLenZ) + "_";
												 
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flAngleXY) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flAngleXZ) + "_";
	strPlate3DParams += to_string((long double)m_Plate3DParams.m_flAngleYZ);


	int nI;
	string strColor = "'";
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_Plate3DParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += "'";

	string strSQLCommand = "INSERT INTO Plate3D (Plate3DMatrix, Plate3DColor, Plate3DTexture, PrimitiveID) VALUES('"
		+ strPlate3DParams + "',"
		+ strColor + ",'"
		+ m_Plate3DParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Plate3D'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Plate3D::initFromSQLData(const string & astrSQLData)	{
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
		vector < float > arrflColor;
		for (nI=0;nI<4;nI++)	{
			m_Plate3DParams.m_arrflRGBA[nI] = stof(arrstrColor[nI]);
		}
	}

	m_Plate3DParams.m_flPosX = arrflMatrix[0];
	m_Plate3DParams.m_flPosY = arrflMatrix[1];
	m_Plate3DParams.m_flPosZ = arrflMatrix[2];

	m_Plate3DParams.m_flLenX = arrflMatrix[3];
	m_Plate3DParams.m_flLenY = arrflMatrix[4];
	m_Plate3DParams.m_flLenZ = arrflMatrix[5];

	m_Plate3DParams.m_strFileNameTexture = arrstrPlateParams[3];

	init(m_Plate3DParams);
}

//----------------------------------------------------------------------

void Plate3D::predefinedObject()	{
	init(m_Plate3DParams);
	setIsTargetPick(true);
}
