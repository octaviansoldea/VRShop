#ifndef VR_MAIN_WINDOW_GUI_H
#define VR_MAIN_WINDOW_GUI_H

#include <QMainWindow>
#include <QMdiArea>

#include "VRPipeClient.h"

#include "ui_VRMainWindow_GUI.h"

namespace VR {
	class MainWindow_GUI : public QMainWindow, public Ui::MainWindow
	{
		Q_OBJECT

	public:
		MainWindow_GUI(std::string & astrPipeName);
		~MainWindow_GUI();

		void checkIfOK();

	private:
		PipeClient m_pC;
	};
}

#endif //VR_MAIN_WINDOW_GUI_H
