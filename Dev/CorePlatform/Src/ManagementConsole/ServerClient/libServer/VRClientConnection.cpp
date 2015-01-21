#include <QDataStream>
#include <QTcpSocket>

#include "VRServerClientCommands.h"

#include "VRDatabaseNetworkManager.h"

#include "VRClientConnection.h"

using namespace VR;
using namespace std;


ClientConnection::ClientConnection(QObject *parent) : QTcpSocket(parent)	{
	connect(this, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
	connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

	m_unPackageSize = 0;
}

//=====================================================================

void ClientConnection::registerClientVisitor(const std::string & astrIP, const int & anUserID)	{
	QByteArray qData;
	QDataStream out(&qData, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrInputData;

	int nType = ServerClientCommands::NEW_USER_REGISTER;
	QString qstrIP = astrIP.c_str();

	out << quint8(nType) << qstrIP << anUserID;

	DatabaseNetworkManager::databaseRequest(qData);
}

//----------------------------------------------------------------------

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

	QByteArray output = DatabaseNetworkManager::databaseRequest(qData);

	//Write to client
	QDataStream out(&output, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	bool bRes = out.device()->seek(0);
	quint64 unWritten = 0;
	quint64 unTotalToWrite = (quint64)(output.size());
	out << (quint64)(unTotalToWrite - sizeof(quint64));

	//unWritten = this->write(output);
	//this->waitForBytesWritten();

	//Check that everything is written
	while (unTotalToWrite - unWritten > 0)	{
		unWritten += write(output.data() + unWritten,unTotalToWrite-unWritten);
	}
}

//----------------------------------------------------------------------
