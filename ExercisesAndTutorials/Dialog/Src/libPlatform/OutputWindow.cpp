#include "OutputWindow.h"
#include <iostream>

#include <QtGui>
#include <QListView>

OutputWindow::OutputWindow(QWidget *parent) : QDialog(parent)	{
	inputWindow = new InputWindow;
	dataModel = new DataModel;
	database = new Database;

	QObject::connect(inputWindow,SIGNAL(inputDataChanged(QString &, QString &, QString &)),
		database,SLOT(newEntry(QString &, QString &, QString &)));

	inputWindow->exec();
	database->writeToFile("Database.dat");
	database->readFromFile("Database.dat");

	setWindowTitle(tr("Price Comparison"));
	createWidget();
	createLayout();
}

OutputWindow::~OutputWindow()	{
	delete inputWindow;
	delete database;
	delete dataModel;
}

void OutputWindow::createWidget()	{
	//Cancel and OK buttons
    cancelButton = new QPushButton(tr("Quit"));
	cancelButton->setEnabled(true);
	QObject::connect(cancelButton, SIGNAL(clicked()),this, SLOT(close()));

	resumeButton = new QPushButton(tr("Resume"));
	resumeButton->setEnabled(true);
	QObject::connect(resumeButton, SIGNAL(clicked()),this,SLOT(resumeSearch()));
	
	//Labels
	yourPriceLabel = new QLabel(tr("Your Price"));
	yourPriceLabel->setAlignment(Qt::AlignHCenter);
	yourPrice = new QLabel(tr("20.90"));
	yourPrice->setAlignment(Qt::AlignHCenter);

	bestPriceLabel = new QLabel(tr("Best Price"));
	bestPriceLabel->setAlignment(Qt::AlignHCenter);
	bestPrice = new QLabel(tr("20.90"));
	bestPrice->setAlignment(Qt::AlignHCenter);
}

void OutputWindow::createLayout()	{
	//Left layout
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(yourPriceLabel);
	leftLayout->addWidget(yourPrice);

	QSpacerItem *vSpacer = new QSpacerItem(1,10,QSizePolicy::Minimum, QSizePolicy::Fixed);

	leftLayout->addSpacerItem(vSpacer);
	leftLayout->addWidget(bestPriceLabel);
	leftLayout->addWidget(bestPrice);
	leftLayout->addStretch();

	//Right layout - list
	QListView *listView = new QListView;

	//Left-right layout
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addLayout(leftLayout);
	layout->addWidget(listView);

	//Bottom buttons
	bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(resumeButton);
	bottomLayout->addWidget(cancelButton);

	//Main layout
	commonLayout = new QVBoxLayout;
	commonLayout->addLayout(layout);
	commonLayout->addLayout(bottomLayout);

	setLayout(commonLayout);
}

void OutputWindow::resumeSearch()	{
	inputWindow->exec();
}

void OutputWindow::newData(QString &astrStore, QString &astrProduct, QString &astrPrice)	{
	m_strStore = astrStore;
	m_strProduct = astrProduct;
	m_strPrice = astrPrice;
}