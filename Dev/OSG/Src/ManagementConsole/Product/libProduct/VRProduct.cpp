#include "VRProduct.h"

using namespace VR;

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
	//Define a product

	std::string strSQLCommand = "SELECT PrimitiveID, ItemID FROM PrimitiveItemList "
		"WHERE EquipmentItemID = 1";

}
