#ifndef VR_SHOPPING_PLACE_GUI_H
#define VR_SHOPPING_PLACE_GUI_H

#include <QMainWindow>
#include "VRShoppingPlace.h"

#include "ui_VRShoppingPlace_GUI.h"

class Grid;

namespace VR	{
	class ShoppingPlace_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShoppingPlace_GUI();
		ShoppingPlace m_ShoppingPlace;

	private:
		void buildConnections();

	private slots:
		void slotSignUp();
		void slotSignIn();
	};
}
#endif //VR_SHOPPING_PLACE_GUI_H