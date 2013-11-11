#include "VRShopBuilder.h"

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() {	
	setupUi(this);

	//Define a scene as a group
	pScene = new Group;

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(pScene);
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);

	//Get geometry from the GUI for compatibility
	m_pOSGQTWidget->setGeometry(this->x(), this->y(), this->width(), this->height());
	m_pOSGQTWidget->setWindowTitle("Qt widget window");

	//To get a widget without a "TitleBar"
//	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);

	m_pOSGQTWidget->show();

	//SIGNAL/SLOT CONNECTIONS
	signalSlotComm();
}


//=========================================================================================

void ShopBuilder::signalSlotComm()	{
//	QObject::connect(pushButton, SIGNAL(clicked()),this, SLOT(changeColor()));	
}