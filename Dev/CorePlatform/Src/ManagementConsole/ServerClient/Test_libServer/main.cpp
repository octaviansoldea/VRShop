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

	Server server;
	bRes = server.init();

	if (!bRes)	{
		return (0);
	}

	Server_GUI server_GUI(&server);
	server_GUI.show();

	//Creates necessary databases if missing
	UserAccountManager::createUserAccountDB();
	AvatarManagerServer::createAvatarDB();

	return app.exec();
}