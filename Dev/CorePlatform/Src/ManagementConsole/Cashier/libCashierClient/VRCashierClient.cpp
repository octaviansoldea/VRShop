#include "VRBasketClient.h"
#include "VRVisitor.h"

#include "VRCashierScreenManager.h"
#include "VRCashierInterface.h"

#include "VRCashierManagerClient.h"

#include "VRCashierClient.h"

using namespace VR;
using namespace std;

CashierClient::CashierClient() : m_pCashierScreenManager(0),m_pVisitor(0)	{
	m_pCashierInterface = new CashierInterface;
}

//------------------------------------------------------------------------------

CashierClient::~CashierClient()	{
	if (m_pCashierScreenManager != 0)	{
		delete m_pCashierScreenManager;
		m_pCashierScreenManager = 0;
	}
	delete m_pCashierInterface;
}

//=============================================================================

void CashierClient::init(Visitor * apVisitor)	{
	if (m_pCashierScreenManager != 0)	{
		delete m_pCashierScreenManager;
		m_pCashierScreenManager = 0;
	}

	m_pVisitor = apVisitor;
	BasketClient * pBasket = m_pVisitor->getBasket();
	m_pCashierScreenManager = new CashierScreenManager(pBasket);
	m_pCashierScreenManager->setCashierScreen(true);
}

//------------------------------------------------------------------------------

void CashierClient::requestToPay(const string & astrUserID, BasketClient * apBasket)	{
	CashierManagerClient::CashierManagerClientParams cmcp;
	cmcp.m_strVisitorName = astrUserID;
	cmcp.m_strBasketProdQty = apBasket->getBasketIDQuantity2String();

	m_pCashierManagerClient->requestToServer(ServerClientCommands::PURCHASE_REQUEST,&cmcp);
}

//------------------------------------------------------------------------------

void CashierClient::confirmTransaction()	{
	CashierManagerClient::CashierManagerClientParams cmcp;
	m_pCashierManagerClient->requestToServer(ServerClientCommands::USER_CONFIRMS_PURCHASE,&cmcp);
}