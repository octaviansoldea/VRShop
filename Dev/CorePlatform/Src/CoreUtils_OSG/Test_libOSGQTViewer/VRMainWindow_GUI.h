#ifndef VR_MAIN_WINDOW_GUI_H
#define VR_MAIN_WINDOW_GUI_H

#include <QMainWindow>
#include <QMdiArea>

#include "ui_VRMainWindow_GUI.h"

namespace VR {
	class MainWindow_GUI : public QMainWindow, public Ui::MainWindow
	{
		Q_OBJECT

	public:
		MainWindow_GUI();
	};
}

#endif //VR_MAIN_WINDOW_GUI_H
