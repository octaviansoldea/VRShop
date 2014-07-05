#include <iostream>
#include <QString>

#include <QFileDialog>
#include <QMessageBox>

#include "VRFileManager.h"

using namespace VR;
using namespace std;

FileManager::FileManager()	{
}

//=====================================================================

QString FileManager::openDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getOpenFileName(0, 
		tr("Open File"),
		tr("."), apchDBName);

	return(qstrFileName);
}

//---------------------------------------------------------------------

QString FileManager::saveDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getSaveFileName(0, 
		tr("Save file"),
		tr(".\\"), apchDBName);
	return(qstrFileName);
}

//---------------------------------------------------------------------

bool FileManager::newProject()	{

	bool bRes = false;
	return bRes;
}

//---------------------------------------------------------------------

bool FileManager::openDB()	{
	bool bRes = false;
	return bRes;
}

//---------------------------------------------------------------------

bool FileManager::saveDB()	{
	bool bRes = false;
	return bRes;
}

//---------------------------------------------------------------------

bool FileManager::saveAsDB()	{
	bool bRes = false;
	return bRes;
}

//---------------------------------------------------------------------

bool FileManager::closeDB()	{
	bool bRes = false;
	return bRes;
}

//---------------------------------------------------------------------
