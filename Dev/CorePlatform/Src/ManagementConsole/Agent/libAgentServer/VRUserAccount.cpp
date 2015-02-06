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

bool UserAccount::trySignIn(string & astrUser, string & astrPsw, string & astrUserID)	{
	string strSqlQuery = "SELECT UserAccountID FROM UserAccount WHERE UserEMail = '" 
		+ astrUser + "' AND UserPassword = '" + astrPsw + "'";

	DatabaseInterface *pDI = UserAccountManager::getDatabaseInterface();

	list<string> lststrResult = pDI->executeAndGetResult(strSqlQuery);

	if (lststrResult.size() == 0)	{
		return false;
	}

	string strResult = lststrResult.front();
//	strResult.pop_back();

	strSqlQuery = "UPDATE UserAccount SET VisitorID = '" + astrUserID + "' WHERE UserAccountID = " + strResult;
	pDI->execute(strSqlQuery);
	return true;
}

//------------------------------------------------------------------------------

bool UserAccount::trySignUp(UserAccountParams & aUserAccountParams)	{
	//Check if the user name is already in the DB
	string strSqlQuery;

	bool bRes = UserAccount::checkUserAccountValidity(aUserAccountParams.m_strEMail);
	
	if (bRes) {
		strSqlQuery =	"INSERT INTO UserAccount(UserFirstName, UserSecondName, UserEMail, UserPassword, UserCreatedDateTime, VisitorID) "
			"VALUES ('" + 
			aUserAccountParams.m_strFirstName + "','" + 
			aUserAccountParams.m_strLastName + "','" +
			aUserAccountParams.m_strEMail + "','" + 
			aUserAccountParams.m_strPsw + "','" + tostr(time(NULL)) + "','" +
			aUserAccountParams.m_strUserIDName + "')";

		DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
		list<string> lststrResult = pDIUA->executeAndGetResult(strSqlQuery);
	} else {
		bRes = false;
	}

	return bRes;
}

//------------------------------------------------------------------------------

void UserAccount::trySignOut(std::string & astrUser)	{
	string strSqlQuery="UPDATE UserAccount SET "
		"UserAccountID = '0' WHERE UserAccountID = '" + astrUser + "'";

	DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
	pDIUA->execute(strSqlQuery);
}

//------------------------------------------------------------------------------

bool UserAccount::tryModifyUserAccount(UserAccountParams & aUserAccountParams)	{
	bool bRes = UserAccount::checkUserAccountValidity(aUserAccountParams.m_strEMail);

	if (bRes) {
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

bool UserAccount::insertUserPersonalData(UserPersonalData & aUserPersonalData)	{
	string strSqlQuery = "INSERT INTO AddressBook ("
		"FirstName, MiddleName, LastName, Address, City, PostalCode, State, Country, UserAccountID) VALUES('" +
		aUserPersonalData.m_strFirstName + "','" +
		aUserPersonalData.m_strMiddleName + "','" +
		aUserPersonalData.m_strLastName + "','" +
		aUserPersonalData.m_strAddress + "','" +
		aUserPersonalData.m_strCity + "','" +
		aUserPersonalData.m_strPostalCode + "','" +
		aUserPersonalData.m_strState + "','" +
		aUserPersonalData.m_strCountry + "','" +
		aUserPersonalData.m_strUserID + "')";

	DatabaseInterface * pDIUA = UserAccountManager::getDatabaseInterface();
	bool bRes = pDIUA->executeAndGetResult(strSqlQuery).empty() ? false : true;

	return bRes;
}