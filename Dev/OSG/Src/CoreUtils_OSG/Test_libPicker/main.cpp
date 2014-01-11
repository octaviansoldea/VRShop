#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"

#include "VRContainer.h"

#include "VRPickAndDragHandler.h"
#include "VRKeyboardMouseManipulator.h"

#include <osgViewer/Viewer>

#include "VRGrid.h"
#include <osgDB/readFile>

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

void main_Plate3D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Plate3D> pPlate3D = new Plate3D();
	vector < float > arrflColor;
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	arrflColor.push_back(1.0);

	pPlate3D->setColor(arrflColor);
	pPlate3D->setIsTargetPick(true);
	pScene->addChild(pPlate3D.get());
}

//----------------------------------------------------------------------

void main_Cylinder(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Cylinder> pCylinder = new Cylinder();
	vector < float > arrflColor;
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	arrflColor.push_back(1.0);

	pCylinder->setColor(arrflColor);
	pCylinder->setResolution(20);
	pCylinder->setIsTargetPick(true);
	pScene->addChild(pCylinder);
}

//----------------------------------------------------------------------

void main_VRUntransformedSphere(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<UntransformedSphere> pSphere = new UntransformedSphere();
	vector < float > arrflColor;
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	arrflColor.push_back(1.0);

	pSphere->setColor(arrflColor);
	pSphere->setResolution(20,20);
	pSphere->setIsTargetPick(true);
	pScene->addChild(pSphere);
}

//----------------------------------------------------------------------

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile( "../../../Resources/Models3D/axes.osgt");
	root->addChild(axes);
	root->addChild(new VR::Grid);
	
//	main_Plate3D(root);
	main_Cylinder(root);
//	main_VRUntransformedSphere(root);

	osg::ref_ptr < Container > pContainer = new Container;
	pContainer->predefinedObject();
	root->addChild(pContainer);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
//	viewer.setUpViewInWindow(0, 0, 1000, 800);
	viewer.setCameraManipulator(new VR::KeyboardMouseManipulator);
	viewer.addEventHandler( new VR::PickAndDragHandler );

	return viewer.run();
}


