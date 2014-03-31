#include <iostream>

#include <QMessageBox>
#include <qsqlresult.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QVariantList>
#include <QDir>

#include <QString>


#include "VRDatabaseManagerShopEditor.h"

//#include "DatabaseManagerShopEditorSystemTables.h"

using namespace VR;
using namespace std;

struct SystemOfTables	{
	SystemOfTables();

	vector<pair<string,string>> m_vecStmtPairs;
};

//-------------------------------------------------------------------------------

SystemOfTables::SystemOfTables()	{	
	string strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Scene ( \
		SceneID INTEGER PRIMARY KEY AUTOINCREMENT, \
		SceneName TEXT);";
	m_vecStmtPairs.push_back(make_pair("Scene", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS SceneObject ( \
		SceneObjectID INTEGER PRIMARY KEY AUTOINCREMENT, \
		ClassName TEXT, \
		SceneObjectName TEXT, \
		SceneObjectParams TEXT, \
		SceneID INTEGER, \
		FOREIGN KEY (SceneID) REFERENCES Scene(SceneID) );";
	m_vecStmtPairs.push_back(make_pair("SceneObject", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS SceneObjectPrimitive ( \
		SceneObjectPrimitiveID INTEGER PRIMARY KEY AUTOINCREMENT, \
		ClassName TEXT, \
		SceneObjectPrimitiveName TEXT, \
		SceneObjectPrimitiveParams TEXT, \
		SceneObjectID INTEGER, \
		FOREIGN KEY (SceneObjectID) REFERENCES SceneObject(SceneObjectID) );";
	m_vecStmtPairs.push_back(make_pair("SceneObjectPrimitive", strSQLFormat));

}

//==================================================================================

DatabaseManagerShopEditorParams::DatabaseManagerShopEditorParams() :
DatabaseManagerParams()	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopEditor::DatabaseManagerShopEditor(QObject * parent) :
DatabaseManager(parent)	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopEditor::DatabaseManagerShopEditor(const DatabaseManagerShopEditorParams & aDBMgrParams, QObject * parent):
DatabaseManager(aDBMgrParams,parent)	{

	SystemOfTables sysTables;
	vector<pair<string,string>> * psysTables = &sysTables.m_vecStmtPairs;

	vector<pair<string,string>>::iterator it;
	for (it=psysTables->begin(); it != psysTables->end(); it++)	{
		createTable(it->first,it->second);
	}
}

//-------------------------------------------------------------------------------

DatabaseManagerShopEditor::~DatabaseManagerShopEditor()	{
}

//===============================================================================

void DatabaseManagerShopEditor::insertObject(const string & astrScene, vector<string> & avecstrData)	{

	std::cout << astrScene << std::endl;
	vector<string>::iterator it;
	for (it = avecstrData.begin(); it != avecstrData.end(); it++)	{
		std::cout << *it << endl;
	}
}