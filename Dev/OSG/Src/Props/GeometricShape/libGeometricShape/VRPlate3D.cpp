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
	"CREATE TABLE IF NOT EXISTS Plate3D "
	"(Plate3DID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"Plate3DMatrix TEXT,"
	"Plate3DColor TEXT,"
	"Plate3DTexture TEXT,"
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

//-----------------------------------------------------------------------

Plate3DParams::Plate3DParams() : AbstractGeomShapeParams()	{
}

//========================================================================

Plate3D::Plate3D() : AbstractGeomShape(new Plate3DParams())	{
	m_pUntransformedPlate3D = new UntransformedPlate3D();
	addChild(m_pUntransformedPlate3D);

	setName("Plate3D");
}

//-----------------------------------------------------------------------

Plate3D::Plate3D(Plate3DParams * apPlate3DParams) : AbstractGeomShape(apPlate3DParams)	{
	m_pUntransformedPlate3D = new UntransformedPlate3D();
	addChild(m_pUntransformedPlate3D);

	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams*>(m_pAbstractObjectParams);
	init(*pPlate3DParams);
}

//-----------------------------------------------------------------------

const char* Plate3D::className() const	{
	return "Plate3D";
}

//-----------------------------------------------------------------------

void Plate3D::init(AbstractGeomShapeParams & aAbstractGeomShapeParams)	{
	*((Plate3DParams *)m_pAbstractObjectParams) = *((Plate3DParams*)&aAbstractGeomShapeParams);

	Plate3DParams & aGSP = dynamic_cast<Plate3DParams&>(aAbstractGeomShapeParams);

	setScaling(aGSP.m_flLenX, aGSP.m_flLenY, aGSP.m_flLenZ);
	setRotation(aGSP.m_flAngleYZ, aGSP.m_flAngleXZ, aGSP.m_flAngleXY);
	setPosition(aGSP.m_flPosX, aGSP.m_flPosY, aGSP.m_flPosZ);
	
	Matrix & plate3DMatrix = calculateMatrix();
	setMatrix(plate3DMatrix);

	setColor(aGSP.m_arrflRGBA);
	if ((aGSP.m_strFileNameTexture != " ") && (aGSP.m_strFileNameTexture != ""))
		setTexture(aGSP.m_strFileNameTexture);

	setName("Plate3D");
}

//----------------------------------------------------------------------

void Plate3D::setColor(const std::vector < float > & aarrflColor)	{
	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams *>(m_pAbstractObjectParams);
	if(pPlate3DParams != 0) {
		pPlate3DParams->m_arrflRGBA = aarrflColor;
		m_pUntransformedPlate3D->setColor(pPlate3DParams->m_arrflRGBA);
	}
}

//----------------------------------------------------------------------

void Plate3D::setTexture(const std::string & astrFileName) {
	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams *>(m_pAbstractObjectParams);
	if(pPlate3DParams != 0) {
		pPlate3DParams->m_strFileNameTexture = astrFileName;
		m_pUntransformedPlate3D->setTexture(pPlate3DParams->m_strFileNameTexture);
	}
}

//----------------------------------------------------------

string Plate3D::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

std::string Plate3D::getSQLCommand() const	{
	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams *>(m_pAbstractObjectParams);
	if(pPlate3DParams == 0) {
		return(0);
	}

	string strPlate3DParams;
	strPlate3DParams = to_string((long double)pPlate3DParams->m_flPosX) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flPosY) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flPosZ) + "_";

	strPlate3DParams += to_string((long double)pPlate3DParams->m_flLenX) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flLenY) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flLenZ) + "_";

	strPlate3DParams += to_string((long double)pPlate3DParams->m_flAngleXY) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flAngleXZ) + "_";
	strPlate3DParams += to_string((long double)pPlate3DParams->m_flAngleYZ);


	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)pPlate3DParams->m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Plate3D (Plate3DMatrix, Plate3DColor, Plate3DTexture, PrimitiveID) VALUES('"
		+ strPlate3DParams + "','"
		+ strColor + "','"
		+ pPlate3DParams->m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Plate3D'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Plate3D::initFromSQLData(const string & astrSQLData)	{
	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams*>(m_pAbstractObjectParams);
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
			pPlate3DParams->m_arrflRGBA[nI] = stof(arrstrColor[nI]);
		}
	}

	pPlate3DParams->m_flPosX = arrflMatrix[0];
	pPlate3DParams->m_flPosY = arrflMatrix[1];
	pPlate3DParams->m_flPosZ = arrflMatrix[2];

	pPlate3DParams->m_flLenX = arrflMatrix[3];
	pPlate3DParams->m_flLenY = arrflMatrix[4];
	pPlate3DParams->m_flLenZ = arrflMatrix[5];

	pPlate3DParams->m_strFileNameTexture = arrstrPlateParams[3];

	init(*pPlate3DParams);
}

//----------------------------------------------------------------------

void Plate3D::predefinedObject()	{
	Plate3DParams * pPlate3DParams = dynamic_cast<Plate3DParams*>(m_pAbstractObjectParams);
	init(*pPlate3DParams);
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------

void Plate3D::print(std::ostream & os) const	{
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