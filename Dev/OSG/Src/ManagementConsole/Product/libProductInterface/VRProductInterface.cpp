#include <string>
#include <iostream>

#include "VRProduct.h"
#include "VRProductShopClient.h"
#include "VRProductManagerClient.h"
#include "VRBasket.h"

#include "VRPickAndDragHandlerShopClient.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QTimer>
#include <QCursor>

#include <osg/Group>
#include "BasicStringDefinitions.h"

#include "VRProductInterface.h"

using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

ProductInterface::ProductInterface(
	QFrame * apFrameProductInterface,
	QLabel * apLabelProductInterfaceImage,
	QLabel * apLabelProductInterfaceInfo,
	QPushButton * apPushButtonProductInterface2Basket,
	QPushButton * apPushButtonProductInterfaceDetails,
	QLabel * apLabelProductInterfacePrice,
	Basket * apBasket,
	PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient) : m_pProductShopClient(0)	{

	m_pFrameProductInterface = apFrameProductInterface;
	m_pLabelProductInterfaceImage = apLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo = apLabelProductInterfaceInfo;
	m_pPushButtonProductInterface2Basket = apPushButtonProductInterface2Basket;
	m_pPushButtonProductInterfaceDetails = apPushButtonProductInterfaceDetails;
	m_pLabelProductInterfacePrice = apLabelProductInterfacePrice;
	m_pBasket = apBasket;
	m_pPickAndDragHandlerShopClient = apPickAndDragHandlerShopClient;

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);

	//Signal/slot connections
	connect(m_pPushButtonProductInterfaceDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
	connect(m_pPushButtonProductInterface2Basket,SIGNAL(clicked(bool)),this,SLOT(slotAdd2Basket()));
}

//----------------------------------------------------------------------

ProductInterface::~ProductInterface()	{
}

//=======================================================================

void ProductInterface::init(const ProductShopClient * apProductShopClient)	{
	const ProductShopClient * pProduct = apProductShopClient;
	ProductShopClientParams productParams;
	pProduct->getParams(productParams);

	string & strPrice = productParams.m_strCurrency + " " + tostr(productParams.m_flPricePerUnit).c_str();
	m_pLabelProductInterfacePrice->setText(strPrice.c_str());

	string strTextureFile = productParams.m_strTextureFile;
	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled ( m_pLabelProductInterfaceImage->width(),m_pLabelProductInterfaceImage->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelProductInterfaceImage->setPixmap(imageScaled);

	string & strProductName = productParams.m_strProductName;
	string & strManufacturer = productParams.m_strProductManufacturer;
	m_pLabelProductInterfaceInfo->setText((strProductName + "\n" + strManufacturer).c_str());	//Product name and manufacturer

	m_pFrameProductInterface->setVisible(true);
	m_pLabelProductInterfacePrice->setVisible(true);

	//This timer closes interface
	QTimer::singleShot(1000,this,SLOT(slotCloseInterface()));
}

//-----------------------------------------------------------------------------------------

void ProductInterface::init(const string & astrProductName)	{
	//Get mouse coordinates at the click
	QPoint cursor(QCursor::pos());
	int & x = cursor.rx();
	int & y = cursor.ry();

	m_pFrameProductInterface->setGeometry(x,y,m_pFrameProductInterface->width(),m_pFrameProductInterface->height());
	m_pLabelProductInterfacePrice->setGeometry(x+(m_pFrameProductInterface->width()-m_pLabelProductInterfacePrice->width())/2,
									(m_pFrameProductInterface->y()-8),
									m_pLabelProductInterfacePrice->width(), m_pLabelProductInterfacePrice->height());
	m_ProductMgrClient.initProduct(astrProductName);
	connect(&m_ProductMgrClient,SIGNAL(signalProductInitialized()),this,SLOT(slotGetProduct()));
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotGetProduct()	{
	m_pProductShopClient = m_ProductMgrClient.getProduct();
	if (m_pProductShopClient!=0)
		init(m_pProductShopClient);
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotAdd2Basket()	{
	if (m_pProductShopClient != 0)	{
		ProductShopClientParams pParams;
		m_pProductShopClient->getParams(pParams);
		
		ProductShopClient * pProduct = new ProductShopClient(pParams);
		m_pBasket->addProduct(pProduct);
	}
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotProductDetails()	{
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotCloseInterface()	{
	if (m_pFrameProductInterface->underMouse())	{
		QTimer::singleShot(100,this,SLOT(slotCloseInterface()));
		return;
	}

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);
}

//----------------------------------------------------------------------------------------

void ProductInterface::setGeometry()	{
}