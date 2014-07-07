#ifndef VR_INSERT_NEW_ITEM_GUI_H
#define VR_INSERT_NEW_ITEM_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRInsertNewItem_GUI.h"

namespace VR	{
	class InsertNewItem_GUI : public QDialog, public Ui::InsertNewItem {
		Q_OBJECT
	public:
		InsertNewItem_GUI();

	public slots:
		void slotDisplayWidgetItems(QListWidgetItem * item);
		void slotInsertNewItem();
		void slotInsertfromFile();

	signals:
		void signalNewItemRequested(const QString & astrItem);
	};
}
#endif //VR_SELECT_ITEM_GUI_H