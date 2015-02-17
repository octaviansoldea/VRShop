#ifndef VR_INSERT_NEW_ITEM_GUI_H
#define VR_INSERT_NEW_ITEM_GUI_H

#include <QDialog>

#include "ui_VRInsertNewItem_GUI.h"

namespace VR	{
	class InsertNewItem_GUI : public QDialog, public Ui::InsertNewItem {
	public:
		InsertNewItem_GUI();

		QString m_qstrFileName;

		void slotDisplayWidgetItems(QListWidgetItem * item);
		void slotInsertfromFile();
	};
}
#endif //VR_SELECT_ITEM_GUI_H