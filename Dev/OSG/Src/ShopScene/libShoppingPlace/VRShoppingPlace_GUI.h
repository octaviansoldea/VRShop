#ifndef VR_SHOPPING_PLACE_GUI_H
#define VR_SHOPPING_PLACE_GUI_H

#include <QMainWindow>

#include "ui_VRShoppingPlace_GUI.h"

namespace VR	{
	struct ShoppingPlace;
	class Grid;
	class ProductInterface;
	class AgentInterface;
	class ProductBasketInterface;
	class KeyboardMouseManipulatorShopClient;
	class PickAndDragHandlerShopClient;
	class CameraController;

	class ShoppingPlace_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShoppingPlace_GUI();
		~ShoppingPlace_GUI();

	private:
		ShoppingPlace * m_pShoppingPlace;
		ProductInterface * m_pProductInterface;
		AgentInterface * m_pAgentInterface;
		ProductBasketInterface * m_pProductBasketInterface;
		CameraController * m_pCameraController;

		PickAndDragHandlerShopClient * m_pPickAndDragHandlerShopClient;

		void buildConnections();
		void updateGeometry();

	protected:
		virtual void resizeEvent(QResizeEvent *event);

	private slots:
		void slotProductClicked();
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H