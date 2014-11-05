#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRScene.h"

#include "VRProductShopClient.h"

#include "VRProductManager.h"
#include "VRAvatar.h"
#include "VRAvatarManagerClient.h"
#include "VRVisitor.h"
#include "VRBasketClient.h"
#include "VRProductManagerClient.h"

#include "VRModelViewControllerClient.h"

#include "VRDatabaseInterfaceShopClient.h"

#include "VRFloor.h"
#include "VRRoom.h"
#include "VRLighting.h"

#include "VRAbstractObject.h"

#include "VRPickAndDragHandlerShopClient.h"
#include "VRKeyboardMouseManipulatorShopClient.h"

#include <osgDB/ReadFile>
#include "VRReadAndSaveFileCallback.h"

#include "VROSGQT_Widget.h"

#include "VRShoppingPlace.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace::ShoppingPlace(
OSGQT_Widget * apOSGQTWidget,
OSGQT_Widget * apOSGQTWidgetMap,
string & astrShopScene,
string & astrAvatarName) :
m_pOSGQTWidget(apOSGQTWidget),
m_pOSGQTWidgetMap(apOSGQTWidgetMap),
m_strDBFileName(astrShopScene),
m_strAvatarName(astrAvatarName)	{	

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


	//Insert room
	Room room;
	ref_ptr<MatrixTransform> pMt = dynamic_cast<MatrixTransform*>(room.createRoom().get());
	m_pScene->addChild(pMt.get());


	//A pointer to products sent to the scene
//	m_pProductMgr = new ProductManager;
	Node * pProductsRepresentation = m_ProductManager.getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);

	//Insert Scene objects
	createClientScene(m_strDBFileName);

	//Avatar
	AvatarParams avatarParams;
	avatarParams.m_pKeyboardMouseManipulatorShopClient = pKeyboardMouseManipulatorShopClient;
	avatarParams.m_strAvatarFile = //"../../../Resources/Models3D/avatarOut.osg";
		"C:/Projekti/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
		//"D:/Octavian/Companies/VirtualShop/GitHub/VRShop/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
	avatarParams.m_strAvatarName = m_strAvatarName;
	avatarParams.m_mtrxAvatarMatrix = osg::Matrix(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,-2,0,1);

	m_pAvatar = new Avatar(&avatarParams);
	m_pScene->addChild(m_pAvatar);

	//Get a matrix of the camera in the scene and initialize the camera itself
	Matrix & mtrxCamera = m_pScene->calculateInitialCameraMatrix();
	pKeyboardMouseManipulatorShopClient->setByMatrix(mtrxCamera);

//	pKeyboardMouseManipulatorShopClient->setCameraPredefinedViews((MatrixTransform*)m_pAvatar);
	pKeyboardMouseManipulatorShopClient->setCameraPosition2Object((MatrixTransform*)m_pAvatar);
	m_pAvatar->slotUpdatePosition(false);

	m_pVisitor = new Visitor((Avatar*)m_pAvatar);

	//Other avatars
	m_pAvatarMgr = new AvatarManagerClient(m_pAvatar);
	m_pScene->addChild(m_pAvatarMgr->getAvatars());


	//Insert lighting
	Lighting lighting;
	ref_ptr<LightSource> pNode = lighting.createLights();
    m_pScene->addChild(pNode);

	//Insert products
	insertProducts();

	m_pMVCClient = new ModelViewControllerClient;

	m_pProductMgr = new ProductManagerClient(m_pMVCClient, (BasketClient*)m_pVisitor->getBasket());
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {
	delete m_pAvatarMgr;
	delete m_pProductMgr;
	delete m_pVisitor;
	delete m_pMVCClient;
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShoppingPlace::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

ref_ptr<Node> ShoppingPlace::getProducts()	{
	return m_ProductManager
		.getProductsRepresentation();
}

//----------------------------------------------------------------------

PickAndDragHandlerShopClient * ShoppingPlace::getPicker() const	{
	return m_pPickAndDragHandlerShopClient;
}

//----------------------------------------------------------------------

bool ShoppingPlace::createClientScene(const string & astrSceneFileName)	{
	m_strDBFileName = astrSceneFileName.c_str();

	DatabaseInterfaceShopClientParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName.c_str();

	DatabaseInterfaceShopClient db(dbParams);

	//Get list of objects in the scene
	list<string> lststrSceneObjects = db.getListOfObjects("Untitled");

	ref_ptr<AbstractObject> pAO = 0;

	list<string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int nFindPos1 = it->find_first_of(";");
		const int nFindPos2 = it->find_first_of(";", nFindPos1+1);
		string strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		if (strClassName == "ProductDisplay")	{
			vector<string> vecstrObjectData = db.getObjectData(*it);
			m_ProductManager
				//m_pProductMgr->
				.initFromSQLData(vecstrObjectData);

			continue;
		}

		pAO = AbstractObject::createInstance(strClassName);
		pAO->setDataVariance(Object::STATIC);
		vector<string> vecstrObjectData = db.getObjectData(*it);

		pAO->initFromSQLData(vecstrObjectData);

		//Cashier should be pickable
		if (pAO->getName() == "Cashier")	{
			pAO->setIsTargetPick(true);
		} else {
			pAO->setIsTargetPick(false);
		}

		m_pScene->addChild(pAO);
	}

	return true;
}

//----------------------------------------------------------------------

BasketClient * ShoppingPlace::getBasket()	{
	return m_pVisitor->getBasket();
}

//----------------------------------------------------------------------

AbstractUser * ShoppingPlace::getAbstractUser()	{
	return m_pVisitor;
}

//----------------------------------------------------------------------

void ShoppingPlace::insertProducts()	{
}

//----------------------------------------------------------------------

void ShoppingPlace::avatarClicked(const string & astrAvatarName)	{
}

//----------------------------------------------------------------------

void ShoppingPlace::productClicked(const string & astrProductName)	{
	string strProductName = astrProductName;
	m_pProductMgr->productClicked(strProductName);
}

//----------------------------------------------------------------------

void ShoppingPlace::product2BasketRequest(ProductShopClient * apProduct)	{
	string strUserID = m_pVisitor->getUserIDName();

	m_pProductMgr->addProduct2Basket(strUserID,apProduct);
}

//----------------------------------------------------------------------

void ShoppingPlace::removeProductRequest(ProductShopClient * apProduct)	{
	string strUserID = m_pVisitor->getUserIDName();

	m_pProductMgr->removeProductRequest(strUserID,apProduct);
}

//----------------------------------------------------------------------

void ShoppingPlace::modifyProductQuantityRequest(ProductShopClient * apProduct, float aflNewQuantity)	{
	string strUserID = m_pVisitor->getUserIDName();

	m_pProductMgr->modifyProductQuantityRequest(strUserID,apProduct,aflNewQuantity);
}

//----------------------------------------------------------------------

void ShoppingPlace::purchaseRequest()	{
	m_pVisitor->payRequest();
}

//----------------------------------------------------------------------

ModelViewControllerClient * ShoppingPlace::getModelViewController() const	{
	return m_pMVCClient;
}