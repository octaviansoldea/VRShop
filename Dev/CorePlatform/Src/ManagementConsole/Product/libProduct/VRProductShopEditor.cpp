#include "VRAbstractObjectFactory.h"
#include "VRAbstractObject.h"

#include "VRDatabaseInterfaceShopEditor.h"

#include "BasicStringDefinitions.h"

#include "VRProductShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;

ProductShopEditorParams::ProductShopEditorParams() : 
AbstractProductParams(),
m_strProductCategory(""),
m_strProductName(""),
m_ulProductCode(0),
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
m_strProductDateAdded(""),
m_strProductDateLastModified(""),
m_strTextureFile("")	{
}

//==============================================================================

ProductShopEditor::ProductShopEditor() : 
AbstractProduct()/*, m_pRepresentation(0)*/	{
}

//------------------------------------------------------------------------------

ProductShopEditor::ProductShopEditor(string & astrSQLParams) : 
AbstractProduct()	{
	initFromSQLData(astrSQLParams);
}

//------------------------------------------------------------------------------

ProductShopEditor::ProductShopEditor(ref_ptr <AbstractObject> apRepresentation, const ProductShopEditorParams & aProductShopEditorParams) :
m_pRepresentation(apRepresentation)	{
	m_ProductShopEditorParams = aProductShopEditorParams;

	setParams(m_ProductShopEditorParams);
}

//------------------------------------------------------------------------------

ProductShopEditor::~ProductShopEditor()	{
}

//==============================================================================

void ProductShopEditor::createRepresentation(const std::string & astrRepresentation)	{
	m_pRepresentation = AbstractObjectFactory::createAbstractObject(astrRepresentation);
	m_pRepresentation->setIsTargetPick(true);
}

//------------------------------------------------------------------------------

ref_ptr<AbstractObject> ProductShopEditor::getRepresentation() const	{
	return m_pRepresentation;
}

//------------------------------------------------------------------------------

void ProductShopEditor::setColor(const std::vector < float > & aarrflColor)	{
	m_pRepresentation->setColor(aarrflColor);
}

//------------------------------------------------------------------------------

void ProductShopEditor::setTexture(const std::string & astrFileName)	{
	m_pRepresentation->setTexture(astrFileName);
}

//------------------------------------------------------------------------------

string ProductShopEditor::getTexture() const	{
	return m_ProductShopEditorParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

void ProductShopEditor::setParams(const ProductShopEditorParams & aProductShopEditorParams)	{
	m_ProductShopEditorParams.m_strProductCategory = aProductShopEditorParams.m_strProductCategory;
	m_ProductShopEditorParams.m_strProductName = aProductShopEditorParams.m_strProductName;
	m_ProductShopEditorParams.m_ulProductCode = aProductShopEditorParams.m_ulProductCode;
	m_ProductShopEditorParams.m_strProductDescription = aProductShopEditorParams.m_strProductDescription;
	m_ProductShopEditorParams.m_strProductShortDescription = aProductShopEditorParams.m_strProductShortDescription;
	m_ProductShopEditorParams.m_strManufacturerName = aProductShopEditorParams.m_strManufacturerName;
	m_ProductShopEditorParams.m_strManufacturerOrigin = aProductShopEditorParams.m_strManufacturerOrigin;
	m_ProductShopEditorParams.m_strProductDateAdded = aProductShopEditorParams.m_strProductDateAdded;
	m_ProductShopEditorParams.m_strProductDateLastModified = aProductShopEditorParams.m_strProductDateLastModified;
	m_ProductShopEditorParams.m_strProductUnit = aProductShopEditorParams.m_strProductUnit;
	m_ProductShopEditorParams.m_flPricePerUnit = aProductShopEditorParams.m_flPricePerUnit;
	m_ProductShopEditorParams.m_flQuantity = aProductShopEditorParams.m_flQuantity;
	m_ProductShopEditorParams.m_flTaxRate = aProductShopEditorParams.m_flTaxRate;
	m_ProductShopEditorParams.m_strCurrency = aProductShopEditorParams.m_strCurrency;
	m_ProductShopEditorParams.m_strTextureFile = aProductShopEditorParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

void ProductShopEditor::getParams(ProductShopEditorParams & aProductShopEditorParams) const	{
	aProductShopEditorParams.m_strProductCategory = m_ProductShopEditorParams.m_strProductCategory;
	aProductShopEditorParams.m_strProductName = m_ProductShopEditorParams.m_strProductName;
	aProductShopEditorParams.m_ulProductCode = m_ProductShopEditorParams.m_ulProductCode;
	aProductShopEditorParams.m_strProductDescription = m_ProductShopEditorParams.m_strProductDescription;
	aProductShopEditorParams.m_strProductShortDescription = m_ProductShopEditorParams.m_strProductShortDescription;
	aProductShopEditorParams.m_strManufacturerName = m_ProductShopEditorParams.m_strManufacturerName;
	aProductShopEditorParams.m_strManufacturerOrigin = m_ProductShopEditorParams.m_strManufacturerOrigin;
	aProductShopEditorParams.m_strProductDateAdded = m_ProductShopEditorParams.m_strProductDateAdded;
	aProductShopEditorParams.m_strProductDateLastModified = m_ProductShopEditorParams.m_strProductDateLastModified;
	aProductShopEditorParams.m_strProductUnit = m_ProductShopEditorParams.m_strProductUnit;
	aProductShopEditorParams.m_flPricePerUnit = m_ProductShopEditorParams.m_flPricePerUnit;
	aProductShopEditorParams.m_flQuantity = m_ProductShopEditorParams.m_flQuantity;
	aProductShopEditorParams.m_flTaxRate = m_ProductShopEditorParams.m_flTaxRate;
	aProductShopEditorParams.m_strCurrency = m_ProductShopEditorParams.m_strCurrency;
	aProductShopEditorParams.m_strTextureFile = m_ProductShopEditorParams.m_strTextureFile;
}

//------------------------------------------------------------------------------

void ProductShopEditor::setQuantity(float aflQuantity)	{
	m_ProductShopEditorParams.m_flQuantity = aflQuantity;
}

//------------------------------------------------------------------------------

float ProductShopEditor::getQuantity() const	{
	return m_ProductShopEditorParams.m_flQuantity;
}

//------------------------------------------------------------------------------

void ProductShopEditor::setPrice(float aflPrice)	{
	m_ProductShopEditorParams.m_flPricePerUnit = aflPrice;
}

//------------------------------------------------------------------------------

float ProductShopEditor::getPrice() const	{
	return m_ProductShopEditorParams.m_flPricePerUnit;
}

//------------------------------------------------------------------------------

unsigned long ProductShopEditor::getProductCode() const	{
	return m_ProductShopEditorParams.m_ulProductCode;
}

//------------------------------------------------------------------------------

string ProductShopEditor::prepareRowData(const string & astrParentName)	{
	ProductShopEditorParams productParams;
	getParams(productParams);

	string strProductParams;

	strProductParams += productParams.m_strProductCategory + ";";
	strProductParams += productParams.m_strProductName + ";";
	strProductParams += tostr(productParams.m_ulProductCode) + ";";
	strProductParams += productParams.m_strProductShortDescription + ";";
	strProductParams += productParams.m_strProductDescription + ";";
	strProductParams += productParams.m_strManufacturerName + ";";
	strProductParams += productParams.m_strManufacturerOrigin + ";";
	strProductParams += productParams.m_strProductUnit + ";";
	strProductParams += productParams.m_strProductUnitMeasure + ";";
	strProductParams += tostr(productParams.m_flQuantity) + ";";
	strProductParams += tostr(productParams.m_flPricePerUnit) + ";";
	strProductParams += tostr(productParams.m_flTaxRate) + ";";
	strProductParams += productParams.m_strCurrency + ";";
	strProductParams += productParams.m_strProductDateAdded + ";";
	strProductParams += productParams.m_strProductDateLastModified + ";";
	strProductParams += productParams.m_strTextureFile + ";";

	return strProductParams;
}

//------------------------------------------------------------------------------

void ProductShopEditor::initFromSQLData(std::string & astrSQLData)	{
	vector<string> vecstrProductParams = splitString(astrSQLData,";");
	vector<string>::iterator it = vecstrProductParams.begin();

	m_ProductShopEditorParams.m_strProductCategory = *(it+1);
	m_ProductShopEditorParams.m_strProductName = *(it+2);
	m_ProductShopEditorParams.m_ulProductCode = stol(*(it+3));
	m_ProductShopEditorParams.m_strProductShortDescription = *(it+4);
	m_ProductShopEditorParams.m_strProductDescription = *(it+5);
	m_ProductShopEditorParams.m_strManufacturerName = *(it+6);
	m_ProductShopEditorParams.m_strManufacturerOrigin = *(it+7);
	m_ProductShopEditorParams.m_strProductUnit = *(it+8);
	m_ProductShopEditorParams.m_flQuantity = stof(*(it+10));
	m_ProductShopEditorParams.m_flPricePerUnit = stof(*(it+11));
	m_ProductShopEditorParams.m_flTaxRate = stof(*(it+12));
	m_ProductShopEditorParams.m_strCurrency = *(it+13);
	m_ProductShopEditorParams.m_strTextureFile = *(it+16);
}
