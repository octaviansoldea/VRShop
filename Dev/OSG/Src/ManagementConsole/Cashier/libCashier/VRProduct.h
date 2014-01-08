#ifndef VR_PRODUCT_H
#define VR_PRODUCT_H

namespace VR	{
	struct ProductParams	{
		float m_flPrice;
		float m_flQuantity;
		float m_flTaxRate;


		enum m_enumCurrency { EURO = 0, US_DOLLAR, IL_SHEQEL };

		ProductParams();
	};


	class Product	{
	public:
		Product();
	};
}
#endif //VR_PRODUCT_H