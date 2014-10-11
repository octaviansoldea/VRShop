#include <iostream>
#include <string>
#include <list>

#include "VRProductShopClient.h"

#include "VRDatabaseInterface.h"

#include "VRProductManagerServer.h"

using namespace VR;
using namespace std;
using namespace osg;

//-----------------------------------------------------------------------------

ProductManagerServer::ProductManagerServer()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "Product";
	dbParams.m_qstrDBName = "../../../Databases/Products.db";

	m_pDI = new DatabaseInterface(dbParams);
}

//-----------------------------------------------------------------------------

ProductManagerServer::~ProductManagerServer()	{
	delete m_pDI;
}

//==============================================================================

const char* ProductManagerServer::className() const	{
	return "ProductManagerServer";
}

//-----------------------------------------------------------------------------

string ProductManagerServer::getProductDataFromDB(const std::string astrProductName)	{
	string strQuery = "SELECT * FROM Product WHERE ProductName = '" + astrProductName + "'";

	list<string>::iterator it = m_pDI->executeAndGetResult(strQuery).begin();
	string & strProductData = *it;

	return strProductData;
}