#ifndef VR_SHOP_BUILDER_GUI_H
#define VR_SHOP_BUILDER_GUI_H

#include <QMainWindow>
#include "VRShopBuilder.h"

#include "ui_VRShopBuilder_GUI.h"

class CameraController;
class Grid;

namespace VR	{
	class ShopBuilder_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShopBuilder_GUI();
		~ShopBuilder_GUI();
		ShopBuilder m_ShopBuilder;

	private:
		void buildConnections();

		QString openDialog(const char * apchDBName);
		QString saveDialog(const char * apchDBName);

		CameraController * m_pCameraController;

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

		void slotSetTranslation();
		void slotSetDirectionOfTranslation(const QString & astrText);
		void slotSetTranslateRelativeTo(const QString & astrText);
		void slotSetCenterOfRotation(const QString & astrText);

		void slotSetRotation();
		void slotSetScaling();
		void slotSetShearing();
		void slotSetPosition();

		void slotModifySceneActions();
		void slotModifyProductSettings();
		void slotSetProductSettings(const QString & astrSelectedProduct);
		void slotSetNewPriceQuantity();
		void slotModifyProductButtons();

		void slotAddNewItem(const QString & aqstrItemName);
	};
}
#endif //VR_SHOP_BUILDER_GUI_H