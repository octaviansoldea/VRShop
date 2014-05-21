#include "VRDatabaseManagerShopClient.h"

#include <list>
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

std::list<std::string> DatabaseNetworkManager::getResult()	{
	return m_lststrResult;
}

//----------------------------------------------------------------------

bool DatabaseNetworkManager::requestDatabase(std::string & astrDatabaseRequest)	{
	DatabaseManagerShopClientParams dbParams;
	dbParams.m_qstrDBName = "../../../../../Databases/Products.db";
	
	DatabaseManagerShopClient db(dbParams);
	string strSqlQuery = "SELECT * FROM Products WHERE ProductName = '" + astrDatabaseRequest + "'";
	m_lststrResult = db.executeAndGetResult(strSqlQuery);

	return (m_lststrResult.empty()) ? false : true;
}