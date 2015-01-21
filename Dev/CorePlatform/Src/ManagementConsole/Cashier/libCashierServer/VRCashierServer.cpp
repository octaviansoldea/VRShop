#include "BasicStringDefinitions.h"
#include <iostream>

#include "VRDatabaseInterface.h"
#include "VRCashierManagerServer.h"

#include "VRCashierServer.h"

using namespace VR;
using namespace std;

//=============================================================================

CashierServer::CashierServer() :
m_bIsTransactionApproved(false)	{
}

//=============================================================================

const char* CashierServer::className() const	{
	return "CashierServer";
}

//------------------------------------------------------------------------------

const bool CashierServer::getIsTransactionApproved() const	{
	return m_bIsTransactionApproved;
}

//------------------------------------------------------------------------------

void CashierServer::transactionFinished(string & astrRequest)	{
	vector<string> vecstrSplitString = splitString(astrRequest,";");

	string strSqlQuery = "INSERT INTO Avatar(AvatarName, AvatarMatrix) VALUES ('" + 
		vecstrSplitString[0] + "','" + vecstrSplitString[1] + "')";

	DatabaseInterface *pDI = CashierManagerServer::getDatabaseInterface();
	pDI->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

void CashierServer::prepareReceipt()	{
	bool bRes = canFirmExecuteOrder();
	if (!bRes)	{
		return;
	}

	bRes = canUserSettleReceipt();
	if (!bRes)	{
		return;
	}

	m_bIsTransactionApproved = bRes;
}

//------------------------------------------------------------------------------

bool CashierServer::canFirmExecuteOrder()	{
	return false;
}

//------------------------------------------------------------------------------

bool CashierServer::canUserSettleReceipt()	{
	return false;
}