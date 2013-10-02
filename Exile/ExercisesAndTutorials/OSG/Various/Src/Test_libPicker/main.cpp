#include "OSGPicker.h"
#include "OSGCameraManipulator.h"
#include <osgGA/TrackballManipulator>

#include "Model2D.h"
#include "Model3D.h"

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
	osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile( "C:/Programi/OSG/OpenSceneGraph-Data-3.0.0/cessna.osgt");
	osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile( "C:/Programi/OSG/OpenSceneGraph-Data-3.0.0/cow.osgt" );
	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile( "C:/Projekti/VRShop/Dev/OSG/Resources/Models3D/axes.osgt");

	osg::ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);
	
	osg::ref_ptr<osg::Group> root = new osg::Group;

//	root->addChild( model1.get() );
//	root->addChild( model2.get() );
	root->addChild(pModel3D.get());
	root->addChild(axes);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	viewer.setCameraManipulator(new VR::OSGCameraManipulator);
	viewer.addEventHandler( new VR::PickAndDragHandler );

	return viewer.run();
}

