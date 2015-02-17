#include <assert.h>

#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/Geode>

#include <osg/Material>
#include <osg/BlendFunc>
#include <osg/Depth>

#include "VRUntransformedPolyhedron.h"

using namespace osg;
using namespace VR;
using namespace std;

UntransformedPolyhedronParams::UntransformedPolyhedronParams() :
m_flRadius(1.0),
m_flHeight(1.0),
m_nResolution(6)	{
}

//==========================================================================

UntransformedPolyhedron::UntransformedPolyhedron()	{
}

//--------------------------------------------------------------------------

UntransformedPolyhedron::UntransformedPolyhedron(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams)	{
	m_UntransformedPolyhedronParams = aUntransformedPolyhedronParams;
	init(m_UntransformedPolyhedronParams);
}

//--------------------------------------------------------------------------

void UntransformedPolyhedron::setColor(const vector<float> & aarrflColor, const PolyhedronSide & aPolyhedronSide)	{
	Vec4 vec4(aarrflColor[0], aarrflColor[1], aarrflColor[2], aarrflColor[3]);
	int nPlate = aPolyhedronSide;

	struct	{
		void operator() (ref_ptr<Geode> apGeode, const Vec4 & vec4) const	{
			int nJ;
			int nChildrenNr = apGeode->getNumDrawables();
			for(nJ =0; nJ < nChildrenNr; nJ++) {
				ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(apGeode->getDrawable(nJ));
				ref_ptr<Vec4Array> pColors = new Vec4Array;
				pGeometry->setColorArray(pColors.get());
				pGeometry->setColorBinding(Geometry::BIND_OVERALL);
				pColors->push_back(vec4);
			}
		}
	} PolyColor;

	if (nPlate==PolyhedronSide::ALL)	{
		int nGeodesNr = this->getNumChildren();
		int nI;

		for(nI = 0; nI < nGeodesNr; nI++) {
			ref_ptr<Geode> pGeode = dynamic_cast<Geode*>(getChild(nI));
			PolyColor(pGeode,vec4);
		}	
	} else {
		ref_ptr<Geode> pGeode = dynamic_cast<Geode*>(getChild(nPlate));
		PolyColor(pGeode,vec4);
	}
}

//-----------------------------------------------------------------------------

void UntransformedPolyhedron::setTexture(const string & astrFileName, const PolyhedronSide & aPolyhedronSide) {
	ref_ptr<Image> pImage = osgDB::readImageFile(astrFileName);
	ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);

	ref_ptr<Geode> pGeode = static_cast<Geode *>(getChild(2));
	int nSidesNr = pGeode->getNumDrawables();

	struct {
		void operator()(ref_ptr<Drawable> apDrawable, const ref_ptr<TextureRectangle> apTexture, ref_ptr<Vec2Array> apTexCoords) const	{
			ref_ptr<Geometry> pGeometry = static_cast<Geometry *>(apDrawable.get());
			pGeometry->setTexCoordArray(0,apTexCoords);

			ref_ptr<Vec4Array> pColors = new Vec4Array(1);
			(*pColors)[0].set(1.0,1.0,1.0,1.0);
			pGeometry->setColorArray(pColors.get());
			pGeometry->setColorBinding(Geometry::BIND_OVERALL);
			pGeometry->setUseDisplayList(false);
			ref_ptr<StateSet> pState = pGeometry->getOrCreateStateSet();

			ref_ptr<TexMat> pTexMat = new TexMat;
			pTexMat->setScaleByTextureRectangleSize(true);

			pState->setTextureAttributeAndModes(0, apTexture, StateAttribute::ON);
			pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);
			pState->setMode(GL_LIGHTING, StateAttribute::OFF);
		}
	} PolyTexture;

	int nType = aPolyhedronSide;

	if ((nType==PolyhedronSide::UP) || (nType==PolyhedronSide::BOTTOM) || (nType==PolyhedronSide::ALL))	{
		int nSize = (nType==PolyhedronSide::ALL) ? 2 : 1;
		int nI;
		bool bBottom = (nType==PolyhedronSide::BOTTOM) ? true : false;
		for (nI=0;nI<nSize;nI++)	{
			float flStep = 1.0 / nSidesNr;
			flStep *= 2 * PI;
			ref_ptr<Vec2Array> pTexCoords = new Vec2Array(nSidesNr);
			int nJ;
			for(nJ = 0; nJ < nSidesNr; nJ++) {
				(*pTexCoords)[nJ].set(0.5 * (1.0 + cos(flStep * nJ)), 0.5 * (1.0 + sin(flStep * nJ)));
			}
			ref_ptr<Geode> pGeode = (bBottom==true) ? dynamic_cast<Geode *>(getChild(0)) : dynamic_cast<Geode *>(getChild(1));
			ref_ptr<Drawable> pDrawable = pGeode->getDrawable(0);

			PolyTexture(pDrawable,pTexture,pTexCoords);
			bBottom = (bBottom==true) ? false : true;
		}
	}

	if ((nType==PolyhedronSide::BELT) || (nType==PolyhedronSide::ALL))	{
		float flStep = 1.0 / nSidesNr;
		int nI;
		for(nI = 0; nI < nSidesNr; nI++) {
			ref_ptr<Drawable> pDrawable = pGeode->getDrawable(nI);
			ref_ptr<Vec2Array> pTexCoords = new Vec2Array(4);
			(*pTexCoords)[0].set(flStep * nI, 1.0);
			(*pTexCoords)[1].set(flStep * nI, 0.0);
			(*pTexCoords)[2].set(flStep * (nI + 1), 0.0);
			(*pTexCoords)[3].set(flStep * (nI + 1), 1.0);

			PolyTexture(pDrawable,pTexture,pTexCoords);
		}
	}
}

//-----------------------------------------------------------------------------

void UntransformedPolyhedron::setResolution(int anResolution) {
	m_UntransformedPolyhedronParams.m_nResolution = anResolution;
	init(m_UntransformedPolyhedronParams);
}

//-----------------------------------------------------------------------------

int UntransformedPolyhedron::getResolution() const	{
	return m_UntransformedPolyhedronParams.m_nResolution;
}

//-----------------------------------------------------------------------------

void UntransformedPolyhedron::init(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams)	{
	int nChildren = getNumChildren();
	if (nChildren>0)
		removeChildren(0,nChildren);
	m_UntransformedPolyhedronParams = aUntransformedPolyhedronParams;

	int anSidesNr = m_UntransformedPolyhedronParams.m_nResolution;

	int nPointsNr = 2*anSidesNr+2;
	ref_ptr<Vec3Array> m_pPoints = new Vec3Array(nPointsNr);
	ref_ptr<Vec3Array> m_pPointsBottom = new Vec3Array(anSidesNr);
	ref_ptr<Vec3Array> m_pPointsTop = new Vec3Array(anSidesNr);

	float flAngle = (2*PI) / anSidesNr;

	float flPosX = 0.0;
	const float flPosY = - 1.0 / 2.0;
	float flPosZ = 0.0;

	int nI;
	for (nI=0;nI<anSidesNr;nI++) {
		flPosX = cos(nI*flAngle);
		flPosZ = sin(nI*flAngle);

		(*m_pPoints)[2*nI].set(flPosX, flPosY, flPosZ);
		(*m_pPoints)[2*nI+1].set(flPosX, - flPosY, flPosZ);
	}
	(*m_pPoints)[nPointsNr-2] = Vec3(m_pPoints[0].at(0));
	(*m_pPoints)[nPointsNr-1] = Vec3(m_pPoints[0].at(1));

	for (nI=0;nI<anSidesNr;nI++) {
		(*m_pPointsBottom)[nI] = Vec3(m_pPoints[0].at(2*nI));
		(*m_pPointsTop)[nI] = Vec3(m_pPoints[0].at(2*nI+1));		
	}

	ref_ptr<Geometry> pGeometry = 0;
	ref_ptr<Geode> pGeode = 0;
	ref_ptr<Vec3Array> pN = 0;
	for (nI=0;nI<2;nI++)	{
		pGeometry = new Geometry;
		ref_ptr<Vec3Array> pPoints = (nI==0) ? m_pPointsBottom : m_pPointsTop;
		pGeometry->setVertexArray(pPoints);

		pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::TRIANGLE_FAN, 0, anSidesNr));
		pGeode = new osg::Geode;
		pGeode->addDrawable(pGeometry);
		pN = new Vec3Array;
		Vec3 vec3Normal = (nI==0) ? Vec3(0.0, -1.0, 0.0) : Vec3(0.0, 1.0, 0.0);
		pN->push_back(vec3Normal);
		pGeometry->setNormalArray(pN);
		pGeometry->setNormalBinding(Geometry::BIND_PER_PRIMITIVE_SET);
		addChild(pGeode);
	}

	pGeode = new osg::Geode;
	for (nI=0;nI<anSidesNr;nI++) {
		ref_ptr<Vec3Array> pPoints = new Vec3Array(4);
		(*pPoints)[0] = (*m_pPoints)[2*nI];
		(*pPoints)[1] = (*m_pPoints)[2*nI + 1];
		(*pPoints)[2] = (*m_pPoints)[2*nI + 3];
		(*pPoints)[3] = (*m_pPoints)[2*nI + 2];

		pGeometry = new Geometry;
		pGeometry->setVertexArray(pPoints.get());
		pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));

		pN = new Vec3Array;
		pGeometry->setNormalArray(pN.get());
		pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
		Vec3 normal;
		normal += (*pPoints)[0];
		normal += (*pPoints)[1];
		normal += (*pPoints)[2];
		normal += (*pPoints)[3];
		normal.normalize();
		pN->push_back(normal);
		pGeode->addDrawable(pGeometry);
	}
	addChild(pGeode);
}