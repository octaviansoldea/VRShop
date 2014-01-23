#ifndef VR_CLIENT_H
#define VR_CLIENT_H

#include "VRAbstractUser.h"

namespace VR {
	class Client : public AbstractUser {
	public:
		Client();
		virtual ~Client();

		void pay();

		void openAccount();

		std::list<Product> getBasket() const;

		void addProduct2Basket(const Product & aProduct) const;//check if the shop can satisfy the request.
		void removeProductFromBasket(const Product & aProduct) const;
		void findProductInBasket(const Product & aProduct) const;

		void listProductComplements(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice

		float calculateBasketValue() const;	//Calculate the value of the products in the basket
	};
}
#endif //VR_CLIENT_H