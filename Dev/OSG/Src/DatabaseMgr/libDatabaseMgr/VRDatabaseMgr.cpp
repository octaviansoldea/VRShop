#include <QMessageBox>

#include "VRDatabaseMgrSQLite.h"
#include "VRDatabaseMgrODBC.h"

#include "VRDatabaseMgr.h"

using namespace std;
using namespace VR;


//===========================================================================

DatabaseMgrParams::DatabaseMgrParams() :
	m_strTableName(""),
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
	if(m_pQSqlDatabase->isOpen())	{
		m_pQSqlDatabase->close();

		delete m_pQSqlDatabase;
		m_pQSqlDatabase = NULL;
		QSqlDatabase::removeDatabase(m_pQSqlDatabase->connectionName());
	}
}

//-----------------------------------------------------------------------------------------

QSqlError DatabaseMgr::lastError() const {
	return m_pQSqlDatabase->lastError();
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgr::connect2SQLDatabase() {
	m_pQSqlDatabase = new QSqlDatabase(QSqlDatabase::addDatabase(getDriverName()));
	m_pQSqlDatabase->setDatabaseName(m_qstrDBPathName);

	bool bRes = m_pQSqlDatabase->isOpen() ? true : m_pQSqlDatabase->open();

	return bRes;
}

//-----------------------------------------------------------------------------------------

void DatabaseMgr::disconnectFromSQLDatabase()	{
	if (m_pQSqlDatabase)	{
		m_pQSqlDatabase->close();
		delete m_pQSqlDatabase;
		m_pQSqlDatabase = NULL;
	}

	if (!QSqlDatabase::connectionNames().isEmpty())
		QSqlDatabase::removeDatabase(QSqlDatabase::connectionNames()[0]);
}

//=========================================================================================

DatabaseMgr::DatabaseMgr(const QString & aqstrDBPathName) : m_qstrDBPathName(aqstrDBPathName) {
}

//-----------------------------------------------------------------------------------
