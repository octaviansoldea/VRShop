#include "BasicStringDefinitions.h"
#include "VRDatabaseInterfaceShopClient.h"

#include <iostream>

#include "VRAvatarManagerServer.h"
#include "VRUserAccount.h"

#include "VRServerClientCommands.h"

#include <list>
#include <vector>
#include <string>

#include "Timer.h"

#include "VRDatabaseNetworkManager.h"

using namespace VR;
using namespace std;


//----------------------------------------------------------------------

DatabaseNetworkManager::DatabaseNetworkManager(QObject *apParent) : QObject(apParent)	{
	m_pTimer = Timer::CreateInstance(TimerBase::REAL_TIME);
}

//----------------------------------------------------------------------

DatabaseNetworkManager::~DatabaseNetworkManager()	{
	delete m_pTimer;
}

//=====================================================================

list<string> DatabaseNetworkManager::getResult()	{
	return m_lststrResult;
}

//----------------------------------------------------------------------

bool DatabaseNetworkManager::databaseRequest(int anOperationType, string & astrRequest)	{
	string strSqlQuery;
	string strDatabaseName;	
		
	if (anOperationType == ServerClientCommands::PRODUCT_REQUEST)	{
		strSqlQuery = "SELECT * FROM Product WHERE ProductName = '" + astrRequest + "'";
		strDatabaseName = "Products";
	} else if (anOperationType == ServerClientCommands::AVATAR_REGISTER)	{
		AvatarManagerServer ams;
		ams.registerAvatar(astrRequest);

//		m_lststrResult.push_back(tostr(0));
		return false;
	} else if (anOperationType == ServerClientCommands::AVATAR_UPDATE)	{
		AvatarManagerServer ams;
		ams.updateAvatarData(astrRequest);

		return false;
	} else if (anOperationType == ServerClientCommands::OTHER_AVATARS_REQUEST)	{
		AvatarManagerServer ams;
		m_lststrResult = ams.getAvatarsDataFromDB();

		return (m_lststrResult.empty()) ? false : true;

	} else if (anOperationType == ServerClientCommands::SIGN_IN_REQUEST)	{
		UserAccount ua;
		int nRes = ua.trySignIn(astrRequest) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
		m_lststrResult.push_back(tostr(nRes));

		return true;
		
	} else if (anOperationType == ServerClientCommands::SIGN_UP_REQUEST)	{
		UserAccount ua;
		int nRes = ua.trySignUp(astrRequest) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
		m_lststrResult.push_back(tostr(nRes));

		return true;
	} else if (anOperationType == ServerClientCommands::SIGN_OUT_REQUEST)	{
		UserAccount ua;
		int nRes = ua.trySignOut(astrRequest) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
		m_lststrResult.push_back(tostr(nRes));

		return true;
	} else if (anOperationType == ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST)	{
		UserAccount ua;
		int nRes = ua.tryModifyUserAccount(astrRequest) ? ServerClientCommands::PASSED : ServerClientCommands::FAILED;
		m_lststrResult.push_back(tostr(nRes));

		return true;
	}

	DatabaseInterfaceShopClientParams dbParams;
	dbParams.m_qstrDBName = ("../../../../Databases/" + strDatabaseName + ".db").c_str();
	
	DatabaseInterfaceShopClient db(dbParams);
	
	m_lststrResult = db.executeAndGetResult(strSqlQuery);

	return (m_lststrResult.empty()) ? false : true;
}