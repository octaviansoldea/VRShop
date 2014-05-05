#ifndef VR_PRODUCT_H
#define VR_PRODUCT_H

#include <string>
#include <vector>

#include "VRAbstractObject.h"

namespace VR	{
	struct ProductParams	{
		std::string m_strProductCategory;
		std::string m_strProductName;
		unsigned long m_nProductCode;
		std::string m_strProductDescription;
		std::string m_strProductShortDescription;
		std::string m_strManufacturerName;
		std::string m_strManufacturerOrigin;
		std::string m_strDateAdded;
		std::string m_strDateLastModified;
		std::string m_strProductUnit;
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
		Product(osg::ref_ptr <AbstractObject> apRepresentation, const ProductParams & aProductParams);
		~Product();

		const char* className() const;

		void createRepresentation(const std::string & astrRepresentation);
		osg::ref_ptr<AbstractObject> getRepresentation() const;

		void setColor(const std::vector < float > & aarrflColor);
		void setTexture(const std::string & astrFileName);

		void setParams(const VR::ProductParams & aProductParams);
		void getParams(VR::ProductParams & aProductParams) const;

		std::string prepareRowData(const std::string & astrParentName="");

		void initFromSQLData(const std::string & astrSQLData) {};
		void predefinedObject() {};


	private:
		void createDBTableProduct() const;	//Let be Manufacturers in a separate table

		void productViewed(const Product & aProduct /* User & aUser*/);

		osg::ref_ptr<AbstractObject> m_pRepresentation;
		ProductParams m_ProductParams;
	};
}
#endif //VR_PRODUCT_H