#include <iostream>
#include <QMessageBox>
#include <QFile>

#include <QTcpSocket>

#include "VRClient.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Client::Client(const string & astrIPAddress, const int anPort, QTcpSocket *apParent) 
: QTcpSocket(apParent), m_strIPAddress(astrIPAddress), m_nPort(anPort), m_bIsFirstPackage(true)	{

	connectToHost(m_strIPAddress.c_str(), m_nPort);

	connect(this, SIGNAL(readyRead()), this, SLOT(slotReadReceivedData()));
	connect(this, SIGNAL(error(QAbstractSocket::SocketError)), 
			this, SLOT(slotError(QAbstractSocket::SocketError)));

	connect(this,SIGNAL(connected()),this,SLOT(slotConnected()));
	connect(this,SIGNAL(done()),this,SLOT(slotTransferSuccess()));

}

//----------------------------------------------------------------------

Client::~Client()	{
	close();
	disconnectFromHost();
}

//=====================================================================

void Client::slotReadReceivedData()	{

	QFile file("C:/Matej/Images/Me_1.jpg");
	if(!file.open(QIODevice::Append))	{
		std::cout << "Error opening the file." << std::endl;
		return;
	}

	QDataStream in(this);
	in.setVersion(QDataStream::Qt_4_8);	//Version should equal Server's

	if ((quint64)bytesAvailable() < (quint64)sizeof(quint64))
		return;

	if (m_bIsFirstPackage == true)	{
		quint64 blockSize;
		in >> blockSize;
		m_unPackageSize = (unsigned int)blockSize;	//blockSize contains the size of the whole package

		//int nBytes2Remove = (int)sizeof(data)-sizeof(quint64(0));
		//data = data.remove(0,nBytes2Remove);
	}
	//Read the rest of the byte array
	QByteArray & data = readAll();

	file.write(data);
	file.close();

	m_bIsFirstPackage = false;

	//Deduct the size of each "chunk", m_unPackageSize = 0 => emit done()
	m_unPackageSize -= data.size();
	std::cout << "m_unPackageSize: " << m_unPackageSize << std::endl;

	if (m_unPackageSize == 0)	{
		emit done();
		std::cout << "Emitted" << std::endl;
	}
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
		qstrErrorMsg = "The following error occurred: " + errorString();
	}

	QMessageBox msg;
	msg.setText(qstrErrorMsg);
	msg.setStandardButtons(QMessageBox::Ok);
	msg.setWindowTitle("Error: Client connection");
	int nRes = msg.exec();
}

//---------------------------------------------------------------------------

void Client::slotConnected()	{
	std::cout << "Connected" << std::endl;
}

//---------------------------------------------------------------------------

void Client::slotTransferSuccess()	{
	std::cout << "Data transfer accomplished." << std::endl;
}