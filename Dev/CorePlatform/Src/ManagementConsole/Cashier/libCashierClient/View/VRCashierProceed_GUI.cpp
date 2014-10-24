#include "VRCashierProceed_GUI.h"

using namespace Ui;
using namespace VR;


//----------------------------------------------------------------------

CashierProceed_GUI::CashierProceed_GUI(QDialog * apParent) :
QDialog(apParent) {
	setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	hide();

	connect(m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));

	m_pTableWidgetProducts->setColumnCount(5);

	int nTableWidth = m_pTableWidgetProducts->width();
	QStringList items;
	items << "Product" << "Quantity" << "Price" << "Discount" << "Amount";
	m_pTableWidgetProducts->setHorizontalHeaderLabels(items);
	m_pTableWidgetProducts->horizontalHeader()->setVisible(true);
    m_pTableWidgetProducts->setColumnWidth(0,  0.45*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(1,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(2,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(3,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(4,  0.1*nTableWidth);
	m_pTableWidgetProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//======================================================================
