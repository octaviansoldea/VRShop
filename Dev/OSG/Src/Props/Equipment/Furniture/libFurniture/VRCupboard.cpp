#include <string>
#include <vector>
#include <iostream>

#include "VRAbstractGeomShape.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRPrism.h"
#include "VRUntransformedSphere.h"

#include "StringManipulation.h"

#include "VRCupboard.h"

using namespace std;
using namespace osg;
using namespace VR;

CupboardParams::CupboardParams()	{
}

//=======================================================================

Cupboard::Cupboard()	{
}

//-----------------------------------------------------------------------

Cupboard::Cupboard(const CupboardParams & aCupboardParams) : Furniture(aCupboardParams)	{
	m_CupboardParams = aCupboardParams;
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
		matrix.scale(m_AbstractObjectParams.m_flScaleX, m_AbstractObjectParams.m_flScaleY, m_AbstractObjectParams.m_flScaleZ)
		*
		matrix.rotate(
			m_AbstractObjectParams.m_flAngleYZ, osg::X_AXIS,
			m_AbstractObjectParams.m_flAngleXZ, osg::Y_AXIS,
			m_AbstractObjectParams.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(m_AbstractObjectParams.m_flPosX, m_AbstractObjectParams.m_flPosY, m_AbstractObjectParams.m_flPosZ)
	;
	
	setMatrix(cupboardMatrix);
	setName(Furniture::getParentName() + ":Cupboard");
}

//-----------------------------------------------------------------------

string Cupboard::setSQLCommand(const string & astrCommand)	{
	string strSetSQLCommand = astrCommand;

	string strPrimitiveItemIDs = "SELECT PrimitiveID, ItemID FROM PrimitiveItemList "
		"WHERE EquipmentItemID = 1";

	return strSetSQLCommand;
}

//-----------------------------------------------------------------------

string Cupboard::getSQLCommand() const {
	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentID) "
		"VALUES ('Cupboard', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'))_";
	int nNumParts = m_arrSQLCommandLines.size();

	for (auto it = m_arrSQLCommandLines.begin(); it != m_arrSQLCommandLines.end()-1; it++)	{
		strSQLCommand += *it + "_";
	}
	strSQLCommand += m_arrSQLCommandLines[nNumParts-1];

	return(strSQLCommand);
}

//-----------------------------------------------------------------------

void Cupboard::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);

	CupboardParams cupboardParams;
	cupboardParams.m_flPosX = 0.5;
	cupboardParams.m_flPosY = 0.5;
	cupboardParams.m_flPosZ = 0.5;
	cupboardParams.m_flAngleXY = 45.0;
	cupboardParams.m_flScaleX = 1;

	for (auto it = arrstrSQLData.begin(); it != arrstrSQLData.end()-1; it++)	{
		if(isAtEndOfString(*it, "Plate3D"))	{
			ref_ptr < Plate3D > pPlate = new Plate3D;
			pPlate->initFromSQLData(*it);
			addChild(pPlate);
		}
		else if(isAtEndOfString(*it, "Cylinder"))	{
			ref_ptr < Cylinder > pCylinder = new Cylinder;
			pCylinder->initFromSQLData(*it);
			addChild(pCylinder);
		}
		else if(isAtEndOfString(*it, "Prism"))	{
			ref_ptr < Prism > pPrism = new Prism;
			pPrism->initFromSQLData(*it);
			addChild(pPrism);
		}
		else if(isAtEndOfString(*it, "Sphere"))	{
			ref_ptr < UntransformedSphere > pSphere = new UntransformedSphere;
			pSphere->initFromSQLData(*it);
			addChild(pSphere);
		}
	}
	init(cupboardParams);
}

//-----------------------------------------------------------------------
