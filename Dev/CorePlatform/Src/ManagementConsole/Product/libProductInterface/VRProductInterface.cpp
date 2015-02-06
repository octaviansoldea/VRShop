#include <string>
#include <iostream>
#include <fstream>

#include "VRProductShopClient.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QTimer>
#include <QCursor>

#include "BasicStringDefinitions.h"

#include "VRClient.h"
#include "VRProductManagerClient.h"

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
	QLabel * apLabelProductInterfacePrice,
	Client * apClient)	{

	m_pFrameProductInterface = apFrameProductInterface;
	m_pLabelProductInterfaceImage = apLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo = apLabelProductInterfaceInfo;
	m_pPushButtonProductInterface2Basket = apPushButtonProductInterface2Basket;
	m_pPushButtonProductInterfaceDetails = apPushButtonProductInterfaceDetails;
	m_pLabelProductInterfacePrice = apLabelProductInterfacePrice;

	m_pClient = apClient;

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);

	//Signal/slot connections
	connect(m_pPushButtonProductInterfaceDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
}

//=======================================================================

void ProductInterface::init(const ProductShopClient * apProductShopClient)	{
	ProductShopClientParams productParams;
	m_ProductShopClient.getParams(productParams);

	string strPrice = productParams.m_strCurrency + " " + tostr(productParams.m_flPricePerUnit).c_str();
	m_pLabelProductInterfacePrice->setText(strPrice.c_str());

	string strTextureFile = productParams.m_strTextureFile;
	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled(
		m_pLabelProductInterfaceImage->width(),m_pLabelProductInterfaceImage->height(),
//		Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
		Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation)
	);
	m_pLabelProductInterfaceImage->setPixmap(imageScaled);

	string & strProductName = productParams.m_strProductName;
	string & strManufacturer = productParams.m_strProductManufacturer;
	QString qstrInterfaceText(tr(
		"<html><head/><body><span style=' font-size:10px; font-style:bold;'> %1 </span>"
		"<br><span style='font-size:8px; font-style:italic;color:white;'> %2 </span></br></body></html>")
		.arg(strProductName.c_str()).arg(strManufacturer.c_str())
	);
	m_pLabelProductInterfaceInfo->setText(qstrInterfaceText);

	//Geometry
	QPoint cursor(QCursor::pos());
	int x = cursor.rx();
	int y = cursor.ry();

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

ProductShopClient * ProductInterface::getProduct()	{
	return &m_ProductShopClient;
}

//----------------------------------------------------------------------------------------

void ProductInterface::productClicked(const std::string & astrProductName)	{
	string strProductName = astrProductName;

	ProductManagerClient pmc(m_pClient);
	pmc.productClicked(strProductName);
}

//----------------------------------------------------------------------------------------

void ProductInterface::removeProductRequest(ProductShopClient * apProduct)	{
	string strUserID = tostr(m_pClient->getUserID());

	ProductManagerClient pmc(m_pClient);
	pmc.removeProductRequest(strUserID,apProduct);
}

//----------------------------------------------------------------------------------------

void ProductInterface::productClickedRespond(QDataStream & aDataStream)	{
	QString qstrDataFromServer;
	aDataStream >> qstrDataFromServer;

	m_ProductShopClient.initFromSQLData(qstrDataFromServer.toStdString());

	init(&m_ProductShopClient);
}