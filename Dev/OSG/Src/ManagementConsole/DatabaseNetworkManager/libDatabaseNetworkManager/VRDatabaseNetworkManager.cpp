#include "BasicStringDefinitions.h"
#include "VRDatabaseManagerShopClient.h"

#include <iostream>

#include <list>
#include <vector>
#include <string>

#include "VRDatabaseNetworkManager.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

DatabaseNetworkManager::DatabaseNetworkManager(QObject *apParent) : QObject(apParent)	{

}

//----------------------------------------------------------------------

DatabaseNetworkManager::~DatabaseNetworkManager()	{
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
		strSqlQuery = "SELECT * FROM Products WHERE ProductName = '" + astrRequest + "'";
		strDatabaseName = "Products";
	} else if (anOperationType == 'A')	{	//'A' - avatar
		vector<string> vecstrSplitString = splitString(astrRequest,";");
		strSqlQuery = "UPDATE Avatars" 
			" SET AvatarMatrix = '" + vecstrSplitString[1] + 
			"' WHERE AvatarName = '" + vecstrSplitString[0] + "'";

		strDatabaseName = "Avatars";
	} else if (anOperationType == 'a')	{	//'a' - other avatars
		vector<string> & vecstrSplitString = splitString(astrRequest,";");
		int nI;
		string strSqlCondition = "'" + vecstrSplitString[0] + "'";
		for (nI=1;nI<vecstrSplitString.size();nI++)	{
			strSqlCondition += " OR AvatarName = '" + vecstrSplitString[nI] + "'";
		}

		strSqlQuery = "SELECT * FROM Avatars WHERE AvatarName = " + strSqlCondition;
		strDatabaseName = "Avatars";
	}

	DatabaseManagerShopClientParams dbParams;
	dbParams.m_qstrDBName = ("../../../../Databases/" + strDatabaseName + ".db").c_str();
	
	DatabaseManagerShopClient db(dbParams);
	
	m_lststrResult = db.executeAndGetResult(strSqlQuery);

	return (m_lststrResult.empty()) ? false : true;
}