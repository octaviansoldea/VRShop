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

//-----------------------------------------------------------------------

PrismParams::PrismParams() : AbstractGeomShapeParams()	{
}

//-----------------------------------------------------------------------

Prism::Prism(const PrismParams & aPrismParams) : AbstractGeomShape(aPrismParams)	{
	m_pUntransformedPolyhedron = new UntransformedPolyhedron();
	addChild(m_pUntransformedPolyhedron);

	setName("Prism_"+tostr(getAbstractObjectNo()));

	init(aPrismParams);
}

//----------------------------------------------------------

Prism::Prism(const Prism& pr,const CopyOp& copyop) : AbstractGeomShape(pr,copyop)	{
	m_pUntransformedPolyhedron = new UntransformedPolyhedron();
	addChild(m_pUntransformedPolyhedron);

	PrismParams prP;
	pr.getParams(prP);
	init(prP);

	setName("Prism_"+tostr(getAbstractObjectNo()));
}

//----------------------------------------------------------

const char* Prism::className() const	{
	return "Prism";
}

//----------------------------------------------------------

Object* Prism::cloneType() const	{
	//PrismParams pP;
	//return new Prism(pP);


	PrismParams pPrismParams;
	this->getParams(pPrismParams);

	VR::Prism * pPrism = new VR::Prism(pPrismParams);
	
	return pPrism;
}

//----------------------------------------------------------

Object* Prism::clone(const osg::CopyOp& copyop) const	{
	return new Prism(*this,copyop);
}

//----------------------------------------------------------

void Prism::init(const PrismParams & aPrismParams)	{
	setParams(aPrismParams);

	m_pUntransformedPolyhedron->init(aPrismParams);

	Matrix matrix;
	matrix.set(aPrismParams.m_flRadius,	0,						0,						0,
			   0,						aPrismParams.m_flHeight,0,						0,
			   0,						0,						aPrismParams.m_flRadius,0,
			   0,						0,						0,						1);

	Matrix PrismMatrix =
		matrix.scale(m_flLenX, m_flLenY, m_flLenZ)
		*
		matrix.rotate(
			m_flAngleYZ, osg::X_AXIS,
			m_flAngleXZ, osg::Y_AXIS,
			m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(m_flPosX, m_flPosY, m_flPosZ)
	;
	
	setMatrix(PrismMatrix);

	setColor(aPrismParams.m_arrflRGBA);
	if ((aPrismParams.m_strFileNameTexture != " ") && (aPrismParams.m_strFileNameTexture != ""))
		setTexture(aPrismParams.m_strFileNameTexture);
}

//----------------------------------------------------------------------

void Prism::setColor(const vector < float > & aarrflColor) {
	m_arrflRGBA = aarrflColor;
	m_pUntransformedPolyhedron->setColor(m_arrflRGBA);
}

//----------------------------------------------------------------------

void Prism::setTexture(const string & astrFileName) {
	m_strFileNameTexture = astrFileName;
	m_pUntransformedPolyhedron->setTexture(m_strFileNameTexture);
}

//----------------------------------------------------------------------

string Prism::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

string Prism::getSQLCommand() const {
	PrismParams prismParams;
	getParams(prismParams);

	string strPrismParams;

	strPrismParams= to_string((long double)prismParams.m_flRadius) + "_";
	strPrismParams+= to_string((long double)prismParams.m_flHeight) + "_";

	strPrismParams+= to_string((long double)prismParams.m_flPosX) + "_";
	strPrismParams+= to_string((long double)prismParams.m_flPosY) + "_";
	strPrismParams+= to_string((long double)prismParams.m_flPosZ) + "_";

	strPrismParams += to_string((long double)prismParams.m_flLenX) + "_";
	strPrismParams += to_string((long double)prismParams.m_flLenY) + "_";
	strPrismParams += to_string((long double)prismParams.m_flLenZ) + "_";
			 
	strPrismParams+= to_string((long double)prismParams.m_flAngleXY) + "_";
	strPrismParams+= to_string((long double)prismParams.m_flAngleXZ) + "_";
	strPrismParams+= to_string((long double)prismParams.m_flAngleYZ);

	int nI;
	string strColor;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)prismParams.m_arrflRGBA[nI]) + "_";
	}

	string strSQLCommand = "INSERT INTO Prism (PrismSides, PrismMatrix, PrismColor, PrismTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)prismParams.m_nResolution) + ",'"
		+ strPrismParams + "','"
		+ strColor + "','"
		+ prismParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Prism'));";

	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Prism::initFromSQLData(const std::string & astrSQLData)	{
	PrismParams prismParams;

	string strSQLData = astrSQLData;

	vector <string> arrstrPrismParams = splitString(strSQLData,";");
	vector <string> arrstrMatrix = splitString(arrstrPrismParams[2],"_");
	vector <string> arrstrColor = splitString(arrstrPrismParams[3],"_");

	prismParams.m_nResolution = stof(arrstrPrismParams[1]);
	prismParams.m_flRadius = stof(arrstrMatrix[0]);
	prismParams.m_flHeight = stof(arrstrMatrix[1]);

	prismParams.m_flPosX = stof(arrstrMatrix[2]);
	prismParams.m_flPosY = stof(arrstrMatrix[3]);
	prismParams.m_flPosZ = stof(arrstrMatrix[4]);

	prismParams.m_flLenX = stof(arrstrMatrix[5]);
	prismParams.m_flLenY = stof(arrstrMatrix[6]);
	prismParams.m_flLenZ = stof(arrstrMatrix[7]);

	prismParams.m_flAngleXY = stof(arrstrMatrix[8]);
	prismParams.m_flAngleXZ = stof(arrstrMatrix[9]);
	prismParams.m_flAngleYZ = stof(arrstrMatrix[10]);

	int nI;
	if (arrstrColor.size()!=0)	{
		for (nI=0;nI<4;nI++)	{
			prismParams.m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
	}

	prismParams.m_strFileNameTexture = arrstrPrismParams[4];

	init(prismParams);
}

//----------------------------------------------------------------------

void Prism::predefinedObject()	{
	PrismParams prismParams;
	init(prismParams);
	setIsTargetPick(true);
}

//----------------------------------------------------------------------

void Prism::setParams(const PrismParams & aPrismParams) {
	AbstractGeomShape::setParams(aPrismParams);
}

//----------------------------------------------------------------------

void Prism::getParams(PrismParams & aPrismParams) const {
	AbstractGeomShape::getParams(aPrismParams);
}

//----------------------------------------------------------------------

string Prism::prepareRowData(const string & astrParentName)	{
	PrismParams prismParams;
	getParams(prismParams);
	string strPrismParams;

	strPrismParams= to_string((long double)prismParams.m_flRadius) + "_" +
	to_string((long double)prismParams.m_flHeight) + "_" +

	to_string((long double)prismParams.m_flPosX) + "_" +
	to_string((long double)prismParams.m_flPosY) + "_" +
	to_string((long double)prismParams.m_flPosZ) + "_" +

	to_string((long double)prismParams.m_flLenX) + "_" +
	to_string((long double)prismParams.m_flLenY) + "_" +
	to_string((long double)prismParams.m_flLenZ) + "_" +

	to_string((long double)prismParams.m_flAngleXY) + "_" +
	to_string((long double)prismParams.m_flAngleXZ) + "_" +
	to_string((long double)prismParams.m_flAngleYZ) + ";";	

	int nI;
	string strColor;
	for (nI=0;nI<3;nI++)	{
		strColor += to_string((long double)prismParams.m_arrflRGBA[nI]) + "_";
	}
	strColor += to_string((long double)prismParams.m_arrflRGBA[3]) + ";";

	strPrismParams += strColor + prismParams.m_strFileNameTexture + ";" + astrParentName + ";";

	return strPrismParams;
}