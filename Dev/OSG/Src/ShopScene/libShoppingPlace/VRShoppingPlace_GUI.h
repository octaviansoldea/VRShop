#ifndef VR_SHOPPING_PLACE_GUI_H
#define VR_SHOPPING_PLACE_GUI_H

#include <QMainWindow>

#include "ui_VRShoppingPlace_GUI.h"

namespace VR	{
	struct ShoppingPlace;
	class Grid;
	class ProductInterface;
	class KeyboardMouseManipulatorShopClient;

	class ShoppingPlace_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShoppingPlace_GUI();
		~ShoppingPlace_GUI();

	private:
		ShoppingPlace * m_pShoppingPlace;

		void buildConnections();
		void updateGeometry();

	protected:
		virtual void resizeEvent(QResizeEvent *event);

	private slots:
		void slotSignUp();
		void slotSignIn();
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H