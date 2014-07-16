#ifndef VR_PRODUCT_SHOP_CLIENT_H
#define VR_PRODUCT_SHOP_CLIENT_H

#include "VRAbstractProduct.h"

//Visualization is done within the Scene DB
//3D objects as products are class-named "Product" - separation
//object name returns product code - identification

#include <string>

namespace VR	{
	struct ProductShopClientParams : public AbstractProductParams	{
		std::string m_strProductName;
		unsigned long m_nProductCode;
		std::string m_strProductManufacturer;
		std::string m_strProductShortDescription;
		std::string m_strProductDescription;
		std::string m_strManufacturerName;
		std::string m_strManufacturerOrigin;
		std::string m_strProductUnit;
		std::string m_strProductUnitMeasure;
		float m_flQuantity;
		float m_flPricePerUnit;
		float m_flTaxRate;
		std::string m_strCurrency;
		std::string m_strTextureFile;

		ProductShopClientParams();
	};

	class ProductShopClient : public AbstractProduct	{
	public:
		ProductShopClient();
		ProductShopClient(const ProductShopClientParams & aProductShopClientParams);
		virtual ~ProductShopClient();

		void setParams(const ProductShopClientParams & aProductShopClientParams);
		void getParams(ProductShopClientParams & aProductShopClientParams) const;

		void setQuantity(float aflQuantity);
		float getQuantity() const;
		float getPrice() const;

		virtual void initFromSQLData(std::string & astrSQLData);

	private:
		ProductShopClientParams m_ProductShopClientParams;
	};
}
#endif //VR_PRODUCT_SHOP_CLIENT_H