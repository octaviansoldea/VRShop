#ifndef VR_SHOP_BUILDER_GUI_H
#define VR_SHOP_BUILDER_GUI_H

#include <QMainWindow>

#include "ui_VRShopBuilder_GUI.h"

namespace VR	{
	struct ShopBuilder;
	struct CameraController;
	struct PickAndDragController;

	class ShopBuilder_GUI : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShopBuilder_GUI();
		~ShopBuilder_GUI();

	private:
		void buildConnections();

		ShopBuilder * m_pShopBuilder;

		CameraController * m_pCameraController;
		PickAndDragController * m_pPickAndDragController;

	private slots:
		void slotNewProject();
		void slotOpenDB();
		void slotSaveDB();
		void slotSaveAsDB();
		void slotCloseDB();

		void slotSearchScene();
		void slotItemClicked(const QModelIndex & aItemIndex);

		void slotGridOnOff(bool abIndicator);
		void slotCameraManipulatorOnOff(bool abIndicator);

		void slotRefinedZoom(bool abIndicator);
		void slotPercentageZoom(const QString & astrZoomFactor);

		void slotDefineDragAxis(const QString & astrAxis);

		void slotAddNewItem();

		void slotAboutToQuitCalled();

		void slotAddNewProductClicked();

		void slotRemoveProduct();
		void slotProductMoreSettings();

		void slotProductClicked(const std::string & astrProductName);
		void slotApplyModifyProductClicked();
		void slotComboBoxProductChanged();

		void slotGroupItems();
		void slotSplitItem();
		void slotDuplicateSelection();
		void slotRemoveSelection();
		void slotEditItem();
	};
}
#endif //VR_SHOP_BUILDER_GUI_H