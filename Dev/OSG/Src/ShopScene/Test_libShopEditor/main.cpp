#include <QApplication>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"

using namespace VR;

class A {
	virtual void foo() {};
};


class B {
	virtual void foo() {};
};

class D : public B {
	virtual void foo() {};
};


#include <exception>

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	ShopBuilder_GUI widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}