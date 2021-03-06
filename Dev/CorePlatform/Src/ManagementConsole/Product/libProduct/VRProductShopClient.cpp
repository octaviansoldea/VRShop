#include "VRAbstractObject.h"
#include "VRPlate3D.h"

#include "BasicStringDefinitions.h"

#include <string>
#include <vector>

#include "VRProductShopClient.h"

using namespace VR;
using namespace osg;
using namespace std;

ProductShopClientParams::ProductShopClientParams() : 
AbstractProductParams(),
m_strProductName(""),
m_nProductCode(0),
m_strProductManufacturer(""),
m_strProductShortDescription(""),
m_strProductDescription(""),
m_strManufacturerName(""),
m_strManufacturerOrigin(""),
m_strProductUnit(""),
m_strProductUnitMeasure(""),
m_flQuantity(0),
m_flPricePerUnit(0),
m_flTaxRate(0),
m_strCurrency(""),
m_strTextureFile("")	{
}

//==============================================================================

ProductShopClient::ProductShopClient() : 
AbstractProduct()	{
}

//------------------------------------------------------------------------------

ProductShopClient::ProductShopClient(const ProductShopClientParams & aProductShopClientParams)	{
	setParams(aProductShopClientParams);
}

//------------------------------------------------------------------------------

ProductShopClient::~ProductShopClient()	{
}

//------------------------------------------------------------------------------

void ProductShopClient::setParams(const ProductShopClientParams & aProductShopClientParams)	{
	m_ProductShopClientParams.m_strProductName = aProductShopClientParams.m_strProductName;
	m_ProductShopClientParams.m_nProductCode = aProductShopClientParams.m_nProductCode;
	m_ProductShopClientParams.m_strProductManufacturer = aProductShopClientParams.m_strProductManufacturer;
	m_ProductShopClientParams.m_strProductShortDescription = aProductShopClientParams.m_strProductShortDescription;
	m_ProductShopClientParams.m_strProductDescription = aProductShopClientParams.m_strProductDescription;
	m_ProductShopClientParams.m_strManufacturerName = aProductShopClientParams.m_strManufacturerName;
	m_ProductShopClientParams.m_strManufacturerOrigin = aProductShopClientParams.m_strManufacturerOrigin;
	m_ProductShopClientParams.m_strProductUnit = aProductShopClientParams.m_strProductUnit;
	m_ProductShopClientParams.m_strProductUnitMeasure = aProductShopClientParams.m_strProductUnitMeasure;
	m_ProductShopClientParams.m_flQuantity = aProductShopClientParams.m_flQuantity;
	m_ProductShopClientParams.m_flPricePerUnit = aProductShopClientParams.m_flPricePerUnit;
	m_ProductShopClientParams.m_flTaxRate = aProductShopClientParams.m_flTaxRate;
	m_ProductShopClientParams.m_strCurrency = aProductShopClientParams.m_strCurrency;
	m_ProductShopClientParams.m_strTextureFile = aProductShopClientParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

void ProductShopClient::getParams(ProductShopClientParams & aProductShopClientParams) const	{

	aProductShopClientParams.m_strProductName = m_ProductShopClientParams.m_strProductName;
	aProductShopClientParams.m_nProductCode = m_ProductShopClientParams.m_nProductCode;
	aProductShopClientParams.m_strProductManufacturer = m_ProductShopClientParams.m_strProductManufacturer;
	aProductShopClientParams.m_strProductShortDescription = m_ProductShopClientParams.m_strProductShortDescription;
	aProductShopClientParams.m_strProductDescription = m_ProductShopClientParams.m_strProductDescription;
	aProductShopClientParams.m_strManufacturerName = m_ProductShopClientParams.m_strManufacturerName;
	aProductShopClientParams.m_strManufacturerOrigin = m_ProductShopClientParams.m_strManufacturerOrigin;
	aProductShopClientParams.m_strProductUnit = m_ProductShopClientParams.m_strProductUnit;
	aProductShopClientParams.m_strProductUnitMeasure = m_ProductShopClientParams.m_strProductUnitMeasure;
	aProductShopClientParams.m_flQuantity = m_ProductShopClientParams.m_flQuantity;
	aProductShopClientParams.m_flPricePerUnit = m_ProductShopClientParams.m_flPricePerUnit;
	aProductShopClientParams.m_flTaxRate = m_ProductShopClientParams.m_flTaxRate;
	aProductShopClientParams.m_strCurrency = m_ProductShopClientParams.m_strCurrency;
	aProductShopClientParams.m_strTextureFile = m_ProductShopClientParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

void ProductShopClient::setQuantity(float aflQuantity)	{
	m_ProductShopClientParams.m_flQuantity = aflQuantity;
}

//------------------------------------------------------------------------------

float ProductShopClient::getQuantity() const	{
	return m_ProductShopClientParams.m_flQuantity;
}

//------------------------------------------------------------------------------

float ProductShopClient::getPrice() const	{
	return m_ProductShopClientParams.m_flPricePerUnit;
}

//------------------------------------------------------------------------------

string ProductShopClient::getProductName() const	{
	return m_ProductShopClientParams.m_strProductName;
}

//------------------------------------------------------------------------------

string ProductShopClient::getProductTexture() const	{
	return m_ProductShopClientParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

long ProductShopClient::getProductID() const	{
	return m_ProductShopClientParams.m_nProductCode;
}

//------------------------------------------------------------------------------

void ProductShopClient::initFromSQLData(std::string & astrSQLData)	{
	string & strSqlData = astrSQLData;

	if (strSqlData == "")	{
		return;
	}

	vector<string> vecstrProductParams = splitString(strSqlData, ";");

	m_ProductShopClientParams.m_strProductName = vecstrProductParams[2];
	m_ProductShopClientParams.m_nProductCode = atoi(vecstrProductParams[3].c_str());
	m_ProductShopClientParams.m_strProductShortDescription = vecstrProductParams[4];
	m_ProductShopClientParams.m_strProductDescription = vecstrProductParams[5];
	m_ProductShopClientParams.m_strProductManufacturer = vecstrProductParams[6];
	m_ProductShopClientParams.m_strManufacturerOrigin = vecstrProductParams[7];
	m_ProductShopClientParams.m_strProductUnit = vecstrProductParams[9];
	m_ProductShopClientParams.m_flQuantity = atof(vecstrProductParams[10].c_str());
	m_ProductShopClientParams.m_flPricePerUnit = atof(vecstrProductParams[11].c_str());
	m_ProductShopClientParams.m_flTaxRate = atof(vecstrProductParams[12].c_str());
	m_ProductShopClientParams.m_strCurrency = vecstrProductParams[13];
	m_ProductShopClientParams.m_strTextureFile = vecstrProductParams[16];
}
