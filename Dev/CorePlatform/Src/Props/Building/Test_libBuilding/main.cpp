#include <QApplication>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

#include <osg/MatrixTransform>

#include "VRAppData.h"

#include "VRFloor.h"
#include "VRWall.h"
#include "VRRoom.h"

using namespace VR;
using namespace osg;

int main_Floor(int argc, char * argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	FloorParams fP;
	fP.m_strTextureName = AppData::getFPathResources() + "/Textures/CeramicTileFloor1.bmp";		
	fP.m_vec3dBottomLeft = Vec3d(0,-10,0);
	fP.m_vec3dUpRight = Vec3d(50,10,0);
	Floor floor(fP);
	ref_ptr<Node> pNode = floor.createFloor();
	pScene->addChild(pNode);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}

//--------------------------------------------------------------------------------------------

int main_Wall(int argc, char * argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	ref_ptr<Wall> pWall = new Wall;
	pWall->createWall();
	pScene->addChild(pWall);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}

//--------------------------------------------------------------------------------------------

int main_Room(int argc, char * argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	ref_ptr<Room> pRoom = new Room;
	pRoom->createRoom();

	pScene->addChild(pRoom);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}

int main(int argc, char * argv[])	{	
//	main_Floor(argc,argv);
//	main_Wall(argc,argv);
	main_Room(argc,argv);
}