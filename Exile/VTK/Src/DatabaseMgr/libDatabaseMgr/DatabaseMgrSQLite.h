#ifndef DATABASE_MGR_SQLITE_H
#define DATABASE_MGR_SQLITE_H

#include <string>

#include "DatabaseMgr.h"
#include "Cupboard.h"

class DatabaseMgrSQLite : public DatabaseMgr {

public:
	virtual QString getDriverName() const;

	//Set DB type QODBC (default) or QSQLITE
	DatabaseMgrSQLite(const QString & aqstrDBPathName);
	//~DatabaseMgrSQLite();

	virtual void deleteItem(const QString &aqstrSceneObjectID);	//NOT YET FINISHED
	virtual void saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName);
	virtual void loadScene(const QString &aqstrSceneName);
	virtual void newScene();

	virtual bool createTable();

	virtual void insertPrimitive(const QString &aqstrPrimitiveName, 
								 int anPrimitiveParameterNumber, 
								 const std::vector < double > & aarrdbParams);
	
	virtual void insertTexture(const QString &aqstrTextureName, const QString &aqstrTexturePath);

	virtual void insertCupboard(const Cupboard & aCupboard);

protected:

	//functions
	virtual bool insertObjectType(const QString &aqstrObjectType);
	virtual bool insertCategory(const QString &aqstrCategory, const QString &aqstrObjectType);
	virtual bool insertProduct(const QString &aqstrProduct, const QString &aqstrCategory);
	virtual bool insertProductCode(const QString &aqstrProduct, const QString &aqstrProductCodeNumber);
	virtual bool insertProductCodeImage(const QString &aqstrProductCodeNumber, const QString &aqstrProductCodeImage);


	virtual bool insertLocation(const QString &aqstrProductCodeNumber, const QString aqstrarrLocation[3]);
	virtual bool insertOrientation(const QString &aqstrProductCodeNumber, const QString aqstrarrOrientation[3]);
	virtual bool insertProperties(const QString &aqstrProductCodeNumber, unsigned int m_LocationID, unsigned int m_OrientationID);
	virtual bool insertObject(unsigned int m_ProductCodeID, unsigned int m_PropertiesID);
	virtual bool insertScene(const QString &aqstrSceneName="temp");
	virtual bool insertSceneObject(unsigned int m_SceneID, unsigned int m_ObjectID);
};
#endif //DATABASE_MGR_SQLITE_H