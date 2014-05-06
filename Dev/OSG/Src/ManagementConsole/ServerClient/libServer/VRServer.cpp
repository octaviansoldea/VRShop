#include <iostream>

#include <QFile>

#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QString>

#include "VRScene.h"

#include <QTcpSocket>

#include "VRServer.h"

using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

Server::Server(QObject *parent) : QTcpServer(parent), m_pSocket(0)	{	
	init();

	connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

//----------------------------------------------------------------------

Server::~Server()	{
	close();
}

//=====================================================================

void Server::init()	{
	//These lines give the IP of the router - I think

/*	QList<QHostAddress> & ipAddressesList = QNetworkInterface::allAddresses();
	// use the first non-localhost IPv4 address
	QList<QHostAddress>::iterator it = ipAddressesList.begin();

	for (it; it != ipAddressesList.end(); it++) {
		if (*it != QHostAddress::LocalHost &&
			it->toIPv4Address()) {
				m_strServerIP = it->toString().toStdString();
				break;
		}
	}
*/
	// if we did not find one, use IPv4 localhost
	if (m_strServerIP.empty())	{
		m_strServerIP = QHostAddress(QHostAddress::LocalHost).toString().toStdString();
	}

	m_nPort = 20000;
	
	if (!listen(QHostAddress(m_strServerIP.c_str()), m_nPort)) {	//server listens for incoming conenctions
		QMessageBox msg;
		msg.setText(QString("Unable to start server.\n\n%1").arg(errorString()));
		msg.setStandardButtons(QMessageBox::Ok);
		msg.setWindowTitle("Warning window");
		int nRes = msg.exec();

		close();
		return;
	}
}

//----------------------------------------------------------------------

std::string Server::serverIP() const	{
	return m_strServerIP.c_str();
}

//----------------------------------------------------------------------

void Server::slotNewConnection()	{

	//Add new connection to the list of connections
	m_pSocket = nextPendingConnection();

	connect(m_pSocket,SIGNAL(disconnected()),this,SLOT(slotRemoveConnection()));
	connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(slotSendData()));

	m_lstConnections.push_back(m_pSocket);

	emit m_pSocket->readyRead();
}

//----------------------------------------------------------------------

void Server::slotRemoveConnection() {
	m_pSocket = qobject_cast<QTcpSocket*>(sender());
	m_lstConnections.remove(m_pSocket);
	m_pSocket->deleteLater();
}

//----------------------------------------------------------------------

void Server::slotSendData()	{
	if (!m_pSocket)
		return;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QFile file("C:/Matej/Images/Me.jpg");
	if(!file.open(QIODevice::ReadOnly))	{
		std::cout << "Error opening the file." << std::endl;
		return;
	}

	out << (quint64)0;
	out << file.readAll();
	out.device()->seek(0);
	out << (quint64)(block.size() - (int)sizeof(quint64));

	m_pSocket->write(block);
	m_pSocket->flush();
	m_pSocket->disconnectFromHost();
	//m_pSocket->waitForDisconnected();
}

//----------------------------------------------------------------------

void Server::SendNewSessionID() {
}

//----------------------------------------------------------------------

void Server::SendShopTreeScene() {
}

//----------------------------------------------------------------------

void Server::SendLocationAndClothesOnUsersAroundUntilRadiusX() {
}

//----------------------------------------------------------------------

void Server::SendBasketContent() {
}

//----------------------------------------------------------------------

void Server::SendInfoAboutProduct() {
}

//----------------------------------------------------------------------

void Server::readInputReuestsAndUpdate() {
}

//----------------------------------------------------------------------

void Server::sendAnswer() {
}

//----------------------------------------------------------------------

// If a user was not active for a long time, we close her/him session
void Server::maintenance() {
}

//----------------------------------------------------------------------

void Server::readSceneFromSceneDB(string & astrDBFileName)	{
	m_strDBFileName = astrDBFileName;
}