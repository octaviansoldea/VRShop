#include <QString>
#include <iostream>

#include "VRDatabaseInterface.h"

#include "VRUserAccountManager.h"

using namespace VR;
using namespace std;

DatabaseInterface UserAccountManager::m_DIUA(DatabaseInterfaceParams(UserAccountManager::getDatabaseName().c_str(),"UserAccount"));

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
	return "../../../../Databases/UserAccounts.db";
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

	return vecpairAccountElements;
}

//------------------------------------------------------------------------------

void UserAccountManager::createUserAccountDB()	{
	m_DIUA.createTable(getTableName(), getAccountElements());
}

//------------------------------------------------------------------------------

DatabaseInterface * UserAccountManager::getDatabaseInterface() {
	return(&m_DIUA);
}

//------------------------------------------------------------------------------