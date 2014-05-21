#include <QApplication>

#include "VRServer_GUI.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	Server_GUI server;
	server.show();

	return app.exec();
}