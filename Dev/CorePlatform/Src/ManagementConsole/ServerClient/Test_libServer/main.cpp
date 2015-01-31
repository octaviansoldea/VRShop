#include <QApplication>

#include <QPushButton>
#include <QTimer>

#include "VRDatabaseNetworkManager.h"
#include "VRStaticInitOrderServer.h"

#include <iostream>
#include "VRAppDataServer.h"

#include "VRServer.h"
#include "VRServer_GUI.h"

using namespace std;
using namespace VR;

/*
	ARGUMENTS:
		- IP
		- port
*/

static StaticInitOrderServer staticInitOrderServer;

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

	//Create necessary databases if missing
	DatabaseNetworkManager::checkDatabaseTables();

	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, &DatabaseNetworkManager::checkAvatarActivity);
	timer.start(1000);

	QObject::connect(server_GUI.m_pPushButtonPrint, &QPushButton::clicked, &DatabaseNetworkManager::printOrderList);

	int nRes = app.exec();
	return nRes;
}