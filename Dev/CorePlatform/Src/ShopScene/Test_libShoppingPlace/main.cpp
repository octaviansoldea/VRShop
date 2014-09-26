#include <windows.h>

#include <fstream>
#include <iostream>

#include <QApplication>
#include <QMessageBox>
#include <QHostAddress>

#include <QString>

#include <QTimer>

#include "BasicStringDefinitions.h"

#include "VRClient.h"


#include "VRShoppingPlace_GUI.h"

using namespace VR;
using namespace std;


int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	//Client client;
	//client.slotNewUserRequest();

	string strClientName = 
		tostr(time(NULL));
		//client.getTcpSocket().peerAddress().toString().toStdString();

	string strDBFileName = 
//		"C:/Projekti/VRShopDocs/Scenes/sceneShop_NoProducts.db"
		"../../../Databases/ShopDemo.db"
//"C:/Projekti/VRShop/SampleScenes/Finalna_OK.db"	//This one is working
		;

	ShoppingPlace_GUI widget(strDBFileName,string(strClientName));


	if (argc > 1)	{
		widget.setAttribute(Qt::WA_NativeWindow);

		QString qstrArg = app.arguments().at(1);

		bool bOk;

		SetParent((HWND)widget.winId(), (HWND)qstrArg.toULong(&bOk));
	}

	widget.show();
	
	return app.exec();
}