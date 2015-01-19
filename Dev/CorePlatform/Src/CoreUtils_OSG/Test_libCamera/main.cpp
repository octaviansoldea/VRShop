#include <osgViewer/Viewer>
#include <osgDB/readFile>

#include "VRAppData.h"
#include "VRAxes.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"

using namespace VR;

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/cessna.osgt");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/cow.osgt");
//	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");

	osg::ref_ptr<Axes> pAxes = new Axes;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	//root->addChild(model1.get());
	//root->addChild(model2.get());
	root->addChild(pAxes.get());

	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow(200, 200, 1000, 800);
	viewer.setSceneData(root.get());
	viewer.setCameraManipulator(new VR::KeyboardMouseManipulatorShopEditor);

	return viewer.run();
}