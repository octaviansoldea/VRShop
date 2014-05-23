#include <iostream>
#include <string>
#include <list>

#include "VRProductShopClient.h"

#include "VRDatabaseManager.h"

#include "VRProductManagerServer.h"

using namespace VR;
using namespace std;
using namespace osg;

//-----------------------------------------------------------------------------

ProductManagerServer::ProductManagerServer()	{
	DatabaseManagerParams dbParams;
	dbParams.m_qstrConnectionName = "Product";
	dbParams.m_qstrDBName = "../../../Databases/Product.db";

	m_pDb = new DatabaseManager(dbParams);
}

//-----------------------------------------------------------------------------

ProductManagerServer::~ProductManagerServer()	{
	delete m_pDb;
}

//==============================================================================

const char* ProductManagerServer::className() const	{
	return "ProductManagerServer";
}

//-----------------------------------------------------------------------------

string ProductManagerServer::getProductDataFromDB(const std::string astrProductName)	{
	string strQuery = "SELECT * FROM Product WHERE ProductName = '" + astrProductName + "'";

	list<string>::iterator it = m_pDb->executeAndGetResult(strQuery).begin();
	string & strProductData = *it;

	return strProductData;
}