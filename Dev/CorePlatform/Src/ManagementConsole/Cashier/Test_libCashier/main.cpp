#include <QApplication>
#include "VRBasket.h"

#include "VRCashierScreen.h"
#include <iostream>

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	Basket basket;
	CashierScreen cashier(&basket);
	cashier.setCashierScreen(true);

	return app.exec();
}