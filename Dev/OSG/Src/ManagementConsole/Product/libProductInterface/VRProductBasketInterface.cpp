#include <iostream>

#include <QDoubleSpinBox>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>

#include <QEvent>

#include "VRProductBasketInterface.h"

using namespace VR;

//----------------------------------------------------------------------

ProductBasketInterface::ProductBasketInterface(
QToolButton * apToolButtonMyBasket,
QLabel * apLabelBasketCase,
QFrame * apFrameItemsBasket,
QFrame * apFrameProductItem,
QFrame * apFrameProductItemHover,
QDoubleSpinBox * apDoubleSpinBoxQuantity,
QPushButton * apPushButtonHoverDetails,
QPushButton * apPushButtonHoverRemove,
QLabel * apLabelProductImage,
QLabel * apLabelProductInfo,
QLabel * apLabelBasketProductPrice,
QPushButton * apPushButtonBasketBack,
QPushButton * apPushButtonBasketForward)	{

	m_pToolButtonMyBasket = apToolButtonMyBasket;
	m_pLabelBasketCase = apLabelBasketCase;
	m_pFrameItemsBasket = apFrameItemsBasket;
	m_pFrameProductItem = apFrameProductItem;
	m_pFrameProductItemHover = apFrameProductItemHover;
	m_pDoubleSpinBoxQuantity = apDoubleSpinBoxQuantity;
	m_pPushButtonHoverDetails = apPushButtonHoverDetails;
	m_pPushButtonHoverRemove = apPushButtonHoverRemove;
	m_pLabelProductImage = apLabelProductImage;
	m_pLabelProductInfo = apLabelProductInfo;
	m_pLabelBasketProductPrice = apLabelBasketProductPrice;
	m_pPushButtonBasketBack = apPushButtonBasketBack;
	m_pPushButtonBasketForward = apPushButtonBasketForward;

	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),this,SLOT(slotMyBasket(bool)));
	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),this,SLOT(slotMyBasket(bool)));

	connect(m_pPushButtonHoverDetails,SIGNAL(clicked(bool)),this,SLOT(slotHoverDetails()));
	connect(m_pPushButtonHoverRemove,SIGNAL(clicked(bool)),this,SLOT(slotHoverRemove()));
	connect(m_pDoubleSpinBoxQuantity,SIGNAL(editingFinished()),this,SLOT(slotSetQuantity()));

	connect(m_pPushButtonBasketBack,SIGNAL(clicked(bool)),this,SLOT(slotBasketBack()));
	connect(m_pPushButtonBasketForward,SIGNAL(clicked(bool)),this,SLOT(slotBasketForward()));

	m_pFrameProductItemHover->setVisible(false);
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

void ProductBasketInterface::slotProductItemHovered()	{
	m_pFrameProductItemHover->setVisible(true);
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotHoverDetails()	{
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotHoverRemove()	{
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
