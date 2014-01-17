#ifndef VR_BASKET_H
#define VR_BASKET_H

#include <vector>

#include "VRProduct.h"

namespace VR	{
	class Basket : public std::vector<Product>	{
	public:
		Basket();
		~Basket();

		void listBasketProducts() const;
		void addProduct2Basket(const Product & aProduct) const;//check if the shop can satisfy the request.
		void removeProductFromBasket(const Product & aProduct) const;
		void findProductInBasket(const Product & aProduct) const;

		float calculateCurrentBasketValue() const;	//Calculate the value of the products in the basket
		void getProductProperties(const Product * apProduct) const;

		void listProductComplements(const Product * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(const Product * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice

	private:
	};
}
#endif //VR_BASKET_H