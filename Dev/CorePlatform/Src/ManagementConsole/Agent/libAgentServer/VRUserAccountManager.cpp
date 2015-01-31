#include <QString>
#include <iostream>

#include "BasicStringDefinitions.h"

#include "VRAppDataServer.h"

#include "VRDatabaseInterface.h"

#include "VRUserAccountManager.h"

using namespace VR;
using namespace std;

DatabaseInterface * UserAccountManager::m_pDIUA = 0;

//==============================================================================

UserAccountManager::UserAccountManager()	{
}

//------------------------------------------------------------------------------

UserAccountManager::~UserAccountManager()	{
}

//------------------------------------------------------------------------------

DatabaseInterfaceParams UserAccountManager::getDBParams()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "UserAccount";
	dbParams.m_qstrDBName = getDatabaseName().c_str();

	return dbParams;
}

//------------------------------------------------------------------------------

string UserAccountManager::getTableName()	{
	return "UserAccount";
}

//------------------------------------------------------------------------------

string UserAccountManager::getDatabaseName()	{
	return AppDataServer::getFPathDatabases() + "/UserAccounts.db";
}

//------------------------------------------------------------------------------

vector<pair<string,string>> UserAccountManager::getAccountElements()	{
	vector<pair<string,string>> vecpairAccountElements;

	vecpairAccountElements.push_back(make_pair("UserAccountID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairAccountElements.push_back(make_pair("UserFirstName", "TEXT"));
	vecpairAccountElements.push_back(make_pair("UserSecondName", "TEXT"));
	vecpairAccountElements.push_back(make_pair("UserEMail", "TEXT"));
	vecpairAccountElements.push_back(make_pair("UserPassword", "TEXT"));
	vecpairAccountElements.push_back(make_pair("UserCreatedDateTime", "TEXT"));
	vecpairAccountElements.push_back(make_pair("VisitorID", "INTEGER"));

	return vecpairAccountElements;
}

//------------------------------------------------------------------------------

void UserAccountManager::createUserAccountDB()	{
	m_pDIUA->createTable(getTableName(), getAccountElements());
}

//------------------------------------------------------------------------------

void UserAccountManager::createDB()	{
	createUserAccountDB();

	vector<pair<string,string>> vecpairDBElements;
	{
		vecpairDBElements.push_back(make_pair("AddressBookID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
		vecpairDBElements.push_back(make_pair("FirstName", "TEXT"));
		vecpairDBElements.push_back(make_pair("MiddleName", "TEXT"));
		vecpairDBElements.push_back(make_pair("LastName", "TEXT"));
		vecpairDBElements.push_back(make_pair("Address", "TEXT"));
		vecpairDBElements.push_back(make_pair("City", "TEXT"));
		vecpairDBElements.push_back(make_pair("PostalCode", "TEXT"));
		vecpairDBElements.push_back(make_pair("State", "TEXT"));
		vecpairDBElements.push_back(make_pair("Country", "TEXT"));
		vecpairDBElements.push_back(make_pair("UserAccountID", "TEXT"));
	}
	m_pDIUA->createTable("AddressBook", vecpairDBElements);
}

//------------------------------------------------------------------------------

string UserAccountManager::getUserAddress(const int & anUserID)	{
	string strUserID = getUserAccountID(tostr(anUserID));
	strUserID.pop_back();

	string strQuery = "SELECT FirstName, MiddleName, LastName, Address, City, PostalCode, State, Country "
		" FROM AddressBook WHERE UserAccountID = " + strUserID;

	string strUserAddress = m_pDIUA->executeAndGetResult(strQuery).front();

	return strUserAddress;
}

//------------------------------------------------------------------------------

string UserAccountManager::getUserAccountID(const std::string & astrUserID)	{
	string strQuery = "SELECT UserAccountID FROM UserAccount WHERE VisitorID = '" + tostr(astrUserID) + "'";

	string strUserAddress = m_pDIUA->executeAndGetResult(strQuery).front();

	return strUserAddress;
}

//------------------------------------------------------------------------------

DatabaseInterface * UserAccountManager::getDatabaseInterface() {
	return(m_pDIUA);
}

//------------------------------------------------------------------------------

void UserAccountManager::constructStatics() {
	m_pDIUA = new DatabaseInterface(static_cast<DatabaseInterfaceParams&>(UserAccountManager::getDBParams()));
}

//------------------------------------------------------------------------------

void UserAccountManager::deleteStatics() {
	delete m_pDIUA;
}

