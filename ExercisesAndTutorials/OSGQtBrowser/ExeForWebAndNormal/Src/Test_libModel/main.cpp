#include <QApplication>
#include <QString>

#include "VRMainWindow_GUI.h"

using namespace VR;

int main_GIT( int argc, char** argv )	{
	QApplication application( argc, argv );
	
	MainWindow_GUI mainWindow_GUI;
	mainWindow_GUI.show();
	

	return( application.exec() );
}

#include <QWidget>

#include <windows.h>

#pragma comment(lib, "user32.lib")

int main_Plugin(int argc, char *argv[])	{
	QApplication application(argc, argv);

	MainWindow_GUI mainWindow_GUI;

	mainWindow_GUI.setAttribute(Qt::WA_NativeWindow);

	QString qstrArg = application.arguments().at(1 );

	bool bOk;

	SetParent((HWND)mainWindow_GUI.winId(), (HWND)qstrArg.toULong(&bOk));

	mainWindow_GUI.show();

	return application.exec();
}

int main(int argc, char * argv[])	{
	main_Plugin(argc, argv);
//	main_GIT(argc, argv);
}