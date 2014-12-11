#ifndef VR_SHOPPING_PLACE_GUI_H
#define VR_SHOPPING_PLACE_GUI_H

#include <QMainWindow>

#include <string>

#include "ui_VRShoppingPlace_GUI.h"

namespace VR	{
	struct ShoppingPlace;
	class AbstractObject;
	class ProductInterface;
	class AgentInterface;
	class ProductBasketInterface;
	struct CameraController;
	class ProductShopClient;
	class CashierClient;

	class Client;

	class ShoppingPlace_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShoppingPlace_GUI(Client * apClient, std::string & astrFileName, std::string & astrAvatarName);
		~ShoppingPlace_GUI();

	private:
		ShoppingPlace * m_pShoppingPlace;
		ProductInterface * m_pProductInterface;
		AgentInterface * m_pAgentInterface;
		ProductBasketInterface * m_pProductBasketInterface;
		CameraController * m_pCameraController;

		Client * m_pClient;

		void updateGeometry();
		void signalSlotConnections();

	protected:
		virtual void resizeEvent(QResizeEvent *event);

	private slots:
		void slotProductClicked(const AbstractObject * apAbstractObject);
		void slotAvatarClicked(const std::string & astrAvatarName);

		void slotAdd2Basket();
		void slotRemoveProduct(ProductShopClient * apProduct);
		void slotModifyProductQuantity(ProductShopClient * apProduct, float aflNewQuantity);

		void slotCashierClicked();
		void slotStartCashierClicked();
		void slotRemoveFromCashierClicked();
		void slotRemoveProductConfirmed();
		void slotProductInfoClicked();
		void slotProceedAndPayClicked();

		void slotClientReceiveData();

	private:
		//Cashier
		CashierClient * m_pCashierClient;
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H