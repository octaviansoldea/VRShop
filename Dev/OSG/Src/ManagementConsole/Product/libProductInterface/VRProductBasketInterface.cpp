#include <iostream>

#include <QDoubleSpinBox>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>

#include "VRQFrame.h"

#include "VRProductShopClient.h"

#include "VRProductBasketInterfaceItem_GUI.h"
#include "VRProductBasketInterfaceController.h"

#include "VRBasket.h"

#include "VRProductBasketInterface.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductBasketInterface::ProductBasketInterface(
QToolButton * apToolButtonMyBasket,
QLabel * apLabelBasketCase,
QFrame * apFrameItemsBasket,
QPushButton * apPushButtonBasketBack,
QPushButton * apPushButtonBasketForward) : 
m_nHandlePosition(0),m_nItemsVisible(5), m_pBasket(0)	{

	m_pToolButtonMyBasket = apToolButtonMyBasket;
	m_pLabelBasketCase = apLabelBasketCase;
	m_pFrameItemsBasket = apFrameItemsBasket;
	m_pPushButtonBasketBack = apPushButtonBasketBack;
	m_pPushButtonBasketForward = apPushButtonBasketForward;

	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),this,SLOT(slotMyBasket(bool)));

	connect(m_pPushButtonBasketBack,SIGNAL(clicked(bool)),this,SLOT(slotBasketBack()));
	connect(m_pPushButtonBasketForward,SIGNAL(clicked(bool)),this,SLOT(slotBasketForward()));

	connect(m_pBasket,SIGNAL(signalBasketChanged(const int &,bool)),this,SLOT(slotUpdateItemView(const int &,bool)));

	m_pProductBasketInterfaceController = new ProductBasketInterfaceController(m_pBasket);

	setupBasketInterface();
}

//----------------------------------------------------------------------

ProductBasketInterface::~ProductBasketInterface()	{
	m_lstProductItemGUI.clear();

	delete m_pProductBasketInterfaceController;
}

//======================================================================

void ProductBasketInterface::setBasket(Basket * apBasket)	{
	m_pBasket = apBasket;
}

//----------------------------------------------------------------------

void ProductBasketInterface::slotMyBasket(bool abIndicator)	{
	m_pLabelBasketCase->setVisible(abIndicator);
	m_pFrameItemsBasket->setVisible(abIndicator);
}

//----------------------------------------------------------------------

void ProductBasketInterface::slotBasketBack()	{
	if (m_pBasket == 0 || m_nHandlePosition==0)	{
		return;
	}

	m_nHandlePosition--;

	ProductShopClient * pProduct = m_pBasket->getProduct(m_nHandlePosition);
	setData(pProduct,false);
	initGeometry();

}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotBasketForward()	{
	if (m_pBasket == 0)
		return;

	//Items are put on a line not in a circle
	int nSize = m_pBasket->count();
	int nDiff = nSize - m_nItemsVisible;
	if (m_nHandlePosition > nDiff || (m_nHandlePosition+m_nItemsVisible)==nSize)	{
		return;
	}

	ProductShopClient * pProduct = m_pBasket->getProduct(m_nHandlePosition+m_nItemsVisible);
	setData(pProduct);
	initGeometry();

	m_nHandlePosition++;
}

//-----------------------------------------------------------------------------------------

ProductBasketInterfaceItem_GUI * ProductBasketInterface::getProductItemGUI(int anPosition)	{
	if (anPosition < m_lstProductItemGUI.size())	{
		list<ProductBasketInterfaceItem_GUI*>::iterator it = m_lstProductItemGUI.begin();
		advance(it,anPosition);
		return (*it);
	} else {
		return (ProductBasketInterfaceItem_GUI*)0;
	}
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::initGeometry()	{
	int nSize = m_pBasket->count();

	if (nSize==0)
		return;

	int nI, nX, nY;
	list<VR::ProductBasketInterfaceItem_GUI*>::iterator it;

	nI=0;
	for (it = m_lstProductItemGUI.begin(); it != m_lstProductItemGUI.end(); it++)	{
		nX = 44 + (nI)*93;
		nY = 1;

		(*it)->setGeometry(nX,nY,(*it)->width(),(*it)->height());
		nI++;
	}
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::slotUpdateItemView(const int & anIndex, bool abIsAdded)	{
	int nIndex = anIndex;

	if (nIndex < m_nHandlePosition)	{
	//Change done before the viewed items. Correct index of the first item: m_nHandlePosition
		m_nHandlePosition--;
	} else {
	//Change done amid viewed items.
		list<ProductBasketInterfaceItem_GUI*>::iterator it = m_lstProductItemGUI.begin();
		if (abIsAdded)	{
//			m_nHandlePosition = (anIndex == m_nHandlePosition) ? m_nHandlePosition+1 : m_nHandlePosition;
			ProductShopClient * pProduct = m_pBasket->getProduct(anIndex);
			setData(pProduct,false);
		} else {
			int nSize = m_pBasket->count();
			int nAbsolutePosition = m_nHandlePosition+m_nItemsVisible;

			//Get GUI from the list that needs to be deleted
			ProductBasketInterfaceItem_GUI * pProductGUICurrent = getProductItemGUI(anIndex-m_nHandlePosition);
			delete pProductGUICurrent;
			m_lstProductItemGUI.remove(pProductGUICurrent);

			ProductShopClient * pProduct = 0;
			ProductBasketInterfaceItem_GUI * pProductGUIItem = 0;

			if (m_nHandlePosition>0)	{
				pProductGUIItem = 
					new ProductBasketInterfaceItem_GUI(m_pProductBasketInterfaceController,m_pFrameItemsBasket);
				if (nAbsolutePosition==nSize+1)	{
					m_nHandlePosition -= 1;
					pProduct = m_pBasket->getProduct(m_nHandlePosition);
					m_lstProductItemGUI.push_front(pProductGUIItem);
				} else {
					pProduct = m_pBasket->getProduct(nAbsolutePosition-1);
					m_lstProductItemGUI.push_back(pProductGUIItem);
				}
			} else if (m_nHandlePosition==0 && nAbsolutePosition<nSize+1)	{
				pProduct = m_pBasket->getProduct(m_nItemsVisible-1);
				pProductGUIItem = 
					new ProductBasketInterfaceItem_GUI(m_pProductBasketInterfaceController,m_pFrameItemsBasket);
				m_lstProductItemGUI.push_back(pProductGUIItem);
			}

			if (pProduct != 0)
				pProductGUIItem->init(pProduct);

			//This one has to be always executed
			initGeometry();
			return;
		}
	}
	initGeometry();
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::setData(ProductShopClient * apProduct, bool abAppend)	{
	if (apProduct == 0)
		return;

	//Create new GUI and insert it into the container
	ProductBasketInterfaceItem_GUI * pProductGUIItem
		= new ProductBasketInterfaceItem_GUI(m_pProductBasketInterfaceController,m_pFrameItemsBasket);
	pProductGUIItem->init(apProduct);

	//Put it into the list of GUIs
	if (m_lstProductItemGUI.size() < m_nItemsVisible)	{
		m_lstProductItemGUI.push_back(pProductGUIItem);
	} else {
		int nIndex = (abAppend) ? 0 : m_nItemsVisible-1;
		ProductBasketInterfaceItem_GUI * pCurrent = getProductItemGUI(nIndex);
		//Delete redundant GUI
		delete pCurrent;

		if (abAppend)	{
			//Delete first element, add new element to the tail
			m_lstProductItemGUI.pop_front();
			m_lstProductItemGUI.push_back(pProductGUIItem);
		} else {
			//Delete last element, add new element to the front
			m_lstProductItemGUI.pop_back();
			m_lstProductItemGUI.push_front(pProductGUIItem);
		}
	}
}

//-----------------------------------------------------------------------------------------

void ProductBasketInterface::setupBasketInterface()	{
	if(m_pBasket == 0)
		return;

	int nI;
	int nCount = m_pBasket->count();

	//Which condition is smaller (basket size or number of items shown)
	int nSize = (m_nItemsVisible < nCount) ? m_nItemsVisible : nCount;

	ProductShopClient * pProduct = 0;
	for (nI=0;nI<nSize;nI++)	{
		pProduct = m_pBasket->getProduct(nI);
		setData(pProduct);
	}
	initGeometry();
}