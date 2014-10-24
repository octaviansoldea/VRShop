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
	class CashierScreenManager;
	class ProductShopClient;

	class ShoppingPlace_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShoppingPlace_GUI(std::string & astrFileName, std::string & astrAvatarName);
		~ShoppingPlace_GUI();

	private:
		ShoppingPlace * m_pShoppingPlace;
		ProductInterface * m_pProductInterface;
		AgentInterface * m_pAgentInterface;
		ProductBasketInterface * m_pProductBasketInterface;
		CameraController * m_pCameraController;

		CashierScreenManager * m_pCashierScreenManager;

		void updateGeometry();
		void signalSlotConnections();

	protected:
		virtual void resizeEvent(QResizeEvent *event);

	private slots:
		void slotProductClicked(const AbstractObject * apAbstractObject);
		void slotCashierClicked();
		void slotAvatarClicked(const std::string & astrAvatarName);

		void slotProcesRequest(int anRequestOperation);

		void slotAdd2Basket();
		void slotRemoveProduct(ProductShopClient * apProduct);
		void slotModifyProductQuantity(ProductShopClient * apProduct, float aflNewQuantity);
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H