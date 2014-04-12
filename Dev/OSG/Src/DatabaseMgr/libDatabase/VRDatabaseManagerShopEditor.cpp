#include <iostream>

#include "BasicStringDefinitions.h"

#include "VRDatabaseManagerShopEditor.h"

using namespace VR;
using namespace std;


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
	vector<pair<string,string>> vecStmts;
	systemOfTables(vecStmts);

	vector<pair<string,string>>::iterator it;
	for (it=vecStmts.begin(); it != vecStmts.end(); it++)	{
		createTable(it->first,it->second);
	}
}

//-------------------------------------------------------------------------------

DatabaseManagerShopEditor::~DatabaseManagerShopEditor()	{
}

//===============================================================================

void DatabaseManagerShopEditor::systemOfTables(vector<pair<string,string>> & avecStmtPairs)	{
	string strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Scene ( \
		SceneName TEXT);";
	avecStmtPairs.push_back(make_pair("Scene", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS SceneObject ( \
		ClassName TEXT, \
		SceneObjectName TEXT, \
		SceneObjectParams TEXT, \
		SceneName INTEGER);";
	avecStmtPairs.push_back(make_pair("SceneObject", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS SceneObjectPrimitive ( \
		ClassName TEXT, \
		SceneObjectPrimitiveName TEXT, \
		SceneObjectPrimitiveParams TEXT, \
		SceneObjectName TEXT);";
	avecStmtPairs.push_back(make_pair("SceneObjectPrimitive", strSQLFormat));
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::insertScene(const string & astrScene)	{
	string strValues = astrScene;
	insertRow("Scene",strValues);
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::insertObject(const string & astrScene, vector<string> & avecstrData)	{
/***********************************************
//	HIERARCHY (how you get data inside)
//		SCENE
//		  |--OBJECT1
//			|--PRIMITIVE1
//			|--PRIMITIVE2
//		  |--OBJECT2
//		  |--PRIMITIVE1
//
//		NOTES: 
//			SCENE	- scene is passed via an argument
//			OBJECTS - declared in the vector
*******************************************/

	int nPos;	//Position of the indent
	vector<string> * pvecstrData = &avecstrData;	//Data about the object and its children

	vector<pair<int,string>> vecpairParents;	//INT reflects the layer
	vecpairParents.push_back(make_pair(0,astrScene));

	vector<string>::iterator it;
	for(it = pvecstrData->begin(); it != pvecstrData->end(); it++)	{
		nPos = 0;

		//Find the position of the first character & clear empty spaces
		nPos = it->find_first_not_of(" ");
		it->erase(0,nPos);

		//Layer determines Parent/Child relations
		nPos = nPos/2;	//Divided with 2 because 2 is the layer indent
		if (nPos == 0)	{
			insertRow("SceneObject",*it);
		} else {
			insertRow("SceneObjectPrimitive",*it);
		}
	}
}
