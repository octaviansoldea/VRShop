#include <osgViewer/Viewer>

#include "VRAvatar.h"

using namespace VR;
using namespace osg;

int main_Avatar(int argc, char * argv[])	{

	ref_ptr<Group> pScene = new Group;
	
	ref_ptr<Avatar> pAvatar = new Avatar;
	pScene->addChild(pAvatar);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}

//===================================================================

int main(int argc, char * argv[])	{
	main_Avatar(argc, argv);

	return(0);
}