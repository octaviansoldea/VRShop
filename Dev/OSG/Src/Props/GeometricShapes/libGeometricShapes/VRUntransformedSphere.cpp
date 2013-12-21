#include <iostream>
#include <string>
#include <assert.h>

#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>

#include <osg/Geode>

#include "StringManipulation.h"

#include "VRUntransformedSphere.h"

using namespace std;
using namespace osg;
using namespace VR;

string UntransformedSphere::m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Sphere "
	"(SphereID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"SphereRes INTEGER,"
	"SphereRadius INTEGER,"
	"SphereColor TEXT,"
	"SphereTexture TEXT, "
	"PrimitiveID INTEGER, "
	"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";


SphereParams::SphereParams() : 
m_flRadius(1.0), m_nResPhi(25), m_nResTheta(25), m_strFileNameTexture(" ") {
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
}

//-----------------------------------------------------------------------

UntransformedSphere::UntransformedSphere()	{
	const SphereParams sphereParams;
	init(sphereParams);
}

//-----------------------------------------------------------------------

UntransformedSphere::UntransformedSphere(const SphereParams & aSphereParams)	{
	init(aSphereParams);
}

//--------------------------------------------------------------

void UntransformedSphere::init(const AbstractGeomShapeParams & aAbstractGeomShapeParams)	{
	const SphereParams & aSphereParams = static_cast<const SphereParams&>(aAbstractGeomShapeParams);

	m_SphereParams = aSphereParams;
	m_pGeode = new Geode;

	float flResPhiStep = (2 * PI) / m_SphereParams.m_nResPhi;
	float flResThetaStep = (2 * PI) / m_SphereParams.m_nResTheta;
	
	int nIndxPhi, nIndxTheta;
	for(nIndxPhi = 0; nIndxPhi < m_SphereParams.m_nResPhi; nIndxPhi++) {
		float flPhi = flResPhiStep * nIndxPhi;
		float flPhiP1 = flPhi + flResPhiStep;
		float flCosPhi = cos(flPhi);
		float flCosPhiP1 = cos(flPhiP1);
		float flSinPhi = sin(flPhi);
		float flSinPhiP1 = sin(flPhiP1);
		for(nIndxTheta = 0; nIndxTheta < m_SphereParams.m_nResTheta; nIndxTheta++) {
			float flTheta = flResThetaStep * nIndxTheta;
			float flThetaP1 = flTheta + flResThetaStep;
			float flCosTheta = cos(flTheta);
			float flCosThetaP1 = cos(flThetaP1);
			float flSinTheta = sin(flTheta);
			float flSinThetaP1 = sin(flThetaP1);

			ref_ptr<Vec3Array> pPoints = new Vec3Array(4);
			(*pPoints)[0].set(flCosPhi * flCosTheta,     flSinPhi,   flCosPhi * flSinTheta);
			(*pPoints)[1].set(flCosPhiP1 * flCosTheta ,  flSinPhiP1, flCosPhiP1 * flSinTheta);
			(*pPoints)[2].set(flCosPhiP1 * flCosThetaP1, flSinPhiP1, flCosPhiP1 * flSinThetaP1);
			(*pPoints)[3].set(flCosPhi * flCosThetaP1,   flSinPhi,   flCosPhi * flSinThetaP1);
			

			ref_ptr < Geometry > pGeometry = new Geometry;
			pGeometry->setVertexArray(pPoints.get());
			pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));

			ref_ptr<Vec3Array> pN = new Vec3Array;
			pGeometry->setNormalArray(pN.get());
			pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
			Vec3 normal;
			normal += (*pPoints)[0];
			normal += (*pPoints)[1];
			normal += (*pPoints)[2];
			normal += (*pPoints)[3];
			normal.normalize();
			pN->push_back(normal);
			m_pGeode->addDrawable(pGeometry);
		}
	}
	addChild(m_pGeode);
	setColor(aSphereParams.m_arrflRGBA);
}

//--------------------------------------------------------------

void UntransformedSphere::setColor(const vector < float > & aarrflColor) {	
	int nDrawablesNr = m_pGeode->getNumDrawables();
	for(int nI = 0; nI < nDrawablesNr; nI++) {
		ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(m_pGeode->getDrawable(nI));
		if(pGeometry == 0) {
			continue;
		}
		Vec4 vec4(aarrflColor[0], aarrflColor[1], aarrflColor[2], aarrflColor[3]);
		ref_ptr<Vec4Array> pColors = new Vec4Array;
		
		pGeometry->setColorArray(pColors.get());
		pGeometry->setColorBinding(Geometry::BIND_PER_VERTEX);
		pColors->push_back(vec4);
		pColors->push_back(vec4);
		pColors->push_back(vec4);
		pColors->push_back(vec4);
	}
}

//--------------------------------------------------------------

void UntransformedSphere::setTexture(const std::string astrFileName) {

	int nDrawablesNr = m_pGeode->getNumDrawables();

	assert(nDrawablesNr == m_SphereParams.m_nResPhi * m_SphereParams.m_nResTheta);

	ref_ptr<Image> pImage = osgDB::readImageFile(astrFileName);
	ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);
	ref_ptr<TexMat> pTexMat = new TexMat;
	pTexMat->setScaleByTextureRectangleSize(true);
	

	float flTexPhiStep = 1.0 / m_SphereParams.m_nResPhi;
	float flTexThetaStep = 1.0 / m_SphereParams.m_nResTheta;
	
	int nIndxDrawable = 0;
	int nIndxPhi, nIndxTheta;
	for(nIndxPhi = 0; nIndxPhi < m_SphereParams.m_nResPhi; nIndxPhi++) {
		float flPhi = flTexPhiStep * nIndxPhi;
		float flPhiP1 = flPhi + flTexPhiStep;
		for(nIndxTheta = 0; nIndxTheta < m_SphereParams.m_nResTheta; nIndxTheta++) {
			float flTheta = flTexThetaStep * nIndxTheta;
			float flThetaP1 = flTheta + flTexThetaStep;

			ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(m_pGeode->getDrawable(nIndxDrawable));
			if(pGeometry == 0) {
				continue;
			}

			ref_ptr<Vec2Array> pTexCoords = new Vec2Array(4);
			(*pTexCoords)[0].set(flPhi, flTheta);
			(*pTexCoords)[1].set(flPhiP1, flTheta);
			(*pTexCoords)[2].set(flPhiP1, flThetaP1);
			(*pTexCoords)[3].set(flPhi, flThetaP1);
			pGeometry->setTexCoordArray(0,pTexCoords);

			ref_ptr<Vec4Array> pColors = new Vec4Array(1);
			(*pColors)[0].set(1.0,1.0,1.0,1.0);
			pGeometry->setColorArray(pColors);
			pGeometry->setColorBinding(Geometry::BIND_OVERALL);
			pGeometry->setUseDisplayList(false);
			

			ref_ptr<StateSet> pState = pGeometry->getOrCreateStateSet();
			pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
			pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);
			pState->setMode(GL_LIGHTING, StateAttribute::OFF);

			nIndxDrawable++;
		}
	}
}

//--------------------------------------------------------------

string UntransformedSphere::getSQLFormat() const {
	return(m_strSQLFormat);
}

//----------------------------------------------------------------------

string UntransformedSphere::getSQLCommand() const	{
	string strColor = "'";
	int nI;
	for (nI=0;nI<4;nI++)	{
		strColor += to_string((long double)m_SphereParams.m_arrflRGBA[nI]) + ";";
	}
	strColor += "'";

	string strSQLCommand = "INSERT INTO Sphere (SphereRes, SphereRadius, SphereColor, SphereTexture, PrimitiveID) VALUES("
		+ to_string((_Longlong)m_SphereParams.m_nResPhi) + ","
		+ to_string((_Longlong)m_SphereParams.m_flRadius) + ","
		+ strColor + ",'"
		+ m_SphereParams.m_strFileNameTexture + "',"
		+ "(SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = 'Sphere'))";

	return(strSQLCommand);
}

//--------------------------------------------------------------

void UntransformedSphere::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
	SphereParams sP;
	
	vector <string> arrstrSphereParams = splitString(strSQLData,"_");
	vector <string> arrstrMatrix = splitString(arrstrSphereParams[1],";");
	vector <string> arrstrColor = splitString(arrstrSphereParams[3],";");

	sP.m_nResPhi = sP.m_nResTheta = stof(arrstrSphereParams[1]);
	sP.m_flRadius = stof(arrstrSphereParams[2]);

	if (arrstrColor.size()!=0)	{
		int nI;
		vector < float > arrflColor;
		for (nI=0;nI<4;nI++)	{
			sP.m_arrflRGBA[nI] = (stof(arrstrColor[nI]));
		}
		setColor(sP.m_arrflRGBA);
	}

	if((arrstrSphereParams[4] != " ") && (arrstrSphereParams[4] != ""))	{
		sP.m_strFileNameTexture = arrstrSphereParams[4];
		setTexture(sP.m_strFileNameTexture);
	}
	init(sP);
}

//--------------------------------------------------------------

void UntransformedSphere::setResolution(int anResPhi, int anResTheta) {
}
	
//--------------------------------------------------------------

void UntransformedSphere::setRadius(float aflRadius) {
}