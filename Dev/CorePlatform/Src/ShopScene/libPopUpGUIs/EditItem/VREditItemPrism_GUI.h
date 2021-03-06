#ifndef VR_EDIT_ITEM_PRISM_GUI_H
#define VR_EDIT_ITEM_PRISM_GUI_H

#include "VREditItem_GUIBase.h"

#include "ui_VREditItemPrism_GUI.h"

namespace VR	{
	
	class EditItemPrism_GUI : public EditItem_GUIBase, public Ui::EditPrism	{
		Q_OBJECT
	public:
		EditItemPrism_GUI(AbstractObject * apAbstractObject);

		virtual void slotSetColor();

	public slots:
		void slotSetResolution();

	protected:
		virtual void previewTexture(QString & aqstrFileName);

	public:
		virtual std::vector<float> getColor() const;
		virtual std::string getTexture();

	};
}
#endif //VR_EDIT_ITEM_PRISM_GUI_H