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
m_pchFileName("")	{
	m_flRGBA[0] = 1.0;
	m_flRGBA[1] = 0.0;
	m_flRGBA[2] = 0.0;
	m_flRGBA[3] = 1.0;
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

	setColor(aPlate3DParams.m_flRGBA);
	setTexture(aPlate3DParams.m_pchFileName);
}

//----------------------------------------------------------------------

void Plate3D::setColor(const float aarrflColor[4])	{
	m_pUntransformedPlate3D->setColor(aarrflColor);
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const char * apchFileName)	{
	m_pUntransformedPlate3D->setTexture(apchFileName);
}

//----------------------------------------------------------------------

std::string Plate3D::getSQLCommand() const	{
	string strSQLCommand = "INSERT INTO Parallelepiped (ParallelepipedWidth, ParallelepipedDepth, ParallelepipedHeight, PrimitiveID) VALUES("
		+ to_string((_Longlong)1.0) + ","
		+ to_string((_Longlong)1.0) + ","
		+ to_string((_Longlong)3.0) + ","
		+ to_string((_Longlong)2) + ")";
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
