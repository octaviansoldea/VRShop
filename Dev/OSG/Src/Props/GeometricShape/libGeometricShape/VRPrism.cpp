#include "BasicStringDefinitions.h"

#include "VRPrism.h"

#include <string>
#include <fstream>

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


PrismParams::PrismParams() : AbstractGeomShapeParams()	{
}

//-----------------------------------------------------------------------

Prism::Prism() : AbstractGeomShape(new PrismParams())	{
	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);

	m_pUntransformedPolygon3D = new UntransformedPolygon3D(*pPrismParams);
	addChild(m_pUntransformedPolygon3D);

	setName("Prism");
}

//----------------------------------------------------------

Prism::Prism(PrismParams * apPrismParams) : AbstractGeomShape(apPrismParams)	{
	m_pUntransformedPolygon3D = new UntransformedPolygon3D();

	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);
	init(*pPrismParams);
//	addChild(m_pUntransformedPolygon3D);
}

//----------------------------------------------------------

Prism::Prism(const Prism& pr,const CopyOp& copyop) : AbstractGeomShape(pr,copyop)	{
}

//----------------------------------------------------------

const char* Prism::className() const	{
	return "Prism";
}

//----------------------------------------------------------

void Prism::setResolution(int anRes) {
	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);
	pPrismParams->m_nRes = anRes;
}

//----------------------------------------------------------

void Prism::init(AbstractGeomShapeParams & aAbstractGeomShapeParams) {
	PrismParams & pP = dynamic_cast<PrismParams&>(aAbstractGeomShapeParams);

	m_pUntransformedPolygon3D->init(pP);

	Matrix matrix;
	matrix.set(pP.m_flRadius,	0,				0,				0,
			   0,				pP.m_flHeight,	0,				0,
			   0,				0,				pP.m_flRadius,	0,
			   0,				0,				0,				1);

	Matrix PrismMatrix =
		matrix.scale(pP.m_flLenX, pP.m_flLenY, pP.m_flLenZ)
		*
		matrix.rotate(
			pP.m_flAngleYZ, osg::X_AXIS,
			pP.m_flAngleXZ, osg::Y_AXIS,
			pP.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(pP.m_flPosX, pP.m_flPosY, pP.m_flPosZ)
	;
	
	setMatrix(PrismMatrix);

	setColor(pP.m_arrflRGBA);
	if ((pP.m_strFileNameTexture != " ") && (pP.m_strFileNameTexture != ""))
		setTexture(pP.m_strFileNameTexture);

	setName("Prism");
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
	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);

	string strPrismParams;

	strPrismParams= to_string((long double)pPrismParams->m_flRadius) + "_";
	strPrismParams+= to_string((long double)pPrismParams->m_flHeight) + "_";

	strPrismParams+= to_string((long double)pPrismParams->m_flPosX) + "_";
	strPrismParams+= to_string((long double)pPrismParams->m_flPosY) + "_";
	strPrismParams+= to_string((long double)pPrismParams->m_flPosZ) + "_";

	strPrismParams += to_string((long double)pPrismParams->m_flLenX) + "_";
	strPrismParams += to_string((long double)pPrismParams->m_flLenY) + "_";
	strPrismParams += to_string((long double)pPrismParams->m_flLenZ) + "_";
			 
	strPrismParams+= to_string((long double)pPrismParams->m_flAngleXY) + "_";
	strPrismParams+= to_string((long double)pPrismParams->m_flAngleXZ) + "_";
	strPrismParams+= to_string((long double)pPrismParams->m_flAngleYZ);

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)pPrismParams->m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Prism (PrismSides, PrismMatrix, PrismColor, PrismTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)pPrismParams->m_nRes) + ",'"
		+ strPrismParams + "','"
		+ strColor + "','"
		+ pPrismParams->m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Prism'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Prism::initFromSQLData(const std::string & astrSQLData)	{
	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);

	string strSQLData = astrSQLData;

	vector <string> arrstrPrismParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrPrismParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrPrismParams[3],"_");

	pPrismParams->m_nRes = stof(arrstrPrismParams[1]);
	pPrismParams->m_flRadius = stof(arrstrMatrix[0]);
	pPrismParams->m_flHeight = stof(arrstrMatrix[1]);

	pPrismParams->m_flPosX = stof(arrstrMatrix[2]);
	pPrismParams->m_flPosY = stof(arrstrMatrix[3]);
	pPrismParams->m_flPosZ = stof(arrstrMatrix[4]);

	pPrismParams->m_flLenX = stof(arrstrMatrix[5]);
	pPrismParams->m_flLenY = stof(arrstrMatrix[6]);
	pPrismParams->m_flLenZ = stof(arrstrMatrix[7]);

	pPrismParams->m_flAngleXY = stof(arrstrMatrix[8]);
	pPrismParams->m_flAngleXZ = stof(arrstrMatrix[9]);
	pPrismParams->m_flAngleYZ = stof(arrstrMatrix[10]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			pPrismParams->m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	pPrismParams->m_strFileNameTexture = arrstrPrismParams[4];

	init(*pPrismParams);
}

//----------------------------------------------------------------------

void Prism::predefinedObject()	{
	PrismParams * pPrismParams = dynamic_cast<PrismParams*>(m_pAbstractObjectParams);
	init(*pPrismParams);
	setIsTargetPick(true);
}
