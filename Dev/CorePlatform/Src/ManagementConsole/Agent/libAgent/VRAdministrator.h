#ifndef VR_ADMINISTRATOR_H
#define VR_ADMINISTRATOR_H

#include "VRAbstractUser.h"

namespace VR {
	class ProductShopClient;

	//NOT TO BE IMPLEMENTED IN THE FIRST VERSION
	class Administrator : public AbstractUser	{
	public:
		Administrator(Avatar * apAvatar = 0);
		virtual ~Administrator();

		virtual const char* className() const;

		virtual bool trySignIn();
		bool trySignOut();

		void addProduct2Database(const ProductShopClient & aProduct);
		void removeProductFromDatabase(const ProductShopClient & aProduct);
		void modifyProductInDatabase(const ProductShopClient & aProduct);

		void exposeProduct(const ProductShopClient & aProduct);
		void hideProduct(const ProductShopClient & aProduct);
		
	};
}
#endif //VR_ADMINISTRATOR_H