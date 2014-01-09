#ifndef VR_CASHIER_H
#define VR_CASHIER_H

#include <vector>

#include "VRCashierScreen.h"
#include "VRProduct.h"

class Customer;
class Purchase;
class Receipt;

namespace VR	{

	class Cashier	{
	public:
		Cashier();

		void displayMainMenu();

		void listProductsInBasket(const Customer * apCustomer);

		void addProductToBasket(const Product * apProduct);
		void removeProductFromBasket(const Product * apProduct);

		bool authenticateUser(const Customer * apCustomer);

		void getCurrentSubTotal() const;

		void performPurchase(const Purchase * apPurchase) {};
		void abort();

	protected:
		typedef enum {STORE = 0, HOME} DELIVERY_TYPE;
		typedef enum {CREDIT_CARD = 0, CASH} PAYMENT_TYPE;


		std::vector < Receipt *> m_lstReceipts;
	};
}
#endif //VR_CASHIER_H