#ifndef VR_PRODUCT_SETTINGS_GUI_H
#define VR_PRODUCT_SETTINGS_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRProductSettings_GUI.h"

namespace VR	{
	class ProductSettings_GUI : public QDialog, public Ui::ProductSettings {
		Q_OBJECT
	public:
		ProductSettings_GUI();
	};
}
#endif //VR_PRODUCT_SETTINGS_GUI_H