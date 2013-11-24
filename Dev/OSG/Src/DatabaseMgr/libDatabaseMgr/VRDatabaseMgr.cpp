#include <QMessageBox>

#include "VRDatabaseMgrSQLite.h"
#include "VRDatabaseMgrODBC.h"

#include "VRDatabaseMgr.h"

using namespace std;
using namespace VR;


DatabaseMgrParams::DatabaseMgrParams() :
	m_qstrObjectType(""),
	m_qstrObjectName(""),
	m_arrstrParams(1) {
}

//===========================================================================

void VR::printError(const char * apchMessage) {
	QMessageBox msgBox;
	msgBox.setText(apchMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error window");
	int nRes = msgBox.exec();
}

void VR::printWarning(const char * apchMessage) {
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
	return m_QSqlDatabase.lastError();
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgr::connect2SQLDatabase() {
	m_QSqlDatabase = QSqlDatabase::addDatabase(getDriverName());
	m_QSqlDatabase.setDatabaseName(m_qstrDBPathName);
	if (m_QSqlDatabase.open())	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------

void DatabaseMgr::insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams)	{
}

//=========================================================================================

DatabaseMgr::DatabaseMgr(const QString & aqstrDBPathName) : m_qstrDBPathName(aqstrDBPathName) {
}

//-----------------------------------------------------------------------------------
