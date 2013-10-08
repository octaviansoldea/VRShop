#include "OSGCameraManipulator.h"
#include <osgGA/TrackballManipulator>

#include <osgViewer/Viewer>
#include <osgDB/readFile>

using namespace VR;

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../../Resources/cessna.osg");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../../Resources//cow.osg");
	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile("../../Resources/axes.osgt");


	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(model1.get());
	root->addChild(model2.get());
	root->addChild(axes);

	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow(200, 200, 1000, 800);
	viewer.setSceneData(root.get());
	viewer.setCameraManipulator(new VR::OSGCameraManipulator);
//	viewer.setCameraManipulator(new osgGA::TrackballManipulator);

	return viewer.run();
}