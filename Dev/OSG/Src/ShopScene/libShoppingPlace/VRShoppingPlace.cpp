#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRScene.h"
#include "VRProduct.h"
#include "VRProductManager.h"
#include "VRAvatar.h"
#include "VRAvatarManagerClient.h"

#include "VRDatabaseManagerShopClient.h"

#include "VRFloor.h"
#include "VRRoom.h"

#include "VRFurniture.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"
#include "VRUntransformedPlate2D.h"

#include "VRPickAndDragHandlerShopClient.h"
#include "VRKeyboardMouseManipulatorShopClient.h"

#include <osgDB/ReadFile>
#include "VRReadAndSaveFileCallback.h"

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

	//Reuse of textures => memory optimization taken from "OSG Cookbook"
	osgDB::Registry::instance()->setReadFileCallback(new VR::ReadAndSaveFileCallback);
	osgDB::Registry::instance()->getOrCreateSharedStateManager();
	osgDB::SharedStateManager* ssm = osgDB::Registry::instance()->getSharedStateManager();
	if(ssm) {
		ssm->share(m_pScene.get());
	}

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

	m_pOSGQTWidgetMap->setSceneData(m_pScene);
	m_pOSGQTWidgetMap->setCameraManipulator(pKeyboardMouseManipulatorShopClient,false);
	m_pOSGQTWidgetMap->show();

	//Insert axes
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);

	//Insert Scene objects
	m_strDBFileName = "../../../Databases/Shop.db";
	createClientScene(m_strDBFileName.toStdString());

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);

//	insertProducts();

	//Avatar
	AvatarParams avatarParams;
	avatarParams.m_pKeyboardMouseManipulatorShopClient = pKeyboardMouseManipulatorShopClient;
	avatarParams.m_strAvatarFile = "../../../Resources/Models3D/avatarOut.osg";
	avatarParams.m_strAvatarName = "avatar";

	ref_ptr<Avatar> pAvatar = new Avatar(&avatarParams);
	m_pScene->addChild(pAvatar);

	pKeyboardMouseManipulatorShopClient->setCameraPosition2Object(pAvatar);


	//Other avatars
	m_pAvatarMgr = new AvatarManagerClient(pAvatar);
	m_pScene->addChild(m_pAvatarMgr->getAvatars());


	//Insert room
	Room room;
	ref_ptr<MatrixTransform> pMt = dynamic_cast<MatrixTransform*>(room.createRoom());
	pMt->setMatrix(osg::Matrix::translate(-20,0,0));
	m_pScene->addChild(pMt.get());
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {
	delete m_pProductMgr;
	delete m_pAvatarMgr;
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShoppingPlace::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

ref_ptr<Node> ShoppingPlace::getProducts()	{
	return m_pProductMgr->getProductsRepresentation();
}

//----------------------------------------------------------------------

PickAndDragHandlerShopClient * ShoppingPlace::getPicker() const	{
	return m_pPickAndDragHandlerShopClient;
}

//----------------------------------------------------------------------

bool ShoppingPlace::createClientScene(const string & astrSceneFileName)	{
	m_strDBFileName = astrSceneFileName.c_str();

	DatabaseManagerShopClientParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName;

	DatabaseManagerShopClient db(dbParams);

	//Get list of objects in the scene
	list<string> lststrSceneObjects = db.getListOfObjects("Untitled");

	ref_ptr<AbstractObject> pAO = 0;

	list<string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int & nFindPos1 = it->find_first_of(";");
		const int & nFindPos2 = it->find_first_of(";", nFindPos1+1);
		string & strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		pAO = AbstractObject::createInstance(strClassName);
		pAO->setDataVariance(Object::STATIC);
		vector<string> & vecstrObjectData = db.getObjectData(*it);

		pAO->initFromSQLData(vecstrObjectData);
		pAO->setIsTargetPick(false);

		m_pScene->addChild(pAO);
	}

	return true;
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