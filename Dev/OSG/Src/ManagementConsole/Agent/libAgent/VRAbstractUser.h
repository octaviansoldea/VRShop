#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <list>

#include "VRProduct.h"
#include "VRAvatar.h"

namespace VR {
	class AbstractUser : public Avatar //: public  osg::MatrixTransform  
	{
	public:
		AbstractUser();
		virtual ~AbstractUser() = 0;

		//This function should be implemented in .cpp
		//Inputs directly taken from the GUI dialog
		void openAccount();
		virtual void trySignIn();	//If the user doesn't have an account yet, 
									//open him a create account dialog

		std::list<Product> getBasket() const;

		void addProduct2Basket(const Product & aProduct) const;//check if the shop can satisfy the request.
		void removeProductFromBasket(const Product & aProduct) const;
		void findProductInBasket(const Product & aProduct) const;

		void findProductInShop(const Product & aProduct) const;

		float calculateBasketValue() const;	//Calculate the value of the products in the basket

		void listProductComplements(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk => cereals
		void listProductSubstitutes(std::list < Product > & alstProducts, const Product * apProduct);	//e.g. Milk1 => Mllk2 or Water => Juice

	protected:
		std::list<Product> m_Basket;
	
		
	};
}
#endif //VR_ABSTRACT_USER_H