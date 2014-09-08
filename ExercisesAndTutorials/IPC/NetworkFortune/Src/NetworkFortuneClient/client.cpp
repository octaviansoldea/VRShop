 /****************************************************************************
 **
 ** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
 **     of its contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>
 #include <QtNetwork>

 #include <QDialogButtonBox>
 #include <QLabel>
 #include <QLineEdit>
 #include <QPushButton>
 #include <QTcpSocket>
 #include <QNetworkSession>
 #include <QHostAddress>
 #include <QGridLayout>
 #include <QMessageBox>


 #include "client.h"

#include <iostream>
#include <algorithm>

 Client::Client(QWidget *parent)
 :   QDialog(parent), networkSession(0)
 {
     hostLabel = new QLabel(tr("&Server name:"));
     portLabel = new QLabel(tr("S&erver port:"));

     statusLabel = new QLabel(tr("This examples requires that you run the "
                                 "Fortune Server example as well."));

     getFortuneButton = new QPushButton(tr("Get Fortune"));
     getFortuneButton->setDefault(true);
     getFortuneButton->setEnabled(false);

     quitButton = new QPushButton(tr("Quit"));

     buttonBox = new QDialogButtonBox;
     buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
     buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

 	 //Initializes the socket/client
     tcpSocket = new QTcpSocket(this);

	 //Call functions
	 setIPAddress();
	 networkConfigurationManager();

	 //Define necessary SIGNAL/SLOT connections
     connect(hostLineEdit, SIGNAL(textChanged(QString)),
             this, SLOT(enableGetFortuneButton()));
     connect(portLineEdit, SIGNAL(textChanged(QString)),
             this, SLOT(enableGetFortuneButton()));
     connect(getFortuneButton, SIGNAL(clicked()),
             this, SLOT(requestNewFortune()));
     connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	 //client's readyRead() signals that the data has been received
	 //readyRead() is emitted for every chunk that is received
	 connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
     connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(displayError(QAbstractSocket::SocketError)));

	 // In case of a failer re-try connecting to the local host
	 connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(retryConnection()));

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(hostLabel, 0, 0);
     mainLayout->addWidget(hostLineEdit, 0, 1);
     mainLayout->addWidget(portLabel, 1, 0);
     mainLayout->addWidget(portLineEdit, 1, 1);
     mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
     mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
     setLayout(mainLayout);

     setWindowTitle(tr("Fortune Client"));
 }

//-----------------------------------------------------------------

 void Client::requestNewFortune()
 {
	 //Resets to initial parameter values
     getFortuneButton->setEnabled(false);
     blockSize = 0;

	 //Aborts current connection and resets the socket
	 tcpSocket->abort();

	 //Connects to the socket name provided and emits the signal "connected()", else emits "error()"
	 //When connected server starts sending the data => emits the "readyRead()" signal
	 //Connection to the "Server" class
     tcpSocket->connectToHost(hostLineEdit->text(),
                              portLineEdit->text().toInt());

	 //If connection is not established within 2 seconds, run the retryConnection() SLOT
	 QTimer::singleShot(2000,this,SLOT(retryConnection()));
 }

 //---------------------------------------------------------------------------

 void Client::readFortune()
 {
	 //The slot activates every time the signal readyRead() emits
	 //that the new data is available for reading from the device. 
     QDataStream in(tcpSocket);
     in.setVersion(QDataStream::Qt_4_0);

	 //Size of the received data is read first
     if (blockSize == 0) {
		 //Checks if the space reserved for reading is large enough
         if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
             return;

         in >> blockSize;
     }

     if (tcpSocket->bytesAvailable() < blockSize)
         return;

	 //After the size is read start reading the content. Store it as a QString
     QString nextFortune;
     in >> nextFortune;

	 //In case data is retreived in more chunks
     if (nextFortune == currentFortune) {
         QTimer::singleShot(1000, this, SLOT(requestNewFortune()));
         return;
     }

	 //When read we call the setText() function and transmit the text to the statusLabel object
     currentFortune = nextFortune;
     statusLabel->setText(currentFortune);
     getFortuneButton->setEnabled(true);
 }

 //---------------------------------------------------------------------------

 void Client::displayError(QAbstractSocket::SocketError socketError)
 {
     switch (socketError) {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     case QAbstractSocket::HostNotFoundError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QAbstractSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
     default:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The following error occurred: %1.")
                                  .arg(tcpSocket->errorString()));	 
	 }
	 getFortuneButton->setEnabled(true);
 }

 //---------------------------------------------------------------------------

 void Client::enableGetFortuneButton()
 {
	 getFortuneButton->setEnabled(true);
     getFortuneButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                  !hostLineEdit->text().isEmpty() &&
                                  !portLineEdit->text().isEmpty());

 }

 //---------------------------------------------------------------------------

 void Client::sessionOpened()
 {
     // Save the used configuration
     QNetworkConfiguration config = networkSession->configuration();
     QString id;
     if (config.type() == QNetworkConfiguration::UserChoice)
         id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
     else
		 //identifier() returns the unique and platform specific identifier for this network configuration
         id = config.identifier();

     QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
     settings.beginGroup(QLatin1String("QtNetwork"));
     settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
     settings.endGroup();

     statusLabel->setText(tr("This examples requires that you run the "
                             "Fortune Server example as well."));

     enableGetFortuneButton();
 }

 //---------------------------------------------------------------------

 void Client::setIPAddress()	{
	 // find out which IP to connect to
     QString ipAddress;
	 if(!ipAddress.isEmpty())
		 ipAddress.clear();

	 //Returns all IP addresses found on the host machine.
     QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

	 //Display addresses for checking
     for (int i = 0; i < ipAddressesList.size(); i++) {
		 std::cout << ipAddressesList.at(i).toString().toStdString() << std::endl;
	 }
     // use the first non-localhost IPv4 address
     for (int i = 0; i < ipAddressesList.size(); i++) {
		 if ((ipAddressesList.at(i) != QHostAddress::LocalHost) && 
             ipAddressesList.at(i).toIPv4Address()) {
	             ipAddress = ipAddressesList.at(i).toString();
		         break;
		 }
     }

	 // if we did not find one, use IPv4 localhost
     if (ipAddress.isEmpty())
         ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	 
	 currentAddress = ipAddress;
     hostLineEdit = new QLineEdit(ipAddress);
	 portLineEdit = new QLineEdit;
	 //A validator ensures that a string contains a valid integer within a specified MIN/MAX range.
     portLineEdit->setValidator(new QIntValidator(1, 65535, this));

     hostLabel->setBuddy(hostLineEdit);
     portLabel->setBuddy(portLineEdit);
 }

 //---------------------------------------------------------------------------

void Client::retryConnection()	{
	QString ipAddress;
	tcpSocket->abort();	//I'm not sure this part is needed

	 //Returns all IP addresses found on the host machine.
     QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	 
	 //Display addresses for checking
     for (int i = 0; i < ipAddressesList.size(); i++) {
		 std::cout << ipAddressesList.at(i).toString().toStdString() << std::endl;
	 }
     // use the first non-localhost IPv4 address different from the previous/nonworking IP address
     for (int i = 0; i < ipAddressesList.size(); i++) {
		 if ((ipAddressesList.at(i) != QHostAddress::LocalHost) && 
			 (ipAddressesList.at(i) != currentAddress) &&
             ipAddressesList.at(i).toIPv4Address()) {
	             ipAddress = ipAddressesList.at(i).toString();
		         break;
		 }
     }

	 // if we did not find one, use IPv4 localhost
     if (ipAddress.isEmpty())
         ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

	hostLineEdit->clear();
	hostLineEdit->setText(ipAddress);
}

 //---------------------------------------------------------------------------

void Client::networkConfigurationManager()	{
	 //Provides access to the network configurations known to the system and enables applications
	 //to detect the system capabilities (with regards to network sessions) at runtime.
     QNetworkConfigurationManager manager;
     if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
         // Get saved network configuration
         QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
         settings.beginGroup(QLatin1String("QtNetwork"));
         const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		 //Call endGroup() to reset the current group to what it was before the corresponding beginGroup() call.
         settings.endGroup();

         // If the saved network configuration is not currently discovered use the system default
         QNetworkConfiguration config = manager.configurationFromIdentifier(id);
         if ((config.state() & QNetworkConfiguration::Discovered) !=
             QNetworkConfiguration::Discovered) {
             config = manager.defaultConfiguration();
         }

		 //The QNetworkSession class provides control over the system's access points and enables
		 //session management for cases when multiple clients access the same access point.
         networkSession = new QNetworkSession(config, this);
         connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

         getFortuneButton->setEnabled(false);
         statusLabel->setText(tr("Opening network session."));
         networkSession->open();
     }
}