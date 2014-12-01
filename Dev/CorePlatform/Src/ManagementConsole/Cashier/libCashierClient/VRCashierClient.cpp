#include "VRCashier_GUI.h"

#include "VRProductShopClient.h"
#include "VRBasketClient.h"

#include "BasicStringDefinitions.h"

#include <QPushButton>
#include <QImageReader>

#include "VRCashierClient.h"

using namespace VR;
using namespace std;

CashierClient::CashierClient(QObject * apParent) : m_pBasket(0), QObject(apParent)	{
	m_pCashier_GUI = new Cashier_GUI;
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	slotConnections();
}

//------------------------------------------------------------------------------

CashierClient::CashierClient(BasketClient * apBasket, QObject * apParent) : 
m_pBasket(apBasket), QObject(apParent)	{
	m_pCashier_GUI = new Cashier_GUI;
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	slotConnections();

	m_pCashier_GUI->show();
}

//------------------------------------------------------------------------------

CashierClient::~CashierClient()	{
	delete m_pCashier_GUI;
}

//=============================================================================

void CashierClient::slotConnections()	{
	connect(m_pCashier_GUI->m_pTableWidgetProducts,
		SIGNAL(currentCellChanged(int, int, int, int)), 
		this,
		SLOT(slotChangeImage(int, int, int, int))
	);
	connect(m_pCashier_GUI->m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));

	//Initialize otherwise private members to be used inside ShoppingPlace_GUI
	m_pPushButtonStart = m_pCashier_GUI->m_pPushButtonStart;
	m_pPushButtonRemove = m_pCashier_GUI->m_pPushButtonRemove;
	m_pPushButtonInfo = m_pCashier_GUI->m_pPushButtonInfo;
	m_pPushButtonProceed = m_pCashier_GUI->m_pPushButtonProceed;
}

//------------------------------------------------------------------------------

void CashierClient::slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn)	{
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

void CashierClient::removeFromBasket()	{
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

void CashierClient::addRow()	{
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

void CashierClient::launchCashier()	{
	m_pCashier_GUI->show();
}

//--------------------------------------------------------------------------------------------

void CashierClient::init(BasketClient * apBasket)	{
	m_pBasket = apBasket;

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

//--------------------------------------------------------------------------------------------

int CashierClient::getCurrentSelection()	{
	int nItemNumber = m_pCashier_GUI->m_pTableWidgetProducts->currentRow();

	return nItemNumber;
}

//----------------------------------------------------------------------

bool CashierClient::close()	{
	m_pCashier_GUI->m_pFrameWelcome->setVisible(true);
	m_pCashier_GUI->m_pFrameContinue->setVisible(false);

	m_pCashier_GUI->hide();

	bool bRes = m_pCashier_GUI->close();

	return bRes;
}

//----------------------------------------------------------------------

void CashierClient::moreProductInfoReceived(string & astrProductData)	{
	//Transform data from the string and initialize appropriate GUI
}