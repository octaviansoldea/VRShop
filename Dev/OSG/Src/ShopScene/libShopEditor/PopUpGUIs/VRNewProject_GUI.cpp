#include <fstream>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "VRNewProject_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

NewProject_GUI::NewProject_GUI()	{
	setupUi(this);

	connect(m_pPushButtonBrowseDir, SIGNAL(clicked(bool)), this, SLOT(slotBrowseDirectory()));
	connect(m_pPushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(m_pToolButtonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(m_pPushButtonApply, SIGNAL(clicked(bool)), this, SLOT(slotApplyChanges()));
}

//----------------------------------------------------------------------

void NewProject_GUI::slotBrowseDirectory()	{
	QString qstrDirectoryName = QFileDialog::getExistingDirectory(this);
	m_pLineEditDirectory->setText(qstrDirectoryName);
}

//----------------------------------------------------------------------

void NewProject_GUI::slotApplyChanges()	{
	if((m_pLineEditFileName->text() == "") || (!QFile::exists(m_pLineEditDirectory->text())))	{
		QString qstrWarningText = "New project not opened.\nFile name not given or directory doesn't exist.";

		QMessageBox msgBox;
		msgBox.setText(qstrWarningText);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}
	done(1);
}