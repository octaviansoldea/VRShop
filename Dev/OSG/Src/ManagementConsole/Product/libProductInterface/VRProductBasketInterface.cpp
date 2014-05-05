#include <iostream>

#include <QDoubleSpinBox>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>

#include "VRQFrame.h"

#include "VRProductBasketInterface.h"

using namespace VR;

//----------------------------------------------------------------------

ProductBasketInterface::ProductBasketInterface(
QToolButton * apToolButtonMyBasket,
QLabel * apLabelBasketCase,
QFrame * apFrameItemsBasket,
//QFrame * apFrameProductItem,
VRQFrame * apVRQFrameProductItem,
QFrame * apFrameProductItemHover,
QDoubleSpinBox * apDoubleSpinBoxQuantity,
QPushButton * apPushButtonDetails,
QPushButton * apPushButtonRemove,
QLabel * apLabelProductImage,
QLabel * apLabelProductInfo,
QLabel * apLabelBasketProductPrice,
QPushButton * apPushButtonBasketBack,
QPushButton * apPushButtonBasketForward)	{

	m_pToolButtonMyBasket = apToolButtonMyBasket;
	m_pLabelBasketCase = apLabelBasketCase;
	m_pFrameItemsBasket = apFrameItemsBasket;
//	m_pFrameProductItem = apFrameProductItem;
	m_pVRQFrameProductItem = apVRQFrameProductItem;
	m_pFrameProductItemHover = apFrameProductItemHover;
	m_pDoubleSpinBoxQuantity = apDoubleSpinBoxQuantity;
	m_pPushButtonDetails = apPushButtonDetails;
	m_pPushButtonRemove = apPushButtonRemove;
	m_pLabelProductImage = apLabelProductImage;
	m_pLabelProductInfo = apLabelProductInfo;
	m_pLabelBasketProductPrice = apLabelBasketProductPrice;
	m_pPushButtonBasketBack = apPushButtonBasketBack;
	m_pPushButtonBasketForward = apPushButtonBasketForward;

	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),this,SLOT(slotMyBasket(bool)));

	connect(m_pPushButtonDetails,SIGNAL(clicked(bool)),this,SLOT(slotProductDetails()));
	connect(m_pPushButtonRemove,SIGNAL(clicked(bool)),this,SLOT(slotProductRemove()));
	connect(m_pDoubleSpinBoxQuantity,SIGNAL(editingFinished()),this,SLOT(slotSetQuantity()));

	connect(m_pPushButtonBasketBack,SIGNAL(clicked(bool)),this,SLOT(slotBasketBack()));
	connect(m_pPushButtonBasketForward,SIGNAL(clicked(bool)),this,SLOT(slotBasketForward()));

	m_pFrameProductItemHover->setVisible(false);

	connect(m_pVRQFrameProductItem,SIGNAL(hovered(bool)),this,SLOT(slotProductItemHovered(bool)));
}

//----------------------------------------------------------------------

ProductBasketInterface::~ProductBasketInterface()	{

}

//=======================================================================

void ProductBasketInterface::slotMyBasket(bool abIndicator)	{
	m_pLabelBasketCase->setVisible(abIndicator);
	m_pFrameItemsBasket->setVisible(abIndicator);
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotProductItemHovered(bool abIndicator)	{
	m_pFrameProductItemHover->setVisible(abIndicator);
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotProductDetails()	{
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotProductRemove()	{
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotSetQuantity()	{
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotBasketBack()	{		
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotBasketForward()	{		
}
