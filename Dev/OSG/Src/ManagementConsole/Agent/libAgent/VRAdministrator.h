#ifndef VR_ADMINISTRATOR_H
#define VR_ADMINISTRATOR_H

#include "VRAbstractUser.h"

namespace VR {
	class Administrator : public AbstractUser {
	public:
		Administrator();
		void addProduct2Database(const Product & aProduct);
		void removeProductFromDatabase(const Product & aProduct);
		void modifyProductInDatabase(const Product & aProduct);

		void exposeProduct(const Product & aProduct);
		void hideProduct(const Product & aProduct);

		void hireGeneralWorker();
		void fireGeneralWorker();

	};
}
#endif //VR_ADMINISTRATOR_H