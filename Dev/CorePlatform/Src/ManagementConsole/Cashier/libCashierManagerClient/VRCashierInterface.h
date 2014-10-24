#ifndef VR_CASHIER_INTERFACE_H
#define VR_CASHIER_INTERFACE_H

#include <list>
#include <string>

namespace VR	{
	class BasketClient;
	class CashierManagerClient;

	class CashierInterface	{
	public:
		CashierInterface();
		~CashierInterface();

		void requestToPay(const std::string & astrUserID, const BasketClient * apBasket);
		void confirmTransaction();

		void proceedPayClicked(std::list<std::pair<std::string,float>> & alstBasketContent);
		void moreInfoClicked(const int & anProductID);

	private:
		CashierManagerClient * m_pCashierManagerClient;
	};
}
#endif //VR_CASHIER_INTERFACE_H