#include "VRCashierWelcome_GUI.h"

#include <osg/ref_ptr>
#include <QStringListModel>
#include <QListView>


using namespace Ui;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

CashierWelcome_GUI::CashierWelcome_GUI(QDialog * apParent) : QDialog(apParent) {
	setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));
}

//----------------------------------------------------------------------

CashierWelcome_GUI::~CashierWelcome_GUI()	{
}

//======================================================================
