#include <windows.h>

#include <string>

#include "Log.h"

#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QString>

#include "VRShopBuilder_GUI.h"

using namespace std;
using namespace VR;


int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	CreateLogFile();
	
	ShopBuilder_GUI widget;

	//nSelection = 1: run inside the web plugin
	int nSelection = 0;
	switch (nSelection)	{
	case 1:
		{
			widget.setAttribute(Qt::WA_NativeWindow);

			QString qstrArg = app.arguments().at(1);

			bool bOk;

			SetParent((HWND)widget.winId(), (HWND)qstrArg.toULong(&bOk));

			break;
		}
	default:
		break;
	}

	widget.show();
	
	int nRetVal = app.exec();

	/*
		We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your 
		application's main() function because on some platforms the QCoreApplication::exec() call may not return. 
		For example, on Windows when the user logs off, the system terminates the process after Qt closes all 
		top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop 
		and execute code at the end of the main() function after the QCoreApplication::exec() call.
	*/

	return nRetVal;
}