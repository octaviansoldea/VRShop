#include "VRCashierProceed_GUI.h"

#include <osg/ref_ptr>
#include <QStringListModel>
#include <QListView>

using namespace Ui;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

CashierProceed_GUI::CashierProceed_GUI(QDialog * apParent) :
QDialog(apParent) {
	setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));
}

//----------------------------------------------------------------------

CashierProceed_GUI::~CashierProceed_GUI()	{
}

//======================================================================

void CashierProceed_GUI::addRow()	{
	int row = m_pTableWidgetProducts->rowCount();
	m_pTableWidgetProducts->insertRow(row);

	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pTableWidgetProducts->setItem(row, 0, item0);
	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pTableWidgetProducts->setItem(row, 1, item1);

	m_pTableWidgetProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//----------------------------------------------------------------------