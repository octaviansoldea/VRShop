#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRFurniture.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"

#include "VRPickAndDragHandler.h"
#include "VRKeyboardMouseManipulator.h"

#include <osgDB/ReadFile>

#include "OSGQT_Widget.h"

#include "VRShoppingPlace.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace::ShoppingPlace() {	

	m_qstrFileName = "../../../Databases/Temp.db";

	//Define a scene as a group
	m_pScene = new Group;
	m_pObjects = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);

	m_pGridlines = new Grid;	
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {	
}

//----------------------------------------------------------------------

void ShoppingPlace::init(OSGQT_Widget * apOSGQTWidget) {
	m_pOSGQTWidget = apOSGQTWidget;

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new VR::KeyboardMouseManipulator);
	m_pOSGQTWidget->addEventHandler(new VR::PickAndDragHandler);
	
 	m_pScene->addChild(m_pGridlines);
}

//----------------------------------------------------------------------

void ShoppingPlace::gridOnOff(bool abIndicator) {
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
