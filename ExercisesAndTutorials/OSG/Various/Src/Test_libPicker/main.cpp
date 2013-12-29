#include "VRPicker.h"
#include "OSGCameraManipulator.h"
#include <osgGA/TrackballManipulator>

#include <osgViewer/Viewer>

#include "Model2D.h"
#include "Model3D.h"

#include "VRGrid.h"

#include <osgDB/readFile>

void main_Model2D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	pScene->addChild(pModel2D);
}

//----------------------------------------------------------------------

void main_Model3D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);
	pScene->addChild(pModel3D.get());
}

//----------------------------------------------------------------------

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile( "../../Resources/axes.osgt");

	osg::ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);

	osg::ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	pModel2D->setIsTargetPick(true);

	osg::ref_ptr<osg::Group> root = new osg::Group;

	root->addChild(pModel2D.get());
	root->addChild(pModel3D.get());
	root->addChild(axes);
	root->addChild(new VR::Grid);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	viewer.setCameraManipulator(new VR::OSGCameraManipulator);
	viewer.addEventHandler( new VR::PickAndDragHandler );

	return viewer.run();
}

