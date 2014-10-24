#include <iostream>

#include "VRProductShopClient.h"

#include <QImageReader>
#include <QMessageBox>
#include <QTimer>

#include "BasicStringDefinitions.h"

#include "VRProductBasketInterfaceItem_GUI.h"

using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductBasketInterfaceItem_GUI::ProductBasketInterfaceItem_GUI(
QFrame *apParent) : QFrame(apParent),m_pProductShopClient(0)	{
	setupUi(this);

	connect(m_pPushButtonDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
	connect(m_pPushButtonRemove,SIGNAL(clicked(bool)),this,SLOT(slotProductRemove()));
	connect(m_pDoubleSpinBoxQuantity,SIGNAL(editingFinished()),this,SLOT(slotSetQuantity()));
	connect(m_pVRQFrameProductItem,SIGNAL(hovered(bool)),this,SLOT(slotProductItemHovered(bool)));

	m_pFrameProductItemHover->setVisible(false);
}

//----------------------------------------------------------------------

ProductBasketInterfaceItem_GUI::ProductBasketInterfaceItem_GUI(
ProductShopClient * apProductShopClient, 
QFrame *apParent) : QFrame(apParent)	{
	setupUi(this);

	m_pProductShopClient = apProductShopClient;

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

ProductShopClient * ProductBasketInterfaceItem_GUI::getProduct()	{
	return m_pProductShopClient;
}

//----------------------------------------------------------------------

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
		emit signalRemoveProduct(m_pProductShopClient);
	} else {
		m_pFrameProductItemHover->setVisible(false);
	}
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::slotSetQuantity()	{
	float flNewQuantity = m_pDoubleSpinBoxQuantity->value();

	emit signalModifyProductQuantity(m_pProductShopClient, flNewQuantity);
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

	string strTextureFile = productParams.m_strTextureFile;

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

//-----------------------------------------------------------------------------------------

void ProductBasketInterfaceItem_GUI::slotSetProductSpinBox(float aflNewProductValue)	{
	m_pDoubleSpinBoxQuantity->setValue(aflNewProductValue);
}