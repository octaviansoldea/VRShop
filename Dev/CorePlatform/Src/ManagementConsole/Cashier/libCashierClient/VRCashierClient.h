#ifndef VR_CASHIER_CLIENT_H
#define VR_CASHIER_CLIENT_H

#include <QObject>

class QPushButton;
class QFrame;
class QTableWidget;
class QLabel;
class QPixmap;
class QDialog;
class QLineEdit;

namespace VR	{
	class BasketClient;
	class Client;
	struct AgentClientParams;

	class CashierClient	{
	public:
		CashierClient(Client * apClient);
		virtual ~CashierClient();

		enum ITEM_NAME	{
			PRODUCT = 0,
			QUANTITY,
			PRICE,
			DISCOUNT,
			AMOUNT
		};

		struct InitCashier	{
			QFrame * m_pFrameWelcome;
			QFrame * m_pFrameContinue;
			BasketClient * m_pBasket;
			QLabel * m_pLabelPrice;
			QLabel * m_pLabelProductImage;
			QTableWidget * m_pTableWidgetProducts;
		};

		AgentManagerClient::AgentClientParams m_Acm;

		void initializeCashier(InitCashier & aInitCashier);
		void removeFromCashier(QTableWidget * apTableWidgetProducts, BasketClient * apBasket, QLabel * apLabelPrice);
		void changeImage(BasketClient * apBasket, QTableWidget * apTableWidgetProducts, QLabel * apLabelProductImage);
		void close(QFrame * apFrameWelcome, QFrame * apFrameContinue, QDialog * apDialog);
		void continueClicked(AgentManagerClient::AgentClientParams * apAcm, QFrame * apFrameRightSidePDetails);
		void moeProductClicked(BasketClient * apBasket, int anProductPosition);

	private:
		void addRow(QTableWidget * apTableWidgetProducts);

		Client * m_pClient;
	};
}
#endif //VR_CASHIER_CLIENT_H