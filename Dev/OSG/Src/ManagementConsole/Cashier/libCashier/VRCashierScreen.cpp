#include "VRCashierWelcome_GUI.h"
#include "VRCashierProceed_GUI.h"

#include "VRProductShopClient.h"
#include "VRBasket.h"

#include "BasicStringDefinitions.h"

#include <QImageReader>

#include "VRCashierScreen.h"

using namespace VR;
using namespace std;

//------------------------------------------------------------------------------

CashierScreen::CashierScreen(Basket * apBasket) : 
m_pBasket(apBasket), QObject()	{
	m_pCashierWelcome_GUI = new CashierWelcome_GUI;
	m_pCashierProceed_GUI = new CashierProceed_GUI;
}

//------------------------------------------------------------------------------

CashierScreen::~CashierScreen()	{
	delete m_pCashierWelcome_GUI;
	delete m_pCashierProceed_GUI;
}

//=============================================================================

void CashierScreen::setCashierScreen(bool abIsWelcome)	{
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

void CashierScreen::slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn)	{
	int nRows = m_pCashierProceed_GUI->m_pTableWidgetProducts->rowCount();
	if (currentRow < 0 || nRows < 1)	{
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

void CashierScreen::slotShowProceed()	{
	setCashierScreen(false);

	int nBasketSize = m_pBasket->count();

	if (nBasketSize==0)	{
		m_pCashierProceed_GUI->m_pLabelPrice->setText("0 EUR");
		m_pCashierProceed_GUI->m_pLabelProductImage->setText("");
		return;
	}

	ProductShopClient * pProduct = 0;
	float flBasketValue=0;
	int nRow;
	for (nRow = 0; nRow < nBasketSize; ++nRow) {
		m_pCashierProceed_GUI->addRow();

		pProduct = dynamic_cast<ProductShopClient*>(m_pBasket->getProduct(nRow));

		string strName = pProduct->getProductName();
		float flPrice = pProduct->getPrice();
		float flQuantity = pProduct->getQuantity();

		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, 0)->setText(strName.c_str());
		m_pCashierProceed_GUI->m_pTableWidgetProducts->item(nRow, 1)->setText(tostr(flPrice*flQuantity).c_str());
		flBasketValue+=(flPrice*flQuantity);
	}

	flBasketValue = m_pBasket->calculateBasketValue();
	m_pCashierProceed_GUI->m_pLabelPrice->setText((tostr(flBasketValue)+" EUR").c_str());
}

//--------------------------------------------------------------------------------------------

void CashierScreen::slotRemoveFromBasket()	{
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