#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"

using namespace VR;

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	ShopBuilder_GUI widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}