#include <iostream>

#include "VRServerClientCommands.h"
#include "VRBasicQtOperations.h"

#include <QEventLoop>
#include <QTimer>

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

Client::Client(QObject *apParent) : QObject(apParent), m_nUserID(-1),m_unPackageSize(0)	{	
}

//----------------------------------------------------------------------

Client::~Client()	{
	close();
}

//=====================================================================

void Client::tryToConnect()	{
	connect(&m_TcpSocket,SIGNAL(hostFound()),this,SLOT(slotHostFound()));
	connect(&m_TcpSocket, SIGNAL(readyRead()), this, SLOT(slotIsConnectionApproved()));
	connect(&m_TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), 
		this, SLOT(slotError(QAbstractSocket::SocketError)));
	connect(&m_TcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
	connect(&m_TcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

	m_TcpSocket.connectToHost(QHostAddress::LocalHost, 20000);
//	m_TcpSocket.waitForConnected();

	QEventLoop loop;
	connect(this,SIGNAL(done()),&loop,SLOT(quit()));
	QTimer::singleShot(10000,&loop,SLOT(quit()));
	loop.exec();
}

//---------------------------------------------------------------------------

void Client::close()	{
	m_TcpSocket.disconnectFromHost();
	m_TcpSocket.close();
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

	unWritten = m_TcpSocket.write(aarrRequest);
//	m_TcpSocket.waitForBytesWritten();
}

//---------------------------------------------------------------------

QTcpSocket & Client::getTcpSocket() {
	return(m_TcpSocket);
}

//---------------------------------------------------------------------

void Client::slotReadReceivedData()	{
	QByteArray qData;
	readSocket(qData);

	m_unPackageSize=0;

	m_TransmitData = qData;
	emit done();
}

//---------------------------------------------------------------------

void Client::slotError(QAbstractSocket::SocketError socketError)	{
	int nState = socketError;

	QString qstrErrorMsg;
	switch (nState)	{
	case QAbstractSocket::RemoteHostClosedError:
		{
			qstrErrorMsg = "Remote host closed.";
			break;
		}
	case QAbstractSocket::HostNotFoundError:
		{
			qstrErrorMsg = "The host was not found.\nCheck the \
						   host name and port settings.";
			break;
		}
	case QAbstractSocket::ConnectionRefusedError:
		{
			qstrErrorMsg = "The connection was refused by the server.\n \
						   Make sure the server is running,\n \
						   and check the host name and port number.";
			break;
		}
	default:
		{
			qstrErrorMsg = "The following error occurred: " + m_TcpSocket.errorString();
			break;
		}
	}

	BasicQtOperations::printError(qstrErrorMsg);
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

QByteArray Client::getTransmittedData()	{
	return m_TransmitData;
}

//---------------------------------------------------------------------------

void Client::slotIsConnectionApproved()	{
	QByteArray qData;
	readSocket(qData);

	disconnect(&m_TcpSocket, SIGNAL(readyRead()), this, SLOT(slotIsConnectionApproved()));
	connect(&m_TcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadReceivedData()));

	QDataStream out(&qData,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint16 nRes;
	out >> nRes;

	m_nUserID = nRes;

	emit done();
}

//---------------------------------------------------------------------------

void Client::readSocket(QByteArray & aData)	{
	QDataStream in(&m_TcpSocket);
	in.setVersion(QDataStream::Qt_4_8);

	int nBytesAvailable = m_TcpSocket.bytesAvailable();

	if (m_unPackageSize == 0) {
		if (nBytesAvailable < sizeof(quint64))
			return;
		in >> m_unPackageSize;
	}

	if (nBytesAvailable < m_unPackageSize)
		return;

	aData = in.device()->readAll();
}

//---------------------------------------------------------------------------

void Client::slotHostFound()	{
	std::cout << "Host found, waiting for reply." << std::endl;
}

//---------------------------------------------------------------------------

int Client::getUserID() const	{
	return m_nUserID;
}