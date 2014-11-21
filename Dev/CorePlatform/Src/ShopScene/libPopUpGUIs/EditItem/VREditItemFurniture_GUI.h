#ifndef VR_EDIT_ITEM_FURNITURE_GUI_H
#define VR_EDIT_ITEM_FURNITURE_GUI_H

#include "VREditItem_GUIBase.h"

#include "ui_VREditItemFurniture_GUI.h"

namespace VR	{
	
	class EditItemFurniture_GUI : public EditItem_GUIBase, public Ui::EditFurniture	{
	public:
		EditItemFurniture_GUI(AbstractObject * apAbstractObject);

		virtual void slotSetColor();

	protected:
		virtual void previewTexture(QString & aqstrFileName);

	};
}
#endif //VR_EDIT_ITEM_FURNITURE_GUI_H