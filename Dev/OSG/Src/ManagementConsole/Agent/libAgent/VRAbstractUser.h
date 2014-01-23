#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <list>

#include "VRProduct.h"
#include "VRAvatar.h"

namespace VR {
	class AbstractUser : public Avatar {
	public:
		AbstractUser();
		virtual ~AbstractUser() = 0;

		virtual void trySignIn() = 0;

		void findProductInShop(const Product & aProduct) const;

	protected:
		std::list<Product> m_Basket;
	};
}
#endif //VR_ABSTRACT_USER_H