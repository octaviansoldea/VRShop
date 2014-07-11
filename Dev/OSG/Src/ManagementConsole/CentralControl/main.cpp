#include <QApplication>

#include <iostream>
#include <string>

#include "VRCentralControl.h"

using namespace std;
using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	CentralControl centralControl;

	int nRes = app.exec();
	return nRes;
}
