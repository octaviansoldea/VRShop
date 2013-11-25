#include <string>
#include <vector>
#include <iostream>

#include "VRAbstractGeomShape.h"
#include "VRPlate3D.h"

#include "StringManipulation.h"

#include "VRCupboard.h"

using namespace std;
using namespace osg;
using namespace VR;

CupboardParams::CupboardParams() :
m_flPosX(0.0), m_flPosY(0.0), m_flPosZ(0.0),
m_flScaleX(1.0), m_flScaleY(1.0), m_flScaleZ(1.0),
m_flAngleXY(0.0),m_flAngleXZ(0.0),m_flAngleYZ(0.0)	{
}

//-----------------------------------------------------------------------

Cupboard::Cupboard()	{
}

//-----------------------------------------------------------------------

void Cupboard::init(const CupboardParams & aCupboardParams)	{
	setScaling(aCupboardParams);
	setRotation(aCupboardParams);
	setPosition(aCupboardParams);

	Matrix matrix;
	matrix.set(1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0,	1);

	osg::Matrix cupboardMatrix = 
		matrix.translate(m_CupboardParams.m_flPosX, m_CupboardParams.m_flPosY, m_CupboardParams.m_flPosZ)
		*
		matrix.scale(m_CupboardParams.m_flScaleX, m_CupboardParams.m_flScaleY, m_CupboardParams.m_flScaleZ)
		*
		matrix.rotate(
			m_CupboardParams.m_flAngleYZ, osg::X_AXIS,
			m_CupboardParams.m_flAngleXZ, osg::Y_AXIS,
			m_CupboardParams.m_flAngleXY, osg::Z_AXIS)
		//*
		//matrix.translate(m_CupboardParams.m_flPosX, m_CupboardParams.m_flPosY, m_CupboardParams.m_flPosZ)
		;

	setMatrix(cupboardMatrix);
}

//-----------------------------------------------------------------------

void Cupboard::addPart(ref_ptr < Node > apNode) {
	addChild(apNode);

	AbstractGeomShape * aAbstractGeomShape = dynamic_cast<AbstractGeomShape*>(apNode.get());
	string strCommand = aAbstractGeomShape->getSQLCommand();

	m_arrSQLCommandLines.push_back(strCommand);
}

//-----------------------------------------------------------------------

void Cupboard::removePart(ref_ptr < Node > apNode) {
	removeChild(apNode);
}

//-----------------------------------------------------------------------

string Cupboard::getSQLFormat() const	{
	return ("");
}

//-----------------------------------------------------------------------

string Cupboard::getSQLCommand() const {
	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentID) "
		"VALUES ('Cupboard', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'))_";
	int nNumParts = m_arrSQLCommandLines.size();

	int nI;
	for (nI=0;nI<nNumParts-1;nI++)	{
		strSQLCommand += m_arrSQLCommandLines[nI] + "_";
	}
	strSQLCommand += m_arrSQLCommandLines[nNumParts-1];

	return(strSQLCommand);
}

//-----------------------------------------------------------------------

string Cupboard::setSQLCommand(const string & astrCommand)	{
	string strSetSQLCommand = astrCommand;

	string strPrimitiveItemIDs = "SELECT PrimitiveID, ItemID FROM PrimitiveItemList "
		"WHERE EquipmentItemID = 1";

	return strSetSQLCommand;
}

//-----------------------------------------------------------------------

void Cupboard::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);

	m_Cupboard = new Cupboard;
	CupboardParams cupboardParams;
	cupboardParams.m_flPosX = 0.5;
	cupboardParams.m_flPosY = 0.5;
	cupboardParams.m_flPosZ = 0.5;
	cupboardParams.m_flAngleXY = 90.0;
	cupboardParams.m_flScaleX = 1.5;

	for (vector<string>::iterator it = arrstrSQLData.begin(); it != arrstrSQLData.end()-1; it++)	{
		ref_ptr < Plate3D > pPlate = new Plate3D;
		pPlate->initFromSQLData(*it);
		m_Cupboard->addChild(pPlate);
	}
	m_Cupboard->init(cupboardParams);
}

//-----------------------------------------------------------------------

void Cupboard::setRotation(const CupboardParams & aCupboardParams)	{
	//Rotation goes counter-clockwise
	m_CupboardParams.m_flAngleXY = DegreesToRadians(aCupboardParams.m_flAngleXY);
	m_CupboardParams.m_flAngleXZ = DegreesToRadians(aCupboardParams.m_flAngleXZ);
	m_CupboardParams.m_flAngleYZ = DegreesToRadians(aCupboardParams.m_flAngleYZ);
}

//-----------------------------------------------------------------------

void Cupboard::setPosition(const CupboardParams & aCupboardParams)	{
	m_CupboardParams.m_flPosX = aCupboardParams.m_flPosX;
	m_CupboardParams.m_flPosY = aCupboardParams.m_flPosY;
	m_CupboardParams.m_flPosZ = aCupboardParams.m_flPosZ;
}

//-----------------------------------------------------------------------

void Cupboard::setScaling(const CupboardParams & aCupboardParams)	{
	m_CupboardParams.m_flScaleX = aCupboardParams.m_flScaleX;
	m_CupboardParams.m_flScaleY = aCupboardParams.m_flScaleY;
	m_CupboardParams.m_flScaleZ = aCupboardParams.m_flScaleZ;
}