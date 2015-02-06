#include <iostream>

#include <QMessageBox>
#include <qsqlresult.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QVariantList>
#include <QDir>
#include <QCoreApplication>

#include <QString>

#include "BasicStringDefinitions.h"
#include "VRBasicQtOperations.h"

#include "VRDatabaseInterface.h"

using namespace std;
using namespace VR;


//===========================================================================

DatabaseInterfaceParams::DatabaseInterfaceParams(const QString & aqstrDBName, const QString & aqstrConnectionName) :	
m_qstrDBName(aqstrDBName),
m_qstrConnectionName(aqstrConnectionName)	{
}

//---------------------------------------------------------------------------

DatabaseInterface::DatabaseInterface()	{
}

//---------------------------------------------------------------------------

DatabaseInterface::DatabaseInterface(const DatabaseInterfaceParams & aDBInterfaceParams) {
	init(aDBInterfaceParams);
}

//===========================================================================

void DatabaseInterface::init(const DatabaseInterfaceParams & aDBInterfaceParams)	{
	m_DBInterfaceParams = aDBInterfaceParams;
	createConnection(m_DBInterfaceParams);
}

//---------------------------------------------------------------------------

bool DatabaseInterface::createConnection(const DatabaseInterfaceParams & aDBInterfaceParams)	{
	if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
		BasicQtOperations::printError("Given driver QSQLITE not supported.");
		return false;
	}
	const QString * pqstrConnName = &aDBInterfaceParams.m_qstrConnectionName;
	
	QSqlDatabase * pDb = &QSqlDatabase::addDatabase("QSQLITE",*pqstrConnName);
	pDb->setDatabaseName(aDBInterfaceParams.m_qstrDBName);

	bool bOk = pDb->isOpen() ? true : pDb->open();

	if (!bOk) {
		QString qstrError = QSqlDatabase::database().lastError().text();
		BasicQtOperations::printError(qstrError);
		QSqlDatabase::removeDatabase(*pqstrConnName);		
	}

	return bOk;
}

//---------------------------------------------------------------------------

bool DatabaseInterface::dropDatabase(const QString & aqstrDBName)	{
	const QString * pqstrDBName = &aqstrDBName;

	if (pqstrDBName->isEmpty())	{
		return false;
	}

    if (QFile(*pqstrDBName).exists() && !QDir().remove(*pqstrDBName)) {
		BasicQtOperations::printError("Could not remove DB file: " + *pqstrDBName);
		return false;
    }
    return true;
}

//---------------------------------------------------------------------------

bool DatabaseInterface::removeConnection()	{
	QString * pqstrConnName = &m_DBInterfaceParams.m_qstrConnectionName;
	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName, false);

	if (pDb->isValid() && pDb->isOpen())
		pDb->close();

	QSqlDatabase::removeDatabase(*pqstrConnName);

	return true;
}

//-----------------------------------------------------------------------------------------

DatabaseInterface::~DatabaseInterface()	{
	removeConnection();
}

//-----------------------------------------------------------------------------------------

bool DatabaseInterface::createTable(const string & astrTableName, vector<pair<string,string>> & avecTableElements)	{
	string strSQLFormat = "CREATE TABLE IF NOT EXISTS " + astrTableName + "(";

	std::vector<std::pair<std::string,std::string>>::iterator it = avecTableElements.begin();
	for (it; it != avecTableElements.end(); it++)	{
		strSQLFormat += (it->first + " " + it->second + ",");
	}
	strSQLFormat.pop_back(); strSQLFormat += ");";

	return execute(strSQLFormat);
}

//-----------------------------------------------------------------------------------------

bool DatabaseInterface::createTable(const string & astrTableName, const string & astrTableStmt)	{
	bool bRes = false;

	const string * pstrTableName = &astrTableName;

	if (pstrTableName->empty())	{
		BasicQtOperations::printError("Table name not given");
		return false;
	}
	
	if (!containsTable(pstrTableName->c_str()))	{
		const string * pSql = &astrTableStmt;

		return execute(*pSql);
	}
	
	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseInterface::removeTable(const QString& aqstrTableName)	{
	bool bRes = false;	
	const QString * pqstrTableName = &aqstrTableName;
	if (pqstrTableName->isEmpty())	{
		return bRes;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBInterfaceParams.m_qstrConnectionName);	
	QSqlQuery q(*pDb);
	
	QStringList qlstDBtables = pDb->tables();
	if (qlstDBtables.contains(*pqstrTableName, Qt::CaseInsensitive))	{
		q.exec( "DROP TABLE " + *pqstrTableName);
	} else {
		QString * pqstrError = &QSqlDatabase::database().lastError().text();
		VR::BasicQtOperations::printWarning("Unable to drop table " + *pqstrTableName + " - " + *pqstrError);

		return bRes;
	}

	bRes = containsTable(*pqstrTableName) ? false : true;

	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseInterface::containsTable(const QString & aqstrTableName)	{
	const QString * pqstrTableName = &aqstrTableName;

	if (pqstrTableName->isEmpty())	{
		return false;
	}

	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBInterfaceParams.m_qstrConnectionName);	
	QStringList qlstpDBtables = pDb->tables();

	bool bRes = (qlstpDBtables.contains(*pqstrTableName, Qt::CaseInsensitive)) ? true : false;
	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseInterface::execute(const string & astrQuery)	{
	QString * pqstrConnName = &m_DBInterfaceParams.m_qstrConnectionName;
	const string * pstrQuery = &astrQuery;

	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName);
	QSqlQuery query(*pDb);

	bool bRes = query.exec(pstrQuery->c_str());

	if (!bRes)	{
		BasicQtOperations::printError("Failed to execute SQL");
	}

	return bRes;
}

//-----------------------------------------------------------------------------------------

list<string> DatabaseInterface::executeAndGetResult(const string & astrQuery)	{
	QString * pqstrConnName = &m_DBInterfaceParams.m_qstrConnectionName;
	const string * pstrQuery = &astrQuery;

	QSqlDatabase * pDb = &QSqlDatabase::database(*pqstrConnName);

	QSqlQuery query(*pDb);

	bool bRes = query.exec(pstrQuery->c_str());

	if (!bRes)	{
		return list<string>();
	}
	
	int nI;
	list<string> lststrResult;
	string strResult;
	while(query.next())	{
		QSqlRecord record = query.record();
		int nSize = record.count();
		strResult = "";
		for (nI=0;nI<nSize;nI++)	{
			strResult += (record.field(nI).value().toString().toStdString() + ";");
		}
		//Delete last semi-colon & put it into the list
		strResult.pop_back();
		lststrResult.push_back(strResult);
	}
	return lststrResult;
}

//-----------------------------------------------------------------------------------------

int DatabaseInterface::insertRow(const string & astrTableName, string &astrTblFieldValues)	{
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBInterfaceParams.m_qstrConnectionName);

	QSqlTableModel model(0,*pDb);

	const string * pstrTableName = &astrTableName;
	vector<string> fieldValues = splitString(astrTblFieldValues,";");

	if (!containsTable(pstrTableName->c_str()))	{
		BasicQtOperations::printError("Requested table not part of the database: " + pDb->databaseName());
		return(-1);
	}


	model.setTable(pstrTableName->c_str());
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);

	QSqlRecord * pRec = &model.record();

	int nI=0;
	vector<string>::iterator it;
	for (it = fieldValues.begin(); it != fieldValues.end(); it++,nI++)	{
		nI = (pRec->field(nI).isAutoValue()) ? nI+1 : nI;
			pRec->setValue(nI,it->c_str());
	}

	int row = model.rowCount();

	bool bRes = model.insertRecord(row,*pRec);
	if (bRes)	{
		model.submitAll();
	} else {
		model.revertAll();
		BasicQtOperations::printError("Failed to insert the record.");
		return(-1);
	}

	int nLastInsertedID = model.query().lastInsertId().toInt();

	return nLastInsertedID;
}

//-----------------------------------------------------------------------------------------

void DatabaseInterface::deleteRow(const string & astrTableName, const string & astrObjectName)	{
	QSqlDatabase * pDb = &QSqlDatabase::database(m_DBInterfaceParams.m_qstrConnectionName);
	QSqlTableModel model(0, *pDb);

	const string * pstrTableName = &astrTableName;
	if (!containsTable(pstrTableName->c_str()))	{
		BasicQtOperations::printError("Requested table not part of the Database.");
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

//---------------------------------------------------------------------------

void DatabaseInterface::systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs)	{
}