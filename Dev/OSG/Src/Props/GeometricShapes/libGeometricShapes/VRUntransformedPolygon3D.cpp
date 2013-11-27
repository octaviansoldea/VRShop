#include <assert.h>

#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Geometry>

#include "VRUntransformedPolygon3D.h"

using namespace osg;
using namespace VR;
using namespace std;

UntransformedPolygon3D::UntransformedPolygon3D()	{
}

//--------------------------------------------------------------------------

void UntransformedPolygon3D::setColor(const vector < float > & aarrflColor)	{
	Vec4 vec4(aarrflColor[0], aarrflColor[1], aarrflColor[2], aarrflColor[3]);
	int nI;
	int nGeodesNr = this->getNumChildren();
	assert(nGeodesNr == 3);
	for(nI = 0; nI < nGeodesNr; nI++) {
		osg::Geode * pGeode = dynamic_cast< osg::Geode * >(getChild(nI));

		int nJ;
		int nChildrenNr = pGeode->getNumDrawables();
		for(nJ =0; nJ < nChildrenNr; nJ++) {
			ref_ptr<Drawable> pDrawable = pGeode->getDrawable(nJ);
			ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(pDrawable.get());
			ref_ptr<Vec4Array> pColors = new Vec4Array;
			pGeometry->setColorArray(pColors.get());
			pGeometry->setColorBinding(Geometry::BIND_OVERALL);
			pColors->push_back(vec4);
		}
	}
}

//-----------------------------------------------------------------------------
void UntransformedPolygon3D::setTexture(const std::string & astrFileName) {
	ref_ptr<Image> pImage = osgDB::readImageFile(astrFileName);
	ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);
	ref_ptr<TexMat> pTexMat = new TexMat;
	pTexMat->setScaleByTextureRectangleSize(true);

	osg::Geode * pGeode = dynamic_cast< osg::Geode * >(getChild(2));
	int nSidesNr = pGeode->getNumDrawables();
	int nI;
	double dbStep = 1.0 / nSidesNr;
	for(nI = 0; nI < nSidesNr; nI++) {
		ref_ptr<Drawable> pDrawable = pGeode->getDrawable(nI);
		ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(pDrawable.get());

		ref_ptr<Vec2Array> pTexCoords = new Vec2Array(4);
		(*pTexCoords)[0].set(dbStep * nI, 1.0);
		(*pTexCoords)[1].set(dbStep * nI, 0.0);
		(*pTexCoords)[2].set(dbStep * (nI + 1), 0.0);
		(*pTexCoords)[3].set(dbStep * (nI + 1), 1.0);
		pGeometry->setTexCoordArray(0,pTexCoords);

		ref_ptr<Vec4Array> pColors = new Vec4Array(1);
		(*pColors)[0].set(1.0,1.0,1.0,1.0);
		pGeometry->setColorArray(pColors.get());
		pGeometry->setColorBinding(Geometry::BIND_OVERALL);
		pGeometry->setUseDisplayList(false);
		
		ref_ptr<StateSet> pState = pGeometry->getOrCreateStateSet();
		pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
		pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);
		pState->setMode(GL_LIGHTING, StateAttribute::OFF);
	}

	dbStep *= 2 * PI;
	for(nI = 0; nI < 2; nI++) {
		osg::Geode * pGeode = dynamic_cast< osg::Geode * >(getChild(nI));

		ref_ptr<Drawable> pDrawable = pGeode->getDrawable(0);
		ref_ptr<Geometry> pGeometry = dynamic_cast<Geometry *>(pDrawable.get());

		ref_ptr<Vec2Array> pTexCoords = new Vec2Array(nSidesNr);
		int nJ;
		for(nJ = 0; nJ < nSidesNr; nJ++) {
			(*pTexCoords)[nJ].set(0.5 * (1.0 + cos(dbStep * nJ)), 0.5 * (1.0 + sin(dbStep * nJ)));
		}
		pGeometry->setTexCoordArray(0,pTexCoords);
		pGeometry->setTexCoordArray(0,pTexCoords);

		ref_ptr<Vec4Array> pColors = new Vec4Array(1);
		(*pColors)[0].set(1.0,1.0,1.0,1.0);
		pGeometry->setColorArray(pColors.get());
		pGeometry->setColorBinding(Geometry::BIND_OVERALL);
		pGeometry->setUseDisplayList(false);
		ref_ptr<StateSet> pState = pGeometry->getOrCreateStateSet();
		pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
		pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);
		pState->setMode(GL_LIGHTING, StateAttribute::OFF);


	}
}

//-----------------------------------------------------------------------------

void UntransformedPolygon3D::setResolution(int anSidesNr) {
	removeChildren(0, 3);

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

	ref_ptr < osg::Geometry > pGeometry = new Geometry;
	pGeometry->setVertexArray(m_pPointsBottom.get());
	pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::TRIANGLE_FAN, 0, anSidesNr));
	ref_ptr < osg::Geode > pGeode = new osg::Geode;
	pGeode->addDrawable(pGeometry);
	ref_ptr<Vec3Array> pN = new Vec3Array;
	pGeometry->setNormalArray(pN.get());
	pGeometry->setNormalBinding(Geometry::BIND_PER_PRIMITIVE_SET);
	pN->push_back(Vec3(0.0, -1.0, 0.0));
	addChild(pGeode);

	pGeometry = new Geometry;
	pGeometry->setVertexArray(m_pPointsTop.get());
	pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::TRIANGLE_FAN, 0, anSidesNr));
	pGeode = new osg::Geode;
	pGeode->addDrawable(pGeometry);
	pN = new Vec3Array;
	pGeometry->setNormalArray(pN.get());
	pGeometry->setNormalBinding(Geometry::BIND_PER_PRIMITIVE_SET);
	pN->push_back(Vec3(0.0, 1.0, 0.0));
	addChild(pGeode);

	pGeode = new osg::Geode;
	for (nI=0;nI<anSidesNr;nI++) {
		ref_ptr<Vec3Array> pPoints = new Vec3Array(4);
		(*pPoints)[0] = (*m_pPoints)[2*nI];
		(*pPoints)[1] = (*m_pPoints)[2*nI + 1];
		(*pPoints)[2] = (*m_pPoints)[2*nI + 3];
		(*pPoints)[3] = (*m_pPoints)[2*nI + 2];

		pGeometry = new Geometry;
		ref_ptr < osg::Geometry > pGeometry = new Geometry;
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