#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgDB/readFile>

#include <osg/TextureRectangle>
#include <osg/TexMat>

#include "VRPlate3D.h"
#include "VRAppData.h"

#include "VRWall.h"

using namespace osg;
using namespace VR;
using namespace std;

Wall::MatrixTransformParams::MatrixTransformParams()	{
	pos = Vec3d(0,0,0);
	scale = Vec3d(1,1,1);
	rotate = Vec3d(0,0,0);
}

//===============================================================================

Wall::Wall()	{
}

//===============================================================================

const char* Wall::className() const	{
	return "Wall";
}

//-------------------------------------------------------------------------------

void Wall::createWall()	{
	//Left side
	Plate3DParams p3DP;
	p3DP.m_flLenX = 0.2;
	p3DP.m_flLenY = 51.0;
	p3DP.m_flLenZ = 5.0;
	p3DP.m_flPosX = -25.5;
	p3DP.m_strFileNameTexture = 
		AppData::getFPathResources()+"Textures/WallYellow.bmp";

	ref_ptr<Plate3D> pPlateLeft = new Plate3D(p3DP);
	addChild(pPlateLeft);

	//Right side
	p3DP.m_flPosX = 25.5;
	p3DP.m_strFileNameTexture = 
		AppData::getFPathResources()+"Textures/WallBlue.bmp";

	ref_ptr<Plate3D> pPlateRight = new Plate3D(p3DP);
	addChild(pPlateRight);


	//Left-front side
	p3DP.m_flLenX = 10.0;
	p3DP.m_flLenY = 0.2;
	p3DP.m_flLenZ = 5.0;
	p3DP.m_flPosX = -20.5;
	p3DP.m_flPosY = -25.5;
	ref_ptr<Plate3D> pPlateLeftFront = new Plate3D(p3DP);
	addChild(pPlateLeftFront);


	//Right-front side
	p3DP.m_flPosX = 20.5;
	p3DP.m_flPosY = -25.5;
	ref_ptr<Plate3D> pPlateRightFront = new Plate3D(p3DP);
	addChild(pPlateRightFront);

	//Back side
	p3DP.m_flLenX = 51.0;
	p3DP.m_flPosX = 0.0;
	p3DP.m_flPosY = 25.5;
	p3DP.m_strFileNameTexture = AppData::getFPathResources()+"Textures/WallLightGreen.bmp";
	ref_ptr<Plate3D> pPlateBack = new Plate3D(p3DP);
	addChild(pPlateBack);
}

//-------------------------------------------------------------------------------

ref_ptr<Geometry> Wall::createWallGeometry(Vec3Array * apCoords, string & astrTextureName)	{
	ref_ptr<Geometry> pGeometry = new osg::Geometry;
	ref_ptr<Vec3Array> nrms = new osg::Vec3Array;
	ref_ptr<Vec2Array> tcs = new osg::Vec2Array;
	osg::Vec3 nrm(0,-1,0);

	//Define colors
	ref_ptr<Vec4Array> pColors = new Vec4Array(1);
	(*pColors)[0].set(1.0,1.0,1.0,0.0);
	pGeometry->setColorArray(pColors);
	pGeometry->setColorBinding(Geometry::BIND_OVERALL);

	pGeometry->setVertexArray(apCoords);
	pGeometry->setNormalArray(nrms, osg::Array::BIND_PER_VERTEX);
	pGeometry->setTexCoordArray(0,tcs);

	Vec3Array::iterator it = apCoords->begin();
	for (it; it != apCoords->end(); it++) {
		tcs->push_back(Vec2(it->x(),it->z()));
		nrms->push_back(nrm);
	}
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	ref_ptr<StateSet> stateset = new osg::StateSet();
	osg::Image* image = osgDB::readImageFile(astrTextureName);
	if (image)	{
		ref_ptr<TextureRectangle> pTexture = new osg::TextureRectangle(image);
		pTexture->setWrap(osg::TextureRectangle::WRAP_S, osg::TextureRectangle::REPEAT);
		pTexture->setWrap(osg::TextureRectangle::WRAP_T, osg::TextureRectangle::REPEAT);
		stateset->setTextureAttributeAndModes(0,pTexture,osg::StateAttribute::ON);

		// turn off lighting
		stateset->setMode(GL_LIGHTING, StateAttribute::OFF);
	}
	pGeometry->setStateSet(stateset);

	return pGeometry;
}

//-------------------------------------------------------------------------------

Node * Wall::createMatrixTransform(osg::Geode* geode, MatrixTransformParams & mTParams)	{
	ref_ptr<MatrixTransform> pMt = new MatrixTransform;
	pMt->setMatrix(
		Matrix::scale(mTParams.scale) *
		Matrix::rotate(
			DegreesToRadians(mTParams.rotate.x()),X_AXIS,
			DegreesToRadians(mTParams.rotate.y()),Y_AXIS,
			DegreesToRadians(mTParams.rotate.z()),Z_AXIS) *
		Matrix::translate(mTParams.pos)
	);
	pMt->addChild(geode);
	
	return pMt.release();
}
