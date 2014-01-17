#ifndef VR_CASHIER_H
#define VR_CASHIER_H

#include <vector>

#include "VRCashierScreen.h"
#include "VRProduct.h"

class Basket;
class Customer;
class Receipt;

namespace VR	{

	class Cashier	{
	public:
		Cashier();

		void displayMainMenu();

		void getCurrentSubTotal() const;

		void performPurchase(const Basket & aBasket);
		void abort();

	protected:
		typedef enum {STORE = 0, HOME} DELIVERY_TYPE;
		typedef enum {CREDIT_CARD = 0, CASH} PAYMENT_TYPE;


		std::vector < Receipt *> m_lstReceipts;
	};
}
#endif //VR_CASHIER_H