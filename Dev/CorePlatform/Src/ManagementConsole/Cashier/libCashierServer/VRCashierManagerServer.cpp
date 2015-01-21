#include <QString>
#include <iostream>

#include "BasicStringDefinitions.h"

#include "VRAppData.h"

#include <ctime>

#include "VRDatabaseInterface.h"

#include "VRCashierManagerServer.h"

using namespace VR;
using namespace std;

DatabaseInterface CashierManagerServer::m_DICashier(CashierManagerServer::getDBParams());

//==============================================================================

CashierManagerServer::CashierManagerServer()	{
}

//------------------------------------------------------------------------------

CashierManagerServer::~CashierManagerServer()	{
}

//------------------------------------------------------------------------------

DatabaseInterfaceParams CashierManagerServer::getDBParams()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "Cashier";
	dbParams.m_qstrDBName = getDatabaseName().c_str();

	return dbParams;
}

//------------------------------------------------------------------------------

string CashierManagerServer::getTableName()	{
	return "Cashier";
}

//------------------------------------------------------------------------------

string CashierManagerServer::getDatabaseName()	{
	return AppData::getFPathDatabases() + "/Cashier.db";
}

//------------------------------------------------------------------------------

vector<pair<string,string>> CashierManagerServer::getDBElements()	{
	vector<pair<string,string>> vecpairDBElements;

	vecpairDBElements.push_back(make_pair("ReceiptID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairDBElements.push_back(make_pair("ReceiptValue", "TEXT"));
	vecpairDBElements.push_back(make_pair("ReceiptProducts", "TEXT"));
	vecpairDBElements.push_back(make_pair("PaymentType", "TEXT"));
	vecpairDBElements.push_back(make_pair("DeliveryType", "TEXT"));
	vecpairDBElements.push_back(make_pair("UserAccount", "TEXT"));
	vecpairDBElements.push_back(make_pair("ReceiptDateTime", "TEXT"));

	return vecpairDBElements;
}

//------------------------------------------------------------------------------

void CashierManagerServer::createDB()	{
	m_DICashier.createTable(getTableName(), getDBElements());

	vector<pair<string,string>> vecpairDBElements;
	{
		vecpairDBElements.push_back(make_pair("OrderReservedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBElements.push_back(make_pair("UserID", "TEXT"));
		vecpairDBElements.push_back(make_pair("ProductID", "TEXT"));
		vecpairDBElements.push_back(make_pair("ProductQuantity", "TEXT"));
		vecpairDBElements.push_back(make_pair("TimeOrdered", "TEXT"));
		vecpairDBElements.push_back(make_pair("OrderStatus", "TEXT"));		//Reserved=1; confirmed=2; delivered=3; canceled=0
	}
	m_DICashier.createTable("OrdersReserved", vecpairDBElements);

	vector<pair<string,string>> vecpairDBOrderConfirmed;
	{
		vecpairDBOrderConfirmed.push_back(make_pair("OrderConfirmedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBOrderConfirmed.push_back(make_pair("UserID", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("ProductID", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("ProductQuantity", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("TimeConfirmed", "TEXT"));
	}
	m_DICashier.createTable("OrdersConfirmed", vecpairDBOrderConfirmed);

	vector<pair<string,string>> vecpairDBOrderDelivered;
	{
		vecpairDBOrderDelivered.push_back(make_pair("OrderDeliveredID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBOrderDelivered.push_back(make_pair("UserID", "TEXT"));
		vecpairDBOrderDelivered.push_back(make_pair("Basket", "TEXT"));
		vecpairDBOrderDelivered.push_back(make_pair("TimeConfirmed", "TEXT"));
	}
	m_DICashier.createTable("OrdersDelivered", vecpairDBOrderDelivered);
}

//------------------------------------------------------------------------------

DatabaseInterface * CashierManagerServer::getDatabaseInterface() {
	return(&m_DICashier);
}

//------------------------------------------------------------------------------

bool CashierManagerServer::addProduct2OrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;
	float flProductQuantity = aCMSP.m_flProductQuantity;

	//Check if already in the DB
	string strQuery = "SELECT OrderReservedID FROM OrdersReserved WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";
	list<string> lststrResult = m_DICashier.executeAndGetResult(strQuery);

	//Product not yet in the list => add it
	if (lststrResult.empty())	{
		strQuery = "INSERT INTO OrdersReserved (UserID, ProductID, ProductQuantity, TimeOrdered, OrderStatus) "
			"VALUES('" + strUserID + "','" + strProductName + "','" + tostr(flProductQuantity) + "','" + tostr(time(NULL)) + "','1')";
	} 
	//Product already in the list => modify quantities
	else {
		strQuery = "UPDATE OrdersReserved SET ProductQuantity = (ProductQuantity + '" + tostr(flProductQuantity) + "'), TimeOrdered = '" + tostr(time(NULL)) + "'"
			" WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";
	}

	lststrResult = m_DICashier.executeAndGetResult(strQuery);

	return (lststrResult.empty() ? false : true);
}

//------------------------------------------------------------------------------

bool CashierManagerServer::removeProductFromOrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;

	//Remove from DB selected quantities
	string strQuery = "DELETE FROM OrdersReserved WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";

	m_DICashier.execute(strQuery);

	return true;
}

//------------------------------------------------------------------------------

bool CashierManagerServer::modifyProductOrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;
	float flProductQuantity = aCMSP.m_flProductQuantity;

	//Modify quantities
	string strQuery = "UPDATE Product SET ProductQuantity = '" + tostr(flProductQuantity) +
		"') WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";

	m_DICashier.execute(strQuery);

	return true;
}