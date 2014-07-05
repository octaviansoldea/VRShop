#include "VRAbstractObject.h"
#include "VRPlate3D.h"
#include "VRPrism.h"

#include "VRDatabaseManagerShopEditor.h"

#include "BasicStringDefinitions.h"

#include "VRProductShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;

ProductShopEditorParams::ProductShopEditorParams() : 
AbstractProductParams(),
m_strProductCategory(""),
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
m_nCurrency(0),
m_strDateAdded(""),
m_strDateLastModified("")	{
}

//==============================================================================

ProductShopEditor::ProductShopEditor() : 
AbstractProduct(), m_pRepresentation(0)	{
}


ProductShopEditor::ProductShopEditor(ref_ptr <AbstractObject> apRepresentation, const ProductShopEditorParams & aProductShopEditorParams) :
m_pRepresentation(apRepresentation)	{
	m_ProductShopEditorParams = aProductShopEditorParams;

	setParams(m_ProductShopEditorParams);
}


//------------------------------------------------------------------------------

void ProductShopEditor::createRepresentation(const std::string & astrRepresentation)	{
	m_pRepresentation = AbstractObject::createInstance(astrRepresentation);
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

void ProductShopEditor::setParams(const ProductShopEditorParams & aProductShopEditorParams)	{
	m_ProductShopEditorParams.m_strProductCategory = aProductShopEditorParams.m_strProductCategory;
	m_ProductShopEditorParams.m_strProductName = aProductShopEditorParams.m_strProductName;
	m_ProductShopEditorParams.m_nProductCode = aProductShopEditorParams.m_nProductCode;
	m_ProductShopEditorParams.m_strProductDescription = aProductShopEditorParams.m_strProductDescription;
	m_ProductShopEditorParams.m_strProductShortDescription = aProductShopEditorParams.m_strProductShortDescription;
	m_ProductShopEditorParams.m_strManufacturerName = aProductShopEditorParams.m_strManufacturerName;
	m_ProductShopEditorParams.m_strManufacturerOrigin = aProductShopEditorParams.m_strManufacturerOrigin;
	m_ProductShopEditorParams.m_strDateAdded = aProductShopEditorParams.m_strDateAdded;
	m_ProductShopEditorParams.m_strDateLastModified = aProductShopEditorParams.m_strDateLastModified;
	m_ProductShopEditorParams.m_strProductUnit = aProductShopEditorParams.m_strProductUnit;
	m_ProductShopEditorParams.m_flPricePerUnit = aProductShopEditorParams.m_flPricePerUnit;
	m_ProductShopEditorParams.m_flQuantity = aProductShopEditorParams.m_flQuantity;
	m_ProductShopEditorParams.m_flTaxRate = aProductShopEditorParams.m_flTaxRate;
	m_ProductShopEditorParams.m_nCurrency = aProductShopEditorParams.m_nCurrency;
}

//------------------------------------------------------------------------------

void ProductShopEditor::getParams(ProductShopEditorParams & aProductShopEditorParams) const	{
	aProductShopEditorParams.m_strProductCategory = m_ProductShopEditorParams.m_strProductCategory;
	aProductShopEditorParams.m_strProductName = m_ProductShopEditorParams.m_strProductName;
	aProductShopEditorParams.m_nProductCode = m_ProductShopEditorParams.m_nProductCode;
	aProductShopEditorParams.m_strProductDescription = m_ProductShopEditorParams.m_strProductDescription;
	aProductShopEditorParams.m_strProductShortDescription = m_ProductShopEditorParams.m_strProductShortDescription;
	aProductShopEditorParams.m_strManufacturerName = m_ProductShopEditorParams.m_strManufacturerName;
	aProductShopEditorParams.m_strManufacturerOrigin = m_ProductShopEditorParams.m_strManufacturerOrigin;
	aProductShopEditorParams.m_strDateAdded = m_ProductShopEditorParams.m_strDateAdded;
	aProductShopEditorParams.m_strDateLastModified = m_ProductShopEditorParams.m_strDateLastModified;
	aProductShopEditorParams.m_strProductUnit = m_ProductShopEditorParams.m_strProductUnit;
	aProductShopEditorParams.m_flPricePerUnit = m_ProductShopEditorParams.m_flPricePerUnit;
	aProductShopEditorParams.m_flQuantity = m_ProductShopEditorParams.m_flQuantity;
	aProductShopEditorParams.m_flTaxRate = m_ProductShopEditorParams.m_flTaxRate;
	aProductShopEditorParams.m_nCurrency = m_ProductShopEditorParams.m_nCurrency;
}

//------------------------------------------------------------------------------

string ProductShopEditor::prepareRowData(const std::string & astrParentName)	{
	ProductShopEditorParams productParams;
	getParams(productParams);

	string strProductParams;

	strProductParams += productParams.m_strProductCategory + ";";
	strProductParams += productParams.m_strProductName + ";";
	strProductParams += productParams.m_nProductCode + ";";
	strProductParams += productParams.m_strProductDescription + ";";
	strProductParams += productParams.m_strProductShortDescription + ";";
	strProductParams += productParams.m_strManufacturerName + ";";
	strProductParams += productParams.m_strManufacturerOrigin + ";";
	strProductParams += productParams.m_strDateAdded + ";";
	strProductParams += productParams.m_strDateLastModified + ";";
	strProductParams += productParams.m_strProductUnit + ";";
	strProductParams += tostr(productParams.m_flPricePerUnit) + ";";
	strProductParams += tostr(productParams.m_flQuantity) + ";";
	strProductParams += tostr(productParams.m_flTaxRate) + ";";
	strProductParams += productParams.m_nCurrency + ";";

	return strProductParams;
}

//------------------------------------------------------------------------------

void ProductShopEditor::initFromSQLData(const std::string & astrSQLData)	{
}
