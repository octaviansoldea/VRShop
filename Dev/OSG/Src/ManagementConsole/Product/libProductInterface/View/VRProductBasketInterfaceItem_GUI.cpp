#include <iostream>

#include "VRProductShopClient.h"
#include "VRProductBasketInterfaceController.h"

#include <QImageReader>
#include <QMessageBox>
#include <QTimer>

#include "BasicStringDefinitions.h"

#include <time.h>

#include "VRProductBasketInterfaceItem_GUI.h"

using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductBasketInterfaceItem_GUI::ProductBasketInterfaceItem_GUI(
ProductBasketInterfaceController * apProductBasketInterfaceController,
QFrame *apParent) : QFrame(apParent),m_pProductShopClient(0)	{
	setupUi(this);

	m_pProductBasketInterfaceController = apProductBasketInterfaceController;

	connect(m_pPushButtonDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
	connect(m_pPushButtonRemove,SIGNAL(clicked(bool)),this,SLOT(slotProductRemove()));
	connect(m_pDoubleSpinBoxQuantity,SIGNAL(editingFinished()),this,SLOT(slotSetQuantity()));
	connect(m_pVRQFrameProductItem,SIGNAL(hovered(bool)),this,SLOT(slotProductItemHovered(bool)));

	m_pFrameProductItemHover->setVisible(false);
}

//----------------------------------------------------------------------

ProductBasketInterfaceItem_GUI::ProductBasketInterfaceItem_GUI(
ProductShopClient * apProductShopClient, 
ProductBasketInterfaceController * apProductBasketInterfaceController,
QFrame *apParent) : QFrame(apParent)	{
	setupUi(this);

	m_pProductShopClient = apProductShopClient;
	m_pProductBasketInterfaceController = apProductBasketInterfaceController;

	connect(m_pPushButtonDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
	connect(m_pPushButtonRemove,SIGNAL(clicked(bool)),this,SLOT(slotProductRemove()));
	connect(m_pDoubleSpinBoxQuantity,SIGNAL(editingFinished()),this,SLOT(slotSetQuantity()));

	m_pFrameProductItemHover->setVisible(false);

	connect(m_pVRQFrameProductItem,SIGNAL(hovered(bool)),this,SLOT(slotProductItemHovered(bool)));

	init(m_pProductShopClient);
}

//----------------------------------------------------------------------

ProductBasketInterfaceItem_GUI::~ProductBasketInterfaceItem_GUI()	{
}

//=====================================================================

void ProductBasketInterfaceItem_GUI::slotProductItemHovered(bool abIndicator)	{
	m_pFrameProductItemHover->setVisible(abIndicator);
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::slotProductDetails()	{

}

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::slotProductRemove()	{
	QMessageBox msgBox;
	QString aqstrMessage = "Press OK to remove selected product, else press Cancel";
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
	msgBox.setWindowTitle("Warning window");
	int nRes = msgBox.exec();

	//remove product from the basket
	if (nRes == QMessageBox::Ok)	{
		m_pProductBasketInterfaceController->removeProduct(m_pProductShopClient);
		//Report forward that this product should be removed from the basket
	} else {
		m_pFrameProductItemHover->setVisible(false);
	}
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::slotSetQuantity()	{
	float flQuantity = m_pDoubleSpinBoxQuantity->value();

	m_pProductShopClient->setQuantity(flQuantity);
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::init(ProductShopClient * apProductShopClient)	{
	if (apProductShopClient == 0)
		return;

	m_pProductShopClient = apProductShopClient;
	ProductShopClientParams productParams;
	m_pProductShopClient->getParams(productParams);

	string strPrice = productParams.m_strCurrency + " " + tostr(productParams.m_flPricePerUnit).c_str();
	m_pLabelBasketProductPrice->setText(strPrice.c_str());

	string arrstrTest[] = {"../../../Resources/Textures/samsung-galaxy-s5.bmp",
							"../../../Resources/Textures/Banana.bmp",
							"../../../Resources/Textures/blueFlowers.bmp",
							"../../../Resources/Textures/Avatar_1.bmp",
								"../../../Resources/Textures/brick.bmp",
								"../../../Resources/Textures/facade.bmp",
								"../../../Resources/Textures/facade1.bmp",
								"../../../Resources/Textures/facade2.bmp"};

	srand(time(0));
	int nI = rand() % 7;

	string strTextureFile = arrstrTest[nI];

	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled ( m_pLabelProductImage->width(),m_pLabelProductImage->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelProductImage->setPixmap(imageScaled);

	string strProductName = productParams.m_strProductName;
	m_pLabelProductInfo->setText(strProductName.c_str());	//Product name and manufacturer

	m_pDoubleSpinBoxQuantity->setValue(productParams.m_flQuantity);
	m_pFrameProductItemHover->setVisible(false);

	show();
}