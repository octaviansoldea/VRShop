#include <QApplication>
#include <QMessageBox>

#include "VRShopEditorDlg.h"

using namespace VR;

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	VRShopEditorDlg widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}