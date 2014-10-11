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

bool UserAccount::trySignIn(std::string & astrSqlRequest)	{
	vector<string> vecstrSplitString = splitString(astrSqlRequest,";");
	string strSqlQuery = "SELECT UserAccountID FROM UserAccount WHERE UserEMail = '" 
		+ vecstrSplitString[0] + "' AND UserPassword = '" + vecstrSplitString[1] + "'";

	bool bRes;
	DatabaseInterface *pDI = UserAccountManager::getDatabaseInterface();
	bRes = (pDI->executeAndGetResult(strSqlQuery).empty()) ? false : true;

	return bRes;
}

//------------------------------------------------------------------------------

bool UserAccount::trySignUp(std::string & astrSqlRequest)	{
	//Check if the user name is already in the DB
	vector<string> vecstrSplitString = splitString(astrSqlRequest,";");
	string strSqlQuery;

	bool bRes = checkUserAccountValidity(vecstrSplitString[2]);
	
	if (bRes) {
		string strSqlTemp="";
		int nJ;
		for (nJ=0;nJ<vecstrSplitString.size();nJ++)	{
			strSqlTemp += ("'" + vecstrSplitString[nJ] + "',");
		}
		strSqlTemp += ("'" + tostr(time(NULL)) + "')");
		strSqlQuery =	"INSERT INTO UserAccount(UserFirstName, UserSecondName, UserEMail, UserPassword, UserCreatedDateTime)"
						"VALUES (" + strSqlTemp;

		DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
		list<string> lststrResult = pDIUA->executeAndGetResult(strSqlQuery);
	} else {
		bRes = false;
	}

	return bRes;
}

//------------------------------------------------------------------------------

bool UserAccount::trySignOut(std::string & astrSqlRequest)	{
	return true;
}

//------------------------------------------------------------------------------

bool UserAccount::tryModifyUserAccount(std::string & astrSqlRequest)	{
	vector<string> vecstrSplitString = splitString(astrSqlRequest,";");
	
	bool bRes = checkUserAccountValidity(vecstrSplitString[1]);

	if (bRes) {
		int nI;
		string strSqlQuery="UPDATE UserAccount SET ";

		std::vector<std::pair<std::string,std::string>> & vecAccountElements = UserAccountManager::getAccountElements();

		std::vector<std::pair<std::string,std::string>>::iterator it = vecAccountElements.begin()+1;
		for (it; it != vecAccountElements.end()-1; it++)	{
			nI = it - vecAccountElements.begin();
			strSqlQuery += (it->first + "='" + vecstrSplitString[nI] + "',");
		}
		strSqlQuery.pop_back();
		strSqlQuery += "WHERE UserAccountID = '" + vecstrSplitString[0] + "';";

		DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
		bRes = pDIUA->executeAndGetResult(strSqlQuery).empty() ? true : false;
	}

	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::removeUserAccount()	{
}

//------------------------------------------------------------------------------

bool UserAccount::checkUserAccountValidity(const string & astrUserName) const	{
	string strSqlQuery = "SELECT UserAccountID FROM UserAccount WHERE UserEMail = '" 
		+ astrUserName + "'";

	DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
	bool bRes = pDIUA->executeAndGetResult(strSqlQuery).empty() ? true : false;
	
	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::resetUserAccount()	{
}