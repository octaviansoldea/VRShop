#include <QString>
#include <iostream>
#include <fstream>

#include "BasicStringDefinitions.h"

#include "VRAppDataServer.h"

#include <ctime>

#include "VRDatabaseInterface.h"

#include "VRCashierManagerServer.h"

using namespace VR;
using namespace std;

DatabaseInterface * CashierManagerServer::m_pDICashier = 0;

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
	return AppDataServer::getFPathDatabases() + "/Cashier.db";
}

//------------------------------------------------------------------------------

vector<pair<string,string>> CashierManagerServer::getDBElements()	{
	vector<pair<string,string>> vecpairDBElements;

	vecpairDBElements.push_back(make_pair("ReceiptID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairDBElements.push_back(make_pair("ReceiptValue", "TEXT"));
	vecpairDBElements.push_back(make_pair("ReceiptBasketID", "INTEGER"));
	vecpairDBElements.push_back(make_pair("PaymentType", "TEXT"));
	vecpairDBElements.push_back(make_pair("DeliveryType", "TEXT"));
	vecpairDBElements.push_back(make_pair("UserAccount", "TEXT"));
	vecpairDBElements.push_back(make_pair("ReceiptDateTime", "TEXT"));

	return vecpairDBElements;
}

//------------------------------------------------------------------------------

void CashierManagerServer::createDB()	{
	m_pDICashier->createTable(getTableName(), getDBElements());

	vector<pair<string,string>> vecpairDBElements;
	{
		vecpairDBElements.push_back(make_pair("OrderReservedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBElements.push_back(make_pair("UserID", "TEXT"));
		vecpairDBElements.push_back(make_pair("ProductID", "TEXT"));
		vecpairDBElements.push_back(make_pair("ProductQuantity", "TEXT"));
		vecpairDBElements.push_back(make_pair("TimeOrdered", "TEXT"));
		vecpairDBElements.push_back(make_pair("OrderStatus", "TEXT"));		//Reserved=1; confirmed=2; delivered=3; canceled=0
	}
	m_pDICashier->createTable("OrdersReserved", vecpairDBElements);

	vector<pair<string,string>> vecpairDBOrderConfirmed;
	{
		vecpairDBOrderConfirmed.push_back(make_pair("OrderConfirmedID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBOrderConfirmed.push_back(make_pair("UserID", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("ProductID", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("ProductQuantity", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("TimeConfirmed", "TEXT"));
		vecpairDBOrderConfirmed.push_back(make_pair("BasketID", "INTEGER"));
	}
	m_pDICashier->createTable("OrdersConfirmed", vecpairDBOrderConfirmed);

	vector<pair<string,string>> vecpairDBOrderDelivered;
	{
		vecpairDBOrderDelivered.push_back(make_pair("OrderDeliveredID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBOrderDelivered.push_back(make_pair("UserID", "TEXT"));
		vecpairDBOrderDelivered.push_back(make_pair("BasketID", "INTEGER"));
		vecpairDBOrderDelivered.push_back(make_pair("TimeDelivered", "TEXT"));
	}
	m_pDICashier->createTable("OrdersDelivered", vecpairDBOrderDelivered);
}

//------------------------------------------------------------------------------

DatabaseInterface * CashierManagerServer::getDatabaseInterface() {
	return(m_pDICashier);
}

//------------------------------------------------------------------------------

bool CashierManagerServer::addProduct2OrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;
	float flProductQuantity = aCMSP.m_flProductQuantity;

	//Check if already in the DB
	string strQuery = "SELECT OrderReservedID FROM OrdersReserved WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";
	list<string> lststrResult = m_pDICashier->executeAndGetResult(strQuery);

	//Product not yet in the list => add it
	if (lststrResult.empty())	{
		strQuery = "INSERT INTO OrdersReserved (UserID, ProductID, ProductQuantity, TimeOrdered, OrderStatus) "
			"VALUES('" + strUserID + "','" + strProductName + "','" + tostr(flProductQuantity) + "','" + tostr(time(NULL)) + "','"+ tostr(RESERVED)+"')";
	} 
	//Product already in the list => modify quantities
	else {
		strQuery = "UPDATE OrdersReserved SET ProductQuantity = (ProductQuantity + '" + tostr(flProductQuantity) + "'), TimeOrdered = '" + tostr(time(NULL)) + "'"
			" WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";
	}

	lststrResult = m_pDICashier->executeAndGetResult(strQuery);

	return (lststrResult.empty() ? false : true);
}

//------------------------------------------------------------------------------

bool CashierManagerServer::removeProductFromOrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;

	//Remove from DB selected quantities
	string strQuery = "DELETE FROM OrdersReserved WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";

	m_pDICashier->execute(strQuery);

	return true;
}

//------------------------------------------------------------------------------

void CashierManagerServer::clearProductsReserved(const std::string & astrUserName)	{
	string strQuery = "DELETE FROM OrdersReserved WHERE UserID = '" + astrUserName + "' AND OrderStatus = '" + tostr(RESERVED) + "'";

	m_pDICashier->execute(strQuery);
}

//------------------------------------------------------------------------------

bool CashierManagerServer::modifyProductOrdersReserved(const CashierManagerServerParams & aCMSP)	{
	string strUserID = aCMSP.m_strUserIDName;
	string strProductName = aCMSP.m_strProductName;
	float flProductQuantity = aCMSP.m_flProductQuantity;

	//Modify quantities
	string strQuery = "UPDATE Product SET ProductQuantity = '" + tostr(flProductQuantity) +
		"') WHERE ProductID = '" + strProductName + "' AND UserID = '" + strUserID + "'";

	m_pDICashier->execute(strQuery);

	return true;
}

//------------------------------------------------------------------------------

void CashierManagerServer::orderConfirmed(const std::string & astrUserName)	{
	//Change status of the printed items
	string strQuery = "UPDATE OrdersReserved SET OrderStatus = '" + tostr(CONFIRMED) + "' WHERE UserID = '" + astrUserName + "'";
	m_pDICashier->execute(strQuery);
}

//------------------------------------------------------------------------------

list<string> CashierManagerServer::getActiveOrdersList()	{
	list<string> lststrActiveOrders;

	//Get all active (non-delivered) orders
	string strQuery = "SELECT * FROM OrdersReserved WHERE OrderStatus = " + tostr(CONFIRMED) + " ORDER BY UserID";
	lststrActiveOrders = m_pDICashier->executeAndGetResult(strQuery);

	if (lststrActiveOrders.empty())	{
		return list<string>(0);
	}

	//Change status of the printed items
	strQuery = "UPDATE OrdersReserved SET OrderStatus = '" + tostr(DELIVERED) + "' WHERE OrderStatus = '"+tostr(CONFIRMED)+"'";
	m_pDICashier->execute(strQuery);

	return lststrActiveOrders;
}

//------------------------------------------------------------------------------

void CashierManagerServer::constructStatics() {
	m_pDICashier = new DatabaseInterface(static_cast<DatabaseInterfaceParams&>(CashierManagerServer::getDBParams()));
}

//------------------------------------------------------------------------------

void CashierManagerServer::deleteStatics() {
	delete m_pDICashier;
}