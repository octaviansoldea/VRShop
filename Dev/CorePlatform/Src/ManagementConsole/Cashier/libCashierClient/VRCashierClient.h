#ifndef VR_CASHIER_CLIENT_H
#define VR_CASHIER_CLIENT_H

namespace VR	{
	class Visitor;
	class BasketClient;

	class CashierScreenManager;
	class CashierInterface;

	class CashierManagerClient;
	
	class CashierClient	{
	public:
		CashierClient();
		~CashierClient();

		void init(Visitor * apVisitor);

		void requestToPay(const std::string & astrUserID, BasketClient * apBasket);
		void confirmTransaction();

	private:
		CashierScreenManager * m_pCashierScreenManager;
		CashierInterface * m_pCashierInterface;

		CashierManagerClient * m_pCashierManagerClient;
		Visitor * m_pVisitor;
	};
}
#endif //VR_CASHIER_CLIENT_H