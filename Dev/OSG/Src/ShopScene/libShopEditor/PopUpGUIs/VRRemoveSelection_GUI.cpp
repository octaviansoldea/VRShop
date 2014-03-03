#include <string>
#include <fstream>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "VRRemoveSelection_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

RemoveSelection_GUI::RemoveSelection_GUI()	{
	setupUi(this);

	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_pToolButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_pPushButtonRemove, SIGNAL(clicked()), this, SLOT(accept()));
}

//----------------------------------------------------------------------
