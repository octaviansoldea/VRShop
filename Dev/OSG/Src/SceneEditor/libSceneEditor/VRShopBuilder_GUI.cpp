#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI() {	
	setupUi(this);

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_ShopBuilder.m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);

	setWindowTitle("VR Shop Server Dialog");

	m_pOSGQTWidget->show();

	//SIGNAL/SLOT CONNECTIONS
	buildConnections();
}


//=========================================================================================

void ShopBuilder_GUI::buildConnections() {
	//	QObject::connect(pushButton, SIGNAL(clicked()),this, SLOT(changeColor()));	
}