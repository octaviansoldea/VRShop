#include <windows.h>
#include <fstream>

#include "BasicStringDefinitions.h"

#include <QApplication>
#include <QString>
#include <QTimer>
#include <QObject>

#include "VRMainWindow_GUI.h"

using namespace VR;
using namespace std;

int main_GIT( int argc, char * argv[] )	{

	if (argc < 2)
		return -1;

	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);

	QApplication application(argc, argv);

	string strPipeName = 
		//"\\\\.\\pipe\\mynamedpipe";
		argv[1];

	out << "test_lib Model strPipeName: " << strPipeName << endl;

	out.close();

	MainWindow_GUI mainWindow_GUI(strPipeName);
	SetParent((HWND)mainWindow_GUI.winId(), NULL);
	mainWindow_GUI.show();

	//Create pipe
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, &mainWindow_GUI, &MainWindow_GUI::checkIfOK);
	timer.start(1000);

	int nRes = application.exec();

	return(nRes);
}

int main(int argc, char * argv[])	{
	main_GIT(argc, argv);
}