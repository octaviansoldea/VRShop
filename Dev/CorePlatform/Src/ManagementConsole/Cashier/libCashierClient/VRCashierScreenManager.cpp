#include "VRCashierWelcome_GUI.h"
#include "VRCashierProceed_GUI.h"

#include "VRProductShopClient.h"
#include "VRBasketClient.h"

#include "BasicStringDefinitions.h"

#include <QImageReader>

#include "VRServerClientCommands.h"

#include "VRCashierScreenManager.h"

using namespace VR;
using namespace std;

CashierScreenManager::CashierScreenManager(QObject * apParent) : QObject(apParent)	{
	m_pCashierWelcome_GUI = new CashierWelcome_GUI();
	m_pCashierProceed_GUI = new CashierProceed_GUI();

	connect(m_pCashierProceed_GUI->m_pPushButtonProceed,SIGNAL(pressed()),this,SLOT(slotProceedAndPayClicked()));
	connect(m_pCashierProceed_GUI->m_pPushButtonInfo,SIGNAL(pressed()),this,SLOT(slotMoreInfoClicked()));
}

//------------------------------------------------------------------------------

CashierScreenManager::CashierScreenManager(BasketClient * apBasket, QObject * apParent) : 
m_pBasket(apBasket), QObject(apParent)	{
	m_pCashierWelcome_GUI = new CashierWelcome_GUI;
	m_pCashierProceed_GUI = new CashierProceed_GUI;

	connect(m_pCashierProceed_GUI->m_pPushButtonProceed,SIGNAL(pressed()),this,SLOT(slotProceedAndPayClicked()));
	connect(m_pCashierProceed_GUI->m_pPushButtonInfo,SIGNAL(pressed()),this,SLOT(slotMoreInfoClicked()));
}

//------------------------------------------------------------------------------

CashierScreenManager::~CashierScreenManager()	{
	delete m_pCashierWelcome_GUI;
	delete m_pCashierProceed_GUI;
}

//=============================================================================

void CashierScreenManager::setCashierScreen(bool abIsWelcome)	{
	if (abIsWelcome)	{
		connect(m_pCashierWelcome_GUI->m_pPushButtonStart,SIGNAL(clicked()),this,SLOT(slotShowProceed()));
		m_pCashierWelcome_GUI->show();
	} else {
		m_pCashierProceed_GUI->setGeometry(m_pCashierWelcome_GUI->geometry());
		m_pCashierProceed_GUI->show();
		m_pCashierWelcome_GUI->close();
		connect(m_pCashierProceed_GUI->m_pTableWidgetProducts,
			SIGNAL(currentCellChanged(int, int, int, int)), 
			this,
			SLOT(slotChangeImage(int, int, int, int))
		);
		connect(m_pCashierProceed_GUI->m_pPushButtonRemove,SIGNAL(pressed()),this,SLOT(slotRemoveFromBasket()));
	}
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn)	{
	int nRows = m_pCashierProceed_GUI->m_pTableWidgetProducts->rowCount();
	if (currentRow < 0 || 
		currentRow > m_pBasket->count()-1 || 
		nRows < 1)	{
			m_pCashierProceed_GUI->m_pLabelProductImage->clear();
			return;
	}

	ProductShopClient * pProduct = m_pBasket->getProduct(currentRow);
	string strTextureFile = pProduct->getProductTexture();

	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled(
		m_pCashierProceed_GUI->m_pLabelProductImage->width(),
		m_pCashierProceed_GUI->m_pLabelProductImage->height(), 
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
	);

	m_pCashierProceed_GUI->m_pLabelProductImage->setPixmap(imageScaled);
}

//--------------------------------------------------------------------------------------------

bool CashierScreenManager::close()	{
	bool bRes = m_pCashierProceed_GUI->close();
	bRes = m_pCashierWelcome_GUI->close();

	return bRes;
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotShowProceed()	{
	setCashierScreen(false);

	int nBasketSize = m_pBasket->count();

	if (nBasketSize==0)	{
		m_pCashierProceed_GUI->m_pLabelPrice->setText("0 EUR");
		m_pCashierProceed_GUI->m_pLabelProductImage->setText("");
		return;
	}

	float flBasketValue=0;
	int nRow;

	for (nRow = 0; nRow < nBasketSize; ++nRow) {
		addRow();

		ProductShopClient * pProduct = dynamic_cast<ProductShopClient*>(m_pBasket->getProduct(nRow));

		string strProductName = pProduct->getProductName();
		float flPrice = pProduct->getPrice();
		float flQuantity = pProduct->getQuantity();

		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, CashierProceed_GUI::PRODUCT)->setText(strProductName.c_str());
		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, CashierProceed_GUI::QUANTITY)->setText(tostr(flQuantity).c_str());
		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, CashierProceed_GUI::PRICE)->setText(tostr(flPrice).c_str());
		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, CashierProceed_GUI::DISCOUNT)->setText("0.0");
		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, CashierProceed_GUI::AMOUNT)->setText(tostr(flPrice*flQuantity).c_str());
		flBasketValue+=(flPrice*flQuantity);
	}

	flBasketValue = m_pBasket->calculateBasketValue();
	m_pCashierProceed_GUI->m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotRemoveFromBasket()	{
	int nCurrentRow = m_pCashierProceed_GUI->m_pTableWidgetProducts->currentRow();

	if (nCurrentRow<0)	{
		return;
	}

	//Remove from the table
	m_pCashierProceed_GUI->m_pTableWidgetProducts->removeRow(nCurrentRow);

	//Remove from the basket
	m_pBasket->removeProduct(m_pBasket->getProduct(nCurrentRow));

	float flBasketValue = m_pBasket->calculateBasketValue();
	m_pCashierProceed_GUI->m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::addRow()	{
	int row = m_pCashierProceed_GUI->m_pTableWidgetProducts->rowCount();
	m_pCashierProceed_GUI->m_pTableWidgetProducts->insertRow(row);

	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashierProceed_GUI->m_pTableWidgetProducts->setItem(row, 0, item0);
	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashierProceed_GUI->m_pTableWidgetProducts->setItem(row, 1, item1);
	QTableWidgetItem *item2 = new QTableWidgetItem;
	item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashierProceed_GUI->m_pTableWidgetProducts->setItem(row, 2, item2);
	QTableWidgetItem *item3 = new QTableWidgetItem;
	item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashierProceed_GUI->m_pTableWidgetProducts->setItem(row, 3, item3);
	QTableWidgetItem *item4 = new QTableWidgetItem;
	item4->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pCashierProceed_GUI->m_pTableWidgetProducts->setItem(row, 4, item4);
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotMoreInfoClicked()	{
	emit signalCashierOperation(ServerClientCommands::PRODUCT_INFO_REQUEST);
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::slotProceedAndPayClicked()	{
	emit signalCashierOperation(ServerClientCommands::PURCHASE_REQUEST);
}

//--------------------------------------------------------------------------------------------

void CashierScreenManager::init(BasketClient * apBasket, QObject * apParent)	{
	m_pBasket = apBasket;

	QWidget * widget = (QWidget *)apParent;
	QPoint center = widget->geometry().center();

	m_pCashierWelcome_GUI->move(center.x()-m_pCashierWelcome_GUI->width()*0.5, center.y()-m_pCashierWelcome_GUI->height()*0.5);
	m_pCashierProceed_GUI->move(center.x()-m_pCashierProceed_GUI->width()*0.5, center.y()-m_pCashierProceed_GUI->height()*0.5);

	m_pCashierWelcome_GUI->setParent(widget);
	m_pCashierProceed_GUI->setParent(widget);

	setCashierScreen(true);
}

//--------------------------------------------------------------------------------------------

int CashierScreenManager::getCurrentSelection()	{
	int nItemNumber = m_pCashierProceed_GUI->m_pTableWidgetProducts->currentRow();

	return nItemNumber;
}