#ifndef VR_CASHIER_CLIENT_H
#define VR_CASHIER_CLIENT_H

#include <QObject>

class QPushButton;

namespace VR	{
	class BasketClient;
	class Cashier_GUI;

	class CashierClient : public QObject	{
		Q_OBJECT
	public:
		CashierClient(QObject * apParent=0);
		CashierClient(BasketClient * apBasket, QObject * apParent=0);
		virtual ~CashierClient();

		void launchCashier();
		void init(BasketClient * apBasket);
		int getCurrentSelection();

		void removeFromBasket();

	private slots:
		void slotChangeImage(int currentRow, int currentColumn, int previousRow, int previousColumn);
		bool close();

	private:
		void slotConnections();
		void addRow();

		Cashier_GUI * m_pCashier_GUI;
		BasketClient * m_pBasket;

	public:
		void moreProductInfoReceived(std::string & astrProductData);

		QPushButton * m_pPushButtonStart;
		QPushButton * m_pPushButtonRemove;
		QPushButton * m_pPushButtonInfo;
		QPushButton * m_pPushButtonProceed;
	};
}
#endif //VR_CASHIER_CLIENT_H