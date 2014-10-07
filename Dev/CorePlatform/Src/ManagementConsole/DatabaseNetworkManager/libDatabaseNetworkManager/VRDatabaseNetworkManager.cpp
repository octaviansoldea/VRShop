#include "BasicStringDefinitions.h"
#include "VRDatabaseManagerShopClient.h"

#include <iostream>

#include "VRAvatarManagerServer.h"
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
		
	if (anOperationType == ServerClientCommands::getOperationType(ServerClientCommands::PRODUCT_REQUEST))	{
		strSqlQuery = "SELECT * FROM Product WHERE ProductName = '" + astrRequest + "'";
		strDatabaseName = "Products";
	} else if (anOperationType == ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_REGISTER))	{
		AvatarManagerServer ams;
		ams.registerAvatar(astrRequest);

		m_lststrResult=list<string>(0);
		return false;
	} else if (anOperationType == ServerClientCommands::getOperationType(ServerClientCommands::AVATAR_UPDATE))	{
		AvatarManagerServer ams;
		ams.updateAvatarData(astrRequest);

		m_lststrResult=list<string>(0);
		return false;
	} else if (anOperationType == ServerClientCommands::getOperationType(ServerClientCommands::OTHER_AVATARS_REQUEST))	{
		AvatarManagerServer ams;
		m_lststrResult = ams.getAvatarsDataFromDB();

		return (m_lststrResult.empty()) ? false : true;
	}

	DatabaseManagerShopClientParams dbParams;
	dbParams.m_qstrDBName = ("../../../../Databases/" + strDatabaseName + ".db").c_str();
	
	DatabaseManagerShopClient db(dbParams);
	
	m_lststrResult = db.executeAndGetResult(strSqlQuery);

	return (m_lststrResult.empty()) ? false : true;
}