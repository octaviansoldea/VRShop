#ifndef VR_ADD_PRODUCT_GUI_H
#define VR_ADD_PRODUCT_GUI_H

#include <QDialog>

#include "ui_VRAddProduct_GUI.h"

namespace VR	{
	class AddProduct_GUI : public QDialog, public Ui::AddProduct {
		Q_OBJECT
	public:
		AddProduct_GUI();

	private slots:
		void slotSetActiveWidget();
	};
}
#endif //VR_ADD_PRODUCT_GUI_H