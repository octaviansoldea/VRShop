#include "OSGCameraManipulator.h"

#include <osgViewer/Viewer>
#include <osgDB/readFile>

using namespace VR;

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../../Resources/cessna.osg");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../../Resources//cow.osg");

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(model1.get());
	root->addChild(model2.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.setCameraManipulator(new VR::OSGCameraManipulator);

	return viewer.run();
}