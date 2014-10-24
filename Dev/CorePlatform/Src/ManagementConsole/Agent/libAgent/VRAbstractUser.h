#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <string>

namespace VR {
	class Avatar;
	class ProductShopClient;
	class BasketClient;

	class AbstractUser	{
	public:
		AbstractUser(Avatar * apAvatar = 0);
		virtual ~AbstractUser() = 0;
		virtual const char* className() const;

		Avatar * getAvatar();
		BasketClient * getBasket();	//This basket is read by the "VRTransaction.h" before the payment
		std::string getUserIDName() const;
	
	protected:

		//not 2 be implemented in the 1. version
		virtual void userActivity();

		void findProductInShop(const ProductShopClient & aProduct) const {};

		//Communication between agents - not 2 be implemented in the 1. version
		void sendMessage(std::string & astrMessage);
		void receiveMessage(std::string & astrMessage);

		Avatar * m_pAvatar;
		BasketClient * m_pBasket;

	private:
		std::string m_strUserIDName;

	public:
		void setUserIDName(std::string m_strUserIDName);
	};
}
#endif //VR_ABSTRACT_USER_H