#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRModelViewControllerClient.h"

#include "VRClient.h"

#include "VRBasketClient.h"

#include "VRServerClientCommands.h"

#include "VRCashierManagerClient.h"

using namespace VR;
using namespace std;


//==============================================================================

CashierManagerClient::CashierManagerClient(Client * apClient, ModelViewControllerClient * apMVCClient, QObject *parent) : 
m_pMVCClient(apMVCClient), AbstractManagerClient(apClient, parent)	{
}

//------------------------------------------------------------------------------

CashierManagerClient::~CashierManagerClient()	{
}

//------------------------------------------------------------------------------

const char* CashierManagerClient::className() const	{
	return "CashierManagerClient";
}

//------------------------------------------------------------------------------

void CashierManagerClient::requestToServer(
const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
AbstractManagerClientParams * apAbstractManagerClientParams)	{

	CashierManagerClientParams * pParams = (CashierManagerClientParams*)apAbstractManagerClientParams;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrInputData;

	int nType = aenumOperationType;

	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::REMOVE_FROM_CASHIER_REQUEST:
		{
			QString qstrUserIDName = pParams->m_strVisitorName.c_str();
			QString qstrProductName = pParams->m_strProductName.c_str();

			out << qstrUserIDName << qstrProductName;

			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			QString qstrProductName = pParams->m_strProductName.c_str();

			out << qstrProductName;

			break;
		}
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			QString qstrVisitorName = pParams->m_strVisitorName.c_str();
			QString qstrBasketProdQty = pParams->m_strBasketProdQty.c_str();

			out << qstrVisitorName << qstrBasketProdQty;
			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			break;
		}
	default:
		return;
	}
	
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void CashierManagerClient::removeFromBasketClicked(const string & astrUserID, const string & astrProductName)	{
	CashierManagerClient::CashierManagerClientParams cmcp;
	cmcp.m_strVisitorName = astrUserID;
	cmcp.m_strProductName = astrProductName;

	requestToServer(ServerClientCommands::REMOVE_FROM_CASHIER_REQUEST,&cmcp);
}

//------------------------------------------------------------------------------

void CashierManagerClient::moreProductInfoClicked(const string & astrProductName)	{
	CashierManagerClient::CashierManagerClientParams cmcp;
	cmcp.m_strProductName = astrProductName;

	requestToServer(ServerClientCommands::PRODUCT_INFO_REQUEST,&cmcp);
}

//------------------------------------------------------------------------------

void CashierManagerClient::proceedAndPayCashier(const string & astrUserID, BasketClient * apBasket)	{
	CashierManagerClient::CashierManagerClientParams cmcp;
	cmcp.m_strVisitorName = astrUserID;
	cmcp.m_strBasketProdQty = apBasket->getBasketIDQuantity2String();

	requestToServer(ServerClientCommands::PURCHASE_REQUEST,&cmcp);
}


//------------------------------------------------------------------------------

void CashierManagerClient::productInfoData(QDataStream & aDataStreamCashier)	{
}

//------------------------------------------------------------------------------

bool CashierManagerClient::removeFromBasketData(QDataStream & aDataStreamCashier)	{
	bool bRes;
	aDataStreamCashier >> bRes;

	if (bRes == 0)	{
		return false;
	}

	emit m_pMVCClient->signalRemoveProduct();

	return true;
}

//------------------------------------------------------------------------------

void CashierManagerClient::basketPurchaseData(QDataStream & aDataStreamCashier)	{
	int nOperationResult;
	aDataStreamCashier >> nOperationResult;
	
	switch (nOperationResult)	{
	case ServerClientCommands::PASSED:
		{

			break;
		}
	case ServerClientCommands::AUTHENTICATION_FAILED:
		{
			//Report to the user that his authentication failed
			break;
		}
	}
}