#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

#include "OSGQT_Widget.h"

#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() {	

	//Define a scene as a group
	m_pScene = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);

	m_pGridlines = new Grid;
}

//----------------------------------------------------------------------

void ShopBuilder::init(OSGQT_Widget * apOSGQTWidget) {
	m_pOSGQTWidget = apOSGQTWidget;

		//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);

	m_pScene->addChild(m_pGridlines);
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	if (abIndicator) {
		m_pGridlines = new Grid;
		m_pScene->addChild(m_pGridlines);
	}
	else {
		m_pScene->removeChild(m_pGridlines);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const std::string & astrDBFileName)
{

}