#ifndef VR_SHOP_BUILDER_GUI_H
#define VR_SHOP_BUILDER_GUI_H

#include <QMainWindow>
#include "VRShopBuilder.h"
#include "ui_VRShopBuilder_GUI.h"

namespace VR	{
	class ShopBuilder_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShopBuilder_GUI();
		ShopBuilder m_ShopBuilder;
	private:
		void buildConnections();

		QString openDialog(const char * apchDBName);
		QString saveDialog(const char * apchDBName);
	
	public slots:
		void slotOpenDB();
		void slotSaveDB();
	};
}
#endif //VR_SHOP_BUILDER_GUI_H