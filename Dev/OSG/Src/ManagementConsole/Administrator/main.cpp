#include <QApplication>

#include <iostream>
#include <string>

#include "VRAdministrator.h"

using namespace std;
using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	Administrator admin;
	bool bRes = admin.runServer();

	if (!bRes)	{	//Server not running
		return(0);
	}

	int nRes = app.exec();
	return nRes;
}
