#include <QString>
#include <vector>
#include <iostream>
#include <time.h>

#include "BasicStringDefinitions.h"

#include "VRDatabaseInterface.h"
#include "VRUserAccountManager.h"

#include "VRUserAccount.h"

using namespace VR;
using namespace std;

//==============================================================================

UserAccount::UserAccount() :
m_nID(0)	{
}

//------------------------------------------------------------------------------

UserAccount::~UserAccount()	{
}

//------------------------------------------------------------------------------

bool UserAccount::trySignIn(std::string & astrUser, std::string & astrPsw)	{
	string strSqlQuery = "SELECT UserAccountID FROM UserAccount WHERE UserEMail = '" 
		+ astrUser + "' AND UserPassword = '" + astrPsw + "'";

	bool bRes;
	DatabaseInterface *pDI = UserAccountManager::getDatabaseInterface();
	bRes = (pDI->executeAndGetResult(strSqlQuery).empty()) ? false : true;

	return bRes;
}

//------------------------------------------------------------------------------

bool UserAccount::trySignUp(UserAccountParams & aUserAccountParams)	{
	//Check if the user name is already in the DB
	string strSqlQuery;

	bool bRes = UserAccount::checkUserAccountValidity(aUserAccountParams.m_strEMail);
	
	if (bRes) {
		strSqlQuery =	"INSERT INTO UserAccount(UserFirstName, UserSecondName, UserEMail, UserPassword, UserCreatedDateTime)"
			"VALUES ('" + 
			aUserAccountParams.m_strFirstName + "','" + 
			aUserAccountParams.m_strLastName + "','" +
			aUserAccountParams.m_strEMail + "','" + 
			aUserAccountParams.m_strPsw + "','" + tostr(time(NULL)) + "')";

		DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
		list<string> lststrResult = pDIUA->executeAndGetResult(strSqlQuery);
	} else {
		bRes = false;
	}

	return bRes;
}

//------------------------------------------------------------------------------

bool UserAccount::trySignOut(std::string & astrUser)	{
	return true;
}

//------------------------------------------------------------------------------

bool UserAccount::tryModifyUserAccount(UserAccountParams & aUserAccountParams)	{
	bool bRes = UserAccount::checkUserAccountValidity(aUserAccountParams.m_strEMail);

	if (bRes) {
		int nI;
		string strSqlQuery="UPDATE UserAccount SET "
			"UserFirstName = '" + aUserAccountParams.m_strFirstName + "', "
			"UserSecondName = '" + aUserAccountParams.m_strLastName + "', "
			"UserEMail = '" + aUserAccountParams.m_strEMail + "', "
			"UserPassword = '" + aUserAccountParams.m_strPsw + "', "
			"UserCreatedDateTime = '" + "TEXT" 
			"WHERE UserAccountID = '" + aUserAccountParams.m_strUserIDName + "';";

		DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
		bRes = pDIUA->executeAndGetResult(strSqlQuery).empty() ? true : false;
	}

	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::removeUserAccount()	{
}

//------------------------------------------------------------------------------

bool UserAccount::checkUserAccountValidity(const string & astrUserName)	{
	string strSqlQuery = "SELECT UserAccountID FROM UserAccount WHERE UserEMail = '" 
		+ astrUserName + "'";

	DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
	bool bRes = pDIUA->executeAndGetResult(strSqlQuery).empty() ? true : false;
	
	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::resetUserAccount()	{
}