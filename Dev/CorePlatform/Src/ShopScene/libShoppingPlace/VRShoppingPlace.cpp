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
#include "VRCustomer.h"
#include "VRBasket.h"

#include "VRDatabaseManagerShopClient.h"

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

	//Insert axes
//	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
//	m_pScene->addChild(pAxes);

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
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

	m_pAvatar = new Avatar(&avatarParams);
	m_pScene->addChild(m_pAvatar);

	pKeyboardMouseManipulatorShopClient->setCameraPosition2Object(m_pAvatar);
	m_pAvatar->slotUpdatePosition(false);

	m_pAbstractUser = new Visitor(m_pAvatar);
	m_pBasket = m_pAbstractUser->getBasket();

	//Other avatars
	m_pAvatarMgr = new AvatarManagerClient(m_pAvatar);
	m_pScene->addChild(m_pAvatarMgr->getAvatars());


	//Insert room
	Room room;
	ref_ptr<MatrixTransform> pMt = dynamic_cast<MatrixTransform*>(room.createRoom().get());
	m_pScene->addChild(pMt.get());


	//Insert lighting
	Lighting lighting;
	ref_ptr<LightSource> pNode = lighting.createLights();
    m_pScene->addChild(pNode);

	//Insert products
	insertProducts();
}

//----------------------------------------------------------------------

ShoppingPlace::~ShoppingPlace() {
	delete m_pProductMgr;
	delete m_pAvatarMgr;
	delete m_pAbstractUser;
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
	dbParams.m_qstrDBName = m_strDBFileName.c_str();

	DatabaseManagerShopClient db(dbParams);

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
			m_pProductMgr->initFromSQLData(vecstrObjectData);

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

Basket * ShoppingPlace::getBasket()	{
	return m_pBasket;
}

//----------------------------------------------------------------------

AbstractUser * ShoppingPlace::getAbstractUser()	{
	return m_pAbstractUser;
}

//----------------------------------------------------------------------

void ShoppingPlace::insertProducts()	{
}