#include "VRDatabaseMgr.h"

#include "VRAbstractUser.h"

#include <string>

using namespace VR;
using namespace std;

//==============================================================================

AbstractUser::AbstractUser()	{
}

//------------------------------------------------------------------------------

AbstractUser::~AbstractUser()	{
}

//------------------------------------------------------------------------------

void AbstractUser::trySignIn()	{
	//These two params are initialized directly from the Sign-In GUI dialog
	string strUserName = "Matej";
	string strPassword = "Password";

	//Check if the passed data is in the DB
	string strQry = "SELECT EXISTS(SELECT 1 FROM UserAccounts "
		"WHERE UserName = '" + strUserName + "' AND Password = '" + strPassword + "' LIMIT 1)";

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strQry);
	QString strDB = "../../../../Databases/UserAccounts.db";

	DatabaseMgr & database = DatabaseMgr::Create(strDB,DatabaseMgr::QSQLITE);
	database.executeQuery(dMgrParams);
}

//------------------------------------------------------------------------------

list<Product> AbstractUser::getBasket() const	{
	return m_Basket;
}
