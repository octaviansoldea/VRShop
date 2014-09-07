#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <string>
#include <osg/ref_ptr>


#include "VRBasket.h"

namespace VR {
	class Avatar;
	class Product;

	class AbstractUser	{
	public:
		AbstractUser(Avatar * apAvatar = 0);
		virtual ~AbstractUser() = 0;
		virtual const char* className() const;

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

		osg::ref_ptr<Avatar> m_pAvatar;
		Basket m_Basket;
	};
}
#endif //VR_ABSTRACT_USER_H