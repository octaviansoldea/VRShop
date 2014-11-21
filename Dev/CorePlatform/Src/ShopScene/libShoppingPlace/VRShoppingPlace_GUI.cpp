#include <string>
#include <iostream>

#include <QPoint>
#include <QMouseEvent>
#include <QtWidgets/QSpacerItem>
#include <QVBoxLayout>

#include "VRScene.h"
#include "VRShoppingPlace.h"
#include "VRProductManager.h"
#include "VRAbstractObject.h"

#include "VRProductInterface.h"
#include "VRAgentInterface.h"
#include "VRProductBasketInterface.h"
#include "VRCameraController.h"

#include "VRModelViewControllerClient.h"

#include "VRCashierScreenManager.h"
#include "VRServerClientCommands.h"

#include "VRKeyboardMouseManipulatorShopClient.h"
#include "VRPickAndDragHandlerShopClient.h"

#include "VRShoppingPlace_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace_GUI::ShoppingPlace_GUI(string & astrFileName, std::string & astrAvatarName)	{	
	setupUi(this);
	setWindowTitle("Shop Client");

	m_pShoppingPlace = new ShoppingPlace(
		m_pOSGQTWidget,m_pOSGQTWidgetMap,astrFileName,astrAvatarName);

	KeyboardMouseManipulatorShopClient * pCameraManipulator = 
		dynamic_cast<KeyboardMouseManipulatorShopClient *>(m_pOSGQTWidget->getCameraManipulator());

	BasketClient * pBasket = m_pShoppingPlace->getBasket();
	AbstractUser * pUser = m_pShoppingPlace->getAbstractUser();

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
		m_pPushButtonSignIn,
		m_pPushButtonSignOut,
		m_pPushButtonRemoveAccount,
		m_pPushButtonChangeSettings,
		pUser);

	//Basket Interface
	m_pProductBasketInterface = new ProductBasketInterface(
		m_pToolButtonMyBasket,
		m_pLabelBasketCase,
		m_pFrameItemsBasket,
		m_pPushButtonBasketBack,
		m_pPushButtonBasketForward,
		pBasket);

	//Client Camera
	m_pCameraController = new CameraController(
		m_pToolButton1View,
		m_pToolButton3View,
		pCameraManipulator);

	updateGeometry();

	m_pCashierScreenManager = new CashierScreenManager(this->centralWidget());

	signalSlotConnections();
}

//-----------------------------------------------------------------------------------------

ShoppingPlace_GUI::~ShoppingPlace_GUI()	{
	delete m_pProductInterface;
	delete m_pAgentInterface;
	delete m_pProductBasketInterface;
	delete m_pCameraController;
	delete m_pCashierScreenManager;
	delete m_pShoppingPlace;
}

//=========================================================================================

void ShoppingPlace_GUI::updateGeometry()	{
	int x = centralWidget()->x();
	int y = centralWidget()->y();

	int width = centralWidget()->width();
	int height = centralWidget()->height();

	m_pOSGQTWidgetMap->setGeometry(x+width-m_pOSGQTWidgetMap->width()-10,y+10,m_pOSGQTWidgetMap->width(),m_pOSGQTWidgetMap->height());

	m_pFrameItemsBasket->setGeometry((x+width-m_pFrameItemsBasket->width())/2,
									(y+height-m_pFrameItemsBasket->height()),
									m_pFrameItemsBasket->width(), m_pFrameItemsBasket->height());
	m_pLabelBasketCase->setGeometry(m_pFrameItemsBasket->x()+(m_pFrameItemsBasket->width()-m_pLabelBasketCase->width())/2,
									(m_pFrameItemsBasket->y()-20),
									m_pLabelBasketCase->width(), m_pLabelBasketCase->height());

	m_pLabelLegalNotice->setGeometry(5,(y+height-m_pLabelLegalNotice->height()),m_pLabelLegalNotice->width(), m_pLabelLegalNotice->height());

	m_pLabelLogoRetailer->setGeometry(10,10,m_pLabelLogoRetailer->width(),m_pLabelLogoRetailer->height());


	//Layouts
	//View buttons
	QVBoxLayout viewLayout;
	viewLayout.insertWidget(0,m_pToolButton1View);
	viewLayout.insertWidget(1,m_pToolButton3View);
	viewLayout.setSpacing(0);
	QRect rect;
	rect.setRect(x+width-m_pToolButton1View->width()-10,
				m_pOSGQTWidgetMap->y()+m_pOSGQTWidgetMap->height()+10,
				m_pToolButton1View->width(),60);
	viewLayout.setGeometry(rect);

	//Top fields
	QGridLayout topLayout;
	topLayout.addItem(new QSpacerItem(5,40,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding),0,0,2,1);
	topLayout.addWidget(m_pToolButtonUser,0,1,2,1);
	topLayout.addWidget(m_pLineEditUserName,0,2,1,1);
	topLayout.addWidget(m_pLineEditPassword,1,2,1,1);
	topLayout.addWidget(m_pPushButtonSignIn,0,3,2,1);
	topLayout.addWidget(m_pToolButtonMyBasket,0,4,2,1);
	topLayout.addItem(new QSpacerItem(5,40,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding),0,5,2,1);
	topLayout.setVerticalSpacing(4);
	topLayout.setHorizontalSpacing(10);

	QRect rect1;
	rect1.setRect(-250+(x+width)/2,10,500,40);
	topLayout.setGeometry(rect1);
}

//=========================================================================================

void ShoppingPlace_GUI::signalSlotConnections()	{
	//Add product to basket
	connect(m_pPushButtonProductInterface2Basket,SIGNAL(clicked(bool)),this,SLOT(slotAdd2Basket()));

	//Remove product
	connect(m_pProductBasketInterface,SIGNAL(signalProductBasketChangeRequest(ProductShopClient * )),
		this,SLOT(slotRemoveProduct(ProductShopClient *)));

	//Modify product
	connect(m_pProductBasketInterface,SIGNAL(signalProductBasketModifyRequest(ProductShopClient *, float)),
		this,SLOT(slotModifyProductQuantity(ProductShopClient *, float)));

	//Product interface manipulation
	ModelViewControllerClient * pMVCClient = m_pShoppingPlace->getModelViewController();
	connect(pMVCClient, SIGNAL(signalNewProductQuantity(float)),
		m_pProductBasketInterface,SIGNAL(signalSetSpinBoxProduct(float)));

	connect(pMVCClient, SIGNAL(signalProductInitialized(const ProductShopClient * )),
		m_pProductInterface,SLOT(slotProductInitialized(const ProductShopClient * )));

	//Cashier operations
	connect(m_pCashierScreenManager,SIGNAL(signalCashierOperation(int)),
		this,SLOT(slotProcesRequest(int)));


	PickAndDragHandlerShopClient * pPickAndDragHandlerShopClient = m_pShoppingPlace->getPicker();
	//Product clicked
	connect(pPickAndDragHandlerShopClient,
		SIGNAL(signalProductPicked(const AbstractObject *)),
		this,
		SLOT(slotProductClicked(const AbstractObject *))
	);

	//cashier clicked
	connect(pPickAndDragHandlerShopClient,
		SIGNAL(signalCashierPicked()),
		this,
		SLOT(slotCashierClicked())
	);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::resizeEvent(QResizeEvent *event)	{
	QWidget::resizeEvent(event);

	updateGeometry();
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotProductClicked(const AbstractObject * apAbstractObject)	{
	string strProductName = apAbstractObject->getName();

	m_pShoppingPlace->productClicked(strProductName);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotAdd2Basket()	{
	ProductShopClient * pProduct = m_pProductInterface->getProduct();
	m_pShoppingPlace->product2BasketRequest(pProduct);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotRemoveProduct(ProductShopClient * apProduct)	{
	m_pShoppingPlace->removeProductRequest(apProduct);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotModifyProductQuantity(ProductShopClient * apProduct, float aflNewQuantity)	{	
	m_pShoppingPlace->modifyProductQuantityRequest(apProduct, aflNewQuantity);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotCashierClicked()	{
	QObject * pParent = this->centralWidget();
	BasketClient * pBasket = m_pShoppingPlace->getBasket();
	m_pCashierScreenManager->init(pBasket,pParent);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotAvatarClicked(const string & astrAvatarName)	{
	m_pShoppingPlace->avatarClicked(astrAvatarName);
}

//----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotProcesRequest(int anRequestOperation)	{
	switch (anRequestOperation)	{
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			m_pShoppingPlace->purchaseRequest();
			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			int nSelectedProduct = m_pCashierScreenManager->getCurrentSelection();
			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			break;
		}
	default:
		{
			break;
		}

		//	m_pShoppingPlace->processCashierRequest(astrRequestOperation);
	}
}

//----------------------------------------------------------------------------------------
