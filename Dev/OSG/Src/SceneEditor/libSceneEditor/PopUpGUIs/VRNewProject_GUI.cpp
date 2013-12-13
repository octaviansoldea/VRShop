#include <iostream>
#include <string>
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

QString NewProject_GUI::newProjectDialog() {
	QString qstrDirectoryName = QFileDialog::getExistingDirectory(this);

	return(qstrDirectoryName);
}

//----------------------------------------------------------------------

void NewProject_GUI::slotBrowseDirectory()	{
	QString qstrDirectoryName = newProjectDialog();
	m_pLineEditDirectory->setText(qstrDirectoryName);
}

//----------------------------------------------------------------------

void NewProject_GUI::slotApplyChanges()	{
	if (m_pLineEditFileName->text() == "")	{
		QMessageBox msgBox;
		msgBox.setText("File name not given.");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}
	
	if(!QFile::exists(m_pLineEditDirectory->text()))	{
		QMessageBox msgBox;
		msgBox.setText("Directory doesn't exist.");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}

	QString qstrPathName = m_pLineEditDirectory->text() + "/" + m_pLineEditFileName->text() + ".vr3";

	std::ofstream myfile(qstrPathName.toStdString());
	myfile.close();
	this->close();
}