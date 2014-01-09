#ifndef VR_CUSTOMER_H
#define VR_CUSTOMER_H

#include "VRBasket.h"

namespace VR	{
	class Customer {
	public:
		Customer();

	private:
		int m_nNumberOfCustomers;
		Basket m_Basket;
	};
}
#endif //VR_CUSTOMER_H