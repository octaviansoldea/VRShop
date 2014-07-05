#ifndef VR_NEW_PROJECT_GUI_H
#define VR_NEW_PROJECT_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRNewProject_GUI.h"

namespace VR	{
	class NewProject_GUI : public QDialog, public Ui::NewProject {
		Q_OBJECT
	public:
		NewProject_GUI();

	public slots:
		void slotBrowseDirectory();
		void slotApplyChanges();
	};
}
#endif //VR_NEW_PROJECT_GUI_H