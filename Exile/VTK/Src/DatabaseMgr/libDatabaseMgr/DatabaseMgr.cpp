#include <iostream>

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <qsqlresult.h>

#include "DatabaseMgr.h"
#include "DatabaseMgrSQLite.h"
#include "DatabaseMgrODBC.h"
#include "Cupboard.h"

using namespace std;

void printError(const char * apchMessage) {
	QMessageBox msgBox;
	msgBox.setText(apchMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error window");
	int nRes = msgBox.exec();
}

void printWarning(const char * apchMessage) {
	QMessageBox msgBox;
	msgBox.setText(apchMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Warning window");
	int nRes = msgBox.exec();
}

QString DatabaseMgr::getDriverName() const {
	return(QString(""));
}

DatabaseMgr & DatabaseMgr::Create(const QString & aqstrDBPathName, DRIVER_NAME aDriverName) {

	qDebug() << "Installed database drivers include: " << QSqlDatabase::drivers();
	
	DatabaseMgr * pDatabaseMgr;

	if(aDriverName == DRIVER_NAME::QODBC) {
		pDatabaseMgr = CreateODBC(aqstrDBPathName);
		if(pDatabaseMgr)
			return(*pDatabaseMgr);
		else
			printWarning("Could not create ODBC");
	}
	pDatabaseMgr = CreateSQLite(aqstrDBPathName);
	return(*pDatabaseMgr);
}

DatabaseMgr * DatabaseMgr::CreateSQLite(const QString & aqstrDBPathName) {
	if (!QSqlDatabase::drivers().contains("QSQLITE")) {
			printError("Given driver QSQLITE not supported.");
			exit(-1);
	}	
	DatabaseMgrSQLite * pDatabaseMgrSQLite = new DatabaseMgrSQLite(aqstrDBPathName);
	return(pDatabaseMgrSQLite);
}

DatabaseMgr * DatabaseMgr::CreateODBC(const QString & aqstrDBPathName) {
	if (!QSqlDatabase::drivers().contains("QODBC")) {
			printError("Given driver QODBC not supported.");
			return(0);
	}	
	DatabaseMgrODBC * pDatabaseMgrODBC = new DatabaseMgrODBC(aqstrDBPathName);
	return(pDatabaseMgrODBC);
}

//-----------------------------------------------------------------------------------------

DatabaseMgr::~DatabaseMgr()	{
	if(m_QSqlDatabase.isOpen())
		m_QSqlDatabase.close();
}

//-----------------------------------------------------------------------------------------

QSqlError DatabaseMgr::lastError() const {
	// If opening database has failed user can ask 
	// error description by QSqlError::text()
	return m_QSqlDatabase.lastError();
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgr::connect2SQLDatabase() {
	m_QSqlDatabase = QSqlDatabase::addDatabase(getDriverName());
	m_QSqlDatabase.setDatabaseName(m_qstrDBPathName);
	if (m_QSqlDatabase.open())	{
		std::cout << "Database opened!" << std::endl;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------------------

void DatabaseMgr::insertItem(const QString &aqstrObjectType, const QString &aqstrCategory, const QString &aqstrProduct, const QString &aqstrProductCodeNumber, const QString &aqstrProductCodeImage, const QString aqstrarrLocation[3],const QString aqstrarrOrientation[3])	{
	if(m_QSqlDatabase.open())	{
		insertObjectType(aqstrObjectType);
		insertCategory(aqstrCategory, aqstrObjectType);
		insertProduct(aqstrProduct, aqstrCategory);
		insertProductCode(aqstrProduct, aqstrProductCodeNumber);
		insertProductCodeImage(aqstrProductCodeNumber, aqstrProductCodeImage);
		m_QSqlDatabase.close();
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//-----------------------------------------------------------------------------------------
void DatabaseMgr::insertPrimitive(
	const QString &aqstrPrimitiveName, 
	int anPrimitiveParameterNumber, 
	const vector < double > & aarrdbParams) {

	std::cout << "Error: No way being here " << std::endl;
	exit(-1);

}

//-----------------------------------------------------------------------------------------

void DatabaseMgr::insertTexture(const QString &aqstrTextureName, const QString &aqstrTexturePath)	{
}

//-----------------------------------------------------------------------------------------

void DatabaseMgr::insertCupboard(const Cupboard & aCupboard) {
}

//=========================================================================================

DatabaseMgr::DatabaseMgr(const QString & aqstrDBPathName) : m_qstrDBPathName(aqstrDBPathName) {
}

//=================================================================================================
