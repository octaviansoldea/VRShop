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

	//nSelection=1: run as a web plugin; default: run as a windows APPi
	int nSelection=1;
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
