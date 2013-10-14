#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"

#include "VRPicker.h"
#include "VRGrid.h"

#include "OSGCameraManipulator.h"
#include <osgGA/TrackballManipulator>


#include <osgDB/readFile>

using namespace VR;


//----------------------------------------------------------------------

void main_Plate3D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Plate3D> pPlate3D = new Plate3D();
	const float color[4] = {0,1,0,1};
	pPlate3D->setColor(color);
	pPlate3D->setIsTargetPick(true);
	pScene->addChild(pPlate3D.get());
}

//----------------------------------------------------------------------

void main_Cylinder(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Cylinder> pCylinder = new Cylinder();
	const float color[4] = {1,1,0,1};
	pCylinder->setResolution(20);
	pCylinder->setColor(color);
	pCylinder->setIsTargetPick(true);
	pScene->addChild(pCylinder);
}

//----------------------------------------------------------------------

void main_VRUntransformedSphere(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<UntransformedSphere> pSphere = new UntransformedSphere();
	const float color[4] = {1,0,0,1};
	pSphere->setResolution(20,20);
	pSphere->setColor(color);
	pSphere->setIsTargetPick(true);
	pScene->addChild(pSphere);
}

//----------------------------------------------------------------------

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile( "../../Resources/axes.osgt");
	root->addChild(axes);
	root->addChild(new VR::Grid);
	
	main_Plate3D(root);
	main_Cylinder(root);
	main_VRUntransformedSphere(root);


	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
//	viewer.setUpViewInWindow(0, 0, 1000, 800);
//	viewer.setCameraManipulator(new VR::OSGCameraManipulator);
//	viewer.addEventHandler( new VR::PickAndDragHandler );

	return viewer.run();
}


