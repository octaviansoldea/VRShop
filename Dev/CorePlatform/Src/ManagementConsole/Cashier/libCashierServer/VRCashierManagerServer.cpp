#include <QString>
#include <iostream>

#include "VRAppData.h"

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
}

//------------------------------------------------------------------------------

DatabaseInterface * CashierManagerServer::getDatabaseInterface() {
	return(&m_DICashier);
}

//------------------------------------------------------------------------------