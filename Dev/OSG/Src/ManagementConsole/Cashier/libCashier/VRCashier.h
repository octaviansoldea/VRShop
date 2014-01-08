#ifndef VR_CASHIER_H
#define VR_CASHIER_H

#include <vector>

#include "VRProduct.h"

namespace VR	{
	struct CashierParams	{
		CashierParams();
	};

	class Cashier	{
	public:
		Cashier();

		void addProductInBasket(const Product & aProduct);
		void removeProductFromBasket(const Product & aProduct);

	private:
		std::vector <Product> m_vecProducts;
	};
}
#endif //VR_CASHIER_H