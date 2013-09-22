#include "VRDatabaseMgrODBC.h"

using namespace VR;
using namespace std;

QString DatabaseMgrODBC::getDriverName() const {
	return(QString("ODBC"));
}

//-----------------------------------------------------------------------------------------

DatabaseMgrODBC::DatabaseMgrODBC(const QString & astrDBPathName) :
DatabaseMgr(astrDBPathName) {
	bool bOk = connect2SQLDatabase();
	if(bOk == false) {
		printError("Could not connect to ODBC database");
		exit(-1);
	}
}

//NOT YET FINISHED
void DatabaseMgrODBC::deleteItem(const QString &astrSceneObjectID) {
}

//NOT YET FINISHED
void DatabaseMgrODBC::saveScene(const QString &astrOldSceneName, const QString &astrNewSceneName) {
}

//NOT YET FINISHED
void DatabaseMgrODBC::loadScene(const QString &astrSceneName) {
}

//NOT YET FINISHED
void DatabaseMgrODBC::newScene() {
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrODBC::createTable()	{
	return(false);
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrODBC::fillPrimitiveTable(string & astrCommand)	{
}

//-----------------------------------------------------------------------------------------

string DatabaseMgrODBC::getSQLData(const int & anElement)	{
	return("");
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrODBC::insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams)	{
}

//-----------------------------------------------------------------------------------------

vector<float> DatabaseMgrODBC::selectFromDatabase(const int & anElementID)	{
	return std::vector<float>(0);
}
