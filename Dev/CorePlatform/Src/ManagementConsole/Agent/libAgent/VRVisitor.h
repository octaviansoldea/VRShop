#ifndef VR_VISITOR_H
#define VR_VISITOR_H

#include "VRAbstractUser.h"

/*	
	Visitor is a user of the platform who hasn't signed-in yet. 
	The visitor can use the platform but has to sign-in should he make a purchase.
*/

#include <list>

namespace VR	{
	class ProductShopClient;
	class BasketClient;

	class Visitor : public AbstractUser {
	public:
		Visitor(Avatar * apAvatar = 0);
		virtual ~Visitor();

		virtual const char* className() const;

		// Track client's activity: client_ID, access_date/time, exit_date/time, products_observed

		BasketClient * getBasket();

		bool addProduct2Basket(ProductShopClient * apProduct); //check if the shop can satisfy the request.
		bool removeProductFromBasket(ProductShopClient * apProduct);
		void listProductsInBasket() const;
		void inspectProduct(const ProductShopClient & aProduct) const;

		void listProductComplements(std::list < ProductShopClient > & alstProducts, const ProductShopClient * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(std::list < ProductShopClient > & alstProducts, const ProductShopClient * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice


		void requestHelp();

		bool approachCashier();	//For now just returns true
		void payRequest();


	private:
		BasketClient * m_pBasket;

		bool tryPay();
	};
}
#endif //VR_VISITOR_H