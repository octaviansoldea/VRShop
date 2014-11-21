#ifndef VR_REMOVE_PRODUCT_GUI_H
#define VR_REMOVE_PRODUCT_GUI_H

#include <QDialog>

#include "ui_VRRemoveProduct_GUI.h"

namespace VR	{
	class RemoveProduct_GUI : public QDialog, public Ui::RemoveProduct {
		Q_OBJECT
	public:
		RemoveProduct_GUI();
	};
}
#endif //VR_REMOVE_PRODUCT_GUI_H