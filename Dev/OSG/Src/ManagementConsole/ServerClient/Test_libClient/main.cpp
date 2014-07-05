#include <QApplication>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QDataStream>

#include <iostream>

#include "VRClient.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);

	Client client;

	QDialog dialog;

	QPushButton * m_pPushButtonEnter = new QPushButton("Enter");
	QPushButton * m_pPushButtonClose = new QPushButton("Close");
	
	QObject::connect(m_pPushButtonEnter, SIGNAL(clicked()), &client, SLOT(slotTryToConnect()));
	QObject::connect(m_pPushButtonClose, SIGNAL(clicked()), &client, SLOT(close()));
	
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(m_pPushButtonEnter);
	buttonLayout->addWidget(m_pPushButtonClose);
	buttonLayout->addStretch(1);
	
	dialog.setLayout(buttonLayout);
	dialog.setWindowTitle("Client");
	dialog.show();


	return app.exec();
}