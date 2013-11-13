#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include <QFileDialog>
#include <QMessageBox>

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI() {	
	setupUi(this);

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_ShopBuilder.m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);

	setWindowTitle("VR Shop Server Dialog");

	m_pOSGQTWidget->show();

	//SIGNAL/SLOT CONNECTIONS
	buildConnections();
}


//=========================================================================================

void ShopBuilder_GUI::buildConnections() {
	//	QObject::connect(pushButton, SIGNAL(clicked()),this, SLOT(changeColor()));	
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenDB()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSaveDB()));
}

//=========================================================================================

QString ShopBuilder_GUI::openDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		tr("."), apchDBName);
	return(qstrFileName);
}

//=========================================================================================

QString ShopBuilder_GUI::saveDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getSaveFileName(this, 
		tr("Save file"),
		tr(".\\"), apchDBName);
	return(qstrFileName);
}

//=========================================================================================

void ShopBuilder_GUI::slotOpenDB() {
	QString qstrFileName = openDialog("*.db");
	if(qstrFileName != "") {
		QMessageBox msgBox;
		msgBox.setText(qstrFileName + "Write");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
	}
	
}

//=========================================================================================

void ShopBuilder_GUI::slotSaveDB() {
	QString qstrFileName = saveDialog("*.db");
	if(qstrFileName != "") {
		QMessageBox msgBox;
		msgBox.setText(qstrFileName + "Save");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
	}
}
