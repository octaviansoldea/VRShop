#include <QApplication>

#include "VRAvatarManagerServer.h"
#include "VRUserAccountManager.h"
#include "VRVisitorManagerServer.h"
#include "VRCashierManagerServer.h"

#include <iostream>

#include "VRServer.h"
#include "VRServer_GUI.h"


using namespace std;
using namespace VR;

/*
	ARGUMENTS:
		- IP
		- port
*/

int main(int argc, char * argv[])	{

	if (argc != 3)	{
		cerr << "Args: " << argc << ". IP address and Port number requested." << endl;
		exit (-1);
	}

	QApplication app(argc,argv);

	bool bRes=true;

	const int nConnectionsMax = 100;

	Server server((QObject*)(0),nConnectionsMax);

	const string strIP = argv[1];
	const unsigned int nPort = stoi(argv[2]);
	bRes = server.init(strIP, nPort);

	if (!bRes)	{
		return (0);
	}

	Server_GUI server_GUI(&server);
	server_GUI.show();

	//Creates necessary databases if missing
	UserAccountManager::createUserAccountDB();
	AvatarManagerServer::createAvatarDB();
	CashierManagerServer::createDB();
	VisitorManagerServer::createDB();


	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, &AvatarManagerServer::checkAvatarActivity);
	timer.start(1000);

	int nRes = app.exec();

	return nRes;
}