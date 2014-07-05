#ifndef VR_SAVE_AS_GUI_H
#define VR_SAVE_AS_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRSaveAs_GUI.h"

namespace VR	{
	class SaveAs_GUI : public QDialog, public Ui::SaveAs	{
		Q_OBJECT
	public:
		SaveAs_GUI();

	private:
		QString saveAsDialog();

	public slots:
		void slotBrowseDirectory();
		void slotApplyChanges();
	};
}
#endif //VR_NEW_PROJECT_GUI_H