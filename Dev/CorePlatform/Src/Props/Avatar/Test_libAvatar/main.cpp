#include <iostream>

#include <osgDB/readFile>
#include <osgViewer/Viewer>

#include "VRAppData.h"

#include "VRKeyboardMouseManipulatorShopClient.h"

#include "VRAvatar.h"

using namespace VR;
using namespace osg;
using namespace std;

int main_Avatar(int argc, char * argv[])	{
	osgViewer::Viewer viewer;
	ref_ptr<Group> pScene = new Group;

	string strAvatarFileName = AppData::getFPathResources() + "/Models3D/avatar.osg";

	ref_ptr<KeyboardMouseManipulatorShopClient> pCamera = new KeyboardMouseManipulatorShopClient(pScene);

	ref_ptr<Avatar> pAvatar = new Avatar(strAvatarFileName, pCamera);
	pCamera->setCameraPosition2Object(pAvatar);

	ref_ptr<Node> pAxes = dynamic_cast<Group*>(osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt"));

	pScene->addChild(pAxes);
	pScene->addChild(pAvatar);

	viewer.setSceneData(pScene);
	viewer.setCameraManipulator(pCamera);
	
	return viewer.run();

//	return 0;
}

//===================================================================

int main(int argc, char * argv[])	{
	main_Avatar(argc, argv);

	return(0);
}