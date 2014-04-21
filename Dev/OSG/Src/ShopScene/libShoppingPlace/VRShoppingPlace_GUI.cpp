#include <string>
#include <iostream>

#include "VRScene.h"
#include "VRShoppingPlace.h"

#include "VRProductInterface.h"
#include "VRAgentInterface.h"
#include "VRProductBasketInterface.h"
#include "VRCameraController.h"

#include "VRKeyboardMouseManipulatorShopClient.h"
#include "VRPickAndDragHandlerShopClient.h"

#include "VRShoppingPlace_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace_GUI::ShoppingPlace_GUI()	{	
	setupUi(this);
	setWindowTitle("Shop Client");

	m_pPickAndDragHandlerShopClient = new PickAndDragHandlerShopClient;

	m_pShoppingPlace = new ShoppingPlace(m_pOSGQTWidget,m_pPickAndDragHandlerShopClient);
	KeyboardMouseManipulatorShopClient * pCameraManipulator = 
		dynamic_cast<KeyboardMouseManipulatorShopClient *>(m_pOSGQTWidget->getCameraManipulator());

	Scene * pScene = m_pShoppingPlace->getScene();

	QGridLayout * pLayoutMap = dynamic_cast<QGridLayout *>(m_pOSGQTWidgetMap->layout());
	pLayoutMap->setMargin(1);

	m_pOSGQTWidgetMap->setCameraManipulator(pCameraManipulator);
	m_pOSGQTWidgetMap->setSceneData(pScene);
	m_pOSGQTWidgetMap->show();

	//ProductInterface
	m_pProductInterface = new ProductInterface(
		m_pFrameProductInterface,
		m_pLabelProductInterfaceImage,
		m_pLabelProductInterfaceInfo,
		m_pPushButtonProductInterface2Basket,
		m_pPushButtonProductInterfaceDetails,
		m_pLabelProductInterfacePrice);

	//Agent Interface
	m_pAgentInterface = new AgentInterface(
		m_pFrameSettings,
		m_pToolButtonUser,
		m_pLineEditPassword,
		m_pLineEditUserName,
		m_pPushButtonSignIn);


	//Basket Interface
	m_pProductBasketInterface = new ProductBasketInterface(
		m_pToolButtonMyBasket,
		m_pLabelBasketCase,
		m_pFrameItemsBasket,
		m_pFrameProductItem,
		m_pFrameProductItemHover,
		m_pDoubleSpinBoxQuantity,
		m_pPushButtonHoverDetails,
		m_pPushButtonHoverRemove,
		m_pLabelProductImage,
		m_pLabelProductInfo,
		m_pLabelBasketProductPrice,
		m_pPushButtonBasketBack,
		m_pPushButtonBasketForward);


	//Client Camera
	m_pCameraController = new CameraController(
		m_pToolButton1View,
		m_pToolButton3View,
		pCameraManipulator);

	m_pOSGQTWidget->show();
	buildConnections();

}

//-----------------------------------------------------------------------------------------

ShoppingPlace_GUI::~ShoppingPlace_GUI()	{
	delete m_pProductInterface;
	delete m_pAgentInterface;
	delete m_pProductBasketInterface;
	delete m_pCameraController;

	delete m_pShoppingPlace;
}

//=========================================================================================

void ShoppingPlace_GUI::buildConnections() {

	connect(m_pPickAndDragHandlerShopClient,SIGNAL(signalProductPicked()),this,SLOT(slotProductClicked()));

//	connect(m_pFrameProductItem_2,SIGNAL(hovered()),this,SLOT(slotProductClicked()));

	
}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::updateGeometry()	{
	int x = centralWidget()->x();
	int y = centralWidget()->y();

	int width = centralWidget()->width();
	int height = centralWidget()->height();

//	m_pToolButtonMyBasket->setGeometry((x+width)/2,y+5,m_pToolButtonMyBasket->width(),m_pToolButtonMyBasket->height());

	m_pOSGQTWidgetMap->setGeometry(x+width-m_pOSGQTWidgetMap->width()-10,y+10,m_pOSGQTWidgetMap->width(),m_pOSGQTWidgetMap->height());

	m_pFrameItemsBasket->setGeometry((x+width-m_pFrameItemsBasket->width())/2,(y+height-m_pFrameItemsBasket->height()),m_pFrameItemsBasket->width(), m_pFrameItemsBasket->height());
	m_pLabelBasketCase->setGeometry(m_pFrameItemsBasket->x()+(m_pFrameItemsBasket->width()-m_pLabelBasketCase->width())/2,(m_pFrameItemsBasket->y()-20),m_pLabelBasketCase->width(), m_pLabelBasketCase->height());

	m_pLabelLegalNotice->setGeometry(5,(y+height-m_pLabelLegalNotice->height()),m_pLabelLegalNotice->width(), m_pLabelLegalNotice->height());
}

//=========================================================================================

void ShoppingPlace_GUI::slotProductClicked()	{
//	Product * pProduct = m_pPickAndDragHandlerShopClient->m_pPickedObject->get;
//	m_pProductInterface->initProductInterface();
	std::cout << "It's working" << std::endl;
}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::resizeEvent(QResizeEvent *event)	{
	QWidget::resizeEvent(event);

	updateGeometry();
}