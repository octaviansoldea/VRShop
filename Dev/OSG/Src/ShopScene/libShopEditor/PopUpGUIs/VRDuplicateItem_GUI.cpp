#include "VRDuplicateItem_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

DuplicateItem_GUI::DuplicateItem_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonDuplicate, SIGNAL(clicked()), this, SLOT(slotDuplicateItem()));
}

//----------------------------------------------------------------------

void DuplicateItem_GUI::slotDuplicateItem()	{
	m_pLineEditLocationX->text();
	return;
}