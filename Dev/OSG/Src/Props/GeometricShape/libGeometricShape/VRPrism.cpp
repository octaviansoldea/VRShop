#include "StringManipulation.h"

#include "VRPrism.h"

#include <string>

using namespace std;
using namespace osg;
using namespace VR;

string Prism::m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Prism "
	"(PrismID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"PrismSides INTEGER,"
	"PrismMatrix TEXT,"
	"PrismColor TEXT,"
	"PrismTexture TEXT, "
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";


PrismParams::PrismParams() :
m_flRadius(1.0), m_flHeight(1.0), m_nRes(5)
{
}

//-----------------------------------------------------------------------

Prism::Prism()	{
	m_pUntransformedPolygon3D = new UntransformedPolygon3D();
	const PrismParams aPrismParams;
	init(aPrismParams);
	addChild(m_pUntransformedPolygon3D);
}

//----------------------------------------------------------

Prism::Prism(const PrismParams & aPrismParams)	{
	m_pUntransformedPolygon3D = new UntransformedPolygon3D();
	init(aPrismParams);
	addChild(m_pUntransformedPolygon3D);
}

//----------------------------------------------------------

void Prism::setResolution(int anRes) {
	m_pUntransformedPolygon3D->setResolution(anRes);
}

//----------------------------------------------------------

void Prism::init(const AbstractGeomShapeParams & aAbstractGeomShapeParams) {
	m_PrismParams = static_cast<const PrismParams&>(aAbstractGeomShapeParams);

	setResolution(m_PrismParams.m_nRes);
	Matrix matrix;
	matrix.set(m_PrismParams.m_flRadius,	0,							0,							0,
			   0,							m_PrismParams.m_flHeight,	0,							0,
			   0,							0,							m_PrismParams.m_flRadius,	0,
			   m_PrismParams.m_flPosX,		m_PrismParams.m_flPosY,		m_PrismParams.m_flPosZ,		1);
	setMatrix(matrix);

	setColor(m_PrismParams.m_arrflRGBA);
	if ((m_PrismParams.m_strFileNameTexture != " ") && (m_PrismParams.m_strFileNameTexture != ""))
		setTexture(m_PrismParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void Prism::setColor(const vector < float > & aarrflColor) {
	m_pUntransformedPolygon3D->setColor(aarrflColor);
}

//----------------------------------------------------------------------

void Prism::setTexture(const string & astrFileName) {
	m_pUntransformedPolygon3D->setTexture(astrFileName);
}

//----------------------------------------------------------------------

string Prism::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

string Prism::getSQLCommand() const {
	string strPrismParams;

	strPrismParams= to_string((long double)m_PrismParams.m_flPosX) + "_";
	strPrismParams+= to_string((long double)m_PrismParams.m_flPosY) + "_";
	strPrismParams+= to_string((long double)m_PrismParams.m_flPosZ) + "_";
	
	strPrismParams+= to_string((long double)m_PrismParams.m_flRadius) + "_";
	strPrismParams+= to_string((long double)m_PrismParams.m_flHeight) + "_";
								 
	strPrismParams+= to_string((long double)m_PrismParams.m_flAngleXY) + "_";
	strPrismParams+= to_string((long double)m_PrismParams.m_flAngleXZ) + "_";
	strPrismParams+= to_string((long double)m_PrismParams.m_flAngleYZ);

	int nI;
	string strColor = "'";
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_PrismParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += "'";

	string strSQLCommand = "INSERT INTO Prism (PrismSides, PrismMatrix, PrismColor, PrismTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_PrismParams.m_nRes) + ",'"
		+ strPrismParams + "',"
		+ strColor + ",'"
		+ m_PrismParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Prism'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Prism::initFromSQLData(const std::string & astrSQLData)	{
	string strSQLData = astrSQLData;

	vector <string> arrstrPrismParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrPrismParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrPrismParams[3],"_");

	m_PrismParams.m_nRes = stof(arrstrPrismParams[1]);
	m_PrismParams.m_flRadius = stof(arrstrMatrix[3]);
	m_PrismParams.m_flHeight = stof(arrstrMatrix[4]);
	
	m_PrismParams.m_flPosX = stof(arrstrMatrix[0]);
	m_PrismParams.m_flPosY = stof(arrstrMatrix[1]);
	m_PrismParams.m_flPosZ = stof(arrstrMatrix[2]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			m_PrismParams.m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	m_PrismParams.m_strFileNameTexture = arrstrPrismParams[4];

	init(m_PrismParams);
}

//----------------------------------------------------------------------

void Prism::predefinedObject()	{
	init(m_PrismParams);
	setIsTargetPick(true);
}
