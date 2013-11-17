#include "StringManipulation.h"

#include "VRPrism.h"

#include <string>

using namespace std;
using namespace osg;
using namespace VR;

PrismParams::PrismParams() :
m_flRadius(1.0), m_flHeight(1.0), m_nRes(5),
m_flPosX(0.0), m_flPosY(0.0), m_flPosZ(0.0),
m_strFileNameTexture("")	{
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
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
	const PrismParams & aPrismParams = static_cast<const PrismParams&>(aAbstractGeomShapeParams);

	setResolution(aPrismParams.m_nRes);
	Matrix matrix;
	matrix.set(aPrismParams.m_flRadius, 0,						0,						0,
			   0,						aPrismParams.m_flHeight,0,						0,
			   0,						0,						aPrismParams.m_flRadius,0,
			   aPrismParams.m_flPosX,	aPrismParams.m_flPosY,	aPrismParams.m_flPosZ,  1);
	setMatrix(matrix);
	m_PrismParams = aPrismParams;
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

string Prism::getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const {
	const PrismParams & aPrismParams = static_cast<const PrismParams&>(aAbstractGeomShapeParams);

	string strSQLCommand = "INSERT INTO Prism (PrismSides, PrismRadius, PrismHeight, PrimitiveID) VALUES("
		+ to_string((_Longlong)aPrismParams.m_nRes) + ","
		+ to_string((long double)aPrismParams.m_flRadius) + ","
		+ to_string((long double)aPrismParams.m_flHeight) + ","
		+ to_string((_Longlong)3) + ")";
	return(strSQLCommand);
}

//----------------------------------------------------------------------

void Prism::initFromSQLData(const std::string & astrSQLData)	{
	string strSQLData = astrSQLData;
	
	vector <string> vecstrPrismParams = splitString(strSQLData," ");

	PrismParams pP;
	pP.m_nRes = stof(vecstrPrismParams.at(0));
	pP.m_flRadius = stof(vecstrPrismParams.at(1));
	pP.m_flHeight = stof(vecstrPrismParams.at(2));

	init(pP);
}
