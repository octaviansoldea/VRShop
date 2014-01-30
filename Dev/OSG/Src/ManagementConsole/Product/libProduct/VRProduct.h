#ifndef VR_PRODUCT_H
#define VR_PRODUCT_H

#include <string>

namespace VR	{
	struct ProductParams	{
		std::string m_strProductCategory;
		std::string m_strProductName;
		unsigned long m_nProductCode;
		std::string m_strProductDescription;
		std::string m_strProductShortDescription;
		unsigned long m_nManufacturerID;
		std::string m_strManufacturerOrigin;
		std::string m_strDateAdded;
		std::string m_strDateLastModified;
		int m_nProductUnit;
		float m_flPricePerUnit;
		float m_flQuantity;
		float m_flTaxRate;
		int m_nCurrency;

		typedef enum PRODUCT_UNIT { PIECE = 0, GRAM, KILOGRAM, MILILITER, LITER };
		typedef enum CURRENCY { EURO = 0, US_DOLLAR, IL_SHEQEL, RO_RON };

		ProductParams();
	};


	class Product	{
	public:
		Product();
		Product(const ProductParams & aProductParams);

		void createProductDB() const;	//Let be Manufacturers in a separate table

		void newProduct(const Product & aProduct);
		void getProduct(const Product & aProduct);
		void removeProduct(const Product & aProduct);
		void modifyProduct(const Product & aProduct);

		void productViewed(const Product & aProduct /* User & aUser*/);

	private:
		ProductParams m_ProductParams;
	};
}
#endif //VR_PRODUCT_H