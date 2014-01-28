#include <vector>

#include "VRDatabaseMgr.h"

#include "VRProduct.h"

using namespace VR;
using namespace std;


ProductParams::ProductParams() : 
m_strProductCategory(""),
m_strProductName(""),
m_nProductCode(NULL),
m_strProductDescription(""),
m_strProductShortDescription(""),
m_strProductManufacturer(""),
m_strManufacturerOrigin(""),
m_nProductUnit(NULL),
m_flPricePerUnit(NULL),
m_flQuantity(NULL),
m_flTaxRate(NULL),
m_nCurrency(NULL)
{
}

//==============================================================================

Product::Product()	{
}

//------------------------------------------------------------------------------

void Product::modifyProduct(const Product & aProduct)	{
}

//------------------------------------------------------------------------------

void Product::createProductDB() const	{
	vector<string> vecstrDBParams;
	vecstrDBParams.push_back("ProductCode TEXT");
	vecstrDBParams.push_back("ProductCategory TEXT");
	vecstrDBParams.push_back("ProductName TEXT");
	vecstrDBParams.push_back("ProductDescription TEXT");
	vecstrDBParams.push_back("ProductShortDescription TEXT");
	vecstrDBParams.push_back("ProductManufacturer TEXT");
	vecstrDBParams.push_back("ManufacturerOrigin TEXT");
	vecstrDBParams.push_back("ProductUnit TEXT");
	vecstrDBParams.push_back("PricePerUnit TEXT");
	vecstrDBParams.push_back("Quantity TEXT");
	vecstrDBParams.push_back("TaxRate TEXT");
	vecstrDBParams.push_back("Currency TEXT");

	DatabaseMgrParams dMgrP;
	dMgrP.m_strTableName = "Products";
	dMgrP.m_arrstrParams = vecstrDBParams;

	string strDBName = "../../../Databases/Products.db";

	DatabaseMgr & database = VR::DatabaseMgr::Create(strDBName.c_str(),DatabaseMgr::QSQLITE);
	database.createTable(dMgrP);
}

//------------------------------------------------------------------------------

void Product::productViewed(const Product & aProduct /* User & aUser*/)	{

	//When a product is viewed, update the database
	string strSQLCommand;

	strSQLCommand = "UPDATE " /* + PRODUCT_TABLE + */ 
		"SET products_viewed = products_viewed+1"
		"WHERE products_id = '" /*+ GET_PRODUCT_ID + */ "'";

}