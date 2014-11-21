#ifndef VR_REMOVE_SELECTION_GUI_H
#define VR_REMOVE_SELECTION_GUI_H

#include <QDialog>

#include "ui_VRRemoveSelection_GUI.h"

namespace VR	{
	class RemoveSelection_GUI : public QDialog, public Ui::RemoveSelection	{
//		Q_OBJECT
	public:
		RemoveSelection_GUI();
	};
}
#endif //VR_REMOVE_SELECTION_GUI_H