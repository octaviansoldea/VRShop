#include <windows.h>
#pragma comment(lib, "user32.lib")

#include <string>
#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"
#include "Log.h"

using namespace std;
using namespace VR;


int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	CreateLogFile();
	
	ShopBuilder_GUI widget;

	if (argc > 1)	{
		widget.setAttribute(Qt::WA_NativeWindow);

		QString qstrArg = app.arguments().at(1);

		bool bOk;

		SetParent((HWND)widget.winId(), (HWND)qstrArg.toULong(&bOk));
	}

	widget.show();
	return app.exec();
}