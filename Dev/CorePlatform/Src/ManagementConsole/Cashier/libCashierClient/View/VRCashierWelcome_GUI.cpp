#include "VRCashierWelcome_GUI.h"

using namespace Ui;
using namespace VR;


//----------------------------------------------------------------------

CashierWelcome_GUI::CashierWelcome_GUI(QDialog * apParent) : QDialog(apParent) {
	setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	hide();

	connect(m_pPushButtonCancel,SIGNAL(pressed()),this,SLOT(close()));
}

//======================================================================
