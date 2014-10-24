#include <windows.h>

#include <fstream>
#include <iostream>

#include <QApplication>
#include <QMessageBox>
#include <QHostAddress>

#include <QString>

#include <QTimer>

#include "BasicStringDefinitions.h"

#include <QFile>

#include "VREmbeddedWidget_GUI.h"

using namespace VR;

//===========================================================

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);

	EmbeddedWidget_GUI embeddedWidget;

	int nSelection=0;

	switch(nSelection)	{
	case 1:	{
		embeddedWidget.setAttribute(Qt::WA_NativeWindow);

		QString qstrArg = app.arguments().at(1);
		bool bOk;

		SetParent((HWND)embeddedWidget.winId(), (HWND)qstrArg.toULong(&bOk));

		break;
			}
	default:
		break;
	}

	embeddedWidget.show();

	int nRes = app.exec();
	return nRes;
}
