#ifndef VR_CASHIER_SCREEN_MANAGER_H
#define VR_CASHIER_SCREEN_MANAGER_H

#include <QObject>

namespace VR	{
	class CashierWelcome_GUI;
	class CashierProceed_GUI;
	class BasketClient;

	class CashierScreenManager : public QObject	{
		Q_OBJECT
	public:
		CashierScreenManager(QObject * apParent=0);
		CashierScreenManager(BasketClient * apBasket, QObject * apParent=0);
		~CashierScreenManager();

		void setCashierScreen(bool abIsWelcome);

		void init(BasketClient * apBasket, QObject * apParent);
		int getCurrentSelection();

	private slots:
		bool close();
		void slotShowProceed();
		void slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void slotRemoveFromBasket();
		void slotMoreInfoClicked();
		void slotProceedAndPayClicked();

	private:
		void addRow();

		CashierWelcome_GUI * m_pCashierWelcome_GUI;
		CashierProceed_GUI * m_pCashierProceed_GUI;

		BasketClient * m_pBasket;

	signals:
		void signalCashierOperation(int anRequestOperation);
	};
}
#endif //VR_CASHIER_SCREEN_MANAGER_H