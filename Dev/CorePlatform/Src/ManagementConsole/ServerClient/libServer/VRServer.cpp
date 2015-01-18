#include "VRServerClientCommands.h"

#include "VRBasicQtOperations.h"

#include <iostream>
#include <string>

#include "VRClientConnection.h"
#include "VRServer.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Server::Server(QObject *parent,int anConnMax) : QTcpServer(parent), m_nMaxNoOfConnections(anConnMax)	{
	setMaxPendingConnections(1000);	//Default value is 30

	connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

//----------------------------------------------------------------------

Server::~Server()	{
	m_Clients.clear();
	close();
}

//=====================================================================

bool Server::init()	{
	QHostAddress hostServerIP = QHostAddress(QHostAddress::LocalHost);
	int nPort = 20000;

	bool bRes = listen(hostServerIP, nPort);
		
	if (bRes == false) {	//server listens for incoming conenctions
		QString qstrMsg = QString("Unable to start server.\n\n%1").arg(errorString());
		BasicQtOperations::printWarning(qstrMsg);

		close();
	}
	return bRes;
}

//----------------------------------------------------------------------

void Server::incomingConnection(qintptr handle)	{
	ClientConnection *pSocket = new ClientConnection(this);
	pSocket->setSocketDescriptor(handle);	//The object is deleted automatically when the connection is terminated.

	if (!pSocket)	{
		return;
	}

	//Checks if the incomingConnection can be accepted
	if (clientCount() >= m_nMaxNoOfConnections)	{
		/*
			FIRST CHECK A PREFERENCE STATUS OF THE CLIENT
				- prospective clients are always granted an access
				- first time users are also preferenced
		*/

		//If not approved, terminate pSocket
		pSocket = NULL;
		delete pSocket;
		return;
	}

	if (pSocket->state() == QAbstractSocket::ConnectedState)	{
		addConnection(pSocket, handle);
		connect(pSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	}
}

//----------------------------------------------------------------------

void Server::addConnection(ClientConnection* apDevice, quint64 anClientID)	{
	m_Clients.insert(anClientID, apDevice);

	QTcpSocket * pSocket = (QTcpSocket *)apDevice;

	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	stream.setVersion(QDataStream::Qt_4_8);

	string strSocket = pSocket->localAddress().toString().toStdString();

	cout << "Server: accepted incoming connection @ " << strSocket
		<< ": SocketNo: " << anClientID 
		<< ": Connections: " << clientCount() << endl;

	stream << quint64(0) << quint16(anClientID);
	stream.device()->seek(0);
	stream << (quint64)(data.size() - sizeof(quint64));
	pSocket->write(data);
}

//----------------------------------------------------------------------

void Server::removeConnection(ClientConnection* apDevice, quint64 anClientID)	{
	if (apDevice)	{
		QTcpSocket * pSocket = qobject_cast<QTcpSocket*>(apDevice);
		if (pSocket)
			pSocket->disconnectFromHost();

		apDevice->close();
		delete m_Clients.take(anClientID);
		m_Clients.remove(anClientID);
	}
}

//----------------------------------------------------------------------

void Server::slotDisconnected()	{
	std::cout << "server: disconnected." << std::endl;

	ClientConnection *pClient = qobject_cast<ClientConnection *>(sender());
	int nSocketID = pClient->socketDescriptor();

	removeConnection(pClient,nSocketID);
}

//----------------------------------------------------------------------

int Server::clientCount() const	{
	int nSize = m_Clients.count();
	return nSize;
}

//----------------------------------------------------------------------

QList<quint64> Server::clients() const	{
	return m_Clients.keys();
}

//----------------------------------------------------------------------

ClientConnection * Server::getClient(quint64 clientID) const	{
	ClientConnection * pSocket = m_Clients.value(clientID);

	return pSocket;
}

//----------------------------------------------------------------------

void Server::slotNewConnection()	{
}