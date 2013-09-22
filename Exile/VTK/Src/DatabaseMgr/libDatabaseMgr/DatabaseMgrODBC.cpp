#include <iostream>

#include <QDebug>
#include <QFile>
#include <QSettings>
#include <qsqlresult.h>

#include "DatabaseMgrODBC.h"

#include "Cupboard.h"

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


void DatabaseMgrODBC::insertPrimitive(
	const QString &aqstrPrimitiveName, 
	int anPrimitiveParameterNumber, 
	const std::vector < double > & aarrdbParams) {
	
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrODBC::insertTexture(const QString &aqstrTextureName, const QString &aqstrTexturePath) {
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrODBC::insertCupboard(const Cupboard & aCupboard) {
}

//=========================================================================================

bool DatabaseMgrODBC::insertObjectType(const QString &astrObjectType) {
	return(false);
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertCategory(const QString &astrCategory, const QString &aqstrObjectType) {
	return(false);
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertProduct(const QString &astrProduct, const QString &astrCategory)	{
	return(false);
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertProductCode(const QString &astrProduct, const QString &astrProductCodeNumber) {
	return(false);
}

//---------------------------------------------------------------------------------------------
bool DatabaseMgrODBC::insertProductCodeImage(const QString &astrProductCodeNumber, const QString &astrProductCodeImage) {
	return(false);
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertLocation(const QString &aqstrProductCodeNumber, const QString aqstrarrLocation[3])	{
	return false;
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertOrientation(const QString &aqstrProductCodeNumber, const QString aqstrarrOrientation[3])	{
	return false;
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertProperties(const QString &astrProductCodeNumber, unsigned int m_LocationID, unsigned int m_OrientationID) {
	return(false);
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertObject(unsigned int m_ProductCodeID, unsigned int m_PropertiesID)	{
	return(false);
}

//-------------------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertScene(const QString &astrSceneName) {
	return(false);
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrODBC::insertSceneObject(unsigned int m_SceneID, unsigned int m_ObjectID)	{
	return(false);
}

//=================================================================================================
