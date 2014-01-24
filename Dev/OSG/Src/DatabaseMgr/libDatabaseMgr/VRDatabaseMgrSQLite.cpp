#include "StringManipulation.h"

#include <iostream>
#include <string>

#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QSqlResult>

#include <QImageWriter>

#include "VRDatabaseMgrSQLite.h"


using namespace VR;
using namespace std;


QString DatabaseMgrSQLite::getDriverName() const {
	return(QString("QSQLITE"));
}

//-----------------------------------------------------------------------------------------

DatabaseMgrSQLite::DatabaseMgrSQLite(const QString & aqstrDBPathName) :
DatabaseMgr(aqstrDBPathName) {
	bool bOk = connect2SQLDatabase();
	if(bOk == false) {
		printError("Could not connect to SQLite database");
		exit(-1);
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::createTable(const DatabaseMgrParams & aDatabaseMgrParams)	{
	const DatabaseMgrParams & mgrParams = aDatabaseMgrParams;

	int nSize = mgrParams.m_arrstrParams.size();

	string strSQLCommand = "CREATE TABLE IF NOT EXISTS " + mgrParams.m_strTableName + "(";
	for (auto it = mgrParams.m_arrstrParams.begin(); it != mgrParams.m_arrstrParams.end()-1; it++)	{
		strSQLCommand += (*it + ",");
	}
	strSQLCommand += (mgrParams.m_arrstrParams[nSize-1] + ");");

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	bool bRes = executeQuery(dMgrParams);
	return bRes;
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::executeQuery(const DatabaseMgrParams & aDatabaseMgrParams) {
	bool bRes = m_pQSqlDatabase->isOpen() ? true : m_pQSqlDatabase->open();

	if (bRes)	{
		const vector <string> arrstrCommands = aDatabaseMgrParams.m_arrstrParams;

		vector<string>::const_iterator it;
		for (it = arrstrCommands.begin(); it != arrstrCommands.end(); it++)	{
			QSqlQuery query(it->c_str());
			query.finish();
		}
	} else {
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
	disconnectFromSQLDatabase();
	return bRes;
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrSQLite::fillPrimitiveTable(string & astrCommand)	{
	bool bRes = m_pQSqlDatabase->isOpen() ? true : m_pQSqlDatabase->open();

	if (bRes)	{
		//Command is string of SQL commands that are delimited with ";"
		vector <string> arrstrSQLCommands = splitString(astrCommand,";");
		QSqlQuery query(arrstrSQLCommands[0].c_str());

		int nEquipmentItemID = query.lastInsertId().toInt();

		//First query relates to the "Equipment"
		vector<string> vecstrEquipment = splitString(arrstrSQLCommands[0]," ");
		QString qstrEquipmentName = vecstrEquipment[5].c_str();

		for (auto it = arrstrSQLCommands.begin()+1; it != arrstrSQLCommands.end(); it++)	{
			QSqlQuery qry(it->c_str());

			//Number of the inserted item
			int nID = qry.lastInsertId().toInt();
			if (nID)	{
				vector<string> vecstrQuery = splitString(*it," ");
				string strPrimitive = vecstrQuery[2];

				//Everything is set, fill the PrimitiveItemList with proper data
				QString qstrPIL = QString("INSERT INTO PrimitiveItemList (PrimitiveID, ItemID, EquipmentItemID) "
					"VALUES((SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = '%1'), %2, %3)")
					.arg(strPrimitive.c_str()).arg(nID).arg(nEquipmentItemID);

				QSqlQuery tempQuery;
				tempQuery.exec(qstrPIL);
			} else {
				string strError = "Item not selected.";
				printError(strError.c_str());

				disconnectFromSQLDatabase();
				return;
			}
		}
	} else {
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
	disconnectFromSQLDatabase();
}

//=============================================================================================

string DatabaseMgrSQLite::readFromDB(string & astrCommand)	{
	bool bRes = m_pQSqlDatabase->isOpen() ? true : m_pQSqlDatabase->open();

	if (bRes)	{
		QSqlQuery sqlQuery;
		sqlQuery.exec(astrCommand.c_str());
		vector <string> arrstrEquipmentItem;
		while (sqlQuery.next())	{
			arrstrEquipmentItem.push_back(sqlQuery.value(0).toString().toStdString());
			arrstrEquipmentItem.push_back(sqlQuery.value(1).toString().toStdString());
			arrstrEquipmentItem.push_back(sqlQuery.value(2).toString().toStdString());
		}

		QString strQueryPIL = QString("SELECT Primitive.PrimitiveName, PrimitiveItemList.ItemID FROM Primitive, PrimitiveItemList "
			"WHERE PrimitiveItemList.PrimitiveID = Primitive.PrimitiveID AND PrimitiveItemList.EquipmentItemID = %1")
			.arg(arrstrEquipmentItem[0].c_str());
		sqlQuery.exec(strQueryPIL);

		vector < string> arrstrPrimitiveName;
		vector <int> arrnItemID;
		while(sqlQuery.next())	{
			arrstrPrimitiveName.push_back(sqlQuery.value(0).toString().toStdString());
			arrnItemID.push_back(sqlQuery.value(1).toInt());
		}

		//get names of columns of the given table
		vector <int> nColumns;
		for (auto it = arrstrPrimitiveName.begin(); it != arrstrPrimitiveName.end(); it++)	{
			QString qstrColumnNames = QString("PRAGMA table_info(%1)").arg(it->c_str());
			QSqlQuery tblColsQry(qstrColumnNames);
			vector<QString> vecColumnNames;
			while (tblColsQry.next())	{
				vecColumnNames.push_back(tblColsQry.value(1).toString());
			}
			nColumns.push_back(vecColumnNames.size());
		}

		string strResult;
		QString strQueryData;
		int nI;
		for (auto it = arrnItemID.begin(); it != arrnItemID.end(); it++)	{
			nI = it - arrnItemID.begin();
			strQueryData = QString("SELECT * FROM %1 WHERE %1ID = %2")
				.arg(arrstrPrimitiveName[nI].c_str()).arg(*it);

			sqlQuery.exec(strQueryData);
			while(sqlQuery.next())	{
				string strTemp;
				for (int i=0;i<nColumns[nI]-1;i++)	{
					strTemp += sqlQuery.value(i).toString().toStdString() + ";";
				}
				strTemp += (arrstrPrimitiveName[nI] + "?").c_str();
				strResult += strTemp;
			}
		}
		disconnectFromSQLDatabase();

		return strResult;
	} else {
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());

		exit(-1);
	}
}

//=============================================================================================