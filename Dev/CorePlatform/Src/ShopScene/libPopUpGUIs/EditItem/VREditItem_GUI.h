#ifndef VR_EDIT_ITEM_GUI_H
#define VR_EDIT_ITEM_GUI_H

#include "VREditItem_GUIBase.h"

#include "ui_VREditItem_GUI.h"

namespace VR	{
	
	class EditItem_GUI : public EditItem_GUIBase, public Ui::EditItem	{
	public:
		EditItem_GUI(AbstractObject * apAbstractObject);

		virtual void slotSetColor();

	protected:
		virtual void previewTexture(QString & aqstrFileName);

	};
}
#endif //VR_EDIT_ITEM_GUI_H