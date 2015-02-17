#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgDB/readFile>

#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osg/TexMat>

#include "VRFloor.h"

using namespace osg;
using namespace VR;

FloorParams::FloorParams() :
m_vec3dBottomLeft(0,0,0),
m_vec3dUpRight(0,0,0),
m_strTextureName("")	{
}

//===============================================================================

Floor::Floor(const FloorParams & aFloorParams)	{
	m_FloorParams = aFloorParams;
}

//-------------------------------------------------------------------------------

Floor::Floor()	{
}

//===============================================================================

const char* Floor::className() const	{
	return "Floor";
}

//-------------------------------------------------------------------------------

Node * Floor::createFloor()	{
	ref_ptr<Geode> pGeode = new Geode;
	pGeode->addDrawable(setGeometry());

	return pGeode.release();
}

//-------------------------------------------------------------------------------

ref_ptr<Geometry> Floor::setGeometry()	{
	ref_ptr<Geometry> pGeometry = new osg::Geometry;
	ref_ptr<Vec3Array> coords = new osg::Vec3Array;
	ref_ptr<Vec3Array> nrms = new osg::Vec3Array;
	ref_ptr<Vec2Array> tcs = new osg::Vec2Array;
	osg::Vec3 nrm(0,-1,0);

	Vec3d vec3dPoint0 = m_FloorParams.m_vec3dBottomLeft;
	Vec3d vec3dPoint1 = m_FloorParams.m_vec3dUpRight;

	float flarrCoords[4][2] = { 
		{ vec3dPoint0.x(), vec3dPoint0.y() },
		{ vec3dPoint0.x(), vec3dPoint1.y() },
		{ vec3dPoint1.x(), vec3dPoint1.y() },
		{ vec3dPoint1.x(), vec3dPoint0.y() }
	};

	//Define colors
	ref_ptr<Vec4Array> pColors = new Vec4Array(1);
	(*pColors)[0].set(1.0,1.0,1.0,0.0);
	pGeometry->setColorArray(pColors);
	pGeometry->setColorBinding(Geometry::BIND_OVERALL);

	pGeometry->setVertexArray(coords);
	pGeometry->setNormalArray(nrms, osg::Array::BIND_PER_VERTEX);
	pGeometry->setTexCoordArray(0,tcs);

	int nI;
	for (nI=0; nI<4; nI++) {
		coords->push_back(osg::Vec3(flarrCoords[nI][0],flarrCoords[nI][1],0));
		tcs->push_back(osg::Vec2(flarrCoords[nI][0],flarrCoords[nI][1]));
		nrms->push_back(nrm);
	}
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	ref_ptr<osg::Image> pImage = osgDB::readImageFile(m_FloorParams.m_strTextureName);
	if (pImage)	{
		ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);
		pTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
		ref_ptr<TexMat> pTexMat = new TexMat;
		pTexMat->setScaleByTextureRectangleSize(true);

		ref_ptr<StateSet> pState = pGeometry->getOrCreateStateSet();
		pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
		pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);


		// turn off lighting
		pState->setMode(GL_LIGHTING, StateAttribute::OFF);
	}

	return pGeometry;
}