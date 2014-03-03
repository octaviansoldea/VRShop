#include <fstream>
#include <ostream>

#include "VRAbstractGeomShape.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRPrism.h"
#include "VRSphere.h"

#include "BasicStringDefinitions.h"

#include "VRCupboard.h"

using namespace std;
using namespace osg;
using namespace VR;

CupboardParams::CupboardParams() : FurnitureParams()	{
}

//=======================================================================

Cupboard::Cupboard() : Furniture(new CupboardParams())	{
	setName("Cupboard");
}

//-----------------------------------------------------------------------

Cupboard::Cupboard(CupboardParams * apCupboardParams) : Furniture(apCupboardParams)	{
	CupboardParams * pCupboardParams = dynamic_cast<CupboardParams*>(m_pAbstractObjectParams);
	init(pCupboardParams);
}

//-----------------------------------------------------------------------

const char* Cupboard::className() const	{
	return "Cupboard";
}

//-----------------------------------------------------------------------

void Cupboard::init(FurnitureParams * apFurnitureParams)	{
	CupboardParams * pCupboardParams = dynamic_cast<CupboardParams*>(apFurnitureParams);
	apFurnitureParams = dynamic_cast<FurnitureParams*>(m_pAbstractObjectParams);

	setScaling(pCupboardParams->m_flLenX, pCupboardParams->m_flLenY, pCupboardParams->m_flLenZ);
	setRotation(pCupboardParams->m_flAngleYZ, pCupboardParams->m_flAngleXZ, pCupboardParams->m_flAngleXY);
	setPosition(pCupboardParams->m_flPosX, pCupboardParams->m_flPosY, pCupboardParams->m_flPosZ);

	Matrix & cupboardMatrix = calculateMatrix();
	setMatrix(cupboardMatrix);

	setName("Cupboard");
}

//-----------------------------------------------------------------------

string Cupboard::getSQLCommand() const {
	CupboardParams * pCupboardParams = dynamic_cast<CupboardParams*>(m_pAbstractObjectParams);

	string strCupboardParams;
	strCupboardParams = to_string((long double)pCupboardParams->m_flPosX) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flPosY) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flPosZ) + "_";

	strCupboardParams += to_string((long double)pCupboardParams->m_flLenX) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flLenY) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flLenZ) + "_";

	strCupboardParams += to_string((long double)pCupboardParams->m_flAngleXY) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flAngleXZ) + "_";
	strCupboardParams += to_string((long double)pCupboardParams->m_flAngleYZ);

	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentItemParams, EquipmentID) "
		"VALUES ('Cupboard', '" + strCupboardParams + "', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'));";

	vector < string >::const_iterator it = m_arrSQLCommandLines.begin();
	for (it; it != m_arrSQLCommandLines.end(); it++)	{
		strSQLCommand += *it;
	}

	return(strSQLCommand);
}

//-----------------------------------------------------------------------

void Cupboard::initFromSQLData(const string & astrSQLData)	{
	CupboardParams * pCupboardParams = dynamic_cast<CupboardParams*>(m_pAbstractObjectParams);
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);
	vector <string> arrstrCupboardParams = splitString(arrstrSQLData[0],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrCupboardParams[nI]));
	}

	pCupboardParams->m_flPosX = arrflMatrix[0];
	pCupboardParams->m_flPosY = arrflMatrix[1];
	pCupboardParams->m_flPosZ = arrflMatrix[2];

	pCupboardParams->m_flLenX = arrflMatrix[3];
	pCupboardParams->m_flLenY = arrflMatrix[4];
	pCupboardParams->m_flLenZ = arrflMatrix[5];

	pCupboardParams->m_flAngleXY = arrflMatrix[6];
	pCupboardParams->m_flAngleXZ = arrflMatrix[7];
	pCupboardParams->m_flAngleYZ = arrflMatrix[8];

	ref_ptr < AbstractGeomShape > pAbstractGeomShape;
	for (auto it = arrstrSQLData.begin()+1; it != arrstrSQLData.end()-1; it++)	{
		if(isAtEndOfString(*it, "Plate3D"))
			pAbstractGeomShape = new Plate3D;
		else if(isAtEndOfString(*it, "Cylinder"))
			pAbstractGeomShape = new Cylinder;
		else if(isAtEndOfString(*it, "Prism"))
			pAbstractGeomShape = new Prism;
		else if(isAtEndOfString(*it, "Sphere"))
			pAbstractGeomShape = new Sphere;

		pAbstractGeomShape->initFromSQLData(*it);
		addChild(pAbstractGeomShape);
	}
	init(pCupboardParams);
}

//-----------------------------------------------------------------------

void Cupboard::predefinedObject()	{
	CupboardParams * pCupboardParams = dynamic_cast<CupboardParams*>(m_pAbstractObjectParams);

	ref_ptr < Plate3D > pPlate3D = new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0.0;
	aPlate3DParams.m_flPosY = 0.0;
	aPlate3DParams.m_flPosZ = 0.0;
	aPlate3DParams.m_arrflRGBA[0] = 0.85;
	aPlate3DParams.m_arrflRGBA[1] = 0.0;
	aPlate3DParams.m_arrflRGBA[2] = 0.85;
	aPlate3DParams.m_arrflRGBA[3] = 1;

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
	aPlate3DParams.m_strFileNameTexture = "../../Resources/Textures/lz.rgb";
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

	init(pCupboardParams);
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------

void Cupboard::print(std::ostream & os) const	{
	os << "Object name: " << getName() << endl;
	int nI, nJ;
	os << "GetMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << getMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;
	os << "calculateMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << calculateMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;

	os << "Child index: " << getChildIndex(this) << endl;

	os << "========================================" << endl;
}