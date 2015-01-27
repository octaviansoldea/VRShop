#include <windows.h>
#include <QApplication>
#include <QString>
#include <string>
#include <iostream>

#include "BasicStringDefinitions.h"

#include "VRAppData.h"

#include "VRClient.h"

#include "VRShoppingPlace_GUI.h"

using namespace VR;
using namespace std;


int main(int argc, char *argv[])	{
	if (argc != 3)	{
		cerr << argv[0] << "Too few arguments set. Set nSelection to 0 or 1" << endl;
		exit(-1);
	}

	QApplication app(argc, argv);

	Client client;
	const string strIP = "127.0.0.1";
	const int nPort = 10000;

	client.tryToConnect(strIP, nPort);

	int nUserID = client.getUserID();

	if (nUserID == -1)	{
		return 0;
	}
	
	string strClientName = tostr(nUserID);
	string strDBFileName = AppData::getFPathDatabases() + "ShopDemo.db";

	ShoppingPlace_GUI widget(&client, strDBFileName,string(strClientName));

	int nSelection=stoi(argv[2]);
	switch(nSelection)	{
	case 1:
		{
			widget.setAttribute(Qt::WA_NativeWindow);
			QString qstrArg = argv[1];

			bool bOk;
			SetParent((HWND)widget.winId(), (HWND)qstrArg.toULong(&bOk));
		}
	default:
		break;
	}

	widget.show();

	int nRes = app.exec();

	return nRes;
}