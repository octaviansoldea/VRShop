#include "StringManipulation.h"

#include <iostream>
#include <string>

#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QSqlResult>
#include <QImageWriter>

#include "VRCylinder.h"
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

bool DatabaseMgrSQLite::createTable() {
	if (m_QSqlDatabase.open())	{

		QSqlQuery query;
		QString qry = "CREATE TABLE IF NOT EXISTS Primitive "
			"(PrimitiveID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveName TEXT UNIQUE)";
		query.exec(qry);

		Cylinder cylinder;
		string strSQLFormat = cylinder.getSQLFormat();
		qry = QString(strSQLFormat.c_str());
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Plate3D "
			"(Plate3DID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"Plate3DMatrix TEXT,"
			"Plate3DColor TEXT,"
			"Plate3DTexture TEXT,"
			"PrimitiveID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Prism "
			"(PrismID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrismSides INTEGER,"
			"PrismMatrix TEXT,"
			"PrismColor TEXT,"
			"PrismTexture TEXT, "
			"PrimitiveID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Sphere "
			"(SphereID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"SphereRes INTEGER,"
			"SphereRadius INTEGER,"
			"SphereColor TEXT,"
			"SphereTexture TEXT, "
			"PrimitiveID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS PrimitiveItemList "
			"(PrimitiveItemListID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveID INTEGER, "
			"ItemID INTEGER, "
			"EquipmentItemID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Texture "
			"(TextureID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"TextureFile TEXT)";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Equipment "
			"(EquipmentID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentName TEXT)";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS EquipmentItem "
			"(EquipmentItemID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentItemName TEXT, "
			"EquipmentID INTEGER,"
			"FOREIGN KEY (EquipmentID) REFERENCES Equipment(EquipmentID))";
		query.exec(qry);

		qry = "CREATE TABLE IF NOT EXISTS Scene "
			"(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"SceneName TEXT)";
		query.exec(qry);

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
		vector <string> arrstrSQLCommands = splitString(astrCommand,"_");
		QSqlQuery query(arrstrSQLCommands[0].c_str());

		int nEquipmentItemID = query.lastInsertId().toInt();

		//First query relates to the "Equipment"
		vector<string> vecstrEquipment = splitString(arrstrSQLCommands[0]," ");
		QString qstrEquipmentName = vecstrEquipment[5].c_str();


		int nI;
		for (nI=1; nI<arrstrSQLCommands.size(); nI++)	{
			QSqlQuery qry(arrstrSQLCommands[nI].c_str());

			//Number of the inserted item
			int nID = qry.lastInsertId().toInt();
			if (nID)	{
				//Number of Primitive
				int nPrimitive;
				vector<string> vecstrQuery = splitString(arrstrSQLCommands[nI]," ");
				string strPrimitive = vecstrQuery[2];

				QString qstrQuery = QString("SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = '%1'").arg(strPrimitive.c_str());
				QSqlQuery tqry(qstrQuery);

				while (tqry.next())	{
					nPrimitive = tqry.value(0).toInt();
				}

				//Everything is set, fill the PrimitiveItemList with proper data
				QString qstrPIL = QString("INSERT INTO PrimitiveItemList (PrimitiveID, ItemID, EquipmentItemID) "
					"VALUES(%1, %2, %3)")
					.arg(nPrimitive).arg(nID).arg(nEquipmentItemID);

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

//-----------------------------------------------------------------------------------------

string DatabaseMgrSQLite::getSQLData(const int & anElement)	{
	if(m_QSqlDatabase.open())	{

		QSqlQuery qSqlFindItem;
		QString qstrFindItem = QString("SELECT PrimitiveID, ItemID FROM PrimitiveItemList WHERE PrimitiveItemListID = %1")
			.arg(anElement);

		qSqlFindItem.exec(qstrFindItem);
		int PrimitiveID;
		int ItemID;

		while(qSqlFindItem.next())	{
			PrimitiveID = qSqlFindItem.value(0).toInt();
			ItemID = qSqlFindItem.value(1).toInt();
		}

		if(PrimitiveID)	{
			QSqlQuery qSqlFindPrimitive;
			QString qstrSqlFindPrimitive = QString("SELECT PrimitiveName FROM Primitive WHERE PrimitiveID = %1").arg(PrimitiveID);
			qSqlFindPrimitive.exec(qstrSqlFindPrimitive);
			QString qstrObjectName;
			while (qSqlFindPrimitive.next())	{
				qstrObjectName = qSqlFindPrimitive.value(0).toString();
			}

			QString qstrQuery = QString("SELECT * FROM %1 WHERE %1ID = %2").arg(qstrObjectName).arg(ItemID);
			QSqlQuery qry(qstrQuery);

			//get names of columns of a given table
			QString qstrColumnNames = QString("PRAGMA table_info(%1)").arg(qstrObjectName);
			QSqlQuery tblColsQry(qstrColumnNames);
			vector<QString> vecColumnNames;
			while (tblColsQry.next())	{
				vecColumnNames.push_back(tblColsQry.value(1).toString());
			}
			int nColumnNames = vecColumnNames.size();

			while (qry.next())	{
				string strGetSQLData;
				int nI;
				for(nI=1; nI<nColumnNames-1; nI++)	{
					strGetSQLData += qry.value(nI).toString().toStdString() + " ";
				}
				strGetSQLData += qry.value(nColumnNames).toString().toStdString();
				return (strGetSQLData);
			}
		}
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());

		exit(-1);
	}
	exit(-1);
}








//=============================================================================================

void DatabaseMgrSQLite::insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams)	{
	if(m_QSqlDatabase.open())	{
		QString qstrObjectType = aDatabaseMgrParams.m_qstrObjectType;
		QString qstrObjectName = aDatabaseMgrParams.m_qstrObjectName;

		//get names of columns of a given table
		QString qstrColumnNames = QString("PRAGMA table_info(%1)").arg(qstrObjectType);
		QSqlQuery tblColsQry(qstrColumnNames);
		vector<QString> vecColumnNames;
		while (tblColsQry.next())	{
			vecColumnNames.push_back(tblColsQry.value(1).toString());
		}
		int nColumnNames = vecColumnNames.size();
		int nNoColumns = (nColumnNames < aDatabaseMgrParams.m_arrflParams.size())
			? nColumnNames : aDatabaseMgrParams.m_arrflParams.size();

		//Check if the entry is already in the DB
		QSqlQuery tempQuery;
		QString tqry = QString("SELECT %1 FROM %2 WHERE %3 = '%4'")
			.arg(vecColumnNames.at(0)).arg(qstrObjectType).arg(vecColumnNames.at(1)).arg(qstrObjectName);
		int nI;
		for (nI=0;nI<nNoColumns;nI++)	{
			tqry += QString(" AND %1 = '%2'").arg(vecColumnNames.at(nI+2)).arg(aDatabaseMgrParams.m_arrflParams[nI]);
		}
		tempQuery.exec(tqry);

		//Entry not yet in the DB, so proceed
		if(tempQuery.last() == '\0')	{

			//Check if the table depends on any foreign key and prepare the query
			QString qstrFKey;
			QString qstrFKeyValue;
			for (nI=1; nI<nColumnNames; nI++)	{
				string strFKey = vecColumnNames.at(nI).toStdString();
				if(isAtEndOfString(strFKey,"ID"))	{
					string strFKeyRef = strFKey.erase(strFKey.size()-2,2);
					qstrFKey += QString(", %1").arg(vecColumnNames.at(nI));
					qstrFKeyValue += QString(",(SELECT %1 FROM %2 WHERE %3 = '%4')")
						.arg(vecColumnNames.at(nI)).arg(strFKeyRef.c_str()).arg((strFKeyRef+string("Name")).c_str()).arg(qstrObjectName);
				}
			}
			
			//Insert entry into the DB
			QString qry1 = QString("INSERT INTO %1(%2").arg(qstrObjectType).arg(vecColumnNames.at(1));
			QString qry2 = QString(")VALUES ('%1'").arg(qstrObjectName);

			for (nI=0;nI<nNoColumns;nI++)	{
				qry1 += QString(", %1 ").arg(vecColumnNames.at(nI+2));
				qry2 += QString(",%1 ").arg(aDatabaseMgrParams.m_arrflParams[nI]);
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

vector<float> DatabaseMgrSQLite::selectFromDatabase(//VR::VeryAbstractObject
													const int & anElementID)	{
	if(m_QSqlDatabase.open())	{

		QSqlQuery qSqlFindItem;
		QString qstrFindElement = QString("SELECT * FROM PrimitiveItemList WHERE PrimitiveItemListID = %1").arg(anElementID);
		qSqlFindItem.exec(qstrFindElement);
		int PrimitiveID;
		int ItemID;

		while(qSqlFindItem.next())	{
			PrimitiveID = qSqlFindItem.value(1).toInt();
			ItemID = qSqlFindItem.value(2).toInt();
		}

		if(PrimitiveID)	{
			QSqlQuery qSqlFindPrimitive;
			QString qstrSqlFindPrimitive = QString("SELECT PrimitiveName FROM Primitive WHERE PrimitiveID = %1").arg(PrimitiveID);
			qSqlFindPrimitive.exec(qstrSqlFindPrimitive);
			QString qstrObjectName;
			while (qSqlFindPrimitive.next())	{
				qstrObjectName = qSqlFindPrimitive.value(0).toString();
			}

			//get names of columns of a given table
			QString qstrColumnNames = QString("PRAGMA table_info(%1)").arg(qstrObjectName);
			QSqlQuery tblColsQry(qstrColumnNames);
			vector<QString> vecNoColumns;
			while (tblColsQry.next())	{
				vecNoColumns.push_back(tblColsQry.value(1).toString());
			}

			QString tqry = QString("SELECT * FROM %1 WHERE %1Name = '%1' AND %1ID = %2").arg(qstrObjectName).arg(ItemID);
			QSqlQuery tempQuery;
			tempQuery.exec(tqry);

			//Check if the table depends on any foreign key and prepare the query
			QString qstrFKey;
			QString qstrFKeyValue;
			int nI;
			int nParamsNumber = vecNoColumns.size() - 2;
			for (nI=1;nI<vecNoColumns.size();nI++)	{
				string strFKey = vecNoColumns.at(nI).toStdString();
				if(isAtEndOfString(strFKey,"ID"))	{
					nParamsNumber -= 1;
				}
			}

			while (tempQuery.last())	{
				vector<float> flvecParameters;
				int nI;
				for(nI=0;nI<nParamsNumber;nI++)	{
					flvecParameters.push_back(tempQuery.value(nI+2).toFloat());
				}
				return flvecParameters;
			}
		}

		else	{
			string strMessage = "Error opening: No such primitive in the database";
			printWarning(strMessage.c_str());

			exit(-1);
		}
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());

		exit(-1);
	}

	exit(-1);
}

//=========================================================================================








//-----------------------------------------------------------------------------------------

void DatabaseMgrSQLite::saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName) {
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		QString tqry = QString("SELECT SceneID FROM Scene WHERE SceneName = '%1'").arg(aqstrOldSceneName);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			string strMessage = "Scene " + aqstrOldSceneName.toStdString() + " not in the table";
			printWarning(strMessage.c_str());
		}
		else	{
			qry = QString("UPDATE Scene SET SceneName = '%1' WHERE SceneName = '%2'").arg(aqstrNewSceneName).arg(aqstrOldSceneName);
			QSqlQuery query(qry);
		}
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::loadScene(const QString &aqstrSceneName) {
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::newScene() {
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::deleteItem(const QString &aqstrSceneObjectID)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Product defined via the argument is in the table
		QString tqry = QString("SELECT SceneID, ObjectID FROM SceneObject WHERE SceneObjectID = '%1'").arg(aqstrSceneObjectID);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Product not found report this and exit
			qDebug() << QString("Item %1 not in the table.").arg(aqstrSceneObjectID);
		}
		else	{
			//We have picked something. Store SceneID and ObjectID
			int nSceneID = tempQuery.value(0).toInt();
			int nObjectID = tempQuery.value(1).toInt();

			qDebug() << QString("Scene ID = %1. Deleted item = %2.").arg(nSceneID).arg(nObjectID);
		}
	}
	else	{
		string strMessage = "Error opening: " + string(lastError().text().toStdString());
		printWarning(strMessage.c_str());
	}
}


//=============================================================================================