 /****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtGui>
 #include <QtNetwork>

 #include <QDialogButtonBox>
 #include <QLabel>
 #include <QLineEdit>
 #include <QPushButton>
 #include <QLocalSocket>
 #include <QGridLayout>
 #include <QMessageBox>


 #include "client.h"

 Client::Client(QWidget *parent)
     : QDialog(parent)
 {
     hostLabel = new QLabel(tr("&Server name:"));
     hostLineEdit = new QLineEdit("fortune");
     hostLabel->setBuddy(hostLineEdit);

     statusLabel = new QLabel(tr("This examples requires that you run the "
                                 "Fortune Server example as well."));

     getFortuneButton = new QPushButton(tr("Get Fortune"));
     getFortuneButton->setDefault(true);

     quitButton = new QPushButton(tr("Quit"));

	 //Arrange buttons in a layout
     buttonBox = new QDialogButtonBox;
     buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
     buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

	 //Initializes the socket/client
     socket = new QLocalSocket(this);

	 //Enables initially disabled "getFortuneButton" button
     connect(hostLineEdit, SIGNAL(textChanged(QString)),
             this, SLOT(enableGetFortuneButton()));
     connect(getFortuneButton, SIGNAL(clicked()),
             this, SLOT(requestNewFortune()));
     connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	 //client's readyRead() signals that the data has been received
	 //readyRead() is emitted for every chunk that is received
     connect(socket, SIGNAL(readyRead()), this, SLOT(readFortune()));

	 //Connects error signal to the slot which displays type of error if/when occured
     connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
             this, SLOT(displayError(QLocalSocket::LocalSocketError)));

	 //Layout
     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(hostLabel, 0, 0);
     mainLayout->addWidget(hostLineEdit, 0, 1);
     mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
     mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
     setLayout(mainLayout);

     setWindowTitle(tr("Fortune Client"));
     hostLineEdit->setFocus();
 }

 void Client::requestNewFortune()
 {
	 //Resets to initial parameter values
     getFortuneButton->setEnabled(false);
     blockSize = 0;

	 //Aborts current connection and resets the socket
     socket->abort();

	 //Connects to the socket name provided and emits the signal "connected()", else emits "error()"
	 //When connected server starts sending the data => emits the "readyRead()" signal
	 //Connection to the "Server" class
     socket->connectToServer(hostLineEdit->text());	
 }

 void Client::readFortune()
 {
	 //The slot activates every time the signal readyRead() emits
	 //that the new data is available for reading from the device. 

	 QDataStream in(socket);
     in.setVersion(QDataStream::Qt_4_0);

	 //Size of the received data is read first
     if (blockSize == 0) {
		 //Checks if the space reserved for reading is large enough
         if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;
         in >> blockSize;
     }

	 //When the end of the stream is attained, terminate
     if (in.atEnd())
         return;

	 //After the size is read start reading the content. Store it as a QString
     QString nextFortune;
     in >> nextFortune;

	 //In case data is retreived in more chunks
     if (nextFortune == currentFortune) {
		 //Timer request a new chunk of data at the moment
         QTimer::singleShot(0, this, SLOT(requestNewFortune()));
         return;
     }

	 //When read we call the setText() function and transmit the text to the statusLabel object
     currentFortune = nextFortune;
     statusLabel->setText(currentFortune);
     getFortuneButton->setEnabled(true);
 }

 void Client::displayError(QLocalSocket::LocalSocketError socketError)
 {
     switch (socketError) {
     case QLocalSocket::ServerNotFoundError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The host was not found. Please check the "
                                     "host name and port settings."));
         break;
     case QLocalSocket::ConnectionRefusedError:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
         break;
     case QLocalSocket::PeerClosedError:
         break;
     default:
         QMessageBox::information(this, tr("Fortune Client"),
                                  tr("The following error occurred: %1.")
                                  .arg(socket->errorString()));
     }

     getFortuneButton->setEnabled(true);
 }

 void Client::enableGetFortuneButton()
 {
     getFortuneButton->setEnabled(!hostLineEdit->text().isEmpty());
 }