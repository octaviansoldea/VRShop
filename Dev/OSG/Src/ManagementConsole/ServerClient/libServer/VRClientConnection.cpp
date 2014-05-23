#include <iostream>

#include <QDataStream>
#include <QTcpSocket>
#include <QHostAddress>

#include <QList>

#include <sstream>
#include <string>

#include "VRDatabaseNetworkManager.h"

#include "VRClientConnection.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ClientConnection::ClientConnection(QObject *parent) : QTcpSocket(parent), m_bIsFirstPackage(true)	{
	connect(this, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
	connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

	connect(this,SIGNAL(done()),this,SLOT(slotTransferSuccess()));

	m_unPackageSize = 0;

	m_pDatabaseNetworkManager = new DatabaseNetworkManager();
}

//----------------------------------------------------------------------

ClientConnection::~ClientConnection()	{
	delete m_pDatabaseNetworkManager;
}

//=====================================================================

void ClientConnection::slotReadClient()	{
	//First block has to be "quint64 blockSize"
	QDataStream in(this);
	in.setVersion(QDataStream::Qt_4_8);

	int nBytesAvailable = this->bytesAvailable();
	std::cout << "Server (slotReadClient()): " << nBytesAvailable << std::endl;

	QByteArray qData;
	if (m_unPackageSize == 0) {
		if (this->bytesAvailable() < sizeof(quint64))
			return;
		in >> m_unPackageSize;
	}

	if (this->bytesAvailable() < m_unPackageSize)
		return;

/*
	quint8 unType;
	QString qstrData;
	in >> unType >> qstrData;
*/
	qData = in.device()->readAll();

	string strTest(qData.begin(),qData.end());

	std::cout << "Server: strTest: " << strTest << endl;

	m_unPackageSize = 0;
	processRequest(qData /*in*/);
}

//----------------------------------------------------------------------

void ClientConnection::slotTransferSuccess()	{
}

//----------------------------------------------------------------------

void ClientConnection::processRequest(QByteArray & data /* QDataStream & in*/)	{
	QDataStream in(&data,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_8);

	quint8 nType;
	QString qstrRequest;

	//Initialize parameters
	in >> nType >> qstrRequest;
	string & strRequest = qstrRequest.toStdString();
	bool bRes=false;

	if (nType == 'P')	{	//'P' - product
		//Access the Database
		bRes = m_pDatabaseNetworkManager->requestDatabase(strRequest);
	}

	QByteArray result;
	QDataStream out(&result, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out << quint64(0);	//Size of the package

	int nBytesAvailable = out.device()->bytesAvailable();
	std::cout << "Server (processRequest()): " << nBytesAvailable << std::endl;

	if (bRes)	{
		QList<string > & lststrResult = QList<string>().fromStdList(m_pDatabaseNetworkManager->getResult());
		QString qstrTest = lststrResult.at(0).c_str();
		out << qstrTest;
	} else {
		out << "Error: Database returns 0.";
	}

	writeToClient(result);
}

//----------------------------------------------------------------------

void ClientConnection::writeToClient(QByteArray & data)	{
	QDataStream out(&data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	bool bRes = out.device()->seek(0);
	quint64 unWritten = 0;
	quint64 unTotalToWrite = (quint64)(data.size());
	out << (quint64)(unTotalToWrite - sizeof(quint64));

	//Check that everything is written
	//while (unTotalToWrite - unWritten > 0)	{
	//	unWritten += write(data.data() + unWritten,unTotalToWrite-unWritten);
	//}

	unWritten = this->write(data);
	this->waitForBytesWritten();
}