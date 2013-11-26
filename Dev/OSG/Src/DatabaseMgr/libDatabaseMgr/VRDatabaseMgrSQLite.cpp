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

bool DatabaseMgrSQLite::createTable(const string & astrSQLCommand) {
	if (m_QSqlDatabase.open())	{
		string strSQLCommand = astrSQLCommand;
		vector <string> arrstrCommands = splitString(strSQLCommand,";");

		QSqlQuery query;
		for (auto it = arrstrCommands.begin(); it != arrstrCommands.end(); it++)	{
			query.exec(it->c_str());
		}
		m_QSqlDatabase.close();
		return true;
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
		return false;
	}
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrSQLite::fillPrimitiveTable(string & astrCommand)	{
	if(m_QSqlDatabase.open())	{

		//Command is string of SQL commands that are delimited with "_"
		vector <string> arrstrSQLCommands = splitString(astrCommand,"_");
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
			}
			else	{
				string strError = "Item not selected.";
				printError(strError.c_str());
				exit(-1);
			}
		}
	}	
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
}

//=============================================================================================

void DatabaseMgrSQLite::insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams)	{
	if(m_QSqlDatabase.open())	{
		QString qstrObjectType = aDatabaseMgrParams.m_qstrObjectType;
		QString qstrObjectName = aDatabaseMgrParams.m_qstrObjectName;

		int nSize = aDatabaseMgrParams.m_arrstrParams.size();
		vector <string> qarrstrParams;
		qarrstrParams.resize(nSize);
		qarrstrParams = aDatabaseMgrParams.m_arrstrParams;

		//get names of columns of a given table
		QString qstrColumnNames = QString("PRAGMA table_info(%1)").arg(qstrObjectType);
		QSqlQuery tblColsQry(qstrColumnNames);
		vector<QString> vecColumnNames;
		while (tblColsQry.next())	{
			vecColumnNames.push_back(tblColsQry.value(1).toString());
		}
		int nColumnNames = vecColumnNames.size();
		int nNoColumns = (nColumnNames < aDatabaseMgrParams.m_arrstrParams.size())
			? nColumnNames : aDatabaseMgrParams.m_arrstrParams.size();

		//Check if the entry is already in the DB
		QSqlQuery tempQuery;
		QString tqry = QString("SELECT %1 FROM %2 WHERE %3 = '%4'")
			.arg(vecColumnNames[0]).arg(qstrObjectType).arg(vecColumnNames[1]).arg(qstrObjectName);
		int nI;
		for (nI=0;nI<nNoColumns;nI++)	{
			tqry += QString(" AND %1 = '%2'").arg(vecColumnNames[nI+2]).arg(aDatabaseMgrParams.m_arrstrParams[nI].c_str());
		}
		tempQuery.exec(tqry);

		//Entry not yet in the DB, so proceed
		if(tempQuery.last() == '\0')	{

			//Check if the table depends on any foreign key and prepare the query
			QString qstrFKey;
			QString qstrFKeyValue;
			for (nI=1; nI<nColumnNames; nI++)	{
				string strFKey = vecColumnNames[nI].toStdString();
				if(isAtEndOfString(strFKey,"ID"))	{
					string strFKeyRef = strFKey.erase(strFKey.size()-2,2);
					qstrFKey += QString(", %1").arg(vecColumnNames[nI]);
					qstrFKeyValue += QString(",(SELECT %1 FROM %2 WHERE %3 = '%4')")
						.arg(vecColumnNames[nI]).arg(strFKeyRef.c_str()).arg((strFKeyRef+string("Name")).c_str()).arg(qstrObjectName);
				}
			}
			
			//Insert entry into the DB
			QString qry1 = QString("INSERT INTO %1(%2").arg(qstrObjectType).arg(vecColumnNames[1]);
			QString qry2 = QString(")VALUES ('%1'").arg(qstrObjectName);

			for (nI=0;nI<nNoColumns;nI++)	{
				qry1 += QString(", %1 ").arg(vecColumnNames[nI+2]);
				qry2 += QString(",%1 ").arg(aDatabaseMgrParams.m_arrstrParams[nI].c_str());
			}
			qry1 = qry1 + qstrFKey + qry2 + qstrFKeyValue + ")";
			QSqlQuery query(qry1);

			//CASCADING INTO THE 'PrimitiveItemList'
			QSqlQuery tempQuery;
			QString tqry1 = QString("SELECT %1ID, PrimitiveID FROM %1 WHERE %1ID = (SELECT MAX(%1ID) FROM %1)").arg(qstrObjectName);
			tempQuery.exec(tqry1);

			while(tempQuery.next())	{
			QString qstrPIL = QString("INSERT INTO PrimitiveItemList (PrimitiveID, ItemID) VALUES(%1, %2)")
				.arg(tempQuery.value(1).toString()).arg(tempQuery.value(0).toString());

			tempQuery.exec(qstrPIL);
			}
		}
		else	{
			string strMessage = "Warning message: Item already in the database.";
			printWarning(strMessage.c_str());
		}
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
}


//-----------------------------------------------------------------------------------------

string DatabaseMgrSQLite::readFromDB(string & astrCommand)	{
	if(m_QSqlDatabase.open())	{
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
					strTemp += sqlQuery.value(i).toString().toStdString() + "_";
				}
				strTemp += (arrstrPrimitiveName[nI] + "?").c_str();
				strResult += strTemp;
			}
		}
		return strResult;
	}

	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());

		exit(-1);
	}
}

//=============================================================================================