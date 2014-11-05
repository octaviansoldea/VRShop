//#ifdef WIN32 
//
//// Replace STL fstream with OSG fstream 
//#include <osgDB/fstream> 
//#define ifstream osgDB::ifstream 
//#define ofstream osgDB::ofstream 
//
//#else 

//#include <fstream> 
//#define ifstream std::ifstream 
//#define ofstream std::ofstream

#include <windows.h>

#include <string>

#include "Log.h"

#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"

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