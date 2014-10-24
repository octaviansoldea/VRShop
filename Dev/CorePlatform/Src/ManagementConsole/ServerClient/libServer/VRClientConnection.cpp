#include <iostream>

#include <QDataStream>
#include <QTcpSocket>
#include <QHostAddress>

#include "VRServerClientCommands.h"

#include <QList>

#include <sstream>
#include <string>

#include <QFile>

#include "VRDatabaseNetworkManager.h"

#include "VRClientConnection.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ClientConnection::ClientConnection(QObject *parent) : QTcpSocket(parent), m_bIsFirstPackage(true)	{
	connect(this, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
	connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

	m_unPackageSize = 0;
}

//----------------------------------------------------------------------

ClientConnection::~ClientConnection()	{
}

//=====================================================================

void ClientConnection::slotReadClient()	{
	//First block has to be "quint64 blockSize"
	QDataStream in(this);
	in.setVersion(QDataStream::Qt_4_8);

	int nBytesAvailable = this->bytesAvailable();

	QByteArray qData;
	if (m_unPackageSize == 0) {
		if (this->bytesAvailable() < sizeof(quint64))
			return;
		in >> m_unPackageSize;
	}

	if (this->bytesAvailable() < m_unPackageSize)
		return;

	qData = in.device()->readAll();

	m_unPackageSize = 0;

	QByteArray & output = DatabaseNetworkManager::databaseRequest(qData);

	//Write to client
	QDataStream out(&output, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	bool bRes = out.device()->seek(0);
	quint64 unWritten = 0;
	quint64 unTotalToWrite = (quint64)(output.size());
	out << (quint64)(unTotalToWrite - sizeof(quint64));

	unWritten = this->write(output);
	this->waitForBytesWritten();
}

//----------------------------------------------------------------------
