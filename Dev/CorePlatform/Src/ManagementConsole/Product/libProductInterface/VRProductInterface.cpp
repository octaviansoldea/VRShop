#include <string>
#include <iostream>

#include "VRProductShopClient.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QTimer>
#include <QCursor>

#include "BasicStringDefinitions.h"

#include "VRProductInterface.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductInterface::ProductInterface(
	QFrame * apFrameProductInterface,
	QLabel * apLabelProductInterfaceImage,
	QLabel * apLabelProductInterfaceInfo,
	QPushButton * apPushButtonProductInterface2Basket,
	QPushButton * apPushButtonProductInterfaceDetails,
	QLabel * apLabelProductInterfacePrice)	{

	m_pFrameProductInterface = apFrameProductInterface;
	m_pLabelProductInterfaceImage = apLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo = apLabelProductInterfaceInfo;
	m_pPushButtonProductInterface2Basket = apPushButtonProductInterface2Basket;
	m_pPushButtonProductInterfaceDetails = apPushButtonProductInterfaceDetails;
	m_pLabelProductInterfacePrice = apLabelProductInterfacePrice;

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);

	//Signal/slot connections
	connect(m_pPushButtonProductInterfaceDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
}

//=======================================================================

void ProductInterface::init(const ProductShopClient * apProductShopClient)	{
	if (apProductShopClient == 0)	{
		return;
	}

	m_ProductShopClient = *apProductShopClient;
	ProductShopClientParams productParams;
	m_ProductShopClient.getParams(productParams);

	string strPrice = productParams.m_strCurrency + " " + tostr(productParams.m_flPricePerUnit).c_str();
	m_pLabelProductInterfacePrice->setText(strPrice.c_str());

	string strTextureFile = productParams.m_strTextureFile;
	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled ( m_pLabelProductInterfaceImage->width(),m_pLabelProductInterfaceImage->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelProductInterfaceImage->setPixmap(imageScaled);

	string & strProductName = productParams.m_strProductName;
	string & strManufacturer = productParams.m_strProductManufacturer;
	m_pLabelProductInterfaceInfo->setText((strProductName + "\n" + strManufacturer).c_str());	//Product name and manufacturer

	//Geometry
	QPoint cursor(QCursor::pos());
	int x = cursor.x();
	int y = cursor.y();

	m_pFrameProductInterface->setGeometry(x,y,m_pFrameProductInterface->width(),m_pFrameProductInterface->height());
	m_pLabelProductInterfacePrice->setGeometry(x+(m_pFrameProductInterface->width()-m_pLabelProductInterfacePrice->width())/2,
									(m_pFrameProductInterface->y()-8),
									m_pLabelProductInterfacePrice->width(), m_pLabelProductInterfacePrice->height());

	m_pFrameProductInterface->show();
	m_pLabelProductInterfacePrice->show();


	//This timer closes interface
	QTimer::singleShot(1000,this,SLOT(slotCloseInterface()));
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotProductDetails()	{
}

//-----------------------------------------------------------------------------------------

void ProductInterface::slotCloseInterface()	{
	if (m_pFrameProductInterface->underMouse())	{
		QTimer::singleShot(1000,this,SLOT(slotCloseInterface()));
		return;
	}

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);

	m_pFrameProductInterface->close();
	m_pLabelProductInterfacePrice->close();
}

//----------------------------------------------------------------------------------------

void ProductInterface::setGeometry()	{
}

//----------------------------------------------------------------------------------------

void ProductInterface::slotProductInitialized(const ProductShopClient * apProductShopClient)	{
	init(apProductShopClient);

	m_pFrameProductInterface->show();
	m_pLabelProductInterfacePrice->show();
}

//----------------------------------------------------------------------------------------

ProductShopClient * ProductInterface::getProduct()	{
	return &m_ProductShopClient;
}