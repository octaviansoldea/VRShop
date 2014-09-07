#include "VRFloor.h"
#include "VRWall.h"

#include "VRRoom.h"

using namespace VR;
using namespace osg;

Room::Room()	{
}

//===================================================

const char* Room::className() const	{
	return "Room";
}

//---------------------------------------------------

ref_ptr<Node> Room::createRoom()	{
	ref_ptr<MatrixTransform> pMt = new MatrixTransform;

	FloorParams fP;
	fP.m_strTextureName = 
		"../../../Resources/Textures/CeramicTileFloor.bmp";
	fP.m_vec3dBottomLeft = Vec3d(-25.5,-25.5,0);
	fP.m_vec3dUpRight = Vec3d(25.5,25.5,0);
	Floor floor(fP);
	ref_ptr<Node> pNode = floor.createFloor();
	pMt->addChild(pNode);

	ref_ptr<Wall> pWall = new Wall;
	pWall->setMatrix(Matrix::translate(0,0,2.5));
	pWall->createWall();
	pMt->addChild(pWall);

	return pMt.get();
}