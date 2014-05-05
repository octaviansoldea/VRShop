#include <string>

#include "VRProduct.h"
#include "VRPickAndDragHandlerShopClient.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>

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
	PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient)	{

	m_pFrameProductInterface = apFrameProductInterface;
	m_pLabelProductInterfaceImage = apLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo = apLabelProductInterfaceInfo;
	m_pPushButtonProductInterface2Basket = apPushButtonProductInterface2Basket;
	m_pPushButtonProductInterfaceDetails = apPushButtonProductInterfaceDetails;
	m_pLabelProductInterfacePrice = apLabelProductInterfacePrice;
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

void ProductInterface::initProductInterface(const Product * apProduct)	{
	const Product * pProduct = apProduct;
	ProductParams productParams;
	pProduct->getParams(productParams);

	m_pLabelProductInterfacePrice->setText(("EUR " + tostr(productParams.m_flPricePerUnit)).c_str());

	string strTextureFile = "../../../Resources/Textures/samsung-galaxy-s5.bmp";
	QImageReader image(strTextureFile.c_str());
	QPixmap ImageBasic(QPixmap::fromImageReader(&image));
	QPixmap ImageScaled(ImageBasic.scaled ( m_pLabelProductInterfaceImage->width(),m_pLabelProductInterfaceImage->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelProductInterfaceImage->setPixmap(ImageScaled);

	string & strProductName = productParams.m_strProductName;
	string & strManufacturer = productParams.m_strManufacturerName;
	m_pLabelProductInterfaceInfo->setText(string(strProductName + "\n" + strManufacturer).c_str());	//Product name and manufacturer

	m_pFrameProductInterface->setVisible(true);
	m_pLabelProductInterfacePrice->setVisible(true);
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotAdd2Basket()	{
	/*
		Add selected product into the basket
		Basket is defined in a class Client
	*/
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotProductDetails()	{
}
