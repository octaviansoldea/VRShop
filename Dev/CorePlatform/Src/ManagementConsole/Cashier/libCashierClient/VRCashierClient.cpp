#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QFrame>
#include <QDialog>
#include <QLineEdit>

#include "BasicStringDefinitions.h"

#include "VRProductShopClient.h"
#include "VRBasketClient.h"

#include "VRClient.h"

#include "VRAgentManagerClient.h"
#include "VRCashierManagerClient.h"

#include "VRCashierClient.h"

using namespace VR;
using namespace std;

CashierClient::CashierClient(Client * apClient)	{
	m_pClient = apClient;
}

//------------------------------------------------------------------------------

CashierClient::~CashierClient()	{
}

//=============================================================================

void CashierClient::changeImage(BasketClient * apBasket, QTableWidget * apTableWidgetProducts, QLabel * apLabelProductImage)	{
	int nRows = apTableWidgetProducts->rowCount();
	int nCurrentRow = apTableWidgetProducts->currentRow();

	if (nCurrentRow < 0 || 
		nCurrentRow > apBasket->count()-1 || 
		nRows < 1)	{
			apLabelProductImage->clear();
			return;
	}

	ProductShopClient * pProduct = apBasket->getProduct(nCurrentRow);
	string strTextureFile = pProduct->getProductTexture();

	QImageReader image(strTextureFile.c_str());
	QPixmap imageBasic(QPixmap::fromImageReader(&image));
	QPixmap imageScaled(imageBasic.scaled(
		apLabelProductImage->width(),
		apLabelProductImage->height(), 
		Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
	);

	apLabelProductImage->setPixmap(imageScaled);
}

//------------------------------------------------------------------------------

void CashierClient::removeFromCashier(QTableWidget * apTableWidgetProducts, BasketClient * apBasket, QLabel * apLabelPrice)	{
	int nCurrentRow = apTableWidgetProducts->currentRow();

	if (nCurrentRow<0)	{
		return;
	}

	//Remove from the table
	apTableWidgetProducts->removeRow(nCurrentRow);

	//Remove from the basket
	apBasket->removeProduct(apBasket->getProduct(nCurrentRow));

	float flBasketValue = apBasket->calculateBasketValue();
	apLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//------------------------------------------------------------------------------

void CashierClient::initializeCashier(InitCashier & aInitCashier)	{
	aInitCashier.m_pFrameWelcome->setVisible(false);
	aInitCashier.m_pFrameContinue->setVisible(false);

	aInitCashier.m_pFrameContinue->setVisible(true);

	int nBasketSize = aInitCashier.m_pBasket->count();

	if (nBasketSize==0)	{
		aInitCashier.m_pLabelPrice->setText("0 EUR");
		aInitCashier.m_pLabelProductImage->setText("");
		return;
	}

	int nRow;
	for (nRow = 0; nRow < nBasketSize; ++nRow) {
		addRow(aInitCashier.m_pTableWidgetProducts);

		ProductShopClient * pProduct = dynamic_cast<ProductShopClient*>(aInitCashier.m_pBasket->getProduct(nRow));

		string strProductName = pProduct->getProductName();
		float flPrice = pProduct->getPrice();
		float flQuantity = pProduct->getQuantity();

		aInitCashier.m_pTableWidgetProducts->item(nRow, PRODUCT)->setText(strProductName.c_str());
		aInitCashier.m_pTableWidgetProducts->item(nRow, QUANTITY)->setText(tostr(flQuantity).c_str());
		aInitCashier.m_pTableWidgetProducts->item(nRow, PRICE)->setText(tostr(flPrice).c_str());
		aInitCashier.m_pTableWidgetProducts->item(nRow, DISCOUNT)->setText("0.0");
		aInitCashier.m_pTableWidgetProducts->item(nRow, AMOUNT)->setText(tostr(flPrice*flQuantity).c_str());
	}

	float flBasketValue = aInitCashier.m_pBasket->calculateBasketValue();
	aInitCashier.m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//----------------------------------------------------------------------------

void CashierClient::addRow(QTableWidget * apTableWidgetProducts)	{
	int row = apTableWidgetProducts->rowCount();
	apTableWidgetProducts->insertRow(row);

	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	apTableWidgetProducts->setItem(row, 0, item0);
	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	apTableWidgetProducts->setItem(row, 1, item1);
	QTableWidgetItem *item2 = new QTableWidgetItem;
	item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	apTableWidgetProducts->setItem(row, 2, item2);
	QTableWidgetItem *item3 = new QTableWidgetItem;
	item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	apTableWidgetProducts->setItem(row, 3, item3);
	QTableWidgetItem *item4 = new QTableWidgetItem;
	item4->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	apTableWidgetProducts->setItem(row, 4, item4);
}

//------------------------------------------------------------------------

void CashierClient::close(QFrame * apFrameWelcome, QFrame * apFrameContinue, QDialog * apDialog)	{
	apFrameWelcome->setVisible(true);
	apFrameContinue->setVisible(false);

	apDialog->hide();

	apDialog->close();
}

//------------------------------------------------------------------------

void CashierClient::continueClicked(AgentManagerClient::AgentClientParams * apAcm, QFrame * apFrameRightSidePDetails)	{
	apFrameRightSidePDetails->setVisible(false);

	AgentManagerClient amc(m_pClient);
	amc.fillUserDetailsRequest(*apAcm,tostr(m_pClient->getUserID()));

	CashierManagerClient cmc(m_pClient);
	
//	cmc.proceedAndPayCashier();
}

//------------------------------------------------------------------------

void CashierClient::moeProductClicked(BasketClient * apBasket, int anProductPosition)	{
	if (anProductPosition < 0 || apBasket->count() == 0)
		return;

	string strProductName = apBasket->getProduct(anProductPosition)->getProductName();

	CashierManagerClient cmc(m_pClient);
	cmc.moreProductInfoClicked(strProductName);
}