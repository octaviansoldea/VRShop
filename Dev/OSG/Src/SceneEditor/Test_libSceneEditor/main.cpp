#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder.h"

using namespace VR;

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	ShopBuilder widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}