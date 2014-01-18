#ifndef VR_DUPLICATE_ITEM_GUI_H
#define VR_DUPLICATE_ITEM_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRDuplicateItem_GUI.h"

namespace VR	{
	class DuplicateItem_GUI : public QDialog, public Ui::DuplicateItem	{
		Q_OBJECT
	public:
		DuplicateItem_GUI();

	public slots:
		void slotDuplicateItem();
	};
}
#endif //VR_DUPLICATE_ITEM_GUI_H