#include <QMessageBox>

#include <iostream>
#include <string>

#include "VRAgentManager.h"

#include "VRClientConnection.h"
#include "VRServer.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Server::Server(QObject *parent,int anConnMax) : QTcpServer(parent), m_nMaxNoOfConnections(anConnMax)	{
	m_nNoOfConnections = 0;

	m_pAgentManager = new AgentManager;
}

//----------------------------------------------------------------------

Server::~Server()	{
	delete m_pAgentManager;
}

//=====================================================================

void Server::incomingConnection(qintptr handle)	{
	//Set an upper limit of users in the shop
	if (m_nNoOfConnections >= m_nMaxNoOfConnections)	{
		return;
	}

	ClientConnection *pSocket = new ClientConnection(this);
	pSocket->setSocketDescriptor(handle);	//The object is deleted automatically when the connection is terminated.

	connect(pSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));

	if (pSocket->state() == QAbstractSocket::ConnectedState)
		m_nNoOfConnections++;

	cout << "Server: accepted incoming connection @ " << pSocket->localAddress().toString().toStdString() 
		<< ": SocketNo: " << handle 
		<< ": Connections: " << getNoOfConnections() << endl;
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
	m_nNoOfConnections--;
}

//----------------------------------------------------------------------

void Server::setMaxNoOfConnections(int anConnMax)	{
	m_nMaxNoOfConnections = anConnMax;
}

//----------------------------------------------------------------------

int Server::getNoOfConnections() const	{
	return m_nNoOfConnections;
}