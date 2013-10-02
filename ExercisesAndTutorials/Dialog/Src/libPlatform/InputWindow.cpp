#include "InputWindow.h"
#include <iostream>

InputWindow::InputWindow(QWidget *parent) : QDialog(parent)	{
	//Main widget
	widget = new QWidget;

	createWidgets();
	createLayout();
	tabOrder();

	setWindowTitle(tr("Price Comparison"));
	setFixedSize(sizeHint().width(),sizeHint().height());
}

//------------------------------------------------------

InputWindow::~InputWindow()	{
	delete widget;
}

//------------------------------------------------------

void InputWindow::createWidgets()	{
	//Defining store
	labelStore = new QLabel(tr("Store Location:"));
	storeLineEdit = new QLineEdit;

	//Defining product
	labelProduct = new QLabel(tr("Product (EAN):"));
	productLineEdit = new QLineEdit;
	productLineEdit->setEnabled(true);

	//Defining price
	labelPrice = new QLabel(tr("Product Price:"));
	priceLineEdit = new QLineEdit;
	priceLineEdit->setEnabled(true);

	//Cancel and OK buttons
    cancelButton = new QPushButton(tr("Cancel"));
	cancelButton->setEnabled(true);
	QObject::connect(cancelButton, SIGNAL(clicked()),this, SLOT(close()));

	okButton = new QPushButton(tr("Compare"));
	okButton->setEnabled(true);
	QObject::connect(okButton, SIGNAL(clicked()),this,SLOT(newInquiry()));
	QObject::connect(okButton, SIGNAL(clicked()),this,SLOT(close()));
}

//------------------------------------------------------

void InputWindow::createLayout()	{
	gridLayout = new QGridLayout;
	gridLayout->addWidget(labelStore,0,0,1,1);
	gridLayout->addWidget(labelProduct,1,0,1,1);
	gridLayout->addWidget(labelPrice,2,0,1,1);
	gridLayout->addWidget(storeLineEdit,0,1,1,1);
	gridLayout->addWidget(productLineEdit,1,1,1,1);
	gridLayout->addWidget(priceLineEdit,2,1,1,1);
	
	bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(okButton);
	bottomLayout->addWidget(cancelButton);
	
	mainLayout = new QVBoxLayout(widget);
	mainLayout->addLayout(gridLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
}

//------------------------------------------------------

void InputWindow::tabOrder()	{
	//Set order of processes
	QWidget::setTabOrder(storeLineEdit, productLineEdit);
	QWidget::setTabOrder(productLineEdit, priceLineEdit);
}

//------------------------------------------------------

void InputWindow::newInquiry()	{
	QString &m_strStore = storeLineEdit->text();
	QString &m_strProduct = productLineEdit->text();
	QString &m_strPrice = priceLineEdit->text();

	//Make a display to check the correctness
	std::cout << m_strStore.toStdString() << " "
			  << m_strProduct.toStdString() << " "
			  << m_strPrice.toStdString() << std::endl;

	emit inputDataChanged(m_strStore,m_strProduct,m_strPrice);
}