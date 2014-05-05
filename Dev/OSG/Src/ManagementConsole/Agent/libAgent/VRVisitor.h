#ifndef VR_VISITOR_H
#define VR_VISITOR_H

#include "VRAbstractUser.h"

/*	
	Visitor is a user of the platform who hasn't signed-in yet. 
	The visitor can use the platform but has to sign-in should he make a purchase.
*/

namespace VR	{
	class Avatar;

	struct VisitorParams	{
		std::string m_strVisitorIP;
	};

	class Visitor : public AbstractUser {
	public:
		Visitor();

		virtual const char* className() const;

		virtual bool trySignIn();

		// Track client's activity: client_ID, access_date/time, exit_date/time, products_observed

		void pay();

		void openAccount();

		std::vector<Product> getBasket() const;

		void addProduct2Basket(const Product & aProduct) const;//check if the shop can satisfy the request.
		void removeProductFromBasket(const Product & aProduct) const;
		void findProductInBasket(const Product & aProduct) const;

		void listProductComplements(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice

		float calculateBasketValue() const;	//Calculate the value of the products in the basket



	};
}
#endif //VR_VISITOR_H