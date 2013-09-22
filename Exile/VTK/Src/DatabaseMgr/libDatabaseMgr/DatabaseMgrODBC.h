#ifndef DATABASE_MGR_ODBC_H
#define DATABASE_MGR_ODBC_H

#include "DatabaseMgr.h"

class DatabaseMgrODBC : public DatabaseMgr {

public:
	virtual QString getDriverName() const;

	//Set DB type QODBC (default) or QSQLITE
	DatabaseMgrODBC(const QString & astrDBPathName);
	//~DatabaseMgrODBC();

	//Creates table within the database

	virtual void deleteItem(const QString &astrSceneObjectID);	//NOT YET FINISHED
	virtual void saveScene(const QString &astrOldSceneName, const QString &astrNewSceneName);
	virtual void loadScene(const QString &astrSceneName);
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
	virtual bool insertCategory(const QString &astrCategory, const QString &aqstrObjectType);
	virtual bool insertProduct(const QString &astrProduct, const QString &astrCategory);
	virtual bool insertProductCode(const QString &astrProduct, const QString &astrProductCodeNumber);
	virtual bool insertProductCodeImage(const QString &astrProductCodeNumber, const QString &astrProductCodeImage);

	virtual bool insertLocation(const QString &aqstrProductCodeNumber, const QString aqstrarrLocation[3]);
	virtual bool insertOrientation(const QString &aqstrProductCodeNumber, const QString aqstrarrOrientation[3]);
	virtual bool insertProperties(const QString &astrProductCodeNumber, unsigned int m_LocationID, unsigned int m_OrientationID);
	virtual bool insertObject(unsigned int m_ProductCodeID, unsigned int m_PropertiesID);
	virtual bool insertScene(const QString &astrSceneName="temp");
	virtual bool insertSceneObject(unsigned int m_SceneID, unsigned int m_ObjectID);
};
#endif //DATABASE_MGR_ODBC_H