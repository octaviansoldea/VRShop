#include <QApplication>
#include <QMessageBox>

#include "VRShoppingPlace_GUI.h"

using namespace VR;

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	ShoppingPlace_GUI widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}