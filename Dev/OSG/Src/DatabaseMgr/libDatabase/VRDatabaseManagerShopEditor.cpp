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
	init(aDBMgrParams);
}

//-------------------------------------------------------------------------------

DatabaseManagerShopEditor::~DatabaseManagerShopEditor()	{
}

//===============================================================================

void DatabaseManagerShopEditor::init(const DatabaseManagerShopEditorParams & aDBMgrParams)	{
	m_DBMgrParams = aDBMgrParams;

	vector<pair<string,string>> vecStmts;
	systemOfTables(vecStmts);

	vector<pair<string,string>>::iterator it;
	for (it=vecStmts.begin(); it != vecStmts.end(); it++)	{
		createTable(it->first,it->second);
	}
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::systemOfTables(vector<pair<string,string>> & avecStmtPairs)	{	
	if (m_DBMgrParams.m_qstrDBName.endsWith("Products.db"))	{
		string strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Product ( \
			ProductID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ProductCategory TEXT, \
			ProductName TEXT, \
			ProductCode INTEGER UNIQUE, \
			ProductShortDescription TEXT, \
			ProductDescription TEXT, \
			ProductManufacturerName TEXT, \
			ProductManufacturerOrigin TEXT, \
			ProductUnit TEXT, \
			ProductUnitMeasure TEXT, \
			ProductQuantity REAL, \
			ProductPricePerUnit REAL, \
			ProductTaxRate REAL, \
			ProductCurrency TEXT, \
			ProductDateAdded TEXT, \
			ProductDateLastModified TEXT, \
			ProductTextureFile TEXT);";
		avecStmtPairs.push_back(make_pair("Product", strSQLFormat));

	} else {
		string strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Scene ( \
			SceneID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			SceneName TEXT);";
		avecStmtPairs.push_back(make_pair("Scene", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS SceneObject ( \
			SceneObjectID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			SceneObjectName TEXT, \
			SceneName TEXT);";
		avecStmtPairs.push_back(make_pair("SceneObject", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS SceneObjectDrawable ( \
			SceneObjectDrawableID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			SceneObjectID INTEGER, \
			DrawableClassName TEXT, \
			DrawableName TEXT);";
		avecStmtPairs.push_back(make_pair("SceneObjectDrawable", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Cupboard ( \
			CupboardID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			CupboardParams TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("Cupboard", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Container ( \
			ContainerID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			ContainerParams TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("Container", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS CustomFurniture ( \
			CustomFurnitureID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			CustomFurnitureParams TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("CustomFurniture", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS ProductDisplay ( \
			ProductDisplayID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			ProductDisplayParams TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("ProductDisplay", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Plate3D ( \
			Plate3DID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			Plate3DParams TEXT, \
			Plate3DColor TEXT, \
			Plate3DTexture TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("Plate3D", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Cylinder ( \
			CylinderID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			CylinderParams TEXT, \
			CylinderColor TEXT, \
			CylinderTexture TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("Cylinder", strSQLFormat));

		strSQLFormat =
			"CREATE TABLE IF NOT EXISTS Prism ( \
			PrismID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
			ClassName TEXT, \
			ObjectName TEXT, \
			PrismParams TEXT, \
			PrismColor TEXT, \
			PrismTexture TEXT, \
			SceneObjectNameObject TEXT);";
		avecStmtPairs.push_back(make_pair("Prism", strSQLFormat));
	}
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::insertScene(const string & astrScene)	{
	string strValues = astrScene;
	insertRow("Scene",strValues);
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::insertObject(const string & astrScene, vector<string> & avecstrData)	{
//**********************************************
//	HIERARCHY (how you get data inside)
//		SCENE				Layer: 0
//		  |--OBJECT1		Layer: 1
//			|--PRIMITIVE1	Layer: 2
//			|--PRIMITIVE2	Layer: 2
//		  |--OBJECT2		Layer: 1
//		  |--PRIMITIVE1		Layer: 1
//
//		NOTES: 
//			SCENE	- scene is passed via an argument
//			OBJECTS - declared in the vector
//*******************************************/

	int nPos, nLastID;	//Position of the indent
	vector<string> * pvecstrData = &avecstrData;	//Data about the object and its children

	vector<string>::iterator it;
	for(it = pvecstrData->begin(); it != pvecstrData->end(); it++)	{
		nPos = 0;

		//Find the position of the first character & clear empty spaces
		nPos = it->find_first_not_of(" ");
		it->erase(0,nPos);

		//Find class and object names
		const int nFindPos1 = it->find_first_of(";");
		string strClassName = it->substr(0,nFindPos1);
		const int nFindPos2 = it->find_first_of(";", nFindPos1+1);
		string strObjectName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		//Layer determines Parent/Child relations
		nPos = nPos/2;	//Divided with 2 because 2 is the layer indent

		if (nPos == 1)	{
			//Returns lastInsertedID
			nLastID = insertRow("SceneObject",strClassName + ";" + strObjectName + ";" + astrScene);
			insertRow(strClassName,*it);
		} else if (nPos == 2) {
			insertRow(strClassName,*it);
			insertRow("SceneObjectDrawable",tostr(nLastID)+";"+strClassName + ";" + strObjectName);
		}
	}
}

//-------------------------------------------------------------------------------

void DatabaseManagerShopEditor::insertProduct(std::vector<std::string> & avecstrData)	{
//**********************************************
//	HIERARCHY (how you get data inside)
//		|--	PRODUCT1				Layer: 0
//		|--	PRODUCT2				Layer: 0
//**********************************************/

	vector<string>::iterator it;
	for(it = avecstrData.begin(); it != avecstrData.end(); it++)	{
		insertRow("Product",*it);
	}
}

//-------------------------------------------------------------------------------

list<string> DatabaseManagerShopEditor::getListOfObjects(const string & astrScene)	{
	//Get IDs of elements of the scene
	string strSqlQuery = 
		"SELECT SceneObjectID, ClassName, SceneObjectName FROM SceneObject WHERE SceneName = '" + astrScene + "'";
	list<string> lststrElements = executeAndGetResult(strSqlQuery);

	return lststrElements;
}

//-------------------------------------------------------------------------------

vector<string> DatabaseManagerShopEditor::getObjectData(string & strSceneObject)	{
	vector<string> vecstrResult;
	vector<string> vecstrSceneObject = splitString(strSceneObject,";");
		
	const int nObjectID = stoi(vecstrSceneObject[0]);
	string strClassName = vecstrSceneObject[1];
	string strObjectName = vecstrSceneObject[2];

	//Get data of the parent and add it to the result vector
	string strSqlQuery = 
		"SELECT * FROM " + strClassName + " WHERE ObjectName = '" + strObjectName + "'";
	list<string> lststrElements = executeAndGetResult(strSqlQuery);
	vecstrResult.push_back(lststrElements.front());

	//Get types of the parent's children
	strSqlQuery = 
		"SELECT DrawableClassName, DrawableName FROM SceneObjectDrawable WHERE SceneObjectID = '" + vecstrSceneObject[0] + "'";
	list<string> lststrSceneObjectElements = executeAndGetResult(strSqlQuery);


	//Get data of the parent's children
	list<string>::iterator itt = lststrSceneObjectElements.begin();
	for (itt; itt != lststrSceneObjectElements.end(); itt++)	{
		vector<string> vecstrDrawable = splitString(*itt,";");

		strSqlQuery = 
			"SELECT * FROM " + vecstrDrawable[0] + " WHERE ObjectName = '" + vecstrDrawable[1] + "'";
		list<string> lststrSceneObjectElements = executeAndGetResult(strSqlQuery);
		vecstrResult.push_back("  " + lststrSceneObjectElements.front());
	}

	return vecstrResult;
}

//-------------------------------------------------------------------------------
