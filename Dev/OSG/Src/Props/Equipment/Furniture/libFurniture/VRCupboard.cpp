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

void Cupboard::init(const FurnitureParams & aFurnitureParams)	{

	setScaling(aFurnitureParams);
	setRotation(aFurnitureParams);
	setPosition(aFurnitureParams);

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
	setName(Furniture::getName() + ":Cupboard");
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
	cupboardParams.m_flPosX = 0.0;
	cupboardParams.m_flPosY = 0.0;
	cupboardParams.m_flPosZ = 0.0;
	cupboardParams.m_flAngleXY = 90.0;
	cupboardParams.m_flScaleX = 1;

	ref_ptr < AbstractGeomShape > pAbstractGeomShape;
	for (auto it = arrstrSQLData.begin(); it != arrstrSQLData.end()-1; it++)	{
		if(isAtEndOfString(*it, "Plate3D"))
			pAbstractGeomShape = new Plate3D;
		else if(isAtEndOfString(*it, "Cylinder"))
			pAbstractGeomShape = new Cylinder;
		else if(isAtEndOfString(*it, "Prism"))
			pAbstractGeomShape = new Prism;
		else if(isAtEndOfString(*it, "Sphere"))
			pAbstractGeomShape = new UntransformedSphere;

		pAbstractGeomShape->initFromSQLData(*it);
		addChild(pAbstractGeomShape);
	}
	init(cupboardParams);
}

//-----------------------------------------------------------------------

void Cupboard::predefinedObject()	{
	ref_ptr < Plate3D > pPlate3D = new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0.0;
	aPlate3DParams.m_flPosY = 0.0;
	aPlate3DParams.m_flPosZ = 0.0;
	aPlate3DParams.m_arrflRGBA[0] = 0.15;
	aPlate3DParams.m_arrflRGBA[1] = 0.85;
	aPlate3DParams.m_arrflRGBA[2] = 0.45;
	aPlate3DParams.m_arrflRGBA[3] = 1;
//	aPlate3DParams.m_strFileNameTexture = "../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);
	

	//Left side
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = -2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Right side
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Back side
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0.475;
	aPlate3DParams.m_flPosZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//shelf 1
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0.675;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);


	//shelf 2
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.375;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//shelf 3
	pPlate3D = new Plate3D;
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 2;
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	init(m_FurnitureParams);
	setIsTargetPick(true);
}