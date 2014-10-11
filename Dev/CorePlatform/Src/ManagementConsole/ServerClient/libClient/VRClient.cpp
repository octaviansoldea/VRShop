#include <iostream>

#include "VRServerClientCommands.h"

#include <QMessageBox>
#include <QHostAddress>

#include <QFile>
#include <QDataStream>
#include <QByteArray>

#include <QTcpSocket>

#include "VRClient.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Client::Client(QObject *apParent) : QObject(apParent)	{
	slotTryToConnect();
}

//----------------------------------------------------------------------

Client::~Client()	{
}

//=====================================================================

void Client::slotTryToConnect()	{
	m_TcpSocket.connectToHost(QHostAddress::LocalHost, 20000);

	connect(&m_TcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadReceivedData()));
	connect(&m_TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), 
			this, SLOT(slotError(QAbstractSocket::SocketError)));
	connect(&m_TcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
	connect(&m_TcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

	m_TcpSocket.waitForConnected();
	m_unPackageSize = 0;
	m_ReceivedData = 0;
}

//---------------------------------------------------------------------

void Client::close()	{
//	m_TcpSocket.close();
	m_TcpSocket.disconnectFromHost();
}

//---------------------------------------------------------------------

void Client::sendRequest(QByteArray & aarrRequest)	{
	QDataStream out(&aarrRequest, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QTcpSocket * pSocket = static_cast<QTcpSocket*>(out.device());

	bool bRes = pSocket->seek(0);
	quint64 unWritten = 0;
	quint64 unTotalToWrite = (quint64)(aarrRequest.size());
	out << (quint64)(unTotalToWrite - sizeof(quint64));

	//Check that everything is written
	//while (unTotalToWrite - unWritten > 0)	{
	//	unWritten += m_TcpSocket.write(aarrRequest.data() + unWritten,unTotalToWrite-unWritten);
	//}
	unWritten = m_TcpSocket.write(aarrRequest);
	m_TcpSocket.waitForBytesWritten();
}

//---------------------------------------------------------------------

QTcpSocket & Client::getTcpSocket() {
	return(m_TcpSocket);
}

//---------------------------------------------------------------------

void Client::slotReadReceivedData()	{
	QDataStream in(&m_TcpSocket);
	in.setVersion(QDataStream::Qt_4_8);
	
	int nBytesAvailable = m_TcpSocket.bytesAvailable();

	QByteArray qData;

	if (m_unPackageSize == 0) {
		if (nBytesAvailable < sizeof(quint64))
			return;
		in >> m_unPackageSize;
	}

	if (nBytesAvailable < m_unPackageSize)
		return;

	qData = in.device()->readAll();

	m_unPackageSize=0;

	m_TransmitData = qData;
	emit done();
}

//---------------------------------------------------------------------

void Client::slotError(QAbstractSocket::SocketError socketError)	{
	int nState = socketError;

	QString qstrErrorMsg;
	if (nState == QAbstractSocket::RemoteHostClosedError)	{
		qstrErrorMsg = "Remote host closed.";
	}
	else if (nState == QAbstractSocket::HostNotFoundError) {
		qstrErrorMsg = "The host was not found.\nCheck the \
			host name and port settings.";
	}
	else if (nState == QAbstractSocket::ConnectionRefusedError)	{
		qstrErrorMsg = "The connection was refused by the server.\n \
			Make sure the server is running,\n \
			and check the host name and port number.";
	} else {
		qstrErrorMsg = "The following error occurred: " + m_TcpSocket.errorString();
	}

	QMessageBox msg;
	msg.setText(qstrErrorMsg);
	msg.setStandardButtons(QMessageBox::Ok);
	msg.setWindowTitle("Error: Client connection");
	int nRes = msg.exec();
}

//---------------------------------------------------------------------------

void Client::slotConnected()	{
	std::cout << "Client: Connected" << std::endl;
}

//---------------------------------------------------------------------------

void Client::slotDisconnected()	{
	std::cout << "Client: Disconnected" << std::endl;
}

//---------------------------------------------------------------------------

void Client::slotNewUserRequest()	{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	char chType = ServerClientCommands::NEW_USER_REQUEST;

	out << quint64(0) << quint8(chType);

	sendRequest(block);
}

//---------------------------------------------------------------------------

QByteArray Client::getTransmittedData()	{
	return m_TransmitData;
}