//  CreateDBCommand($table, $data, $action = 'insert', $parameters = '', $link = 'db_link')

#include <QString>
#include <vector>

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
	//QString strDB = "../../../Databases/UserAccounts.db";
	//DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	//DatabaseMgrParams dMgrParams;

	///* FIRST CHECK IF THE USER ACCOUNT WITH THE SAME NAME ALREADY EXISTS*/
	////Encrypt password
	////Add Date of the insertion
	////Validate E-mail by sending an E-mail that needs to be responded

	//string strCheckUserName = "SELECT UserName FROM UserAccounts "
	//	"WHERE UserName = '" + m_strUserName + "'";

	////If SELECT returns a valid cell, report that the username has to be changed

	////When OK, insert the user into the DB
	//string strUserAccountQuery = "INSERT INTO UserAccounts VALUES ('"
	//	+ m_strUserName + "', '" + m_strPassword + "')";

	//dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	//database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

void UserAccount::modifyUserAccount()	{
	/* FIRST CHECK IF THE USER ACCOUNT WITH THE SAME NAME ALREADY EXISTS*/

	//string strUserAccountQuery = "UPDATE UserAccount SET UserName = '" + m_strUserName + "', Password = '" + 
	//	m_strPassword + "' WHERE UserName = '" + m_strUserName + "';";

	//DatabaseMgrParams dMgrParams;
	//dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	//QString strDB = "../../../../Databases/UserAccounts.db";

	//DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	//database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

void UserAccount::removeUserAccount()	{
	//string strUserAccountQuery = "DELETE FROM UserAccounts WHERE "
	//	"Username = '" + m_strUserName + 
	//	"' AND Password = '" + m_strPassword + "'";

	//DatabaseMgrParams dMgrParams;
	//dMgrParams.m_arrstrParams.push_back(strUserAccountQuery);

	//QString strDB = "../../../../Databases/UserAccounts.db";

	//DatabaseMgr & database = VR::DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);

	//database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

bool UserAccount::checkUserAccountValidity()	{
	bool bRes = false;


	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::createUserAccountDB() const	{
}

//------------------------------------------------------------------------------
