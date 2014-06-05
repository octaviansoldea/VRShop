#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRScene.h"
#include "VRProduct.h"
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
OSGQT_Widget * apOSGQTWidgetMap) :
m_pOSGQTWidget(apOSGQTWidget),
m_pOSGQTWidgetMap(apOSGQTWidgetMap),
m_strDBFileName("")	{	

	//Define a scene as a group
	m_pScene = new Scene();

	//Ref_ptr
	m_pPickAndDragHandlerShopClient = new PickAndDragHandlerShopClient;

	ref_ptr<KeyboardMouseManipulatorShopClient> pKeyboardMouseManipulatorShopClient =
		new KeyboardMouseManipulatorShopClient;

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(pKeyboardMouseManipulatorShopClient);
	m_pOSGQTWidget->addEventHandler(m_pPickAndDragHandlerShopClient);
	m_pOSGQTWidget->show();

	//Map of the Scene
	QLayout * pLayoutMap = dynamic_cast<QLayout *>(m_pOSGQTWidgetMap->layout());
	pLayoutMap->setMargin(2);

	m_pOSGQTWidgetMap->setCameraManipulator(pKeyboardMouseManipulatorShopClient);
	m_pOSGQTWidgetMap->setSceneData(m_pScene);
	m_pOSGQTWidgetMap->show();


	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid();
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	m_pScene->addChild(m_pProductMgr);

	insertProducts();
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

PickAndDragHandlerShopClient * ShoppingPlace::getPicker() const	{
	return m_pPickAndDragHandlerShopClient;
}

//----------------------------------------------------------------------

bool ShoppingPlace::createClientScene()	{
	// ../../../Databases/Untitled.db

	return true;
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

void ShoppingPlace::insertProducts()	{
	ref_ptr < AbstractObject > pAbstractObject = 
		dynamic_cast<AbstractObject*>(AbstractObject::createInstance("Plate3D").get());
	pAbstractObject->predefinedObject();

	ProductParams pParams;
	pParams.m_strProductName = "bla1 bla2 bla3 bla4 bla5 bla6 bla7 bla8";
	pParams.m_flPricePerUnit = 0.85;
	pParams.m_strManufacturerName = "Samsung Corp.";

	Product * pProduct = new Product(pAbstractObject,pParams);
	m_pProductMgr->addNewProduct(pProduct);


//
	pParams.m_strProductName = "bla1 bla2 bla3 bla4 bla5 bla6 bla7 bla8";
	pParams.m_flPricePerUnit = 1.85;
	pParams.m_strManufacturerName = "Nokia Corp.";

	ref_ptr < AbstractObject > pAbstractObject1 = 
		dynamic_cast<AbstractObject*>(AbstractObject::createInstance("Plate3D").get());
	pAbstractObject1->predefinedObject();

	Product * pProduct1 = new Product(pAbstractObject1,pParams);
	m_pProductMgr->addNewProduct(pProduct1);

}