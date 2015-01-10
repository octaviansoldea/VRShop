#include <windows.h>

#include <fstream>
#include <iostream>
#include "VRAppData.h"

#include <QApplication>
#include <QMessageBox>
#include <QHostAddress>

#include <QString>
#include <QStringList>
#include <QProcess>

#include <QTimer>

#include "BasicStringDefinitions.h"

#include <QFile>

#include "VRClient.h"

#include "VREmbeddedWidget_GUI.h"

using namespace std;
using namespace VR;

//===========================================================

int main(int argc, char * argv[])	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	if(argc != 3) {
		cerr << argv[0] << " selectArgument(0 or 1)"  << endl;
		exit(-1);
	}

	QApplication app(argc, argv);

	Client client;
	client.tryToConnect();
	int nUserID = client.getUserID();

	if (nUserID == -1)	{
		return 0;
	}
	
	EmbeddedWidget_GUI embeddedWidget(&client);

	//nSelection=1: run as a web plugin; default: run as a windows APPi
	int nSelection=stoi(argv[2]);
	switch(nSelection)	{
	case 1:	{
		embeddedWidget.setAttribute(Qt::WA_NativeWindow);

		QString qstrArg = argv[1];
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
