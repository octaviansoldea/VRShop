#include <iostream>

#include <QDataStream>
#include <QTcpSocket>
#include <QHostAddress>

#include <QList>

#include <sstream>
#include <string>

#include <QFile>

#include "VRAgentManager.h"
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
	processRequest(qData);
}

//----------------------------------------------------------------------

void ClientConnection::processRequest(QByteArray & data)	{
	QDataStream in(&data,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_8);

	quint8 nType;
	QString qstrRequest;

	//Initialize parameters
	in >> nType >> qstrRequest;
	string strRequest = qstrRequest.toStdString();
	bool bRes=false;

	if (nType == 'S')	{
		QByteArray result;
		QDataStream out(&result, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_8);
		out.setFloatingPointPrecision(QDataStream::SinglePrecision);

		string strFileName = "C:/Projekti/VRShop/Dev/OSG/Databases/ShopDemo.db";
		QFile file(strFileName.c_str());
		if(!file.open(QIODevice::ReadOnly))	{
			qDebug() << "Error file can't be opened!";
			return;
		}

		QByteArray bytes = file.readAll();

		
		out << quint64(0) << nType << bytes;	//Size of the package

		writeToClient(result);
		return;
	}

	//Access appropriate database
	DatabaseNetworkManager DBNetworkManager;
	bRes = DBNetworkManager.databaseRequest(nType,strRequest);

	QByteArray result;
	QDataStream out(&result, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out << quint64(0) << nType;	//Size of the package

	int nBytesAvailable = out.device()->bytesAvailable();

	if (bRes)	{
		list<string> lstResult = DBNetworkManager.getResult();
		list<string>::iterator it = lstResult.begin();
		int nI;
		string strResult;
		for (it; it != lstResult.end(); it++)	{
			strResult += (*it) + ";";
		}
		strResult.pop_back();

		QString qstrTest = strResult.c_str();
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