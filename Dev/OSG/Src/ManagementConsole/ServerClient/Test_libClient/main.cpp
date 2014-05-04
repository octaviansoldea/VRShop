#include <QApplication>

#include <iostream>

#include "VRClient.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);
	std::string strIPAddress = "localhost"//"192.168.64.100"
		;
		//argv[1];

		std::cout << std::endl << "strIPAddress = " << strIPAddress << std::endl;

	int nPort = 20000;
	Client client(strIPAddress, nPort);

	return app.exec();
}