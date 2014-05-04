#include "VRServer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QHostAddress>
#include <QNetworkInterface>

#include "BasicStringDefinitions.h"

#include "VRServer_GUI.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Server_GUI::Server_GUI(QWidget * parent) : QWidget(parent)	{
	m_pServer = new Server(this);

	const string & strIP = m_pServer->serverIP();
	const int & nPort = m_pServer->serverPort();

	init(strIP,nPort);
}

//----------------------------------------------------------------------

Server_GUI::~Server_GUI()	{
}

//=====================================================================

void Server_GUI::init(const std::string & astrIPAddress, const int & anPort)	{
	QLabel * m_pLabelStatus = new QLabel(this);
	QPushButton * m_pPushButtonQuit = new QPushButton("Quit");
	
	m_pLabelStatus->setText(QString("The server is running on\n\nIP: %1\nport: %2\n\n")
		.arg(astrIPAddress.c_str()).arg(anPort));

	connect(m_pPushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));
	
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(m_pPushButtonQuit);
	buttonLayout->addStretch(1);

	//No of connections
	m_pConnection = new QLabel();

	QHBoxLayout *connectionsLayout = new QHBoxLayout;
	connectionsLayout->addWidget(new QLabel("No of connections:"));
	connectionsLayout->addWidget(m_pConnection);

	int nSize = m_pServer->m_lstConnections.size();
	m_pConnection->setText(tostr(nSize).c_str());

	connect(m_pServer,SIGNAL(newConnection()),this,SLOT(slotConnections()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_pLabelStatus);
	mainLayout->addLayout(connectionsLayout);
	mainLayout->addLayout(buttonLayout);
	
	setLayout(mainLayout);
	setWindowTitle("Server");
}

void Server_GUI::slotConnections()	{
	int nSize = m_pServer->m_lstConnections.size();
	m_pConnection->setText(tostr(nSize).c_str());
}