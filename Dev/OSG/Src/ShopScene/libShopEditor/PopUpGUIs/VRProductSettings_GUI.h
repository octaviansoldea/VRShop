#ifndef VR_PRODUCT_SETTINGS_GUI_H
#define VR_PRODUCT_SETTINGS_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRProductSettings_GUI.h"

namespace VR	{
	class ProductController;

	class ProductSettings_GUI : public QDialog, public Ui::ProductSettings {
	public:
		ProductSettings_GUI();
		~ProductSettings_GUI();

	public slots:
		void slotSaveProductChanges();

		void slotInsertProduct();
		void slotModifyProduct();
		void slotRemoveProduct();

	private:
		Q_OBJECT

		void buildConnections();

		ProductController * m_pProductController;
	};
}
#endif //VR_PRODUCT_SETTINGS_GUI_H