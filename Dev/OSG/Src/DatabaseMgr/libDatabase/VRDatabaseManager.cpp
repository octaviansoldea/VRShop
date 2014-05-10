#include <iostream>

#include <QMessageBox>
#include <qsqlresult.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QVariantList>
#include <QDir>

#include <QString>

#include "BasicStringDefinitions.h"
#include "VRBasicQTOperations.h"

#include "VRDatabaseManager.h"

using namespace std;
using namespace VR;


//===========================================================================

DatabaseManagerParams::DatabaseManagerParams() :	
m_qstrDBName("../../../Databases/Default.db"),
m_qstrConnectionName("")	{
}

//===========================================================================

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
	createConnection(m_DBMgrParams);
}

//---------------------------------------------------------------------------

DatabaseManager::DatabaseManager(const DatabaseManagerParams & aDBMgrParams, QObject *parent) :
QObject(parent) {
	m_DBMgrParams = aDBMgrParams;

	createConnection(m_DBMgrParams);
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

bool DatabaseManager::dropDatabase(const QString & aqstrDBName)	{
	const QString * pqstrDBName = &aqstrDBName;

	if (pqstrDBName->isEmpty())	{
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
	QString * pqstrConnName = &m_DBMgrParams.m_qstrConnectionName;
	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName, false);

	if (pDb->isValid() && pDb->isOpen())
		pDb->close();

	QSqlDatabase::removeDatabase(*pqstrConnName);

	return true;
}

//-----------------------------------------------------------------------------------------

DatabaseManager::~DatabaseManager()	{
	removeConnection();
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::createTable(const string & astrTableName, const string & astrTableStmt)	{
	const string * pstrTableName = &astrTableName;
	if (pstrTableName->empty())	{
		printError("Table name not given");
		return false;
	}
	
	if (containsTable(pstrTableName->c_str()))	{
		printWarning(("Table " + *pstrTableName + " already exists and is not created.").c_str());
		return false;
	}

	const string * pSql = &astrTableStmt;

	return execute(*pSql);
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::removeTable(const QString& aqstrTableName)	{
	bool bRes = false;	
	const QString * pqstrTableName = &aqstrTableName;
	if (pqstrTableName->isEmpty())	{
		return bRes;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBMgrParams.m_qstrConnectionName);	
	QSqlQuery q(*pDb);
	
	QStringList & qlstDBtables = pDb->tables();
	if (qlstDBtables.contains(*pqstrTableName, Qt::CaseInsensitive))	{
		q.exec( "DROP TABLE " + *pqstrTableName);
	} else {
		QString * pqstrError = &QSqlDatabase::database().lastError().text();
		printWarning("Unable to drop table " + *pqstrTableName + " - " + *pqstrError);

		return bRes;
	}

	bRes = containsTable(*pqstrTableName) ? false : true;

	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::containsTable(const QString & aqstrTableName)	{
	const QString * pqstrTableName = &aqstrTableName;

	if (pqstrTableName->isEmpty())	{
		return false;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBMgrParams.m_qstrConnectionName);	
	QStringList & qlstpDBtables = pDb->tables();

	bool bRes = (qlstpDBtables.contains(*pqstrTableName, Qt::CaseInsensitive)) ? true : false;
	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::execute(const string & astrQuery)	{
	QString * pqstrConnName = &m_DBMgrParams.m_qstrConnectionName;
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

void DatabaseManager::insertRow(const string & astrTableName, string &astrTblFieldValues)	{
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBMgrParams.m_qstrConnectionName);
	QSqlTableModel model(this,*pDb);

	const string * pstrTableName = &astrTableName;
	vector<string> fieldValues = splitString(astrTblFieldValues,";");

	if (!containsTable(pstrTableName->c_str()))	{
		printError("Requested table not part of the database: " + pDb->databaseName());
		return;
	}


	model.setTable(pstrTableName->c_str());
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);

	QSqlRecord * pRec = &model.record();

	int nI;
	vector<string>::iterator it;
	for (it = fieldValues.begin(); it != fieldValues.end(); it++)	{
		nI = it - fieldValues.begin();
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
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBMgrParams.m_qstrConnectionName);
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
	
	const int nRow = pRec->value(0).toInt();

	model.removeRow(nRow);

	model.submitAll();
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::updateDB() {
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs)	{
}
