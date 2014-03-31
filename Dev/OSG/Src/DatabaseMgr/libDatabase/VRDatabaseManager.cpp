#include <iostream>

#include <QMessageBox>
#include <qsqlresult.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QVariantList>
#include <QDir>

#include <QString>

#include "VRDatabaseManager.h"

using namespace std;
using namespace VR;

DatabaseManagerParams::DatabaseManagerParams() :	
m_qstrDBName("../Default.db"),
m_qstrConnectionName("")
{
}

//===========================================================================

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
	createConnection(m_DatabaseManagerParams);
}

//---------------------------------------------------------------------------

DatabaseManager::DatabaseManager(const DatabaseManagerParams & aDBMgrParams, QObject *parent) :
QObject(parent) {
	m_DatabaseManagerParams = aDBMgrParams;

	createConnection(m_DatabaseManagerParams);
}

//===========================================================================

bool DatabaseManager::createConnection(const DatabaseManagerParams & aDBMgrParams)	{
	if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
		printError("Given driver QSQLITE not supported.");
		return false;
	}
	const QString * pqstrConnName = &aDBMgrParams.m_qstrConnectionName;
	
	QSqlDatabase * pDb = &QSqlDatabase::addDatabase("QSQLITE",*pqstrConnName);
	pDb->setDatabaseName(aDBMgrParams.m_qstrDBName);

	bool bOk = pDb->isOpen() ? true : pDb->open();

	if (!bOk) {
		QString & qstrError = QSqlDatabase::database().lastError().text();
		printError(qstrError);
		QSqlDatabase::removeDatabase(*pqstrConnName);
	}
	return bOk;
}

//---------------------------------------------------------------------------

bool DatabaseManager::dropDatabase(const QString & astrDBName)	{
	const QString * pqstrDBName = &astrDBName;

	if (astrDBName.isEmpty())	{
		return false;
	}

    if (QFile(*pqstrDBName).exists() && !QDir().remove(*pqstrDBName)) {
		printError("Could not remove DB file: " + *pqstrDBName);
		return false;
    }
    return true;
}

//---------------------------------------------------------------------------

bool DatabaseManager::removeConnection()	{
	QString * pqstrConnName = &m_DatabaseManagerParams.m_qstrConnectionName;
	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName, false);

	if (pDb->isValid() && pDb->isOpen())
		pDb->close();

	QSqlDatabase::removeDatabase(*pqstrConnName);

	return true;
}

//---------------------------------------------------------------------------

void DatabaseManager::printError(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error window");
	int nRes = msgBox.exec();
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::printWarning(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Warning window");
	int nRes = msgBox.exec();
}

//-----------------------------------------------------------------------------------------

DatabaseManager::~DatabaseManager()	{
	removeConnection();
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::createTable(const string & aqstrTableName, const string & astrTableStmt)	{
	const string * pstrTableName = &aqstrTableName;
	if (pstrTableName->empty())	{
		printError("Table name not given");
		return (0);
	}
	
	if (containsTable(pstrTableName->c_str()))	{
		printWarning(("Table " + *pstrTableName + " already exists and is not created.").c_str());
		return (0);
	}

	const string * pSql = &astrTableStmt;

	return execute(*pSql);
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::removeTable(const QString& aqstrTableName)	{
	bool bRes = false;	
	const QString * pTableName = &aqstrTableName;
	if (pTableName->isEmpty())	{
		return bRes;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DatabaseManagerParams.m_qstrConnectionName);	
	QSqlQuery q(*pDb);
	
	QStringList & lstDBtables = pDb->tables();
	if (lstDBtables.contains(*pTableName, Qt::CaseInsensitive))	{
		q.exec( "DROP TABLE " + *pTableName);
	} else {
		QString * pqstrError = &QSqlDatabase::database().lastError().text();
		printWarning("Unable to drop table " + *pTableName + " - " + *pqstrError);

		return bRes;
	}

	bRes = containsTable(*pTableName) ? false : true;

	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::containsTable(const QString & astrTableName)	{
	const QString * pqstrTableName = &astrTableName;

	if (pqstrTableName->isEmpty())	{
		return false;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DatabaseManagerParams.m_qstrConnectionName);	
	QStringList & lstpDBtables = pDb->tables();

	bool bRes = (lstpDBtables.contains(*pqstrTableName, Qt::CaseInsensitive)) ? true : false;
	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::execute(const string & astrQuery)	{
	QString * pqstrConnName = &m_DatabaseManagerParams.m_qstrConnectionName;
	const string * pstrQuery = &astrQuery;

	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName);
	QSqlQuery query(*pDb);

	bool bRes = query.exec(pstrQuery->c_str());

	if (!bRes)	{
		printError("Failed to execute SQL");
	}

	return bRes;
}



//-----------------------------------------------------------------------------------------

void DatabaseManager::insertRow(const string & astrTableName, vector<string> &aarrstrTblFieldValues)	{
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DatabaseManagerParams.m_qstrConnectionName);
	QSqlTableModel model(this,*pDb);

	const string * pstrTableName = &astrTableName;
	vector<string> * pFieldValues = &aarrstrTblFieldValues;

	if (!containsTable(pstrTableName->c_str()))	{
		printError("Requested table not part of the database: " + pDb->databaseName());
		return;
	}


	model.setTable(pstrTableName->c_str());
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);

	QSqlRecord * pRec = &model.record();

	int nI;
	vector<string>::iterator it;
	for (it = pFieldValues->begin(); it != pFieldValues->end(); it++)	{
		nI = it - pFieldValues->begin();
		if (pRec->field(nI).isAutoValue())	{
			continue;
		} else {
			pRec->setValue(nI,it->c_str());
		}
	}

	int row = model.rowCount();

	bool bRes = model.insertRecord(row,*pRec);
	if (bRes)	{
		model.submitAll();
	} else {
		model.revertAll();
		printError("Failed to insert the record.");
		return;
	}
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::deleteRow(const string & astrTableName, const string & astrObjectName)	{
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DatabaseManagerParams.m_qstrConnectionName);
	QSqlTableModel model(this, *pDb);

	const string * pstrTableName = &astrTableName;
	if (!containsTable(pstrTableName->c_str()))	{
		printError("Requested table not part of the Database.");
		return;
	}

	const string * pstrObjectName = &astrObjectName;

	model.setTable(pstrTableName->c_str());
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);
	model.select();

	QSqlQuery q(("SELECT * FROM " + *pstrTableName).c_str(),*pDb);
	QSqlRecord * pRec = &q.record();
	
	const int & nRow = pRec->value(0).toInt();

	model.removeRow(nRow);

	model.submitAll();
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::updateDB() {
}