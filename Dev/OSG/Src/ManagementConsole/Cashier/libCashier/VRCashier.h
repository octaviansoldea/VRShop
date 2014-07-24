#ifndef VR_CASHIER_H
#define VR_CASHIER_H

#include <vector>

#include "VRCashierScreen.h"
#include "VRProduct.h"

class Customer;
class Receipt;

namespace VR	{
	class Basket;

	class Cashier	{
	public:
		Cashier();
		~Cashier();

		void init(Basket * apBasket);

		void displayMainMenu();

		void getCurrentSubTotal() const;

		void performPurchase(Basket * apBasket);
		void abort();

	protected:
		typedef enum {STORE = 0, HOME} DELIVERY_TYPE;
		typedef enum {CREDIT_CARD = 0, CASH} PAYMENT_TYPE;


		std::vector < Receipt *> m_lstReceipts;

	private:
		CashierScreen * m_pCashierScreen;
		Basket * m_pBasket;
	};
}
#endif //VR_CASHIER_H