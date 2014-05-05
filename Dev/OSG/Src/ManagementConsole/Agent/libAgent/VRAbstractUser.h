#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

#include <vector>
#include "VRAvatar.h"
#include "VRProduct.h"

namespace VR {
	class AbstractUser	{
	public:
		AbstractUser();
		virtual ~AbstractUser() = 0;
		virtual const char* className() const;

		virtual bool trySignIn() = 0;

		void findProductInShop(const Product & aProduct) const;

	protected:
		Avatar m_Avatar;
		std::vector<Product> m_Basket;
	};
}
#endif //VR_ABSTRACT_USER_H