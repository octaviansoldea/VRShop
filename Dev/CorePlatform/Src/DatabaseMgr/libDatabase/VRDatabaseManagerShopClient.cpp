#include "BasicStringDefinitions.h"

#include "VRDatabaseManagerShopClient.h"

using namespace VR;
using namespace std;


//==================================================================================

DatabaseManagerShopClientParams::DatabaseManagerShopClientParams() :
DatabaseManagerParams()	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::DatabaseManagerShopClient(QObject * parent) :
DatabaseManager(parent)	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::DatabaseManagerShopClient(const DatabaseManagerShopClientParams & aDBMgrParams, QObject * parent):
DatabaseManager(aDBMgrParams,parent)	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::~DatabaseManagerShopClient()	{
}

//===============================================================================

void DatabaseManagerShopClient::loadScene(const std::string & astrScene)	{
	//list<string> lststrSceneObjects = getListOfObjects(astrScene);

	//ref_ptr<AbstractObject> pAO = 0;

	//list<string>::iterator it = lststrSceneObjects.begin();
	//for (it; it != lststrSceneObjects.end(); it++)	{
	//	//Find class and object names
	//	const int & nFindPos1 = it->find_first_of(";");
	//	const int & nFindPos2 = it->find_first_of(";", nFindPos1+1);
	//	string & strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

	//	pAO = AbstractObject::createInstance(strClassName);
	//	vector<string> & vecstrObjectData = dbMgr.getObjectData(*it);

	//	pAO->initFromSQLData(vecstrObjectData);

	//	m_pScene->addChild(pAO);
	//}

}

//-------------------------------------------------------------------------------

list<string> DatabaseManagerShopClient::getListOfObjects(const string & astrScene)	{
	//Get IDs of elements of the scene
	string & strSqlQuery = 
		"SELECT SceneObjectID, ClassName, SceneObjectName FROM SceneObject WHERE SceneName = '" + astrScene + "'";
	list<string> & lststrElements = executeAndGetResult(strSqlQuery);

	return lststrElements;
}

//-------------------------------------------------------------------------------

vector<string> DatabaseManagerShopClient::getObjectData(string & strSceneObject)	{
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
