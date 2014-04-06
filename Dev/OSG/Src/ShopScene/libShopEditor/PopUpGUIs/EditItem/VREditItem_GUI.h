#ifndef VR_EDIT_ITEM_GUI_H
#define VR_EDIT_ITEM_GUI_H

#include <QDialog>

#include <osg/Node>
#include "VRAbstractObject.h"

#include "ui_VREditItem_GUI.h"

namespace VR	{
	
	class EditItem_GUI : public QDialog, public Ui::EditItem	{
		Q_OBJECT
	public:
		//EditItem_GUI();
		EditItem_GUI(AbstractObject * apAbstractObject);

	public slots:
		void slotApplyEditItem();
		void slotInsertImage();

	private:

		AbstractObject * m_pAbstractObject;
	};
}
#endif //VR_EDIT_ITEM_GUI_H