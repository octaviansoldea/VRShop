#include <string>
#include <fstream>
#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"
#include "Log.h"

using namespace std;
using namespace VR;


int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	string strFileName = getLogFile();
	ofstream output;
	output.open(strFileName);
	output.close();

	ShopBuilder_GUI widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}