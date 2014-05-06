#ifndef VR_BASKET_H
#define VR_BASKET_H

#include <list>

namespace VR	{
	class Product;

	class Basket {
	public:
		Basket();
		~Basket();

		const char* className() const;

		void addProduct(const Product & aProduct);
		void removeProduct(const Product & aProduct);
		void modifyQuantity(const Product & aProduct);

		float calculateBasketValue() const;

		Basket * getBasket() const;
		Product * getProduct(std::string & astrProductName);

	private:
		std::list<Product> m_lstBasket;
	};
}
#endif //VR_BASKET_H