#include "OSG_GUI.h"

#include <osgGA/TrackballManipulator>

#include "OSGCameraManipulator.h"

#include <osgDB/ReadFile>


using namespace osg;
using namespace Ui;

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
	m_pOSGQTWidget->setSceneData(pScene);
//	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);
	m_pOSGQTWidget->setCameraManipulator(new VR::OSGCameraManipulator);

	//Get geometry from the GUI for compatibility
	m_pOSGQTWidget->setGeometry(this->x(), this->y(), this->width(), this->height());
	m_pOSGQTWidget->setWindowTitle("Qt widget window");

	//To get a widget without a "TitleBar"
//	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);

	m_pOSGQTWidget->show();

	addToScene();
	//SIGNAL/SLOT CONNECTIONS
	signalSlotComm();
}

//=========================================================================================

void OSGQT_GUI::addToScene()	{
	ref_ptr<Group> grp = new Group;
	main_Model3D(grp);
	pScene->addChild(grp);
}

void OSGQT_GUI::changeColor()	{
	ref_ptr<Node> pNode = dynamic_cast<Node*>(pScene->getChild(0));
	ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->addChild(pNode.get());
	pModel3D->setColor(Vec4(1, 1,1,1));
	pScene->removeChild(pNode);
	pScene->addChild(pModel3D);
}

//=========================================================================================

void OSGQT_GUI::signalSlotComm()	{
//	QObject::connect(pushButton, SIGNAL(clicked()),this, SLOT(changeColor()));	
}