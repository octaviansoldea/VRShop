#include "VRServer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QHostAddress>
#include <QNetworkInterface>

#include "VRServer_GUI.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

Server_GUI::Server_GUI(Server * apServer, QWidget * parent) 
: m_pServer(apServer), QWidget(parent)	{
	const string & strIP = m_pServer->serverAddress().toString().toStdString();
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

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_pLabelStatus);
	mainLayout->addLayout(buttonLayout);
	
	setLayout(mainLayout);
	setWindowTitle("Server");
}

//---------------------------------------------------------------

void Server_GUI::close()	{
	m_pServer->close();

	bool bRes = m_pServer->isListening();

	if (!bRes)
		QWidget::close();
}