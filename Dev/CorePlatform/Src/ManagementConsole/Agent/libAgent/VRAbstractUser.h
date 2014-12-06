#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <string>
#include <osg/ref_ptr>

namespace VR {
	class Avatar;
	class ProductShopClient;

	class AbstractUser	{
	public:
		AbstractUser(Avatar * apAvatar = 0);
		virtual ~AbstractUser() = 0;
		virtual const char* className() const;

		Avatar * getAvatar();
		std::string getUserIDName() const;
		bool getIsUserAuthorized() const;
	
	protected:

		//not 2 be implemented in the 1. version
		virtual void userActivity();

		void findProductInShop(const ProductShopClient & aProduct) const {};

		//Communication between agents - not 2 be implemented in the 1. version
		void sendMessage(std::string & astrMessage);
		void receiveMessage(std::string & astrMessage);

		osg::ref_ptr<Avatar> m_pAvatar;

	private:
		std::string m_strUserIDName;
		bool m_bIsUserAuthorized;

	public:
		void setUserIDName(std::string m_strUserIDName);
	};
}
#endif //VR_ABSTRACT_USER_H