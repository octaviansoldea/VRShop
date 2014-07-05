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

Cupboard::Cupboard(const CupboardParams & aCupboardParams) : Furniture(aCupboardParams)	{
	setParams(aCupboardParams);

	setName("Cupboard_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

Cupboard::Cupboard(const Cupboard& cup,const CopyOp& copyop) : Furniture(cup, copyop)	{
	CupboardParams aCup;
	cup.getParams(aCup);
	setParams(aCup);

	setName("Cupboard_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

const char* Cupboard::className() const	{
	return "Cupboard";
}

//-----------------------------------------------------------------------

Object* Cupboard::cloneType() const	{
	CupboardParams aCup;
	return new Cupboard(aCup);
}

//-----------------------------------------------------------------------

Object* Cupboard::clone(const CopyOp& copyop) const	{
	return new Cupboard(*this,copyop);
}

//-----------------------------------------------------------------------

void Cupboard::init(const CupboardParams & aCupboardParams)	{
	setParams(aCupboardParams);

	Matrix & cupboardMatrix = calculateMatrix();
	setMatrix(cupboardMatrix);
}

//-----------------------------------------------------------------------

string Cupboard::getSQLCommand() const {
	CupboardParams cupboardParams;
	getParams(cupboardParams);

	string strCupboardParams;
	strCupboardParams = to_string((long double)cupboardParams.m_flPosX) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flPosY) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flPosZ) + "_";

	strCupboardParams += to_string((long double)cupboardParams.m_flLenX) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flLenY) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flLenZ) + "_";

	strCupboardParams += to_string((long double)cupboardParams.m_flAngleXY) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flAngleXZ) + "_";
	strCupboardParams += to_string((long double)cupboardParams.m_flAngleYZ);

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
	CupboardParams cupboardParams;
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);
	vector <string> arrstrCupboardParams = splitString(arrstrSQLData[0],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrCupboardParams[nI]));
	}

	cupboardParams.m_flPosX = arrflMatrix[0];
	cupboardParams.m_flPosY = arrflMatrix[1];
	cupboardParams.m_flPosZ = arrflMatrix[2];

	cupboardParams.m_flLenX = arrflMatrix[3];
	cupboardParams.m_flLenY = arrflMatrix[4];
	cupboardParams.m_flLenZ = arrflMatrix[5];

	cupboardParams.m_flAngleXY = arrflMatrix[6];
	cupboardParams.m_flAngleXZ = arrflMatrix[7];
	cupboardParams.m_flAngleYZ = arrflMatrix[8];

	ref_ptr < AbstractGeomShape > pAbstractGeomShape;
	for (auto it = arrstrSQLData.begin()+1; it != arrstrSQLData.end()-1; it++)	{
		if(isAtEndOfString(*it, "Plate3D"))	{
			Plate3DParams p3Dp;
			pAbstractGeomShape = new Plate3D(p3Dp);
		} else if(isAtEndOfString(*it, "Cylinder"))	{
			CylinderParams cP;
			pAbstractGeomShape = new VR::Cylinder(cP);
		} else if(isAtEndOfString(*it, "Prism"))	{
			PrismParams pP;
			pAbstractGeomShape = new Prism(pP);
		} else if(isAtEndOfString(*it, "Sphere"))	{
			SphereParams sP;
			pAbstractGeomShape = new Sphere(sP);
		}

		pAbstractGeomShape->initFromSQLData(*it);
		addChild(pAbstractGeomShape);
	}
	init(cupboardParams);
}

//-----------------------------------------------------------------------

void Cupboard::predefinedObject()	{
	CupboardParams cupboardParams;
	cupboardParams.m_flAngleXY = 0;
	cupboardParams.m_flAngleXZ = 0;
	cupboardParams.m_flAngleYZ = 0;

	ref_ptr < Plate3D > pPlate3D;
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

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);
	

	//Left side
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = -2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.0;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Right side
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.0;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Back side
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0.475;
	aPlate3DParams.m_flPosZ = 1.0;
	aPlate3DParams.m_strFileNameTexture = "../../Resources/Textures/lz.rgb";

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//shelf 1
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0.675;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);


	//shelf 2
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1.375;
	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//shelf 3
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 2;
	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	init(cupboardParams);
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------
