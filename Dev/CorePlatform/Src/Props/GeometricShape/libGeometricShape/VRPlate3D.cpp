#include "VRUntransformedPlate3D.h"
#include "VRPlate3D.h"

#include "BasicStringDefinitions.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace osg;
using namespace VR;

//===================================================================

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

	setName("Plate3D_"+tostr(getAbstractObjectNo()));
	init(aPlate3DParams);
}

//-----------------------------------------------------------------------

Plate3D::Plate3D(const Plate3D& p3D,const CopyOp& copyop) : AbstractGeomShape(p3D,copyop)	{
	m_pUntransformedPlate3D = new UntransformedPlate3D();
	addChild(m_pUntransformedPlate3D);

	Plate3DParams aPlate3DParams;
	p3D.getParams(aPlate3DParams);
	init(aPlate3DParams);

	setName("Plate3D_"+tostr(getAbstractObjectNo()));
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
	Plate3DParams pPlate3DParams;
	this->getParams(pPlate3DParams);

	Plate3D * pPlate3D = new Plate3D(pPlate3DParams);

	return pPlate3D;
}

//-----------------------------------------------------------------------

void Plate3D::init(const Plate3DParams & aPlate3DParams)	{
	setParams(aPlate3DParams);

	Matrix plate3DMatrix = calculateMatrix();
	setMatrix(plate3DMatrix);

	setColor(aPlate3DParams.m_arrflRGBA);
	if ((aPlate3DParams.m_strFileNameTexture != " ") && (aPlate3DParams.m_strFileNameTexture != ""))
		setTexture(aPlate3DParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void Plate3D::setColor(const std::vector < float > & aarrflColor)	{
	m_arrflRGBA = aarrflColor;	

	UntransformedPlate3D::Surface surface;
	surface.m_bIsColor=true;
	surface.m_PlateSide = UntransformedPlate3D::PlateSide::ALL;
	surface.m_vecColor=m_arrflRGBA;
	m_pUntransformedPlate3D->setTextureOrColor(surface);
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const std::string & astrFileName) {
	m_strFileNameTexture = astrFileName;
	
	UntransformedPlate3D::Surface surface;
	surface.m_bIsColor=false;
	surface.m_PlateSide = UntransformedPlate3D::PlateSide::ALL;
	surface.m_strFileName=m_strFileNameTexture;
	m_pUntransformedPlate3D->setTextureOrColor(surface);
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
	strPlate3DParams = tostr((long double)plate3DParams.m_flPosX) + "_" +
	tostr((long double)plate3DParams.m_flPosY) + "_" +
	tostr((long double)plate3DParams.m_flPosZ) + "_" +

	tostr((long double)plate3DParams.m_flLenX) + "_" +
	tostr((long double)plate3DParams.m_flLenY) + "_" +
	tostr((long double)plate3DParams.m_flLenZ) + "_" +

	tostr((long double)plate3DParams.m_flAngleYZ) + "_" +
	tostr((long double)plate3DParams.m_flAngleXZ) + "_" +
	tostr((long double)plate3DParams.m_flAngleXY);


	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += tostr((long double)plate3DParams.m_arrflRGBA[nI]) + "_";
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
	string strSQLData = astrSQLData;

	vector <string> arrstrPlateParams = splitString(strSQLData,";");
	initFromSQLData(arrstrPlateParams);
}

//----------------------------------------------------------------------

void Plate3D::initFromSQLData(vector<string> & avecstrSQLData)	{
	vector <string> arrstrPlateParams = avecstrSQLData;

	Plate3DParams plate3DParams;

	vector <string> arrstrMatrix = splitString(arrstrPlateParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrPlateParams[3],"_");

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

	plate3DParams.m_strFileNameTexture = arrstrPlateParams[4];

	init(plate3DParams);
}

//----------------------------------------------------------------------

void Plate3D::predefinedObject()	{
	setIsTargetPick(true);
}


//=====================================================================

string Plate3D::prepareRowData(const std::string & astrParentName)	{
	Plate3DParams plate3DParams;
	getParams(plate3DParams);

	string strPlate3DParams;
	strPlate3DParams = to_string((long double)plate3DParams.m_flPosX) + "_" +
	to_string((long double)plate3DParams.m_flPosY) + "_" +
	to_string((long double)plate3DParams.m_flPosZ) + "_" +

	to_string((long double)plate3DParams.m_flLenX) + "_" +
	to_string((long double)plate3DParams.m_flLenY) + "_" +
	to_string((long double)plate3DParams.m_flLenZ) + "_" +

	to_string((long double)plate3DParams.m_flAngleYZ) + "_" +
	to_string((long double)plate3DParams.m_flAngleXZ) + "_" +
	to_string((long double)plate3DParams.m_flAngleXY) + ";";


	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += to_string((long double)plate3DParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += to_string((long double)plate3DParams.m_arrflRGBA[3]) + ";";

	strPlate3DParams += strColor + plate3DParams.m_strFileNameTexture + ";" + astrParentName;

	return strPlate3DParams;
}

//--------------------------------------------------------------------------

void Plate3D::setParams(const Plate3DParams & aPlate3DParams) {
	AbstractGeomShape::setParams(aPlate3DParams);
}

//--------------------------------------------------------------------------

void Plate3D::getParams(Plate3DParams & aPlate3DParams) const {
	AbstractGeomShape::getParams(aPlate3DParams);
}
