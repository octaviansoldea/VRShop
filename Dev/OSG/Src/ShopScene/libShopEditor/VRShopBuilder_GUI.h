#ifndef VR_SHOP_BUILDER_GUI_H
#define VR_SHOP_BUILDER_GUI_H

#include <QMainWindow>

#include "ui_VRShopBuilder_GUI.h"

class ShopBuilder;
class CameraController;
class PickAndDragController;
class Grid;

namespace VR	{
	class ShopBuilder_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShopBuilder_GUI();
		~ShopBuilder_GUI();

	private:
		void buildConnections();

		QString openDialog(const char * apchDBName);
		QString saveDialog(const char * apchDBName);

		ShopBuilder * m_pShopBuilder;

		CameraController * m_pCameraController;
		PickAndDragController * m_pPickAndDragController;

	public slots:
		void slotNewProject();
		void slotOpenDB();
		void slotSaveDB();
		void slotSaveAsDB();
		void slotCloseDB();

		void slotGridOnOff(bool abIndicator);
		void slotCameraManipulatorOnOff(bool abIndicator);

		void slotRefinedZoom(bool abIndicator);
		void slotPercentageZoom(const QString & astrZoomFactor);

		void slotDefineDragAxis(const QString & astrAxis);

		void slotModifySceneActions();
		void slotModifyProductSettings();
		void slotSetProductSettings(const QString & astrSelectedProduct);
		void slotSetNewPriceQuantity();
		void slotModifyProductButtons();

		void slotAddNewItem(const QString & aqstrItemName);
	};
}
#endif //VR_SHOP_BUILDER_GUI_H