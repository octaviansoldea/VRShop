#include "OSGPicker.h"

#include "OSGCameraManipulator.h"

#include <osgDB/readFile>

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile( "C:/Programi/OSG/OpenSceneGraph-Data-3.0.0/cessna.osg");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile( "C:/Programi/OSG/OpenSceneGraph-Data-3.0.0/cow.osg" );

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild( model1.get() );
	root->addChild( model2.get() );

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	viewer.setCameraManipulator(new VR::OSGCameraManipulator);
	viewer.addEventHandler( new VR::PickHandler );

	std::string axes = "C:/Projekti/VRShop/Dev/OSG/Resources/Models3D/axes.osgt";
	osg::ref_ptr<osg::Node> pAxes = osgDB::readNodeFile(axes);
	root->addChild(pAxes);

	return viewer.run();
}

