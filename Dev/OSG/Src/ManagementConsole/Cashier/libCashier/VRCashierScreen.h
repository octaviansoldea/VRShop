#ifndef VR_CASHIER_SCREEN_H
#define VR_CASHIER_SCREEN_H

#include <QObject>

namespace VR	{
	class CashierWelcome_GUI;
	class CashierProceed_GUI;
	class Basket;

	class CashierScreen	: public QObject	{
		Q_OBJECT
	public:
		CashierScreen(Basket * apBasket);
		~CashierScreen();

		void setCashierScreen(bool abIsWelcome);

	private slots:
		void slotShowProceed();
		void slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void slotRemoveFromBasket();

	private:
		CashierWelcome_GUI * m_pCashierWelcome_GUI;
		CashierProceed_GUI * m_pCashierProceed_GUI;

		Basket * m_pBasket;
	};
}
#endif //VR_CASHIER_SCREEN_H