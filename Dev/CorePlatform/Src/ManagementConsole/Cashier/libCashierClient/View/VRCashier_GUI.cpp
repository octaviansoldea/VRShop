#include "VRCashier_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

Cashier_GUI::Cashier_GUI(QDialog * apParent) : QDialog(apParent) {
	setupUi(this);
	resize(559, 371);
	setWindowFlags(Qt::FramelessWindowHint);

	m_pTableWidgetProducts->setColumnCount(5);

	int nTableWidth = m_pTableWidgetProducts->width();
	QStringList qstrlstItems;
	qstrlstItems << "Product" << "Quantity" << "Price" << "Discount" << "Amount";
	m_pTableWidgetProducts->setHorizontalHeaderLabels(qstrlstItems);
	m_pTableWidgetProducts->horizontalHeader()->setVisible(true);
    m_pTableWidgetProducts->setColumnWidth(0,  0.45*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(1,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(2,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(3,  0.1*nTableWidth);
    m_pTableWidgetProducts->setColumnWidth(4,  0.1*nTableWidth);
	m_pTableWidgetProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//======================================================================
