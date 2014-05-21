#include <QApplication>

#include <QDataStream>

#include <iostream>

#include "VRClient.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);

	QByteArray block;

	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out << quint64(0) << "Test: client request data";

	Client client;
	client.sendRequest(block);

	return app.exec();
}