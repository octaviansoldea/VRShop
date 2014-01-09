#ifndef VR_PRODUCT_H
#define VR_PRODUCT_H

#include <string>

namespace VR	{
	struct ProductParams	{
		int m_nProductID;
		std::string m_strProductName;
		std::string m_strProductManufacturer;
		float m_flPricePerUnit;
		float m_flQuantity;
		float m_flTaxRate;
		float m_flDiscountRate;

		enum PRODUCT_UNIT { PIECE = 0, GRAM, KILOGRAM, MILILITER, LITER };
		enum CURRENCY { EURO = 0, US_DOLLAR, IL_SHEQEL };

		ProductParams();
	};


	class Product	{
	public:
		Product();
		Product(const ProductParams & aProductParams);

		void init(const ProductParams & aProductParams);

		void modifyProductSettings(const Product * apProduct);

	private:
		ProductParams m_ProductParams;
	};
}
#endif //VR_PRODUCT_H