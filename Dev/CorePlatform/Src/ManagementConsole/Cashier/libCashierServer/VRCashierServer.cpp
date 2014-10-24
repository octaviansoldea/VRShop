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

//------------------------------------------------------------------------------

CashierServer::~CashierServer()	{
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

/*
	DatabaseName = Cashier.db

	vector<pair<string,string>> vecpairDBElements;
	vecpairDBElements.push_back(make_pair("OrderReservedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairDBElements.push_back(make_pair("UserID", "TEXT"));
	vecpairDBElements.push_back(make_pair("ProductID", "TEXT"));
	vecpairDBElements.push_back(make_pair("ProductQuantity", "TEXT"));
	vecpairDBElements.push_back(make_pair("TimeOrdered", "TEXT"));
	vecpairDBElements.push_back(make_pair("OrderStatus", "TEXT"));		//Resereved=1; confirmed=2; delivered=3; canceled=0
	TableName = OrdersResereved

	vector<pair<string,string>> vecpairDBElements;
	vecpairDBElements.push_back(make_pair("OrderConfirmedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairDBElements.push_back(make_pair("UserID", "TEXT"));
	vecpairDBElements.push_back(make_pair("ProductID", "TEXT"));
	vecpairDBElements.push_back(make_pair("ProductQuantity", "TEXT"));
	vecpairDBElements.push_back(make_pair("TimeConfirmed", "TEXT"));
	TableName = OrdersConfirmed

	vector<pair<string,string>> vecpairDBElements;
	vecpairDBElements.push_back(make_pair("OrderDeliveredID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairDBElements.push_back(make_pair("UserID", "TEXT"));
	vecpairDBElements.push_back(make_pair("Basket", "TEXT"));
	vecpairDBElements.push_back(make_pair("TimeConfirmed", "TEXT"));
	TableName = OrdersDelivered	
*/