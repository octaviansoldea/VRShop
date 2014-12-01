#include "VRCashier_GUI.h"

#include "VRProductShopClient.h"
#include "VRBasketClient.h"

#include "VRCashierInterface.h"

#include "BasicStringDefinitions.h"

#include <QImageReader>

#include "VRCashierScreenManager.h"

using namespace VR;
using namespace std;

CashierScreenManager::CashierScreenManager(QObject * apParent) : m_pBasket(0), QObject(apParent)	{
	m_pCashier_GUI = new Cashier_GUI;
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	m_pCashierInterface = new CashierInterface(
		m_pCashier_GUI->m_pPushButtonRemove,
		m_pCashier_GUI->m_pPushButtonInfo,
		m_pCashier_GUI->m_pPushButtonProceed
	);

	slotConnections();
}

//------------------------------------------------------------------------------

CashierScreenManager::CashierScreenManager(BasketClient * apBasket, QObject * apParent) : 
m_pBasket(apBasket), QObject(apParent)	{
	m_pCashier_GUI = new Cashier_GUI;
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	m_pCashierInterface = new CashierInterface(
		m_pCashier_GUI->m_pPushButtonRemove,
		m_pCashier_GUI->m_pPushButtonInfo,
		m_pCashier_GUI->m_pPushButtonProceed
	);

	slotConnections();

	m_pCashier_GUI->show();
}

//------------------------------------------------------------------------------

CashierScreenManager::~CashierScreenManager()	{
	delete m_pCashierInterface;
	delete m_pCashier_GUI;
}

//=============================================================================

void CashierScreenManager::slotConnections()	{
	connect(m_pCashier_GUI->m_pPushButtonProceed,SIGNAL(pressed()),this,SLOT(slotProceedAndPayClicked()));
	connect(m_pCashier_GUI->m_pPushButtonInfo,SIGNAL(pressed()),this,SLOT(slotMoreInfoClicked()));

	connect(m_pCashier_GUI->m_pTableWidgetProducts,
		SIGNAL(currentCellChanged(int, int, int, int)), 
		this,
		SLOT(slotChangeImage(int, int, int, int))
	);
	connect(m_pCashier_GUI->m_pPushButtonRemove,SIGNAL(pressed()),this,SLOT(slotRemoveFromBasket()));

	connect(m_pCashier_GUI->m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));
	connect(m_pCashier_GUI->m_pPushButtonStart,SIGNAL(pressed()),this,SLOT(slotStartButtonClicked()));
}

//------------------------------------------------------------------------------

void CashierScreenManager::slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn)	{
	int nRows = m_pCashier_GUI->m_pTableWidgetProducts->rowCount();
	if (currentRow < 0 || 
		currentRow > m_pBasket->count()-1 || 
		nRows < 1)	{
			m_pCashier_GUI->m_pLabelProductImage->clear();
			return;
	}

	ProductShopClient * pProduct = m_pBasket->getProduct(currentRow);
	string strTextureFile = pProduct->getProductTexture();

	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled(
		m_pCashier_GUI->m_pLabelProductImage->width(),
		m_pCashier_GUI->m_pLabelProductImage->height(), 
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
	);

	m_pCashier_GUI->m_pLabelProductImage->setPixmap(imageScaled);
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotRemoveFromBasket()	{
	int nCurrentRow = m_pCashier_GUI->m_pTableWidgetProducts->currentRow();

	if (nCurrentRow<0)	{
		return;
	}

	//Remove from the table
	m_pCashier_GUI->m_pTableWidgetProducts->removeRow(nCurrentRow);

	//Remove from the basket
	m_pBasket->removeProduct(m_pBasket->getProduct(nCurrentRow));

	float flBasketValue = m_pBasket->calculateBasketValue();
	m_pCashier_GUI->m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::addRow()	{
	int row = m_pCashier_GUI->m_pTableWidgetProducts->rowCount();
	m_pCashier_GUI->m_pTableWidgetProducts->insertRow(row);

	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashier_GUI->m_pTableWidgetProducts->setItem(row, 0, item0);
	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashier_GUI->m_pTableWidgetProducts->setItem(row, 1, item1);
	QTableWidgetItem *item2 = new QTableWidgetItem;
	item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashier_GUI->m_pTableWidgetProducts->setItem(row, 2, item2);
	QTableWidgetItem *item3 = new QTableWidgetItem;
	item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashier_GUI->m_pTableWidgetProducts->setItem(row, 3, item3);
	QTableWidgetItem *item4 = new QTableWidgetItem;
	item4->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashier_GUI->m_pTableWidgetProducts->setItem(row, 4, item4);
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotMoreInfoClicked()	{
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotProceedAndPayClicked()	{
	int nSize = m_pBasket->count();

	if (nSize==0)
		return;

}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::init(BasketClient * apBasket)	{
	m_pBasket = apBasket;

	m_pCashier_GUI->show();
}

//--------------------------------------------------------------------------------------------

int CashierScreenManager::getCurrentSelection()	{
	int nItemNumber = m_pCashier_GUI->m_pTableWidgetProducts->currentRow();

	return nItemNumber;
}

//----------------------------------------------------------------------

void CashierScreenManager::slotStartButtonClicked()	{
	m_pCashier_GUI->m_pFrameWelcome->setVisible(false);
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	m_pCashier_GUI->m_pFrameContinue->setVisible(true);

	int nBasketSize = m_pBasket->count();

	if (nBasketSize==0)	{
		m_pCashier_GUI->m_pLabelPrice->setText("0 EUR");
		m_pCashier_GUI->m_pLabelProductImage->setText("");
		return;
	}

	int nRow;
	for (nRow = 0; nRow < nBasketSize; ++nRow) {
		addRow();

		ProductShopClient * pProduct = dynamic_cast<ProductShopClient*>(m_pBasket->getProduct(nRow));

		string strProductName = pProduct->getProductName();
		float flPrice = pProduct->getPrice();
		float flQuantity = pProduct->getQuantity();

		m_pCashier_GUI->m_pTableWidgetProducts->item(nRow, Cashier_GUI::PRODUCT)->setText(strProductName.c_str());
		m_pCashier_GUI->m_pTableWidgetProducts->item(nRow, Cashier_GUI::QUANTITY)->setText(tostr(flQuantity).c_str());
		m_pCashier_GUI->m_pTableWidgetProducts->item(nRow, Cashier_GUI::PRICE)->setText(tostr(flPrice).c_str());
		m_pCashier_GUI->m_pTableWidgetProducts->item(nRow, Cashier_GUI::DISCOUNT)->setText("0.0");
		m_pCashier_GUI->m_pTableWidgetProducts->item(nRow, Cashier_GUI::AMOUNT)->setText(tostr(flPrice*flQuantity).c_str());
	}

	float flBasketValue = m_pBasket->calculateBasketValue();
	m_pCashier_GUI->m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//----------------------------------------------------------------------

bool CashierScreenManager::close()	{
	m_pCashier_GUI->m_pFrameWelcome->setVisible(true);
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	m_pCashier_GUI->hide();

	bool bRes = m_pCashier_GUI->close();

	return bRes;
}

//----------------------------------------------------------------------

void CashierScreenManager::moreProductInfoReceived(string & astrProductData)	{
	//Transform data from the string and initialize appropriate GUI
}