#ifndef VR_ADMINISTRATOR_H
#define VR_ADMINISTRATOR_H

#include "VRAbstractUser.h"

namespace VR {
	//NOT TO BE IMPLEMENTED IN THE FIRST VERSION
	class Administrator : public AbstractUser	{
	public:
		Administrator(Avatar * apAvatar = 0);
		virtual ~Administrator();

		virtual const char* className() const;

		virtual bool trySignIn();
		bool trySignOut();

		void addProduct2Database(const Product & aProduct);
		void removeProductFromDatabase(const Product & aProduct);
		void modifyProductInDatabase(const Product & aProduct);

		void exposeProduct(const Product & aProduct);
		void hideProduct(const Product & aProduct);
		
	};
}
#endif //VR_ADMINISTRATOR_H