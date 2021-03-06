#include <iostream>
#include <string>
#include <list>

#include "BasicStringDefinitions.h"

#include "VRAppDataServer.h"
#include "VRBasketServer.h"
#include "VRDatabaseInterface.h"

#include "VRProductManagerServer.h"

using namespace VR;
using namespace std;

DatabaseInterface * ProductManagerServer::m_pDIProduct = 0;

//==============================================================================

const char* ProductManagerServer::className() const	{
	return "ProductManagerServer";
}

//-----------------------------------------------------------------------------

DatabaseInterfaceParams ProductManagerServer::getDBParams()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "Product";
	dbParams.m_qstrDBName = getDatabaseName().c_str();

	return dbParams;
}

//-----------------------------------------------------------------------------

string ProductManagerServer::getTableName()	{
	return "Product";
}

//------------------------------------------------------------------------------

string ProductManagerServer::getDatabaseName()	{
	return AppDataServer::getFPathDatabases() + "/Products.db";
}

//------------------------------------------------------------------------------

DatabaseInterface * ProductManagerServer::getDatabaseInterface() {
	return(m_pDIProduct);
}

//------------------------------------------------------------------------------

void ProductManagerServer::createDB()	{
	vector<pair<string,string>> vecpairDBElements;
	{
		vecpairDBElements.push_back(make_pair("ProductID", "INTEGER"));
		vecpairDBElements.push_back(make_pair("ProductViewed", "INTEGER"));
	}
	m_pDIProduct->createTable("ProductStats", vecpairDBElements);
}

//------------------------------------------------------------------------------

string ProductManagerServer::getProductDataFromDB(const std::string astrProductName)	{
	string strQuery = "SELECT * FROM Product WHERE ProductName = '" + astrProductName + "' OR ProductCode = '" +astrProductName + "'";

	list<string> lstResult = m_pDIProduct->executeAndGetResult(strQuery);
	if (lstResult.empty())	{
		return "";
	}

	list<string>::iterator it = lstResult.begin();
	string strProductData = *it;

	//Modify productStats table
	productViewedCounter(astrProductName);

	return strProductData;
}

//------------------------------------------------------------------------------

string ProductManagerServer::getProductInfo(const string astrProductName)	{
	//NOT YET IMPLEMENTED

	string strProductData;
	return strProductData;
}

//------------------------------------------------------------------------------

bool ProductManagerServer::canFullfilRequest(std::string & astrBasketRequest)	{
	//Requested quantities
	vector<string> vecstrBasket = splitString(astrBasketRequest,";");
	int nSize = vecstrBasket.size();
	if (nSize % 2 != 0)	{
		//Size doesn't match. Try to identify the missing item
		return false;
	}
	map<long,float> mapIDQuantityRequest;
	string strQuery = "SELECT ProductCode, ProductQuantity FROM Product WHERE ";

	int nI;
	nSize /= 2;
	for (nI=0; nI < nSize-1; nI++)	{
		mapIDQuantityRequest[stol(vecstrBasket[2*nI])] = stof(vecstrBasket[2*nI+1]);
		strQuery += " ProductCode = '" + vecstrBasket[2*nI] + "' AND ";
	}
	mapIDQuantityRequest[stol(vecstrBasket[2*nSize-2])] = stof(vecstrBasket[2*nSize-1]);
	strQuery += " ProductCode = '" + vecstrBasket[2*nSize-2] + "'";


	//Available quantities
	map < long, float > mapIDQuantityAvailable;
	list<string> lststrResult = m_pDIProduct->executeAndGetResult(strQuery);

	nSize = lststrResult.size();
	list<string>::iterator it = lststrResult.begin();
	for (nI=0;nI<nSize;nI++)	{
		vector<string> vecstrBasket = splitString(*it,";");
		mapIDQuantityAvailable[stoi(vecstrBasket[0])] = stof(vecstrBasket[1]);
	}

	//INSERT INTO TRANSACTION (SELECT ...) - CREATE TRANSACTION AND PUT IT ON HOLD

	//Compare both containers

	map < long, float > mapApprovedQuantities;
	//	translation to string encodsing: P1;Q1;P2;Q2...



	return true;
}

//------------------------------------------------------------------------------

float ProductManagerServer::tryAddProduct2Basket(const ProductManagerServerParams & aProductManagerServerParams)	{
	string strUserID = aProductManagerServerParams.m_strUserIDName;
	string strProductName = aProductManagerServerParams.m_strProductName;
	float flProductQuantityRequest = aProductManagerServerParams.m_flProductQuantity;

	string strQuery = 
		"SELECT ("
			"CASE "
				"WHEN ProductQuantity > " + tostr(flProductQuantityRequest) +  
				" THEN " + tostr(flProductQuantityRequest) + 
				" ELSE ProductQuantity "
			"END) "
		"FROM Product WHERE ProductName = '" + strProductName + "'";

	list<string> lststrResult = m_pDIProduct->executeAndGetResult(strQuery);

	if (lststrResult.empty())	{
		return 0;
	}
	float flQuantity = stof(lststrResult.front());

	//Remove from DB selected quantities
	strQuery = "UPDATE Product SET ProductQuantity = (ProductQuantity - " + tostr(flQuantity) +
		") WHERE ProductName = '" + strProductName + "'";

	m_pDIProduct->execute(strQuery);

	return flQuantity;
}

//------------------------------------------------------------------------------

bool ProductManagerServer::removeProduct(const ProductManagerServerParams & aProductManagerServerParams)	{
	//NOT YET FINISHED
	aProductManagerServerParams.m_strUserIDName;

	string strProductName = aProductManagerServerParams.m_strProductName;
	float flQuantity = aProductManagerServerParams.m_flProductQuantity;

	//Make these quantities available again
	string strQuery = "UPDATE Product SET ProductQuantity = (ProductQuantity + " + tostr(flQuantity) +
		") WHERE ProductName = '" + strProductName + "'";

	m_pDIProduct->execute(strQuery);

	//Remove product from temporary basket of user

	return true;
}

//------------------------------------------------------------------------------

float ProductManagerServer::modifyProductQuantity(const ProductManagerServerParams & aProductManagerServerParams)	{
	string strProductName = aProductManagerServerParams.m_strProductName;
	float flDiffQuantity = aProductManagerServerParams.m_flProductNewQuantity - aProductManagerServerParams.m_flProductQuantity;

	if (flDiffQuantity > 0)	{
		//Increase in quantity

		ProductManagerServerParams pmsp = aProductManagerServerParams;
		pmsp.m_flProductQuantity = flDiffQuantity;

		float flNewValue = (tryAddProduct2Basket(pmsp) + aProductManagerServerParams.m_flProductQuantity);

		return flNewValue;
	} else {
		//Make these quantities available again
		string strQuery = "UPDATE Product SET ProductQuantity = (ProductQuantity + " + tostr(fabs(flDiffQuantity)) +
			") WHERE ProductName = '" + strProductName + "'";

		m_pDIProduct->execute(strQuery);

		//Remove product from temporary basket of user

		return aProductManagerServerParams.m_flProductNewQuantity;
	}
}

//------------------------------------------------------------------------------

void ProductManagerServer::productViewedCounter(const string astrProductName)	{
	string strQuery = "UPDATE ProductStats SET ProductViewed = (ProductViewed+1) WHERE ProductCode IN (SELECT ProductCode FROM Product "
		" WHERE ProductName = '" + astrProductName + "')";

	m_pDIProduct->executeAndGetResult(strQuery);
}

//------------------------------------------------------------------------------

void ProductManagerServer::constructStatics() {
	m_pDIProduct = new DatabaseInterface(static_cast<DatabaseInterfaceParams&>(ProductManagerServer::getDBParams()));
}

//------------------------------------------------------------------------------

void ProductManagerServer::deleteStatics() {
	delete m_pDIProduct;
}