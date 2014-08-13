#include <QApplication>
#include <QMessageBox>
#include <QHostAddress>

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
//		"../../../Databases/Shop.db";
		"C:/Matej/BookStore.db";

	ShoppingPlace_GUI widget(strDBFileName,strClientName);

	widget.show();

	int nRetCode = app.exec();
	return nRetCode;
}