#ifndef VR_SHOPPING_PLACE_GUI_H
#define VR_SHOPPING_PLACE_GUI_H

#include <QMainWindow>

#include <string>

#include "ui_VRShoppingPlace_GUI.h"

namespace VR	{
	struct ShoppingPlace;
	class AbstractObject;
	class Avatar;
	class Grid;
	class ProductInterface;
	class AgentInterface;
	class ProductBasketInterface;
	class ProductManagerClient;
	class Cashier;
	struct CameraController;

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
		ProductManagerClient * m_pProductManagerClient;
		CameraController * m_pCameraController;
		Cashier * m_pCashier;

		void updateGeometry();

	protected:
		virtual void resizeEvent(QResizeEvent *event);

	private slots:
		void slotProductClicked(const AbstractObject * apAbstractObject);
		void slotCashierClicked();
		void slotAvatarClicked(const Avatar * apAvatar);
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H