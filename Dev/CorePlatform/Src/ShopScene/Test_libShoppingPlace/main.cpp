#include <windows.h>

#include <fstream>
#include <iostream>

#include <QApplication>
#include <QMessageBox>
#include <QHostAddress>

#include <QString>

#include "BasicStringDefinitions.h"

#include "VRClient.h"

#include "VRShoppingPlace_GUI.h"

using namespace VR;
using namespace std;


int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	Client client;
	client.tryToConnect();
	int nUserID = client.getUserID();

	if (nUserID == -1)	{
		return 0;

	} else {
		string strClientName = tostr(nUserID);

		string strDBFileName = 
			"../../../Databases/ShopDemo.db"
			;

		ShoppingPlace_GUI widget(&client, strDBFileName,string(strClientName));


		//if (argc > 1)	{
		//	widget.setAttribute(Qt::WA_NativeWindow);

		//	QString qstrArg = app.arguments().at(1);

		//	bool bOk;

		//	SetParent((HWND)widget.winId(), (HWND)qstrArg.toULong(&bOk));
		//}

		widget.show();

		return app.exec();
	}
}