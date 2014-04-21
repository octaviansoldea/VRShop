#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRScene.h"
#include "VRProductManager.h"

#include "VRFurniture.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"

#include "VRPickAndDragHandlerShopClient.h"
#include "VRKeyboardMouseManipulatorShopClient.h"

#include <osgDB/ReadFile>

#include "VRGrid.h"
#include "OSGQT_Widget.h"

#include "VRShoppingPlace.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace::ShoppingPlace(
OSGQT_Widget * apOSGQTWidget,
PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient) :
m_pOSGQTWidget(apOSGQTWidget),
m_strDBFileName("../../../Databases/Untitled.db")	{	

	//Define a scene as a group
	m_pScene = new Scene();

	PickAndDragHandlerShopClient * pPickAndDragHandlerShopClient = apPickAndDragHandlerShopClient;
	
	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopClient);
	m_pOSGQTWidget->addEventHandler(pPickAndDragHandlerShopClient);

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid();
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	m_pProductMgr = new ProductManager();
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {
	
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShoppingPlace::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

ref_ptr<ProductManager> ShoppingPlace::getProducts() const	{
	return m_pProductMgr;
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
