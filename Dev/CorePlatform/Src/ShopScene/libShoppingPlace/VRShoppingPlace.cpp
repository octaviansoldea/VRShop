#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include <osgDB/ReadFile>

#include "VRAppData.h"

#include "VRScene.h"

#include "VRProductShopClient.h"

#include "VRClient.h"

#include "VRProductManager.h"
#include "VRAvatar.h"
#include "VRAvatarManagerClient.h"
#include "VRVisitor.h"
#include "VRBasketClient.h"
#include "VRProductManagerClient.h"
#include "VRCashierManagerClient.h"
#include "VRAgentManagerClient.h"

#include "VRModelViewControllerClient.h"

#include "VRDatabaseInterfaceShopClient.h"

#include "VRFloor.h"
#include "VRRoom.h"
#include "VRLighting.h"

#include "VRAbstractObjectFactory.h"
#include "VRAbstractObject.h"

#include "VRPickAndDragHandlerShopClient.h"
#include "VRKeyboardMouseManipulatorShopClient.h"

#include "VRReadAndSaveFileCallback.h"

#include "VROSGQT_Widget.h"

#include "VRShoppingPlace.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace::ShoppingPlace(
Client * apClient,
OSGQT_Widget * apOSGQTWidget,
OSGQT_Widget * apOSGQTWidgetMap,
string & astrShopScene,
string & astrAvatarName) :
m_pClient(apClient),
m_pOSGQTWidget(apOSGQTWidget),
m_pOSGQTWidgetMap(apOSGQTWidgetMap),
m_strDBFileName(astrShopScene),
m_strAvatarName(astrAvatarName)	{
	//Define a scene as a group
	m_pScene = new Scene();

	//Reuse of textures => memory optimization taken from "OSG Cookbook"
	osgDB::Registry::instance()->setReadFileCallback(new VR::ReadAndSaveFileCallback);	//To optimize texture loading
	osgDB::Registry::instance()->setReadFileCallback(new VR::ReadAndSaveNodeCallback);	//To optimize avatar loading
	osgDB::Registry::instance()->getOrCreateSharedStateManager();
	osgDB::SharedStateManager* ssm = osgDB::Registry::instance()->getSharedStateManager();
	if(ssm) {
		ssm->share(m_pScene.get());
	}

	//Ref_ptr
	m_pPickAndDragHandlerShopClient = new PickAndDragHandlerShopClient;

	ref_ptr<KeyboardMouseManipulatorShopClient> pKeyboardMouseManipulatorShopClient =
		new KeyboardMouseManipulatorShopClient((Node*)m_pScene);

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
	ref_ptr<Node> pProductsRepresentation = m_ProductManager.getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);

	//Insert Scene objects
	createClientScene(m_strDBFileName);

	//Avatar
	AvatarParams avatarParams;
	avatarParams.m_pKeyboardMouseManipulatorShopClient = pKeyboardMouseManipulatorShopClient;
	avatarParams.m_strAvatarFile = 
			AppData::getFPathResources() + "/Models3D/avatarOut.osg";
			//"http://cdn.rawgit.com/octaviansoldea/VRShop/master/Dev/CorePlatform/Resources/Models3D/avatarOut.osg";
	
	avatarParams.m_strAvatarName = m_strAvatarName;
	avatarParams.m_mtrxAvatarMatrix = osg::Matrix(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,-2,0,1);

	m_pAvatar = new Avatar(&avatarParams);
	m_pScene->addChild(m_pAvatar);

	//Get a matrix of the camera in the scene and initialize the camera itself
	Matrix mtrxCamera = m_pScene->calculateInitialCameraMatrix();
	pKeyboardMouseManipulatorShopClient->setByMatrix(mtrxCamera);

//	pKeyboardMouseManipulatorShopClient->setCameraPredefinedViews((MatrixTransform*)m_pAvatar);
	pKeyboardMouseManipulatorShopClient->setCameraPosition2Object((MatrixTransform*)m_pAvatar);
	m_pAvatar->slotUpdatePosition(false);

	m_pVisitor = new Visitor((Avatar*)m_pAvatar);

	//Other avatars
	m_pAvatarMgr = new AvatarManagerClient(m_pClient, m_pAvatar);
	m_pScene->addChild(m_pAvatarMgr->getAvatars());


	//Insert lighting
	Lighting lighting;
	ref_ptr<LightSource> pNode = lighting.createLights();
    m_pScene->addChild(pNode);

	//Insert products
	insertProducts();

	m_pMVCClient = new ModelViewControllerClient;

	BasketClient * pBasket = m_pVisitor->getBasket();
	m_pProductMgr = new ProductManagerClient(m_pClient);
	m_pCashierMgr = new CashierManagerClient(m_pClient, m_pMVCClient, pBasket);
	m_pAgentMgr = new AgentManagerClient(m_pClient,m_pVisitor);

	//Product created for the ProductManager purposes
	m_pProduct = new ProductShopClient;
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {
	delete m_pAvatarMgr;
	delete m_pProductMgr;
	delete m_pCashierMgr;
	delete m_pVisitor;
	delete m_pMVCClient;

	delete m_pProduct;
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShoppingPlace::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

ref_ptr<Node> ShoppingPlace::getProducts()	{
	return m_ProductManager.getProductsRepresentation();
}

//----------------------------------------------------------------------

PickAndDragHandlerShopClient * ShoppingPlace::getPicker() const	{
	return m_pPickAndDragHandlerShopClient;
}

//----------------------------------------------------------------------

AgentManagerClient * ShoppingPlace::getAgentManagerClient()	{
	return m_pAgentMgr;
}

//----------------------------------------------------------------------

bool ShoppingPlace::createClientScene(const string & astrSceneFileName)	{
	m_strDBFileName = astrSceneFileName.c_str();

	DatabaseInterfaceShopClientParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName.c_str();

	DatabaseInterfaceShopClient db(dbParams);

	//Get list of objects in the scene
	list<string> lststrSceneObjects = db.getListOfObjects("Untitled");

	list<string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int nFindPos1 = it->find_first_of(";");
		const int nFindPos2 = it->find_first_of(";", nFindPos1+1);
		string strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		if (strClassName == "ProductDisplay")	{
			vector<string> vecstrObjectData = db.getObjectData(*it);
			m_ProductManager.initFromSQLData(vecstrObjectData);

			continue;
		}

		ref_ptr<AbstractObject> pAO = AbstractObjectFactory::createAbstractObject(strClassName);
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

AbstractUser * ShoppingPlace::getAbstractUser()	{
	return m_pVisitor;
}

//----------------------------------------------------------------------

bool ShoppingPlace::isUserAuthorized() const	{
	bool bIsUserAuthorized = m_pVisitor->getIsUserAuthorized();
	return bIsUserAuthorized;
}

//----------------------------------------------------------------------

void ShoppingPlace::insertProducts()	{
}

//----------------------------------------------------------------------

void ShoppingPlace::avatarClicked(const string & astrAvatarName)	{
}

//----------------------------------------------------------------------

void ShoppingPlace::product2BasketRequest(ProductShopClient * apProduct)	{
	ProductManagerClient::ProductManagerClientParams aPMCP;
	aPMCP.m_strUserIDName = m_pVisitor->getUserIDName();
	aPMCP.m_flProductQuantity = 1.0;
	aPMCP.m_strProductName = apProduct->getProductName();
	aPMCP.m_pProduct = apProduct;

	m_pProductMgr->addProduct2Basket(aPMCP);
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

//----------------------------------------------------------------------

void ShoppingPlace::handleClientData()	{
	QByteArray data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	out >> nType;

	switch (nType)	{
	//RELATES TO THE PRODUCT MANAGER CLIENT
	case ServerClientCommands::PRODUCT_REQUEST:
		{
			m_pProductMgr->initProductFromData(out,m_pProduct);

			emit m_pMVCClient->signalProductInitialized(m_pProduct);
			
			break;
		}
	case ServerClientCommands::PRODUCT_TO_BASKET_REQUEST:
		{
			ProductShopClient * pProduct = new ProductShopClient;
			bool bRes = m_pProductMgr->addProduct2Basket(out, pProduct);

			if (bRes == false)	{
				delete pProduct;
			} else {
				bRes = m_pVisitor->addProduct2Basket(pProduct);

				if (bRes == false)
					delete pProduct;
			}
			break;
		}
	case ServerClientCommands::REMOVE_PRODUCT_REQUEST:
		{
			ProductShopClient * pProduct = m_pProductMgr->removeProductFromBasket(out);
			m_pVisitor->removeProductFromBasket(pProduct);

			break;
		}
	case ServerClientCommands::MODIFY_PRODUCT_REQUEST:
		{
			float flNewValue = m_pProductMgr->modifyProductQuantityRequest(out);
			emit m_pMVCClient->signalNewProductQuantity(flNewValue);

			break;
		}

	//RELATES TO THE AVATAR MANAGER CLIENT
	case ServerClientCommands::AVATAR_REGISTER:
		{
			m_pAvatarMgr->registerAvatarReceived(out);
			break;
		}
	case ServerClientCommands::AVATAR_UPDATE:
		{
			break;
		}
	case ServerClientCommands::OTHER_AVATARS_REQUEST:
		{
			m_pAvatarMgr->otherAvatarsReceived(out);
			break;
		}

	//RELATES TO THE CASHIER MANAGER CLIENT
	case ServerClientCommands::REMOVE_FROM_CASHIER_REQUEST:
		{
			bool bRes = m_pCashierMgr->removeFromBasketData(out);
			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			m_pCashierMgr->productInfoData(out);
			break;
		}
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			m_pCashierMgr->basketPurchaseData(out);
			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			break;
		}

	//RELATES TO THE AGENT MANAGER CLIENT
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			bool bRes = m_pAgentMgr->signInRespond(out);
			break;
		}

	case ServerClientCommands::SIGN_UP_REQUEST:
		{
			bool bRes = m_pAgentMgr->signUpRespond(out);
			break;
		}

	case ServerClientCommands::SIGN_OUT_REQUEST:
		{
			bool bRes = m_pAgentMgr->signOutRespond(out);
			break;
		}

	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST:
		{
			bool bRes = m_pAgentMgr->modifyAccountRespond(out);
			break;
		}
	default:
		{
			break;
		}
	}
}