#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <string>
#include "VRBasket.h"

namespace VR {
	class Basket;
	class Product;
	class Avatar;

	class PickAndDragHandlerShopClient;

	class AbstractUser	{
	public:
		AbstractUser();
		virtual ~AbstractUser() = 0;
		virtual const char* className() const;

		void setPicker(PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient);

		Avatar * getAvatar();
		Basket * getBasket();	//This basket is read by the "VRTransaction.h" before the payment
	
	protected:
		virtual bool trySignIn() = 0;

		//not 2 be implemented in the 1. version
		virtual void userActivity();

		void findProductInShop(const Product & aProduct) const;

		//Communication between agents - not 2 be implemented in the 1. version
		void sendMessage(std::string & astrMessage);
		void receiveMessage(std::string & astrMessage);

		Avatar * m_pAvatar;
		Basket m_Basket;

		PickAndDragHandlerShopClient * m_pPickAndDragHandlerShopClient;
	};
}
#endif //VR_ABSTRACT_USER_H