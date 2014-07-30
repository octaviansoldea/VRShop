#include <QApplication>

#include "VRMainWindow_GUI.h"

using namespace VR;

int main( int argc, char** argv )	{
	QApplication application( argc, argv );
	
	MainWindow_GUI mainWindow_GUI;
	mainWindow_GUI.show();

	return( application.exec() );
}
