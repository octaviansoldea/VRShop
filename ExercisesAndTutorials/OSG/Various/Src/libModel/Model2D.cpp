#include "Model2D.h"

#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>

#include <iostream>

using namespace osg;

Model2D::Model2D()	{
	//Define initial points
	ref_ptr<Vec3Array> pPoints = new Vec3Array(4);
	(*pPoints)[0].set(- 1.0 / 2.0, - 1.0 / 2.0, - 1.0 / 2.0);
	(*pPoints)[1].set(- 1.0 / 2.0, - 1.0 / 2.0,   1.0 / 2.0);
	(*pPoints)[2].set(  1.0 / 2.0, - 1.0 / 2.0,   1.0 / 2.0);
	(*pPoints)[3].set(  1.0 / 2.0, - 1.0 / 2.0, - 1.0 / 2.0);

	//Geometry
	m_pGeometry = new Geometry;
	m_pGeometry->setVertexArray(pPoints.get());


	ref_ptr<Vec3Array> pN = new Vec3Array;
	m_pGeometry->setNormalArray(pN.get());
	m_pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
	pN->push_back(Vec3(0.0, -1.0, 0.0));

	m_pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));
	m_pGeometry->setUseDisplayList(false);

	//Draw geometry
	addDrawable(m_pGeometry);
}

//--------------------------------------------------------------

void Model2D::setColor(Vec4 aVec4) {
	ref_ptr<Vec4Array> pColors = new Vec4Array;
	m_pGeometry->setColorArray(pColors.get());
	m_pGeometry->setColorBinding(Geometry::BIND_PER_VERTEX);
	pColors->push_back(aVec4);
	pColors->push_back(aVec4);
	pColors->push_back(aVec4);
	pColors->push_back(aVec4);
}

//--------------------------------------------------------------

void Model2D::setTexture(const char * apchFileName) {
	//Define texture coordinates
    ref_ptr<Vec2Array> pTexCoords = new Vec2Array(4);
    (*pTexCoords)[0].set(0.0, 0.0);
    (*pTexCoords)[1].set(1.0, 0.0);
    (*pTexCoords)[2].set(1.0, 1.0);
    (*pTexCoords)[3].set(0.0, 1.0);
    m_pGeometry->setTexCoordArray(0,pTexCoords);

	//Define colors
	ref_ptr<Vec4Array> pColors = new Vec4Array(1);
    (*pColors)[0].set(1.0,1.0,1.0,1.0);
    m_pGeometry->setColorArray(pColors);
    m_pGeometry->setColorBinding(Geometry::BIND_OVERALL);

    // disable display list so our modified tex coordinates show up
    m_pGeometry->setUseDisplayList(false);

    // load image
	ref_ptr<Image> pImage = osgDB::readImageFile(apchFileName);

    // setup texture
    ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);

    ref_ptr<TexMat> pTexMat = new TexMat;
    pTexMat->setScaleByTextureRectangleSize(true);

    // setup state
    ref_ptr<StateSet> pState = m_pGeometry->getOrCreateStateSet();
    pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
    pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);

    // turn off lighting 
    pState->setMode(GL_LIGHTING, StateAttribute::OFF);
}
