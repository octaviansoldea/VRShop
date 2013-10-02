#include "OSGQT_GUI.h"

#include "OSGCameraManipulator.h"
#include "OSGPicker.h"

#include <osgDB/ReadFile>

#include "Model2D.h"
#include "Model3D.h"

using namespace osg;
using namespace Ui;

//----------------------------------------------------------------------

void main_Model2D(ref_ptr<Group> pScene)	{
	ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(Vec4(1.0, 0.0, 0.0, 1.0));
	pModel2D->setIsTargetPick(true);
	pScene->addChild(pModel2D);
}

//----------------------------------------------------------------------

void main_Model3D(ref_ptr<Group> pScene)	{
	ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);
	pScene->addChild(pModel3D);
}

//----------------------------------------------------------------------

OSGQT_GUI::OSGQT_GUI() {	
	setupUi(this);

	//Define a scene as a group
	pScene = new Group;

	//Send scene to the Widget
	m_pOSGQT_Widget->setSceneData(pScene);
	m_pOSGQT_Widget->setCameraManipulator(new VR::OSGCameraManipulator);
	m_pOSGQT_Widget->addEventHandler( new VR::PickAndDragHandler );

	//Get geometry from the GUI for compatibility
	m_pOSGQT_Widget->setGeometry(this->x(), this->y(), this->width(), this->height());
	m_pOSGQT_Widget->setWindowTitle("Qt widget window");

	//To get a widget without a "TitleBar"
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);

	m_pOSGQT_Widget->show();

	//SIGNAL/SLOT CONNECTIONS
	signalSlotComm();
}

//=========================================================================================

void OSGQT_GUI::addToScene()	{

	//Add parallelepiped to the scene
	osg::ref_ptr<osg::Group> grp = new osg::Group;
	osg::ref_ptr<osg::Group> grp1 = new osg::Group;

	main_Model3D(grp);
	main_Model2D(grp1);

	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile("../../Resources/axes.osgt");

	pScene->addChild(axes);
	pScene->addChild(grp);
	pScene->addChild(grp1);
}

//=========================================================================================

void OSGQT_GUI::removeFromScene()	{
	unsigned int nChildNumber = 0;
	pScene->removeChild(nChildNumber);

//	pScene->removeChildren(0,pScene->getNumChildren());	//To clear the scene
}

//=========================================================================================
void OSGQT_GUI::signalSlotComm()	{
	QObject::connect(m_pQAddButton, SIGNAL(clicked()),this, SLOT(addToScene()));
	QObject::connect(m_pQRemoveButton, SIGNAL(clicked()),this, SLOT(removeFromScene()));
}