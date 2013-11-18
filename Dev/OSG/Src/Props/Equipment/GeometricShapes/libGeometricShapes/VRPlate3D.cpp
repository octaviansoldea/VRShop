#include "VRUntransformedPlate3D.h"
#include "VRPlate3D.h"

#include "StringManipulation.h"

#include <string>
#include <iostream>

using namespace std;
using namespace osg;
using namespace VR;

Plate3DParams::Plate3DParams() : 
m_flLenX(1.0), m_flLenY(1.0), m_flLenZ(1.0),
m_flPosX(0.0), m_flPosY(0.0), m_flPosZ(0.0),
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
	const Plate3DParams & aPlate3DParams = static_cast<const Plate3DParams&>(aAbstractGeomShapeParams);

	Matrix matrix;
	matrix.set(aPlate3DParams.m_flLenX, 0,						 0,						  0,
			   0,						aPlate3DParams.m_flLenY, 0,						  0,
			   0,						0,						 aPlate3DParams.m_flLenZ, 0,
			   aPlate3DParams.m_flPosX, aPlate3DParams.m_flPosY, aPlate3DParams.m_flPosZ, 1);
	setMatrix(matrix);

	m_Plate3DParams = aPlate3DParams;
}

//----------------------------------------------------------------------
void Plate3D::setColor(const std::vector < float > & aarrflColor)	{
	m_pUntransformedPlate3D->setColor(aarrflColor);
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const std::string & astrFileName) {
	m_pUntransformedPlate3D->setTexture(astrFileName);
}

//----------------------------------------------------------------------

std::string Plate3D::getSQLCommand() const	{

	Matrixd plate3DMatrix = getMatrix();
	string strMatrix4X4 = "'";
	int nI, nJ;

	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			strMatrix4X4 += to_string((long double)plate3DMatrix(nI,nJ)) + ";";
		}
	}
	strMatrix4X4 += "'";

	string strColor = "'";
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_Plate3DParams.m_arrflRGBA[nI]) + ";";
	}
	strColor += "'";

	string strSQLCommand = "INSERT INTO Plate3D (Plate3DMatrix, Plate3DColor, Plate3DTexture, PrimitiveID) VALUES("
		+ strMatrix4X4 + ","
		+ strColor + ",'"
		+ m_Plate3DParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Plate3D'))";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Plate3D::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
	
	vector <string> vecstrSphereParams = splitString(strSQLData," ");

	Plate3DParams p3DP;
	p3DP.m_flLenX = stof(vecstrSphereParams.at(0));
	p3DP.m_flLenY = stof(vecstrSphereParams.at(1));
	p3DP.m_flLenZ = stof(vecstrSphereParams.at(2));

	init(p3DP);
}
