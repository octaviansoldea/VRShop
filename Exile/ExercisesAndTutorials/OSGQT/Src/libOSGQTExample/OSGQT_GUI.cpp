#include "OSGQT_GUI.h"

#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include "Model2D.h"
#include "Model3D.h"

using namespace osg;
using namespace Ui;

//----------------------------------------------------------------------

void main_Model2D(ref_ptr<Group> pScene)	{
	ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(Vec4(1.0, 0.0, 0.0, 1.0));
	pScene->addChild(pModel2D);
}

//----------------------------------------------------------------------

void main_Model3D(ref_ptr<Group> pScene)	{
	ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(Vec4(0.0, 1.0, 0.0, 1.0));
	pScene->addChild(pModel3D);
}

//----------------------------------------------------------------------

OSGQT_GUI::OSGQT_GUI() {	
	setupUi(this);

	//Define a scene as a group
	pScene = new Group;

	//add axes to the scene
	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile("../Resources/axes.osgt");
	pScene->addChild(axes);

	//elements of the scene are grouped into "pElements"
	ref_ptr<Group> pElements = new Group;
	//1. front plate
	main_Model2D(pElements);
	pScene->addChild(pElements);

	//Send scene to the Widget
	m_pOSGQT_Widget->setSceneData(pScene);
	m_pOSGQT_Widget->setCameraManipulator(new osgGA::TrackballManipulator);

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
	ref_ptr<Group> pElements = new Group;

	//Add parallelepiped to the scene
	main_Model3D(pElements);

	pScene->addChild(pElements);	//Auto-generated index
//	pScene->insertChild(pScene->getNumChildren(),pElements);	//Put into the concrete position
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