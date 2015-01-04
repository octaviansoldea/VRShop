#include <windows.h>
#include <QApplication>
#include <QString>

#include "BasicStringDefinitions.h"

#include "VRAppData.h"

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
	}
	
	string strClientName = tostr(nUserID);
	string strDBFileName = AppData::get_FPath_Databases() + "ShopDemo.db";

		

	ShoppingPlace_GUI widget(&client, strDBFileName,string(strClientName));

	int nSelection=0;
	switch(nSelection)	{
	case 1:
		{
			widget.setAttribute(Qt::WA_NativeWindow);
			QString qstrArg = app.arguments().at(1);
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