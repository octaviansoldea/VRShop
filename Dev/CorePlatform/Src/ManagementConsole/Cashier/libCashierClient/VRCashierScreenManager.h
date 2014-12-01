#ifndef VR_CASHIER_SCREEN_MANAGER_H
#define VR_CASHIER_SCREEN_MANAGER_H

#include <QObject>

namespace VR	{
	class BasketClient;
	class Cashier_GUI;
	class CashierInterface;

	class CashierScreenManager : public QObject	{
		Q_OBJECT
	public:
		CashierScreenManager(QObject * apParent=0);
		CashierScreenManager(BasketClient * apBasket, QObject * apParent=0);
		virtual ~CashierScreenManager();

		void init(BasketClient * apBasket);
		int getCurrentSelection();

	private slots:
		void slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void slotRemoveFromBasket();
		void slotMoreInfoClicked();
		void slotProceedAndPayClicked();
		void slotStartButtonClicked();
		bool close();

	private:
		void slotConnections();
		void addRow();

		Cashier_GUI * m_pCashier_GUI;
		BasketClient * m_pBasket;

		CashierInterface * m_pCashierInterface;

	public:
		void moreProductInfoReceived(std::string & astrProductData);
	};
}
#endif //VR_CASHIER_SCREEN_MANAGER_H