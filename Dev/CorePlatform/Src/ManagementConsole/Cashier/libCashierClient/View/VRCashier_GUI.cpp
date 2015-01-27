#include "VRClient.h"
#include "VRBasketClient.h"

#include <string>

#include "VRAgentManagerClient.h"

#include "VRCashierClient.h"

#include "VRCashier_GUI.h"

using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Cashier_GUI::Cashier_GUI(Client * apClient, BasketClient * apBasket, QDialog * apParent) : 
QDialog(apParent), m_pBasket(apBasket) {
	setupUi(this);
	resize(559, 371);
	setWindowFlags(Qt::FramelessWindowHint);

	m_pTableWidgetProducts->setColumnCount(5);
	int nTableWidth = m_pTableWidgetProducts->width();
	QStringList qstrlstItems;
	qstrlstItems << "Product" << "Quantity" << "Price" << "Discount" << "Amount";
	m_pTableWidgetProducts->setHorizontalHeaderLabels(qstrlstItems);
	m_pTableWidgetProducts->horizontalHeader()->setVisible(true);
    m_pTableWidgetProducts->setColumnWidth(0,  0.45*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(1,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(2,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(3,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(4,  0.1*nTableWidth);
	m_pTableWidgetProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_pClient = apClient;

	//SIGNAL/SLOT
	connect(m_pPushButtonStart,&QPushButton::clicked,this,&Cashier_GUI::startClicked);
	connect(m_pPushButtonProceed,&QPushButton::clicked,this,&Cashier_GUI::proceedAndPayClicked);
	connect(m_pPushButtonContinue,&QPushButton::clicked,this,&Cashier_GUI::continueClicked);
	connect(m_pPushButtonRemove,&QPushButton::pressed,this,&Cashier_GUI::removeFromCashierClicked);

	m_pFrameRightSidePDetails->setVisible(false);
	m_pFrameContinue->setVisible(false);

	m_pCashierClient = new CashierClient(m_pClient);

	connect(m_pTableWidgetProducts, &QTableWidget::currentCellChanged, this, &Cashier_GUI::slotChangeImage);
	connect(m_pPushButtonCancel, &QPushButton::pressed,this,&Cashier_GUI::close);
}

//-------------------------------------------------------------------------------------------------------

void Cashier_GUI::startClicked()	{
	VR::CashierClient::InitCashier iC;
	iC.m_pBasket = m_pBasket;
	iC.m_pFrameContinue=m_pFrameContinue;
	iC.m_pFrameWelcome=m_pFrameWelcome;
	iC.m_pLabelPrice=m_pLabelPrice;
	iC.m_pLabelProductImage=m_pLabelProductImage;
	iC.m_pTableWidgetProducts=m_pTableWidgetProducts;
	m_pCashierClient->initializeCashier(iC);
}

//-------------------------------------------------------------------------------------------------------

void Cashier_GUI::slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn)	{
	m_pCashierClient->changeImage(m_pBasket, m_pTableWidgetProducts, m_pLabelProductImage);
}

//----------------------------------------------------------------------

Cashier_GUI::~Cashier_GUI()	{
	delete m_pCashierClient;
}

//======================================================================

void Cashier_GUI::proceedAndPayClicked()	{
	m_pFrameRightSidePDetails->setVisible(true);
}

//----------------------------------------------------------------------

void Cashier_GUI::continueClicked()	{
	AgentManagerClient::AgentClientParams & acm = m_pCashierClient->m_Acm;
	acm.m_strAddress = m_pLineEditAddress->text().toStdString();
	acm.m_strCity = m_pLineEditCity->text().toStdString();
	acm.m_strCountry = m_pLineEditCountry->text().toStdString();
	acm.m_strFirstName = m_pLineEditName->text().toStdString();
	acm.m_strLastName = m_pLineEdit2Name->text().toStdString();
	acm.m_strMiddleName = m_pLineEditMName->text().toStdString();
	acm.m_strPostalCode = m_pLineEditPostCode->text().toStdString();
	acm.m_strState = m_pLineEditState->text().toStdString();

	m_pCashierClient->continueClicked(&acm, m_pFrameRightSidePDetails);
}

//----------------------------------------------------------------------

void Cashier_GUI::removeFromCashierClicked()	{
	m_pCashierClient->removeFromCashier(m_pTableWidgetProducts, m_pBasket, m_pLabelPrice);
}

//----------------------------------------------------------------------

void Cashier_GUI::productInfoClicked()	{
}

//----------------------------------------------------------------------

void Cashier_GUI::close()	{
	m_pCashierClient->close(m_pFrameWelcome,m_pFrameContinue,this);
}

//----------------------------------------------------------------------

int Cashier_GUI::getCurrentSelection()	{
	int nItemNumber = m_pTableWidgetProducts->currentRow();

	return nItemNumber;
}

//----------------------------------------------------------------------

void Cashier_GUI::cashierClicked()	{
	show();
}