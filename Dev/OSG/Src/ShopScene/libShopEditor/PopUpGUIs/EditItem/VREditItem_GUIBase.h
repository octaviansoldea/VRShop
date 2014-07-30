#ifndef VR_EDIT_ITEM_GUI_BASE_H
#define VR_EDIT_ITEM_GUI_BASE_H

#include <QDialog>
#include "VRAbstractObject.h"

namespace VR	{
	class EditItem_GUIBase : public QDialog	{
		Q_OBJECT
	public:
		EditItem_GUIBase(AbstractObject * apAbstractObject);
		virtual ~EditItem_GUIBase() = 0;

		static EditItem_GUIBase * createInstance(AbstractObject * apAbstractObject);
		osg::ref_ptr<AbstractObject> getAbstractObject();

	public slots:
		virtual void slotBrowseDirectory();
		virtual void slotInsertImage();
		virtual void slotSetColor() = 0;
		virtual void accept();

	protected:
		virtual void previewTexture(QString & aqstrFileName) = 0;

		osg::ref_ptr<AbstractObject> m_pAbstractObject;
	};
}
#endif //VR_EDIT_ITEM_GUI_BASE_H