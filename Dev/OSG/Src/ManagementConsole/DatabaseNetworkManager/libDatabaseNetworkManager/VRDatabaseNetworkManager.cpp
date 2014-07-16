#include "BasicStringDefinitions.h"
#include "VRDatabaseManagerShopClient.h"

#include <iostream>

#include <list>
#include <vector>
#include <string>

#include "Timer.h"

#include "VRDatabaseNetworkManager.h"

using namespace VR;
using namespace std;

#define DEBUG_AVATARS 0

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

	string strType;
	if (anOperationType == 'P')	{	//'P' - product
		strSqlQuery = "SELECT * FROM Product WHERE ProductName = '" + astrRequest + "'";
		strDatabaseName = "Products";
	} else if (anOperationType == 'R')	{	//'R' - Register avatar
		strSqlQuery = "INSERT INTO Avatar(AvatarName) VALUES ('" + astrRequest + "')";
		strDatabaseName = "Avatars";
	} else if (anOperationType == 'A')	{	//'A' - avatar
		vector<string> vecstrSplitString = splitString(astrRequest,";");
		strSqlQuery = "UPDATE Avatar" 
			" SET AvatarMatrix = '" + vecstrSplitString[1] + 
//			"', AvatarDateTime = CURRENT_TIMESTAMP" + 
			"', AvatarDateTime = '" + tostr(m_pTimer->getCurrTimeInMiliSeconds()) + "'"+ 
			" WHERE AvatarName = '" + vecstrSplitString[0] + "'";
		strDatabaseName = "Avatars";
	} else if (anOperationType == 'a')	{	//'a' - other avatars

#if DEBUG_AVATARS
		vector<string> vecstrSplitString = splitString(astrRequest,";");
		int nI;
		string strSqlCondition = "'" + vecstrSplitString[0] + "'";
		for (nI=1;nI<vecstrSplitString.size();nI++)	{
			strSqlCondition += " OR AvatarName = '" + vecstrSplitString[nI] + "'";
		}
		strSqlQuery = "SELECT * FROM Avatar WHERE AvatarName = " + strSqlCondition;
#else
		strSqlQuery = "SELECT AvatarName, AvatarMatrix FROM Avatar";
#endif //DEBUG_AVATAR

		strDatabaseName = "Avatars";
	}

	DatabaseManagerShopClientParams dbParams;
	dbParams.m_qstrDBName = ("../../../../Databases/" + strDatabaseName + ".db").c_str();
	
	DatabaseManagerShopClient db(dbParams);
	
	m_lststrResult = db.executeAndGetResult(strSqlQuery);

	return (m_lststrResult.empty()) ? false : true;
}