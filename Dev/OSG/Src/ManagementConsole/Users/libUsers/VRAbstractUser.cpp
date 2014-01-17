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
	bool nRes = false;

	//These two params are initialized directly from the Sign-In GUI dialog
	string strUserName = "Matej";
	string strPassword = "Password";

	//Check if the passed data is in the DB
	string strQry = "SELECT EXISTS(SELECT 1 FROM UserAccounts "
		"WHERE UserName = '" + strUserName + "' AND Password = '" + strPassword +"' LIMIT 1)";

	string strDB = "../../../../Databases/UserAccounts.db";

	DatabaseMgr & database = DatabaseMgr::Create(strDB.c_str(),DatabaseMgr::DRIVER_NAME::QSQLITE);

	nRes = database.executeQuery(strQry);	
}