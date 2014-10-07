#include <string>
#include <fstream>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "VRSaveAs_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

SaveAs_GUI::SaveAs_GUI()	{
	setupUi(this);

	connect(m_pPushButtonBrowseDir, SIGNAL(clicked(bool)), this, SLOT(slotBrowseDirectory()));
	connect(m_pPushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(m_pToolButtonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(m_pPushButtonApply, SIGNAL(clicked(bool)), this, SLOT(slotApplyChanges()));
}

//----------------------------------------------------------------------

QString SaveAs_GUI::saveAsDialog() {
	QString qstrDirectoryName = QFileDialog::getExistingDirectory(this);

	return(qstrDirectoryName);
}

//----------------------------------------------------------------------

void SaveAs_GUI::slotBrowseDirectory()	{
	QString qstrDirectoryName = saveAsDialog();
	m_pLineEditDirectory->setText(qstrDirectoryName);
}

//----------------------------------------------------------------------

void SaveAs_GUI::slotApplyChanges()	{
	QString qstrWarningText;

	if((m_pLineEditFileName->text() == "") && (!QFile::exists(m_pLineEditDirectory->text())))
		qstrWarningText = "File name not given.\nDirectory doesn't exist.";
	else if(m_pLineEditFileName->text() == "")
		qstrWarningText = "File name not given.";
	else if(!QFile::exists(m_pLineEditDirectory->text()))
		qstrWarningText = "Directory doesn't exist.";

	if(!qstrWarningText.isNull())	{
		QMessageBox msgBox;
		msgBox.setText(qstrWarningText);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}

	done(1);

	//QString qstrPathName = m_pLineEditDirectory->text() + "/" + m_pLineEditFileName->text() + ".db";

	//std::ofstream myfile(qstrPathName.toStdString());
	//myfile.close();
	//close();
}