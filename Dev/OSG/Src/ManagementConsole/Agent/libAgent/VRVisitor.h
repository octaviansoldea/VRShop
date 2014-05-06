#ifndef VR_VISITOR_H
#define VR_VISITOR_H

#include "VRBasket.h"

#include "VRAbstractUser.h"

/*	
	Visitor is a user of the platform who hasn't signed-in yet. 
	The visitor can use the platform but has to sign-in should he make a purchase.
*/

namespace VR	{
	struct VisitorParams	{
		std::string m_strVisitorIP;
	};

	class Visitor : public AbstractUser {
	public:
		Visitor();

		virtual const char* className() const;

	protected:
		virtual bool trySignIn();
		bool openAccount();

		// Track client's activity: client_ID, access_date/time, exit_date/time, products_observed
		
		bool addProduct2Basket(const Product & aProduct) const;//check if the shop can satisfy the request.
		bool removeProductFromBasket(const Product & aProduct) const;
		void listProductsInBasket() const;
		void inspectProduct(const Product & aProduct) const;

		void listProductComplements(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice


		void requestHelp();

	};
}
#endif //VR_VISITOR_H