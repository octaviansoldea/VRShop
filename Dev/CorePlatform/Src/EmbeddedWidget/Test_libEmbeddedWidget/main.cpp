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

	if(argc < 2) {
		cerr << argv[0] << " selectArgument(0 or 1)"  << endl;
		exit(-1);
	}

	QApplication app(argc, argv);

	Client client;

	const string strIP = 
		//"62.219.47.47";
		"127.0.0.1";
	const unsigned int nPort = 
		//5900;
		10000;

	client.tryToConnect(strIP, nPort);
	int nUserID = client.getUserID();

	if (nUserID == -1)	{
		return 0;
	}

	client.setObjectName(tostr(nUserID).c_str());
	string strPipeName = argv[3];

	EmbeddedWidget_GUI embeddedWidget(&client,strPipeName);
	QTimer timer;

	//nSelection=1: run as a web plugin; default: run as a windows APPi
	int nSelection=stoi(argv[2]);
	switch(nSelection)	{
	case 1:
		{
			embeddedWidget.setAttribute(Qt::WA_NativeWindow);
//			embeddedWidget.setWindowFlags(Qt::FramelessWindowHint);

			//STRING TO HWND
			long lNum;
			char* pE;
			lNum = strtol(argv[1], &pE, 16);
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
