#include <QApplication>

#include "VRAvatarManagerServer.h"
#include "VRUserAccountManager.h"

#include <iostream>

#include "VRServer.h"
#include "VRServer_GUI.h"


using namespace std;
using namespace VR;


int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	bool bRes=true;

	Server server((QObject*)(0),10);
	bRes = server.init();

	if (!bRes)	{
		return (0);
	}

	Server_GUI server_GUI(&server);
	server_GUI.show();

	//Creates necessary databases if missing
	UserAccountManager::createUserAccountDB();
	AvatarManagerServer::createAvatarDB();

	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, &AvatarManagerServer::checkAvatarActivity);
	timer.start(1000);

	int nRes = app.exec();

	return nRes;
}