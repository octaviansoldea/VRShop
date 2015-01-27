#ifndef VR_CASHIER_GUI_H
#define VR_CASHIER_GUI_H

#include <QDialog>
#include "ui_VRCashier_GUI.h"

namespace VR	{
	class BasketClient;
	class CashierClient;
	class Client;

	class Cashier_GUI : public QDialog, public Ui::Cashier	{
	public:
		Cashier_GUI(Client * apClient, BasketClient * apBasket, QDialog * apParent = 0);
		~Cashier_GUI();

		void proceedAndPayClicked();
		void removeFromCashierClicked();
		void productInfoClicked();
		int getCurrentSelection();

		void cashierClicked();

	private:
		CashierClient * m_pCashierClient;
		BasketClient * m_pBasket;
		Client * m_pClient;

		void close();

		void slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void continueClicked();

		void startClicked();
	};
}
#endif //VR_CASHIER_GUI_H