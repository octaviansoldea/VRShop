#include <iostream>
#include <string>
#include <assert.h>

#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>

#include "BasicStringDefinitions.h"

#include "VRUntransformedSphere.h"

using namespace std;
using namespace osg;
using namespace VR;

UntransformedSphereParams::UntransformedSphereParams() : 
m_flRadius(1.0), m_nResPhi(25), m_nResTheta(25)	{
}

//-----------------------------------------------------------------------

UntransformedSphere::UntransformedSphere()	{
	init(m_UntransformedSphereParams);
}

//-----------------------------------------------------------------------

UntransformedSphere::UntransformedSphere(const UntransformedSphereParams & aUntransformedSphereParams)	{
	m_UntransformedSphereParams = aUntransformedSphereParams;
	init(m_UntransformedSphereParams);
}

//--------------------------------------------------------------

void UntransformedSphere::init(UntransformedSphereParams & aUntransformedSphereParams)	{
	m_UntransformedSphereParams = aUntransformedSphereParams;

	float flResPhiStep = (2 * PI) / m_UntransformedSphereParams.m_nResPhi;
	float flResThetaStep = (2 * PI) / m_UntransformedSphereParams.m_nResTheta;
	
	int nIndxPhi, nIndxTheta;
	for(nIndxPhi = 0; nIndxPhi < m_UntransformedSphereParams.m_nResPhi; nIndxPhi++) {
		float flPhi = flResPhiStep * nIndxPhi;
		float flPhiP1 = flPhi + flResPhiStep;
		float flCosPhi = cos(flPhi);
		float flCosPhiP1 = cos(flPhiP1);
		float flSinPhi = sin(flPhi);
		float flSinPhiP1 = sin(flPhiP1);
		for(nIndxTheta = 0; nIndxTheta < m_UntransformedSphereParams.m_nResTheta; nIndxTheta++) {
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
			addDrawable(pGeometry);
		}
	}
}

//--------------------------------------------------------------

void UntransformedSphere::setColor(const vector < float > & aarrflColor) {	
	int nDrawablesNr = getNumDrawables();
	for(int nI = 0; nI < nDrawablesNr; nI++) {
		ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(getDrawable(nI));
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

void UntransformedSphere::setTexture(const std::string & astrFileName) {

	int nDrawablesNr = getNumDrawables();

	assert(nDrawablesNr == m_UntransformedSphereParams.m_nResPhi * m_UntransformedSphereParams.m_nResTheta);

	ref_ptr<Image> pImage = osgDB::readImageFile(astrFileName);
	ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);
	ref_ptr<TexMat> pTexMat = new TexMat;
	pTexMat->setScaleByTextureRectangleSize(true);
	

	float flTexPhiStep = 1.0 / m_UntransformedSphereParams.m_nResPhi;
	float flTexThetaStep = 1.0 / m_UntransformedSphereParams.m_nResTheta;
	
	int nIndxDrawable = 0;
	int nIndxPhi, nIndxTheta;
	for(nIndxPhi = 0; nIndxPhi < m_UntransformedSphereParams.m_nResPhi; nIndxPhi++) {
		float flPhi = flTexPhiStep * nIndxPhi;
		float flPhiP1 = flPhi + flTexPhiStep;
		for(nIndxTheta = 0; nIndxTheta < m_UntransformedSphereParams.m_nResTheta; nIndxTheta++) {
			float flTheta = flTexThetaStep * nIndxTheta;
			float flThetaP1 = flTheta + flTexThetaStep;

			ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(getDrawable(nIndxDrawable));
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

void UntransformedSphere::setResolution(int anResPhi, int anResTheta) {
}

//--------------------------------------------------------------

void UntransformedSphere::setRadius(float aflRadius) {
}

//----------------------------------------------------------------------

