#include <vector>
#include <string>

#include "VRAbstractObject.h"
#include "VRPlate3D.h"
#include "VRPrism.h"

#include "VRDatabaseManagerShopEditor.h"

#include "VRProduct.h"

using namespace VR;
using namespace std;
using namespace osg;

ProductParams::ProductParams() : 
m_strProductCategory(""),
m_strProductName(""),
m_nProductCode(NULL),
m_strProductDescription(""),
m_strProductShortDescription(""),
m_nManufacturerID(NULL),
m_strManufacturerOrigin(""),
m_strDateAdded(""),
m_strDateLastModified(""),
m_strProductUnit(""),
m_flPricePerUnit(NULL),
m_flQuantity(NULL),
m_flTaxRate(NULL),
m_nCurrency(NULL)
{
}

//==============================================================================

Product::Product() : m_pRepresentation(0)	{
}

//------------------------------------------------------------------------------

Product::Product(ref_ptr <AbstractObject> apRepresentation, const ProductParams & aProductParams) :
m_pRepresentation(apRepresentation)	{
	m_ProductParams = aProductParams;
//	setParams(aProductParams);

	setParams(m_ProductParams);
}

//------------------------------------------------------------------------------

Product::~Product()	{
}

//------------------------------------------------------------------------------

void Product::createRepresentation(const std::string & astrRepresentation)	{
	m_pRepresentation = AbstractObject::createInstance(astrRepresentation);
	m_pRepresentation->setIsTargetPick(true);
}

//------------------------------------------------------------------------------

ref_ptr<AbstractObject> Product::getRepresentation() const	{
	return m_pRepresentation;
}

//------------------------------------------------------------------------------

const char* Product::className() const	{
	return "Product";
}

//-----------------------------------------------------------------------

void Product::setColor(const vector < float > & aarrflColor)	{
	m_pRepresentation->setColor(aarrflColor);
}

//-----------------------------------------------------------------------

void Product::setTexture(const string & astrFileName)	{
	m_pRepresentation->setTexture(astrFileName);
}

//-----------------------------------------------------------------------

void Product::setParams(const ProductParams & aProductParams)	{
	m_ProductParams.m_strProductCategory = aProductParams.m_strProductCategory;
	m_ProductParams.m_strProductName = aProductParams.m_strProductName;
	m_ProductParams.m_nProductCode = aProductParams.m_nProductCode;
	m_ProductParams.m_strProductDescription = aProductParams.m_strProductDescription;
	m_ProductParams.m_strProductShortDescription = aProductParams.m_strProductShortDescription;
	m_ProductParams.m_nManufacturerID = aProductParams.m_nManufacturerID;
	m_ProductParams.m_strManufacturerOrigin = aProductParams.m_strManufacturerOrigin;
	m_ProductParams.m_strDateAdded = aProductParams.m_strDateAdded;
	m_ProductParams.m_strDateLastModified = aProductParams.m_strDateLastModified;
	m_ProductParams.m_strProductUnit = aProductParams.m_strProductUnit;
	m_ProductParams.m_flPricePerUnit = aProductParams.m_flPricePerUnit;
	m_ProductParams.m_flQuantity = aProductParams.m_flQuantity;
	m_ProductParams.m_flTaxRate = aProductParams.m_flTaxRate;
	m_ProductParams.m_nCurrency = aProductParams.m_nCurrency;
}

//-----------------------------------------------------------------------

void Product::getParams(ProductParams & aProductParams) const	{
	aProductParams.m_strProductCategory = m_ProductParams.m_strProductCategory;
	aProductParams.m_strProductName = m_ProductParams.m_strProductName;
	aProductParams.m_nProductCode = m_ProductParams.m_nProductCode;
	aProductParams.m_strProductDescription = m_ProductParams.m_strProductDescription;
	aProductParams.m_strProductShortDescription = m_ProductParams.m_strProductShortDescription;
	aProductParams.m_nManufacturerID = m_ProductParams.m_nManufacturerID;
	aProductParams.m_strManufacturerOrigin = m_ProductParams.m_strManufacturerOrigin;
	aProductParams.m_strDateAdded = m_ProductParams.m_strDateAdded;
	aProductParams.m_strDateLastModified = m_ProductParams.m_strDateLastModified;
	aProductParams.m_strProductUnit = m_ProductParams.m_strProductUnit;
	aProductParams.m_flPricePerUnit = m_ProductParams.m_flPricePerUnit;
	aProductParams.m_flQuantity = m_ProductParams.m_flQuantity;
	aProductParams.m_flTaxRate = m_ProductParams.m_flTaxRate;
	aProductParams.m_nCurrency = m_ProductParams.m_nCurrency;
}

//------------------------------------------------------------------------------

string Product::prepareRowData(const string & astrParentName)	{
	ProductParams productParams;
	getParams(productParams);

	string strProductParams;

	return strProductParams;
}


//------------------------------------------------------------------------------

void Product::createDBTableProduct() const	{
	vector<pair<string,string>> avecStmtPairs;
	string strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Products ( \
		ProductCode TEXT UNIQUE \
		ProductCategory TEXT \
		ProductName TEXT \
		ProductDescription TEXT \
		ProductShortDescription TEXT \
		ManufacturerID INTEGER UNIQUE \
		ManufacturerOrigin TEXT \
		ProductUnit TEXT \
		PricePerUnit TEXT \
		Quantity TEXT \
		TaxRate TEXT \
		Currency TEXT \
		ProductFrame TEXT \
		ProductImage TEXT \
		ProductSize TEXT \
		FOREIGN KEY (ManufacturerID) REFERENCES Manufacturer(ManufacturerID)";
	avecStmtPairs.push_back(make_pair("Products", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Manufacturer ( \
		ManufacturerID INTEGER UNIQUE \
		ManufacturerName TEXT \
		ManufacturerAddress TEXT \
		ManufacturerOrigin TEXT \
		ManufacturerURL TEXT);";
	avecStmtPairs.push_back(make_pair("Manufacturer", strSQLFormat));
}

//------------------------------------------------------------------------------

void Product::productViewed(const Product & aProduct /*, User & aUser*/)	{

	//When a product is viewed, update the database
	string strSQLCommand;

	strSQLCommand = "UPDATE " /* + PRODUCT_TABLE + */ 
		"SET products_viewed = products_viewed+1"
		"WHERE products_id = '" /*+ GET_PRODUCT_ID + */ "'";

}