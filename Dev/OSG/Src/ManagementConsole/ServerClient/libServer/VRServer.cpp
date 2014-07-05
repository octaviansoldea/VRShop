#include <QMessageBox>

#include <iostream>
#include <string>

#include "VRClientConnection.h"
#include "VRServer.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Server::Server(QObject *parent) : QTcpServer(parent)	{
}

//----------------------------------------------------------------------

Server::~Server()	{
}

//=====================================================================

void Server::incomingConnection(qintptr handle)	{
	ClientConnection *pSocket = new ClientConnection(this);
	pSocket->setSocketDescriptor(handle);	//The object is deleted automatically when the connection is terminated.

	connect(pSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));

	std::cout << "Server: accepted incoming connection @ " << pSocket->localAddress().toString().toStdString() << ": SocketNo: " << handle << std::endl;
}

//----------------------------------------------------------------------

bool Server::init()	{
	bool bRes=true;

	string & strServerIP = QHostAddress(QHostAddress::LocalHost).toString().toStdString();
	int nPort = 20000;
	
	if (!listen(QHostAddress(strServerIP.c_str()), nPort)) {	//server listens for incoming conenctions
		QMessageBox msg;
		msg.setText(QString("Unable to start server.\n\n%1").arg(errorString()));
		msg.setStandardButtons(QMessageBox::Ok);
		msg.setWindowTitle("Warning window");
		int nRes = msg.exec();

		close();
		return(false);
	}
	return bRes;
}

//----------------------------------------------------------------------

void Server::slotDisconnected()	{
	std::cout << "server: disconnected." << std::endl;
}

