#include "VRDatabaseMgr.h"

#include "VRUserAccount.h"

using namespace VR;
using namespace std;

//==============================================================================

UserAccount::UserAccount()	{
}

//------------------------------------------------------------------------------

UserAccount::UserAccount(const string & astrUserName, const string & astrPassword) :
m_strUserName(astrUserName),
m_strPassword(astrPassword)
{
}

//------------------------------------------------------------------------------

void UserAccount::addUserAccount()	{

	/* FIRST CHECK IF THE USER ACCOUNT WITH THE SAME NAME ALREADY EXISTS*/

	string strUserAccountQuery = "INSERT INTO UserAccounts VALUES ('"
		+ m_strUserName + "', '" + m_strPassword + "')";

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	QString strDB = "../../../Databases/UserAccounts.db";

	DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

void UserAccount::modifyUserAccount()	{
	/* FIRST CHECK IF THE USER ACCOUNT WITH THE SAME NAME ALREADY EXISTS*/

	string strUserAccountQuery = "UPDATE UserAccount SET UserName = '" + m_strUserName + "', Password = '" + 
		m_strPassword + "' WHERE UserName = '" + m_strUserName + "';";

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	QString strDB = "../../../../Databases/UserAccounts.db";

	DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

void UserAccount::removeUserAccount()	{
	string strUserAccountQuery = "DELETE FROM UserAccounts WHERE "
		"Username = '" + m_strUserName + 
		"' AND Password = '" + m_strPassword + "'";

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	QString strDB = "../../../../Databases/UserAccounts.db";

	DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

void UserAccount::createUserAccountDB() const	{
	bool nRes;

	vector<string> vecstrDBParams;
	vecstrDBParams.push_back("UserName TEXT");
	vecstrDBParams.push_back("Password TEXT");

	DatabaseMgrParams dMgrP;
	dMgrP.m_strTableName = "UserAccounts";
	dMgrP.m_arrstrParams = vecstrDBParams;

	QString strDBName = "../../../../Databases/UserAccounts.db";

	DatabaseMgr & database = VR::DatabaseMgr::Create(strDBName,DatabaseMgr::QSQLITE);
	database.createTable(dMgrP);
}

//------------------------------------------------------------------------------
