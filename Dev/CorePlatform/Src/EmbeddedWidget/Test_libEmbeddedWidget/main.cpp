#include <QApplication>

#include <QSize>
#include <QPoint>
#include <QProcess>

#include <QTimer>

#include <windows.h>

#include <fstream>
#include <iostream>

#include "BasicStringDefinitions.h"
#include "VRAppData.h"

#include "VREmbeddedWidgetStatics.h"

#include "VRClient.h"

#include "VREmbeddedWidget_GUI.h"

using namespace std;
using namespace VR;

//===========================================================

/*
	ARGUMENTS:
		- .EXE
		- PARENT HWND
		- nSELECTION
		- PIPE NAME

		- IP
		- PORT
		- PARENT HWND
		- PIPE NAME
*/

static EmbeddedWidgetStatics staticInitializerOrderer;


int main(int argc, char * argv[])	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	out << "VRSHOP" << endl;
	for (int nI=0;nI<argc;nI++)	{
		out << "Arg " << nI << ": " << argv[nI] << "; ";
	}
	out << endl;
	out.close();

	if((argc != 3) && (argc != 5)) {
		cerr << "Error: incorrect number of arguments: they were" << argc<< endl;
		cerr << "Usage: ";
		cerr << " IP port [parentHWD pipeName]"  << endl;
		exit(-1);
	}

	QApplication app(argc, argv);

	Client client;

	const string strIP = string(argv[1]);
	cerr << "Understood ip = " << strIP << endl;
	const unsigned int nPort = atoi(argv[2]);
	cerr << "Understood nPort = " << nPort << endl;

	client.tryToConnect(strIP, nPort);
	int nUserID = client.getUserID();

	if (nUserID < 1)	{
		return 0;
	}

	client.setObjectName(tostr(nUserID).c_str());
	string strPipeName;
	if(argc == 5) {
		strPipeName = argv[4];
	}

	EmbeddedWidget_GUI embeddedWidget(&client,strPipeName);
	QTimer timer;

	//nSelection=1: run as a web plugin; default: run as a windows APPi
	switch(argc)	{
	case 5:
		{
			embeddedWidget.setAttribute(Qt::WA_NativeWindow);
//			embeddedWidget.setWindowFlags(Qt::FramelessWindowHint);

			//STRING TO HWND
			long lNum;
			char* pE;
			lNum = strtol(argv[3], &pE, 16);
			HWND hW = (HWND)lNum;
			//END

			SetParent((HWND)embeddedWidget.winId(), hW);

			QSize  size = embeddedWidget.size();
			SetWindowPos((HWND)embeddedWidget.winId(),HWND_TOP,0,0,size.width(),size.height(),SWP_FRAMECHANGED);  // WINDOWS CALL

			embeddedWidget.show();

			//Create pipe
			QObject::connect(&timer, &QTimer::timeout, &embeddedWidget, &EmbeddedWidget_GUI::checkIfParentExists);
			timer.start(1000);

			break;
		}
	default:
		{
			embeddedWidget.show();
			break;
		}
	}

	//This signal is emitted when the Application is about to quit; last chance to make the cleaning 
	//(network operations inhibited)
	QObject::connect(&app, &QApplication::aboutToQuit, &embeddedWidget, &EmbeddedWidget_GUI::slotAboutToQuit);

	int nRes = app.exec();

	return nRes;
}
